/*-----�萔1(�ϊ��s��Ǝ��_���W)-----*/
cbuffer cabuff0 : register(b0)
{
    matrix world; //���[���h�ϊ��s��
    matrix viewproj; //�r���[�v���W�F�N�V�����s��
    float4 color; //�F
    float3 eye; //���_���W
}

/*-----�萔2(�}�e���A��)-----*/
cbuffer cbuff1 : register(b1)
{
    float3 mAmbient : packoffset(c0); //�A���r�G���g�W��
    float3 mDiffuse : packoffset(c1); //�f�B�t�[�Y�W��
    float3 mSpecular : packoffset(c2); //�X�y�L�����[�W��
    float mAlpha : packoffset(c2.w); //�A���t�@
}

/*-----�萔3(���C�g�֌W)-----*/
//�_�����̐�
#define POINTLIGHT_NUM 120
//�ʌ����̐�
#define DIRECTIONLIGHT_NUM 1
//�X�|�b�g���C�g�̐�
#define SPOTLIGHT_NUM 1
//�ۉe�̐�
#define CIRCLESHADOW_NUM 120
//�_�����̃f�[�^
struct PointLight
{
    float3 lightpos; //���C�g���W
    float3 lightcolor; //���C�g�̐F
    float3 lightatten; //���C�g���������W��
    uint active; //�A�N�e�B�u�t���O
};
//�ʌ����̃f�[�^
struct DirLight
{
    float3 lightv; //�����x�N�g��
    float3 lightcolor; //���C�g�̐F
    uint active; //�A�N�e�B�u�t���O
};
//�X�|�b�g���C�g�̃f�[�^
struct SpotLight
{
    float3 lightv; //���C�g�̕����x�N�g��
    float3 lightpos; //���C�g���W
    float3 lightcolor; //���C�g�̐F
    float3 lightatten; //���C�g���������W��
    float2 lightfactoranglecos; //���C�g�p�x�����W��
    uint active; //�A�N�e�B�u�t���O
};
//�ۉe�̃f�[�^
struct CircleShadow
{
    float3 dir; //���e�����̋t�x�N�g��(�P�ʃx�N�g��)
    float3 casterpos; //CASTER���W
    float distanceCasterLight; //�L���X�^�[�ƃ��C�g�̋���
    float3 atten; //���������W��
    float2 factorAngleCos; //�����p�x�̃R�T�C��
    uint active; //�A�N�e�B�u�t���O
};
cbuffer cbuff2 : register(b2)
{
    PointLight pointLights[POINTLIGHT_NUM]; //�_����
    DirLight dirLights[DIRECTIONLIGHT_NUM]; //�ʌ���
    SpotLight spotlights[SPOTLIGHT_NUM]; //�X�|�b�g���C�g
    //CircleShadow circleShadow[CIRCLESHADOW_NUM];//�ۉe
}

//���_�V�F�[�_�[����Ԃ����f�[�^�\����
struct VSOutput
{
    float4 svpos : SV_POSITION; //�V�X�e���p���_���W
    float4 worldpos : POSITION; //���[���h���W
    float3 normal : NORMAL; //�@���x�N�g��
    float2 uv : TEXCOORD; //uv�l
};