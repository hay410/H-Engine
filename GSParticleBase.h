#pragma once
#include "DrawDataBase.h"

class GSParticleBase : public DrawDataBase {

protected:

	// ���_�f�[�^�֌W
	XMFLOAT3 vertex;											//���_
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView;							//���_�o�b�t�@�r���[

	// �萔�f�[�^�֌Wb0
	GSConstBufferDataB0 constBufferDataB0;						//�萔 �s��⎋�_���W�A�J���[�Ȃ�
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@

	// �萔�f�[�^�p�f�B�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�p�f�B�X�N���v�^�q�[�v

};