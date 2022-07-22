cbuffer cbuff0:register(b0)
{
	matrix viewproj;
	matrix world;
	float3 cameraPos;
};

//頂点バッファ―の入力
struct VSInput
{
	float4 pos    : POSITION;	//位置
	float3 normal : NORMAL;		//法線
	float2 uv     : TEXCOORD;	//テクスチャ―座標
	uint4 boneIndices:BONEINDICES;
	float4 boneWeights:BONEWEIGHTS;

};

struct VSOutput
{
	float4 svpos  : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv     : TEXCOORD;
};

//ボーンの最大数
static const int MAX_BONES = 32;

cbuffer skinning:register(b3)//ボーンのスキニング行列が入る
{
	matrix matSkinning[MAX_BONES];
};