/*-----�萔1(�ϊ��s��Ǝ��_���W)-----*/
cbuffer cabuff0 : register(b0)
{
    matrix world; //���[���h�ϊ��s��
    float4 color; //�F
}

//���_�V�F�[�_�[����Ԃ����f�[�^�\����
struct VSOutput
{
    float4 pos : POSITION; //�V�X�e���p���_���W
    //matrix scale;
};

//�W�I���g���V�F�[�_�[����Ԃ����f�[�^�\����
struct GSOutput
{
    float4 svpos : SV_POSITION; //�V�X�e���p���_���W
    float2 uv : TEXCOORD; //uv�l
};