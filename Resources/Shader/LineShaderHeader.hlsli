//�萔�o�b�t�@
cbuffer cbuff0 : register(b0)
{
    matrix world; //���[���h�ϊ��s��
    matrix viewproj; //�r���[�v���W�F�N�V�����s��
    float4 color; //�F
    float3 eye; //���_���W
};

//���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; //�V�X�e���p���_���W
    float3 normal : NORMAL; //�@���x�N�g��
    float2 uv : TEXCOORD; //uv�l
};