#pragma once
#include"struct.h"
#include"fbxsdk.h"
#include<DirectXTex.h>

class FbxModel
{
public://定数
	//ボーンインデックスの最大
	static const int MAX_BONE_INDICES = 4;

	//フレンドクラス
	friend class FbxModelLoader;

	struct VertexFbx
	{
		XMFLOAT3 pos;		//座標
		XMFLOAT3 normal;	//法線
		XMFLOAT2 uv;		//uv座標
		UINT boneIndex[MAX_BONE_INDICES];
		float boneWeight[MAX_BONE_INDICES];
	};

	//ボーン構造体
	struct Bone
	{
		//名前
		string name;
		//初期姿勢の逆行列
		XMMATRIX invInitialPose;
		//クラスター
		FbxCluster* fbxCluster;
		//コンストラクタ
		Bone(const string& name) {
			this->name = name;
		}

	};


private:
	//モデル名
	string name;
	//ノード配列
	vector<Node> nodes;

	//メッシュを持つノード
	Node* meshNode = nullptr;

	//Fbxシーン
	FbxScene* fbxScene = nullptr;

	//頂点保存先のオブジェクト
	//Object3D objectBuff;

	//頂点データ配列
	vector<VertexFbx> vertices;
	//インデックス配列
	vector<unsigned short>indices;
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};


	//アンビエント係数
	XMFLOAT3 ambient = { 1,1,1 };
	//ディフューズ係数
	XMFLOAT3 diffuse = { 1,1,1 };
	//テクスチャメタデータ
	TexMetadata metadata = {};
	//スクラッチイメージ
	ScratchImage scratchImg = {};

	//テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;

	//SRVデスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	//ボーン配列
	vector<Bone> bones;

	//バッファ生成
	void CreateBuffers(ComPtr<ID3D12Device>);
public:
	//デストラクタ
	~FbxModel();

	//描画
	void Draw();

	//モデルの変形行列取得
	const XMMATRIX& GetModelTransform() { return meshNode->globalTransform; }

	vector<Bone>& GetBones() { return bones; }

	FbxScene* GetFbxScene() { return fbxScene; }
};