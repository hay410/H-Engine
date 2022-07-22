#include "MultiPathShaderHeader.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳��ăe�N�X�`��

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
    VSOutput output;
    output.svpos = mul(mul(viewproj, world), pos); //���W�ɍs�����Z

    float4 inormal = float4(normal, 0);
    //output.normal = inormal;
    output.normal = normalize(mul(world, inormal).rgb); //�@���ɂ����[���h�ϊ����s��

    //�e�N�X�`���̃T�C�Y���擾
    float2 texSize = 0;
    float level = 0;
    tex.GetDimensions(0, texSize.x, texSize.y, level);

    //��e�N�Z����uv���W���v�Z
    float2 standardTex = uv;

    //��e�N�Z������V���W��+1�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex0.xy = float2(0.0f, 1.0f / texSize.y);

    //��e�N�Z������V���W��+3�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex1.xy = float2(0.0f, 5.0f / texSize.y);

    //��e�N�Z������V���W��+5�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex2.xy = float2(0.0f, 9.0f / texSize.y);

    //��e�N�Z������V���W��+7�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex3.xy = float2(0.0f, 13.0f / texSize.y);

    //��e�N�Z������V���W��+9�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex4.xy = float2(0.0f, 17.0f / texSize.y);

    //��e�N�Z������V���W��+11�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex5.xy = float2(0.0f, 21.0f / texSize.y);

    //��e�N�Z������V���W��+13�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex6.xy = float2(0.0f, 25.0f / texSize.y);

    //��e�N�Z������V���W��+15�e�N�Z�����炷���߂̃I�t�Z�b�g���v�Z����
    output.uv.tex7.xy = float2(0.0f, 29.0f / texSize.y);

    //�I�t�Z�b�g��-1���|���ă}�C�i�X�����̃I�t�Z�b�g���v�Z����
    output.uv.tex0.zw = output.uv.tex0.xy * -1.0f;
    output.uv.tex1.zw = output.uv.tex1.xy * -1.0f;
    output.uv.tex2.zw = output.uv.tex2.xy * -1.0f;
    output.uv.tex3.zw = output.uv.tex3.xy * -1.0f;
    output.uv.tex4.zw = output.uv.tex4.xy * -1.0f;
    output.uv.tex5.zw = output.uv.tex5.xy * -1.0f;
    output.uv.tex6.zw = output.uv.tex6.xy * -1.0f;
    output.uv.tex7.zw = output.uv.tex7.xy * -1.0f;

    //�I�t�Z�b�g�Ɋ�e�N�Z����uv���W�𑫂��āA���ۂɃT���v�����O����uv���W�ɕϊ�����
    output.uv.tex0 += float4(standardTex, standardTex);
    output.uv.tex1 += float4(standardTex, standardTex);
    output.uv.tex2 += float4(standardTex, standardTex);
    output.uv.tex3 += float4(standardTex, standardTex);
    output.uv.tex4 += float4(standardTex, standardTex);
    output.uv.tex5 += float4(standardTex, standardTex);
    output.uv.tex6 += float4(standardTex, standardTex);
    output.uv.tex7 += float4(standardTex, standardTex);

    return output;
}