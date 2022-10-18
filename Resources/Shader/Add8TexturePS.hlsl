#include "SpriteShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> tex2 : register(t1); //1�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> tex3 : register(t2); //2�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> tex4 : register(t3); //3�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> tex5 : register(t4); //4�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> tex6 : register(t5); //5�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> tex7 : register(t6); //6�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
Texture2D<float4> tex8 : register(t7); //7�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    //return float4(1, 1, 1, 1);

    float4 combineColor = tex.Sample(smp, input.uv);
    combineColor += tex2.Sample(smp, input.uv);
    combineColor += tex3.Sample(smp, input.uv);
    combineColor += tex4.Sample(smp, input.uv);
    combineColor += tex5.Sample(smp, input.uv);
    combineColor += tex6.Sample(smp, input.uv);
    combineColor += tex7.Sample(smp, input.uv);
    combineColor += tex8.Sample(smp, input.uv);
    combineColor.x /= 8.0f;
    combineColor.y /= 8.0f;
    combineColor.z /= 8.0f;
    //combineColor.a = 1.0f;

    saturate(combineColor);

    //if (combineColor.a <= 0.0)
    //    discard;

    return combineColor;
}