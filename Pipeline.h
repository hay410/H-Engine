#pragma once
#include "ShaderStorage.h"
#include <d3dx12.h>
#include "Enum.h"

class Pipeline {
private:
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelinestate;		// パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;		// ルートシグネチャ
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive;		// プリミティブ
	PipelineID pipelineID;							// パイプラインのID

public:
	Pipeline() {};
	///<summary>
	///コンストラクタ
	///</summary>
	///<param name="PSname"><ロードするピクセルシェーダーのファイル名/param>
	///<param name="VSname"><ロードする頂点シェーダーのファイル名/param>
	///<param name="inputLayoutCount"><インプットレイアウトの数/param>
	///<param name="inputLayout"><インプットレイアウト/param>
	///<param name="rootparamCount"><ルートパラメーター数/param>
	///<param name="rootparam"><ルートパラメーター/param>
	///<param name="primitive"><プリミティブ形状param>
	///<param name="blendID"><どのブレンドをするかのID/param>
	Pipeline(
		PipelineID pipelineID,
		std::string PSname,
		std::string VSname,
		int inputLayoutCount,
		D3D12_INPUT_ELEMENT_DESC* inputLayout,
		int rootparamCount,
		CD3DX12_ROOT_PARAMETER* rootparam,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
		int blendID,
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK,
		DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM);

	Pipeline(
		PipelineID pipelineID,
		std::string PSname,
		std::string VSname,
		int inputLayoutCount,
		D3D12_INPUT_ELEMENT_DESC* inputLayout,
		int rootparamCount,
		CD3DX12_ROOT_PARAMETER* rootparam,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
		int blendID,
		bool isMRT,
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK,
		DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT dxgiFormat2 = DXGI_FORMAT_R8_UNORM);

	Pipeline(
		PipelineID pipelineID,
		std::string PSname,
		std::string VSname,
		std::string GSname,
		int inputLayoutCount,
		D3D12_INPUT_ELEMENT_DESC* inputLayout,
		int rootparamCount,
		CD3DX12_ROOT_PARAMETER* rootparam,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
		int blendID,
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK,
		DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM);

	//パイプラインのセット
	void SetPipeline();

	//パイプラインIDを取得
	PipelineID GetPipelineID() { return pipelineID; }

	//パイプライン設定
	void SetPipelineDesc(D3D12_GRAPHICS_PIPELINE_STATE_DESC& gpipelineDesc, D3D12_INPUT_ELEMENT_DESC* inputLayout, int inputLayoutCount, CD3DX12_ROOT_PARAMETER* rootparam, int rootparamCount, int blendID, D3D12_CULL_MODE cullMode, DXGI_FORMAT dxgiFormat);
	void SetPipelineDescDepth(D3D12_GRAPHICS_PIPELINE_STATE_DESC& gpipelineDesc, D3D12_INPUT_ELEMENT_DESC* inputLayout, int inputLayoutCount, CD3DX12_ROOT_PARAMETER* rootparam, int rootparamCount, int blendID, D3D12_CULL_MODE cullMode, DXGI_FORMAT dxgiFormat, DXGI_FORMAT dxgiFormat2);
};