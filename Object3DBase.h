#pragma once
#include "DrawDataBase.h"
#include "struct.h"
//#include "ConstBufferData.h"

class Object3DBase : public DrawDataBase {

protected:

	/*-- �����o�ϐ� --*/

	// �萔b1�Ab2���}�b�v�������邩�ǂ���
	bool isLighting;

	// �萔b1(�}�e���A��)��]���������ǂ����̃t���O
	bool isAlreadyMapB1;

	// ���_�f�[�^�֌W
	vector<Vertex> vertex;										//���_
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView;							//���_�o�b�t�@�r���[

	// ���_�C���f�b�N�X�f�[�^�֌W
	vector<unsigned short> index;								//���_�C���f�b�N�X
	ComPtr<ID3D12Resource> indexBuff;							//���_�C���f�b�N�X�o�b�t�@
	D3D12_INDEX_BUFFER_VIEW ibView;								//���_�C���f�b�N�X�o�b�t�@�r���[

	// �萔�f�[�^�֌Wb0
	ConstBufferDataB0 constBufferDataB0;						//�萔 �s��⎋�_���W�A�J���[�Ȃ�
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@

	// �萔�f�[�^�֌Wb1
	ConstBufferDataB1 constBufferDataB1;						//�萔2	�}�e���A���Ȃ�
	ComPtr<ID3D12Resource> constBuffB1;							//�萔�o�b�t�@

	// �萔�f�[�^�֌Wb2
	ConstBufferDataB2 constBufferDataB2;						//�萔3	���C�g�Ȃ�
	ComPtr<ID3D12Resource> constBuffB2;							//�萔�o�b�t�@

	// �ǉ��̒萔�o�b�t�@�֌W
	vector<ComPtr<ID3D12Resource>> constBufferData;				// �ǉ����ꂽ�萔�o�b�t�@
	vector<string> constBufferDataName;							// �ǉ����ꂽ�萔�o�b�t�@�̌^����ۑ����邽�߂̔z��

	// �萔�f�[�^�p�f�B�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�p�f�B�X�N���v�^�q�[�v

public:

	// ���_�f�[�^�̃}�b�v����
	void MapVertexData();

	// �F�f�[�^������
	void ChangeColor(const XMFLOAT4& color) { constBufferDataB0.color = color; };

	// �萔�o�b�t�@��ǉ�
	short AddConstBuffer(const int& dataSize, const string& structName);

	// �萔�o�b�t�@��]��
	bool TransData(const short& handle, const void* data, const int& dataSize, const string& structName);

};