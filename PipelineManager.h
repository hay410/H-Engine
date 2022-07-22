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
	//static map<string, Pipeline> pipeline;				//�p�C�v���C��
	vector<Pipeline> pipelines;			//�p�C�v���C��
	friend Singleton<PipelineManager>;
	//�R���X�g���N�^
	PipelineManager() {};

public:
	/// <summary>
	/// �p�C�v���C���𐶐����鏈��
	/// </summary>
	/// <param name="pipelineID">��������p�C�v���C����ID</param>
	/// <param name="PSname">�g�p����s�N�Z���V�F�[�_�[�̃t�@�C����</param>
	/// <param name="VSname">�g�p���钸�_�V�F�[�_�[�̃t�@�C����</param>
	/// <param name="inputLayoutCount">�C���v�b�g���C�A�E�g�̐�</param>
	/// <param name="inputLayout">�C���v�b�g���C�A�E�g</param>
	/// <param name="rootparamCount">���[�g�p�����[�^�[�̐�</param>
	/// <param name="rootparam">���[�g�p�����[�^�[</param>
	/// <param name="primitive">�v���~�e�B�u�`��</param>
	/// <param name="blendID">�u�����h��ID</param>
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
	/// �p�C�v���C���𐶐����鏈��
	/// </summary>
	/// <param name="pipelineID">��������p�C�v���C����ID</param>
	/// <param name="PSname">�g�p����s�N�Z���V�F�[�_�[�̃t�@�C����</param>
	/// <param name="VSname">�g�p���钸�_�V�F�[�_�[�̃t�@�C����</param>
	/// <param name="GSname">�g�p����W�I���g���V�F�[�_�[�̃t�@�C����</param>
	/// <param name="inputLayoutCount">�C���v�b�g���C�A�E�g�̐�</param>
	/// <param name="inputLayout">�C���v�b�g���C�A�E�g</param>
	/// <param name="rootparamCount">���[�g�p�����[�^�[�̐�</param>
	/// <param name="rootparam">���[�g�p�����[�^�[</param>
	/// <param name="primitive">�v���~�e�B�u�`��</param>
	/// <param name="blendID">�u�����h��ID</param>
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


	//�p�C�v�������Z�b�g����
	void SetPipeline(int pipelineID);

	//���[�g�p�����[�^�[�𐶐�
	void Init();
};