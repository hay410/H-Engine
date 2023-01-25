#include "PipelineManager.h"
#include "Pipeline.h"
#include <cassert>

//map<std::std::string, Pipeline> PipelineManager::pipeline{};

void PipelineManager::GeneratePipeline(PipelineID pipelineID,
	std::string PSname,
	std::string VSname,
	int inputLayoutCount,
	D3D12_INPUT_ELEMENT_DESC* inputLayout,
	int rootparamCount,
	CD3DX12_ROOT_PARAMETER* rootparam,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
	int blendID,
	D3D12_CULL_MODE cullMode,
	DXGI_FORMAT dxgiFormat)
{
	//���łɐ������Ă��郊�X�g�̒�����p�C�v���C��ID���d�����Ă��Ȃ������琶������B
	for (int i = 0; i < pipelines.size(); ++i) {
		if (pipelines[i].GetPipelineID() == pipelineID) {

			OutputDebugString(L"\nError ���łɐ������Ă���p�C�v���C���𐶐����悤�Ƃ��܂����B\n");
			exit(true);

			return;
		}
	}

	//�w�肳�ꂽ�p�C�v���C��ID���Ƃɐ������čŌ���ɒǉ�
	pipelines.push_back(Pipeline(pipelineID, PSname, VSname, inputLayoutCount, inputLayout, rootparamCount, rootparam, primitive, blendID, cullMode, dxgiFormat));
}

void PipelineManager::GeneratePipeline(PipelineID pipelineID,
	std::string PSname,
	std::string VSname,
	std::string GSname,
	int inputLayoutCount,
	D3D12_INPUT_ELEMENT_DESC* inputLayout,
	int rootparamCount,
	CD3DX12_ROOT_PARAMETER* rootparam,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
	int blendID,
	D3D12_CULL_MODE cullMode,
	DXGI_FORMAT dxgiFormat)
{
	//���łɐ������Ă��郊�X�g�̒�����p�C�v���C��ID���d�����Ă��Ȃ������琶������
	for (int i = 0; i < pipelines.size(); ++i) {
		if (pipelines[i].GetPipelineID() == pipelineID) {

			OutputDebugString(L"\nError ���łɐ������Ă���p�C�v���C���𐶐����悤�Ƃ��܂����B\n");
			exit(true);

			return;
		}
	}

	//�w�肳�ꂽ�p�C�v���C��ID���Ƃɐ������čŌ���ɒǉ�
	pipelines.push_back(Pipeline(pipelineID, PSname, VSname, inputLayoutCount, inputLayout, rootparamCount, rootparam, primitive, blendID, cullMode, dxgiFormat));

}

void PipelineManager::GeneratePipelineDepth(PipelineID pipelineID,
	std::string PSname,
	std::string VSname,
	int inputLayoutCount,
	D3D12_INPUT_ELEMENT_DESC* inputLayout,
	int rootparamCount,
	CD3DX12_ROOT_PARAMETER* rootparam,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitive,
	int blendID,
	D3D12_CULL_MODE cullMode,
	DXGI_FORMAT dxgiFormat,
	DXGI_FORMAT dxgiFormat2)
{
	//���łɐ������Ă��郊�X�g�̒�����p�C�v���C��ID���d�����Ă��Ȃ������琶������
	for (int i = 0; i < pipelines.size(); ++i) {
		if (pipelines[i].GetPipelineID() == pipelineID) {

			OutputDebugString(L"\nError ���łɐ������Ă���p�C�v���C���𐶐����悤�Ƃ��܂����B\n");
			exit(true);

			return;
		}
	}

	//�w�肳�ꂽ�p�C�v���C��ID���Ƃɐ������čŌ���ɒǉ�
	pipelines.push_back(Pipeline(pipelineID, PSname, VSname, inputLayoutCount, inputLayout, rootparamCount, rootparam, primitive, blendID, cullMode, dxgiFormat));

}

void PipelineManager::SetPipeline(int pipelineID)
{
	for (int i = 0; i < pipelines.size(); ++i) {
		if (pipelines.at(i).GetPipelineID() == pipelineID) {
			pipelines.at(i).SetPipeline();
			return;
		}
	}

	OutputDebugString(L"\nError ���݂��Ă��Ȃ��p�C�v���C�����Z�b�g����悤�Ƃ��܂����B\n");
	assert(0);
}

void PipelineManager::Init()
{
	/*�p�C�v���C���p�̊e�v�f�𐶐�*/
#pragma region inputlayout
	/*InputLayout�𐶐�*/
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{	//���_���W
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{	//�@���x�N�g��
			"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{	//uv���W
			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		}
	};
	D3D12_INPUT_ELEMENT_DESC inputLayoutPos[] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
	};
#pragma endregion

#pragma region descrange
	/*�f�B�X�N���v�^�e�[�u���̐���*/
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);					//t0���W�X�^
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV1(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV2(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1);
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV3(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 2);
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV4(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 3);
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV5(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 4);
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV6(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 5);
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV7(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 6);
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV8(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 7);
#pragma endregion

#pragma region rootparam
	/*���[�g�p�����[�^�̐���*/
	CD3DX12_ROOT_PARAMETER const1Tex1[2]{};
	CD3DX12_ROOT_PARAMETER const2tex1[3]{};
	CD3DX12_ROOT_PARAMETER const3Tex1[4]{};
	CD3DX12_ROOT_PARAMETER const1Tex8[9]{};
	CD3DX12_ROOT_PARAMETER const1Tex2[3]{};
	CD3DX12_ROOT_PARAMETER const3Tex2[5]{};
	CD3DX12_ROOT_PARAMETER const4Tex2[6]{};
	CD3DX12_ROOT_PARAMETER const1[1]{};
	CD3DX12_ROOT_PARAMETER const2[2]{};


	//�萔�p
	const1Tex1[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex1[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const2tex1[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const2tex1[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const2tex1[2].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const3Tex1[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const3Tex1[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const3Tex1[2].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const3Tex1[3].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const1Tex8[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[1].InitAsDescriptorTable(1, &descRangeSRV1, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[2].InitAsDescriptorTable(1, &descRangeSRV2, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[3].InitAsDescriptorTable(1, &descRangeSRV3, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[4].InitAsDescriptorTable(1, &descRangeSRV4, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[5].InitAsDescriptorTable(1, &descRangeSRV5, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[6].InitAsDescriptorTable(1, &descRangeSRV6, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[7].InitAsDescriptorTable(1, &descRangeSRV7, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex8[8].InitAsDescriptorTable(1, &descRangeSRV8, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const1Tex2[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex2[1].InitAsDescriptorTable(1, &descRangeSRV1, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const1Tex2[2].InitAsDescriptorTable(1, &descRangeSRV2, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const3Tex2[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const3Tex2[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const3Tex2[2].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const3Tex2[3].InitAsDescriptorTable(1, &descRangeSRV1, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const3Tex2[4].InitAsDescriptorTable(1, &descRangeSRV2, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const4Tex2[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const4Tex2[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const4Tex2[2].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const4Tex2[3].InitAsConstantBufferView(3, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const4Tex2[4].InitAsDescriptorTable(1, &descRangeSRV1, D3D12_SHADER_VISIBILITY_ALL);
	//�e�N�X�`���p
	const4Tex2[5].InitAsDescriptorTable(1, &descRangeSRV2, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const1[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);

	//�萔�p
	const2[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	//�萔�p
	const2[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);

#pragma endregion

	/*���C���p�̃p�C�v���C��*/
	//GeneratePipeline(PIPELINE_LINE_ALPHA, "Resources/Shader/LinePS.hlsl", "Resources/Shader/LineVS.hlsl", 3, inputLayout, 2, const1Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BLENDMODE_ALPHA);

	/*�X�v���C�g�p�̃p�C�v���C��*/
	GeneratePipeline(PIPELINE_SPRITE_ADD, "Resources/Shader/SpritePS.hlsl", "Resources/Shader/SpriteVS.hlsl", 3, inputLayout, 2, const1Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ADD);
	GeneratePipeline(PIPELINE_SPRITE_ALPHA, "Resources/Shader/SpritePS.hlsl", "Resources/Shader/SpriteVS.hlsl", 3, inputLayout, 2, const1Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA);

	/*�I�u�W�F�N�g�p�̃p�C�v���C��*/
	GeneratePipeline(PIPELINE_OBJECT_SIMPLE_COLOR_ALPHA, "Resources/Shader/ObjectPS.hlsl", "Resources/Shader/ObjectVS.hlsl", 3, inputLayout, 4, const3Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA, D3D12_CULL_MODE_BACK);
	GeneratePipeline(PIPELINE_OBJECT_LIGHT_ALPHA, "Resources/Shader/ObjectLightPS.hlsl", "Resources/Shader/ObjectVS.hlsl", 3, inputLayout, 4, const3Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA, D3D12_CULL_MODE_BACK);
	GeneratePipeline(PIPELINE_OBJECT_NOLIGHT_ALPHA, "Resources/Shader/ObjectNoLightPS.hlsl", "Resources/Shader/ObjectVS.hlsl", 3, inputLayout, 4, const3Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA, D3D12_CULL_MODE_NONE);
	//GeneratePipeline(PIPELINE_OBJECT_OUTLINE_ALPHA, "Resources/Shader/ObjectNoLightPS.hlsl", "Resources/Shader/ObjectVS.hlsl", 3, inputLayout, 4, const3Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA, D3D12_CULL_MODE_FRONT);
	GeneratePipeline(PIPELINE_OBJECT_TOONSHADER_ALPHA, "Resources/Shader/ObjectToonShaderPS.hlsl", "Resources/Shader/ObjectToonShaderVS.hlsl", 3, inputLayout, 5, const3Tex2, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA);

	/*GS�p�[�e�B�N���p�̃p�C�v���C��*/
	//GeneratePipeline(PIPELINE_GSPARTICLE_NOLIGHT_ALPHA, "Resources/Shader/GSParticlePS.hlsl", "Resources/Shader/GSParticleVS.hlsl", "Resources/Shader/GSParticleGS.hlsl", 1, inputLayoutPos, 2, const1Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT, BLENDMODE_ALPHA);
	/*�}���`�p�X�����_�����O�p�̃p�C�v���C��*/
	GeneratePipeline(PIPELINE_MULTIPATH_NORMAL_ADD, "Resources/Shader/MultiPathNormalPS.hlsl", "Resources/Shader/MultiPathNormalVS.hlsl", 3, inputLayout, 3, const2tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ADD);
	GeneratePipeline(PIPELINE_MULTIPATH_NORMAL_ALPHA, "Resources/Shader/MultiPathNormalPS.hlsl", "Resources/Shader/MultiPathNormalVS.hlsl", 3, inputLayout, 3, const2tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA);
	GeneratePipeline(PIPELINE_MULTIPATH_MONOCHROME_ADD, "Resources/Shader/MultiPathMonochromePS.hlsl", "Resources/Shader/MultiPathNormalVS.hlsl", 3, inputLayout, 3, const2tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ADD);
	GeneratePipeline(PIPELINE_MULTIPATH_MONOCHROME_ALPHA, "Resources/Shader/MultiPathMonochromePS.hlsl", "Resources/Shader/MultiPathNormalVS.hlsl", 3, inputLayout, 3, const2tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA);
	GeneratePipeline(PIPELINE_MULTIPATH_GAUSSIAN_X_ALPHA, "Resources/Shader/GaussianXPS.hlsl", "Resources/Shader/GaussianXVS.hlsl", 3, inputLayout, 3, const2tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA);
	GeneratePipeline(PIPELINE_MULTIPATH_GAUSSIAN_Y_ALPHA, "Resources/Shader/GaussianYPS.hlsl", "Resources/Shader/GaussianYVS.hlsl", 3, inputLayout, 3, const2tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ALPHA);
	
	GeneratePipeline(PIPELINE_SPRITE_MIXE_8TEXTURE_ADD, "Resources/Shader/Add8TexturePS.hlsl", "Resources/Shader/SpriteVS.hlsl", 3, inputLayout, 9, const1Tex8, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ADD);
	GeneratePipeline(PIPELINE_SPRITE_LUMINANCE_ADD, "Resources/Shader/LuminancePS.hlsl", "Resources/Shader/SpriteVS.hlsl", 3, inputLayout, 2, const1Tex1, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BLENDMODE_ADD, D3D12_CULL_MODE_BACK, DXGI_FORMAT_R32G32B32A32_FLOAT);
}
