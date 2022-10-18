#pragma once
#include "Object3DBase.h"


class Object3D : public Object3DBase {
private:
	string directoryPath = "Resources/Object/";
	wchar_t* LdirectoryPath = L"Resources/Object/";

public:

	// ��������
	void Generate(XMFLOAT3 centerPos, int projectionID, int piplineID, string modelName, wchar_t* textureFileName, bool isSmoothing = false);

	// �`�揈��
	void Draw();

	// �p�C�v���C�����X�V���鏈��
	void SetPiplineID(int piplineID);

	// �C���f�b�N�X�T�C�Y���擾����
	inline int GetIndexSize() { return index.size(); }

	// ���_�R���e�i���擾����
	inline vector<Vertex> GetVertex() { return vertex; }

	// ���_�C���f�b�N�X�R���e�i���擾����
	inline vector<unsigned short> GetIndex() { return index; }

	/*-- ���C�g���[�V���O�������ɗՎ��Ŏ���������� --*/

	// ���_�o�b�t�@���擾����B
	inline Microsoft::WRL::ComPtr<ID3D12Resource> GetVertexBuff() { return vertBuff; }

	void ConvertStringToWchar_t(string STRING, wchar_t* WCHAR_STRING, int ARRAY_SIZE)
	{
		MultiByteToWideChar(CP_ACP, 0, STRING.c_str(), -1, WCHAR_STRING, ARRAY_SIZE);
	}

};