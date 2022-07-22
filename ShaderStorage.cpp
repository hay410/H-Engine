#include "ShaderStorage.h"
#include "ShaderData.h"

ComPtr<ID3DBlob> ShaderStorage::LoadShader(const string& shaderPath, const string& shaderModel, const string& entryPoint)
{

	/*-- �V�F�[�_�[�̃��[�h���� --*/

	const int SHADER_COUNT = shaderData.size();

	// �V�F�[�_�[�̐������[�v���āA���[�h�ς݂̃V�F�[�_�[�����`�F�b�N����B
	for (int index = 0; index < SHADER_COUNT; ++index) {

		// �V�F�[�_�̖��O������Ă����玟�ցB
		if (shaderData[index]->GetShaderPath() != shaderPath) continue;

		// ����index�̃V�F�[�_�[�����^�[������B
		return shaderData[index]->GetShaderBlob();

	}

	// �V�F�[�_�[�����[�h���ĕۑ��B
	shaderData.emplace_back(make_unique<ShaderData>(shaderPath, entryPoint, shaderModel));

	// �Ō���̃f�[�^�����^�[������B
	return shaderData[shaderData.size() - 1]->GetShaderBlob();
}

ComPtr<ID3DBlob> ShaderStorage::GetShaderData(const string& shaderPath)
{

	/*-- �V�F�[�_�[�f�[�^��Ԃ����� --*/

	const int SHADER_COUNT = shaderData.size();

	// �S�ẴV�F�[�_�[�f�[�^����������B
	for (int index = 0; index < SHADER_COUNT; ++index) {

		// �����̗v�f�������Ă��邩���`�F�b�N����B
		if (!(shaderData[index]->GetShaderPath() == shaderPath)) continue;

		return shaderData[index]->GetShaderBlob();

	}

	return ComPtr<ID3DBlob>();
}