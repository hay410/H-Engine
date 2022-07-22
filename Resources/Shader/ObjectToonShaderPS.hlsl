#include "ObjectToonShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> palette : register(t1); //1�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    //return float4(1,1,1,1);

    float4 shadeColor = float4(0, 0, 0, 1); //�ŏI�I�ɕ`�悷��e�̐F

    //���s����
    for (int i = 0; i < DIRECTIONLIGHT_NUM; ++i)
    {
        if (dirLights[i].active == 1)
        {
            //�����ˌ��̌v�Z
            float3 ambient = mAmbient;
            //�g�U���ˌ��̌v�Z
            float3 diffuse = dot(-dirLights[i].lightv, input.normal) * mDiffuse;
            //����x
            const float shininess = 4.0f;
            //���_���王�_�ւ̕����x�N�g��
            float3 eyedir = normalize(eye - input.worldpos.xyz);
            //���ˌ��x�N�g��
            float3 reflect = normalize(dirLights[i].lightv + 2 * dot(-dirLights[i].lightv, input.normal) * input.normal);
            //���ʔ��ˌ�
            float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * mSpecular;
            //���ׂĉ��Z�����F
            float3 color = (ambient + diffuse + specular) * dirLights[i].lightcolor;
            float3 outputColor = color;
            shadeColor.rgb += outputColor;
        }
    }
    //�_����
    for (int i = 0; i < POINTLIGHT_NUM; ++i)
    {
        if (pointLights[i].active == 1)
        {
            //���C�g�̃x�N�g��
            float3 lightv = pointLights[i].lightpos - input.worldpos.xyz;
            //�x�N�g���̒���
            float d = length(lightv);
            //���K�����ĒP�ʃx�N�g���ɂ���
            lightv = normalize(lightv);
            //���������W��
            float atten = 1.0f / (pointLights[i].lightatten.x +
                pointLights[i].lightatten.y * d +
                pointLights[i].lightatten.z * (d * d));
            atten *= 1000;
            //���C�g�Ɍ������x�N�g���Ɩ@���̓���
            float3 dotlightnormal = dot(lightv, input.normal);
            //���ˌ��x�N�g��
            float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
            //�g�U���ˌ�
            float3 diffuse = dotlightnormal * mDiffuse;
            //����x
            const float shininess = 4.0f;
            //���_���王�_�ւ̕����x�N�g��
            float3 eyedir = normalize(eye - input.worldpos.xyz);
            //���ʔ��ˌ�
            float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * mSpecular;
            //���ׂĉ��Z�����F
            float3 outputColor = saturate(atten * (diffuse + specular) * pointLights[i].lightcolor);
            shadeColor.rgb += outputColor;
        }
    }

    //�e�̐F��RGB�̕��ς����߂�
    float shadeColorU = (shadeColor.r + shadeColor.g + shadeColor.b) / 3.0f;

    //�ŏI�I�ȃ��C�e�B���O�̐F����u�̒l�����߂�
    float4 paletteColor = palette.Sample(smp, float2(shadeColorU, 0.5f));

    //�e�N�X�`���̐F
    float4 texcolor = tex.Sample(smp, input.uv);
    return (paletteColor * texcolor) * color;

}