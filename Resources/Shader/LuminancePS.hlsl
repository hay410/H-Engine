#include "SpriteShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv) * color;

    //if (texcolor.a <= 0.0)
    //    discard;

    //return float4(1, 1, 1, 1);

    //�T���v�����O�����J���[�̖��邳���v�Z
    float t = dot(texcolor.xyz, float3(0.2125f, 0.7154f, 0.0721f));

    //�s�N�Z���̃J���[��1�ȉ��Ȃ�s�N�Z���L������
    clip(t - 0.99f);

    return texcolor;
}