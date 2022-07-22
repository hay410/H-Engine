#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <d3dx12.h>
#include "Singleton.h"
#include "Pipeline.h"

using namespace std;

class PipelineManager :public Singleton<PipelineManager> {
private:
	//static map<string, Pipeline> pipeline;				//パイプライン
	vector<Pipeline> pipelines;			//パイプライン
	friend Singleton<PipelineManager>;
	//コンストラクタ
	PipelineManager() {};

public:
	/// <summary>
	/// パイプラインを生成する処理
	/// </summary>
	/// <param name="pipelineID">生成するパイプラインのID</param>
	/// <param name="PSname">使用するピクセルシェーダーのファイル名</param>
	/// <param name="VSname">使用する頂点シェーダーのファイル名</param>
	/// <param name="inputLayoutCount">インプットレイアウトの数</param>
	/// <param name="inputLayout">インプットレイアウト</param>
	/// <param name="rootparamCount">ルートパラメーターの数</param>
	/// <param name="rootparam">ルートパラメーター</param>
	/// <param name="primitive">プリミティブ形状</param>
	/// <param name="blendID">ブレンドのID</param>
	void GeneratePipeline(PipelineID pipelineID,
		string PSname,
		string VSname,
		int inputLayoutCount,
		D3D12_INPUT_ELEMENT_DESC* inputLayout,
		int rootparamCount,
		CD3DX12_ROOT_PARAMETER* rootparam,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
		int blendID,
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK,
		DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM);
	/// <summary>
	/// パイプラインを生成する処理
	/// </summary>
	/// <param name="pipelineID">生成するパイプラインのID</param>
	/// <param name="PSname">使用するピクセルシェーダーのファイル名</param>
	/// <param name="VSname">使用する頂点シェーダーのファイル名</param>
	/// <param name="GSname">使用するジオメトリシェーダーのファイル名</param>
	/// <param name="inputLayoutCount">インプットレイアウトの数</param>
	/// <param name="inputLayout">インプットレイアウト</param>
	/// <param name="rootparamCount">ルートパラメーターの数</param>
	/// <param name="rootparam">ルートパラメーター</param>
	/// <param name="primitive">プリミティブ形状</param>
	/// <param name="blendID">ブレンドのID</param>
	void GeneratePipeline(PipelineID pipelineID,
		string PSname,
		string VSname,
		string GSname,
		int inputLayoutCount,
		D3D12_INPUT_ELEMENT_DESC* inputLayout,
		int rootparamCount,
		CD3DX12_ROOT_PARAMETER* rootparam,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
		int blendID,
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK,
		DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM);

	void GeneratePipelineDepth(PipelineID pipelineID,
		string PSname,
		string VSname,
		int inputLayoutCount,
		D3D12_INPUT_ELEMENT_DESC* inputLayout,
		int rootparamCount,
		CD3DX12_ROOT_PARAMETER* rootparam,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
		int blendID,
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK,
		DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT dxgiFormat2 = DXGI_FORMAT_R8_UNORM);


	//パイプランをセットする
	void SetPipeline(int pipelineID);

	//ルートパラメーターを生成
	void Init();
};