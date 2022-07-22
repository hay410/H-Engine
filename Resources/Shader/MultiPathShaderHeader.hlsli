struct PS_BlurInput
{
    float4 tex0 : TEXCOORD0;
    float4 tex1 : TEXCOORD1;
    float4 tex2 : TEXCOORD2;
    float4 tex3 : TEXCOORD3;
    float4 tex4 : TEXCOORD4;
    float4 tex5 : TEXCOORD5;
    float4 tex6 : TEXCOORD6;
    float4 tex7 : TEXCOORD7;
};

//�萔�o�b�t�@
cbuffer cbuff0 : register(b0)
{
    matrix world; //���[���h�ϊ��s��
    matrix viewproj; //�r���[�v���W�F�N�V�����s��
    float4 color; //�F
    float3 eye; //���_���W
};

//�}���`�p�X�p�̒萔�o�b�t�@
cbuffer cbuff1 : register(b1)
{
    float4 gaussianWeight[2]; //�K�E�X�t�B���^�[�̏d��
}

//���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; //�V�X�e���p���_���W
    float3 normal : NORMAL; //�@���x�N�g��
    PS_BlurInput uv;
};