#pragma once
#include "DrawDataBase.h"

class LineBase : public DrawDataBase {

protected:

	/*-- �����o�ϐ� --*/

	// ���_�f�[�^�֌W
	vector<Vertex> vertex;										//���_
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView;							//���_�o�b�t�@�r���[

	// �萔�f�[�^�֌W
	ConstBufferDataB0 constBufferDataB0;						//�萔 �s��⎋�_���W�A�J���[�Ȃ�
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�p�f�B�X�N���v�^�q�[�v

	// �f�o�b�Oor�����蔻��p
	XMFLOAT3 pos1;												//���W
	XMFLOAT3 pos2;												//���W

};