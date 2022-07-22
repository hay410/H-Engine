#include "MultiPathShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0番スロットに設定されてテクスチャ
SamplerState smp : register(s0); //0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    //return float4(1, 1, 1, 1);
    float4 texcolor = tex.Sample(smp, input.uv.tex0.xy) * color;
    
    if (texcolor.a <= 0.0)
        discard;
    
    //ピクセルカラーをモノクロ化する
    float mono = 0.299f * texcolor.r + 0.587f * texcolor.g + 0.114f * texcolor.b;
    texcolor.r = mono;
    texcolor.g = mono;
    texcolor.b = mono;
    
    return texcolor;
}