#pragma once
#include "SpriteBase.h"

//�K�E�V�A���u���[�Ɏg�p����X�v���C�g
class GaussianSprite : public SpriteBase {

public:

	// �}���`�p�X�����_�����O�p�̒萔�\����
	struct ConstBufferDataGaussian {
		XMFLOAT4 gaussianWeight[2];				// �K�E�X�t�B���^�[�Ɏg�p����d��
		float pad1;
	};

private:

	ConstBufferDataGaussian constBufferDataB1;	// �萔 �}���`�p�X�����_�����O�Ɏg�p����e���
	ComPtr<ID3D12Resource> constBuffB1;			// �萔�o�b�t�@

private:

	// ���ʂ̐�������
	void CommonGenerate(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID);

public:

	// ��������
	void GenerateForTexture(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, LPCWSTR fileName);
	void GenerateForColor(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, XMFLOAT4 color);
	void GenerateSpecifyTextureID(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, int textureID);

	// �`�揈��
	void Draw();

	// �萔�f�[�^����
	void ChangeConstBufferDataB1(vector<float> amount);

};