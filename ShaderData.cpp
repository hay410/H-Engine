#include "ShaderData.h"
#include <d3dcompiler.h>
#include <system_error>
#include <fstream>
#include <iostream>
#include <sstream>

ShaderData::ShaderData(const string& shaderPath, const string& entryPoint, const string& shaderModel)
{

	/*-- �R���X�g���N�^ --*/

	// ������ۑ��B
	this->shaderPath = shaderPath;
	this->entryPoint = entryPoint;
	this->shaderModel = shaderModel;
	this->shaderBlob = nullptr;

	//�V�F�[�_�[�����[�h�B
	LoadShader();

}

void ShaderData::LoadShader()
{

	/*-- �V�F�[�_�[�����[�h���鏈�� --*/

	wchar_t shaderPathBuff[128];
	ConvertStringToWchar_t(shaderPath, shaderPathBuff, 128);

	ComPtr<ID3DBlob> errorBlob = nullptr;

	HRESULT result = D3DCompileFromFile(
		shaderPathBuff,										//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,					//�C���N���[�h�\�ɂ���
		entryPoint.c_str(), shaderModel.c_str(),			//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//�f�o�b�O�p�ݒ�
		0,
		&shaderBlob, &errorBlob);

	// �V�F�[�_�[�̃G���[�`�F�b�N
	if (FAILED(result)) {

		// hresult����G���[���b�Z�[�W���擾
		string errorMsg = system_category().message(result);

		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";

		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

}