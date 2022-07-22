#include "MultiPathShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳��ăe�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    //return float4(1, 1, 1, 1);
    float4 texcolor;

    //��e�N�Z������v���X������8�e�N�Z���A�d�ݕt���ŃT���v�����O
    texcolor = gaussianWeight[0].x * tex.Sample(smp, input.uv.tex0.xy);
    texcolor += gaussianWeight[0].y * tex.Sample(smp, input.uv.tex1.xy);
    texcolor += gaussianWeight[0].z * tex.Sample(smp, input.uv.tex2.xy);
    texcolor += gaussianWeight[0].w * tex.Sample(smp, input.uv.tex3.xy);
    texcolor += gaussianWeight[1].x * tex.Sample(smp, input.uv.tex4.xy);
    texcolor += gaussianWeight[1].y * tex.Sample(smp, input.uv.tex5.xy);
    texcolor += gaussianWeight[1].z * tex.Sample(smp, input.uv.tex6.xy);
    texcolor += gaussianWeight[1].w * tex.Sample(smp, input.uv.tex7.xy);

    //��e�N�Z���Ƀ}�C�i�X������8�e�N�Z���A�d�ݕt���ŃT���v�����O
    texcolor += gaussianWeight[0].x * tex.Sample(smp, input.uv.tex0.zw);
    texcolor += gaussianWeight[0].y * tex.Sample(smp, input.uv.tex1.zw);
    texcolor += gaussianWeight[0].z * tex.Sample(smp, input.uv.tex2.zw);
    texcolor += gaussianWeight[0].w * tex.Sample(smp, input.uv.tex3.zw);
    texcolor += gaussianWeight[1].x * tex.Sample(smp, input.uv.tex4.zw);
    texcolor += gaussianWeight[1].y * tex.Sample(smp, input.uv.tex5.zw);
    texcolor += gaussianWeight[1].z * tex.Sample(smp, input.uv.tex6.zw);
    texcolor += gaussianWeight[1].w * tex.Sample(smp, input.uv.tex7.zw);

    //if (texcolor.a <= 0.0)
    //    discard;

return float4(texcolor.xyz, 1.0f);
}