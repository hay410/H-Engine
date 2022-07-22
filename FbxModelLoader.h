#pragma once
#include"fbxsdk.h"
#include"struct.h"
#include"FbxModel.h"
#include"Singleton.h"

class FbxModelLoader :public Singleton<FbxModelLoader>
{
public:
	//メンバ定数
	static const string baseDirectory;

	//メンバ変数
	
	//D3D12デバイス
	ComPtr<ID3D12Device> dev;

	//FBXマネージャー
	FbxManager* fbxManager = nullptr;

	//FBXインポーター
	FbxImporter* fbxImporter = nullptr;

	//テクスチャがない場合の標準テクスチャファイル名
	static const string defaultTextureFileName;

	//メンバ関数
	//コンストラクタ
	FbxModelLoader();
	friend Singleton<FbxModelLoader>;

	//初期化
	void Init(ComPtr<ID3D12Device> dev);

	//終了処理
	void Fainalize();

	//ファイル名からモデルを読み込む
	FbxModel* LoadModelFromFile(const string& modelName);

	//再帰的にノード攻勢を解析
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent = nullptr);

	//メッシュ読み込み
	void ParseMesh(FbxModel* model, FbxNode* fbxNode);

	//頂点情報読み取り
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh);
	
	//面情報読み取り
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh);

	//マテリアル読み込み
	void ParseMaterial(FbxModel* model, FbxNode* fbxNode);
	//スキニング情報読み取り
	void ParceSkin(FbxModel* model, FbxMesh* fbxMesh);

	//テクスチャ読み取り
	void LoadTexture(FbxModel* model, string& fileName);

	//ディレクトリを含んだファイルパスからファイル名を抽出する
	string ExtractFileName(const string& path);

	//FBXの行列をXMMATRIXに変換
	static void ConvertMatrixFromFbx(XMMATRIX* dst, const FbxAMatrix& src);

};