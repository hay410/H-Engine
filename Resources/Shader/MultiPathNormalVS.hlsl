#include "MultiPathShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳��ăe�N�X�`��

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
    VSOutput output;
    output.svpos = mul(mul(viewproj, world), pos); //���W�ɍs�����Z

    float4 inormal = float4(normal, 0);
    //output.normal = inormal;
    output.normal = normalize(mul(world, inormal).rgb); //�@���ɂ����[���h�ϊ����s��

    //��e�N�Z����uv���W���v�Z
    output.uv.tex0.xy = uv;

    return output;
}