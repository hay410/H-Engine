#pragma once
#include "Object3DBase.h"


class Object3D : public Object3DBase {
private:
	string directoryPath = "Resources/Object/";
	wchar_t* LdirectoryPath = L"Resources/Object/";

public:

	// 生成処理
	void Generate(XMFLOAT3 centerPos, int projectionID, int piplineID, string modelName, wchar_t* textureFileName, bool isSmoothing = false);

	// 描画処理
	void Draw();

	// パイプラインを更新する処理
	void SetPiplineID(int piplineID);

	// インデックスサイズを取得する
	inline int GetIndexSize() { return index.size(); }

	// 頂点コンテナを取得する
	inline vector<Vertex> GetVertex() { return vertex; }

	// 頂点インデックスコンテナを取得する
	inline vector<unsigned short> GetIndex() { return index; }

	/*-- レイトレーシング実装時に臨時で実装したやつ --*/

	// 頂点バッファを取得する。
	inline Microsoft::WRL::ComPtr<ID3D12Resource> GetVertexBuff() { return vertBuff; }

	void ConvertStringToWchar_t(string STRING, wchar_t* WCHAR_STRING, int ARRAY_SIZE)
	{
		MultiByteToWideChar(CP_ACP, 0, STRING.c_str(), -1, WCHAR_STRING, ARRAY_SIZE);
	}

};