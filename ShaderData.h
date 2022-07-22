#pragma once
#include "DirectXBase.h"
#include <d3d12.h>
#include <string>

// シェーダーデータを保存するためのデータクラス
class ShaderData {

private:

	/*-- メンバ変数 --*/

	ComPtr<ID3DBlob> shaderBlob;		// シェーダーのデータ
	string entryPoint;					// シェーダーのエントリーポイント
	string shaderModel;					// シェーダーモデル
	string shaderPath;					// シェーダーのファイルパス これを使ってシェーダーを判断する。


public:

	/*-- メンバ関数 --*/

	// コンストラクタ
	ShaderData(const string& shaderPath, const string& entryPoint, const string& shaderModel);

	// ロード処理
	void LoadShader();

	// シェーダーのファイルパスを取得する処理
	const string& GetShaderPath() { return shaderPath; }
	// シェーダーのデータを取得する処理
	const ComPtr<ID3DBlob>& GetShaderBlob() { return shaderBlob; }

private:

	std::wstring StringToWString(std::string oString)
	{
		// SJIS → wstring
		int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
			, -1, (wchar_t*)NULL, 0);

		// バッファの取得
		wchar_t* cpUCS2 = new wchar_t[iBufferSize];

		// SJIS → wstring
		MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
			, iBufferSize);

		// stringの生成
		std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

		// バッファの破棄
		delete[] cpUCS2;

		// 変換結果を返す
		return(oRet);
	}

	void ConvertStringToWchar_t(string STRING, wchar_t* WCHAR_STRING, int ARRAY_SIZE)
	{
		MultiByteToWideChar(CP_ACP, 0, STRING.c_str(), -1, WCHAR_STRING, ARRAY_SIZE);
	}

};