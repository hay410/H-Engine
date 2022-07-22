#pragma once
#include "DirectXBase.h"
#include <d3d12.h>
#include <string>

// �V�F�[�_�[�f�[�^��ۑ����邽�߂̃f�[�^�N���X
class ShaderData {

private:

	/*-- �����o�ϐ� --*/

	ComPtr<ID3DBlob> shaderBlob;		// �V�F�[�_�[�̃f�[�^
	string entryPoint;					// �V�F�[�_�[�̃G���g���[�|�C���g
	string shaderModel;					// �V�F�[�_�[���f��
	string shaderPath;					// �V�F�[�_�[�̃t�@�C���p�X ������g���ăV�F�[�_�[�𔻒f����B


public:

	/*-- �����o�֐� --*/

	// �R���X�g���N�^
	ShaderData(const string& shaderPath, const string& entryPoint, const string& shaderModel);

	// ���[�h����
	void LoadShader();

	// �V�F�[�_�[�̃t�@�C���p�X���擾���鏈��
	const string& GetShaderPath() { return shaderPath; }
	// �V�F�[�_�[�̃f�[�^���擾���鏈��
	const ComPtr<ID3DBlob>& GetShaderBlob() { return shaderBlob; }

private:

	std::wstring StringToWString(std::string oString)
	{
		// SJIS �� wstring
		int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
			, -1, (wchar_t*)NULL, 0);

		// �o�b�t�@�̎擾
		wchar_t* cpUCS2 = new wchar_t[iBufferSize];

		// SJIS �� wstring
		MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
			, iBufferSize);

		// string�̐���
		std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

		// �o�b�t�@�̔j��
		delete[] cpUCS2;

		// �ϊ����ʂ�Ԃ�
		return(oRet);
	}

	void ConvertStringToWchar_t(string STRING, wchar_t* WCHAR_STRING, int ARRAY_SIZE)
	{
		MultiByteToWideChar(CP_ACP, 0, STRING.c_str(), -1, WCHAR_STRING, ARRAY_SIZE);
	}

};