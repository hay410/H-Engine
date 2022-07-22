#include "ObjectToonShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0番スロットに設定されてテクスチャ
Texture2D<float4> palette : register(t1); //1番スロットに設定されてテクスチャ
SamplerState smp : register(s0); //0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    //return float4(1,1,1,1);

    float4 shadeColor = float4(0, 0, 0, 1); //最終的に描画する影の色

    //平行光源
    for (int i = 0; i < DIRECTIONLIGHT_NUM; ++i)
    {
        if (dirLights[i].active == 1)
        {
            //環境反射光の計算
            float3 ambient = mAmbient;
            //拡散反射光の計算
            float3 diffuse = dot(-dirLights[i].lightv, input.normal) * mDiffuse;
            //光沢度
            const float shininess = 4.0f;
            //頂点から視点への方向ベクトル
            float3 eyedir = normalize(eye - input.worldpos.xyz);
            //反射光ベクトル
            float3 reflect = normalize(dirLights[i].lightv + 2 * dot(-dirLights[i].lightv, input.normal) * input.normal);
            //鏡面反射光
            float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * mSpecular;
            //すべて加算した色
            float3 color = (ambient + diffuse + specular) * dirLights[i].lightcolor;
            float3 outputColor = color;
            shadeColor.rgb += outputColor;
        }
    }
    //点光源
    for (int i = 0; i < POINTLIGHT_NUM; ++i)
    {
        if (pointLights[i].active == 1)
        {
            //ライトのベクトル
            float3 lightv = pointLights[i].lightpos - input.worldpos.xyz;
            //ベクトルの長さ
            float d = length(lightv);
            //正規化して単位ベクトルにする
            lightv = normalize(lightv);
            //距離減衰係数
            float atten = 1.0f / (pointLights[i].lightatten.x +
                pointLights[i].lightatten.y * d +
                pointLights[i].lightatten.z * (d * d));
            atten *= 1000;
            //ライトに向かうベクトルと法線の内積
            float3 dotlightnormal = dot(lightv, input.normal);
            //反射光ベクトル
            float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
            //拡散反射光
            float3 diffuse = dotlightnormal * mDiffuse;
            //光沢度
            const float shininess = 4.0f;
            //頂点から視点への方向ベクトル
            float3 eyedir = normalize(eye - input.worldpos.xyz);
            //鏡面反射光
            float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * mSpecular;
            //すべて加算した色
            float3 outputColor = saturate(atten * (diffuse + specular) * pointLights[i].lightcolor);
            shadeColor.rgb += outputColor;
        }
    }

    //影の色のRGBの平均を求める
    float shadeColorU = (shadeColor.r + shadeColor.g + shadeColor.b) / 3.0f;

    //最終的なライティングの色からuの値を求める
    float4 paletteColor = palette.Sample(smp, float2(shadeColorU, 0.5f));

    //テクスチャの色
    float4 texcolor = tex.Sample(smp, input.uv);
    return (paletteColor * texcolor) * color;

}