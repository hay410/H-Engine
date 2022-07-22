#pragma once
#include "GaussianSprite.h"
#include "RenderTarget.h"

const int NUM_GAUSS_WEIGHT = 8;

class Gaussian {
public:
	RenderTarget gaussX;
	RenderTarget gaussY;
	GaussianSprite gaussXSprite;
	GaussianSprite gaussYSprite;

	//�R���X�g���N�^
	Gaussian() {};

	void Init();
};

class MultiPath : public Singleton<MultiPath> {
private:
	//�R���X�g���N�^
	friend Singleton<MultiPath>;

public:

	static Gaussian gaussian;			//�K�E�V�A���ڂ���������ۂɎg�p����ϐ�

	MultiPath() {
		gaussian.Init();
	};

public:

	//���\�[�X�o���A�֌W
	void ResourceBarrierBefore(RenderTarget renderTarget);
	void ResourceBarrierAfter(RenderTarget renderTarget);
	void ResourceBarriersAfter(UINT num, RenderTarget* renderTargets[]);
	//�����_�[�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
	void ClearRtvDsv(RenderTarget renderTarget);
	//�����_�[�^�[�Q�b�g��ݒ�
	void SetRenderTargetAndClear(RenderTarget renderTarget);
	void SetRenderTarget(RenderTarget renderTarget);
	//MRT�p�̃����_�[�^�[�Q�b�g�ݒ�
	void SetRenderTargetsAndClear(UINT num, RenderTarget* renderTargets[]);
	void SetRenderTargets(UINT num, RenderTarget* renderTargets[]);

	//�K�E�X�ڂ���
	//void GaussianBlur(SpriteMultiPath xBlur, RenderTarget xBlurTarget, SpriteMultiPath yBlur, RenderTarget yBlurTarget);
	void GaussianBlur(XMFLOAT2 textureSize, float blurAmount, int blurCount, int targetTextureID, RenderTarget& exportTarget);
	//�K�E�X�ڂ����̂ڂ����ʂ�ݒ�
	void SetGaussianAmount(GaussianSprite& xBlur, GaussianSprite& yBlur, float amount);
	//�d�݂̌v�Z
	void CalcWeightsTableFromGaussian(vector<float>& weightsTbl, int sizeOfWeightsTbl, float sigma);

};