cbuffer cbuff0 :register(b0)
{
	float4 color;
	matrix mat;
};

struct VSOutput
{
	float4 svpos :SV_POSITION;	//�V�X�e���p���_���W
	float3 normal :NORMAL;		//�@���x�N�g��
	float2 uv :TEXCOORD;		//uv�l
};



//float4 main() :SV_TARGET
//{
//	return float4(1.0f,1.0f,1.0f,1.0f);
//}