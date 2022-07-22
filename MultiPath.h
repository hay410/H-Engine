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

	//コンストラクタ
	Gaussian() {};

	void Init();
};

class MultiPath : public Singleton<MultiPath> {
private:
	//コンストラクタ
	friend Singleton<MultiPath>;

public:

	static Gaussian gaussian;			//ガウシアンぼかしをする際に使用する変数

	MultiPath() {
		gaussian.Init();
	};

public:

	//リソースバリア関係
	void ResourceBarrierBefore(RenderTarget renderTarget);
	void ResourceBarrierAfter(RenderTarget renderTarget);
	void ResourceBarriersAfter(UINT num, RenderTarget* renderTargets[]);
	//レンダーターゲットと深度バッファをクリア
	void ClearRtvDsv(RenderTarget renderTarget);
	//レンダーターゲットを設定
	void SetRenderTargetAndClear(RenderTarget renderTarget);
	void SetRenderTarget(RenderTarget renderTarget);
	//MRT用のレンダーターゲット設定
	void SetRenderTargetsAndClear(UINT num, RenderTarget* renderTargets[]);
	void SetRenderTargets(UINT num, RenderTarget* renderTargets[]);

	//ガウスぼかし
	//void GaussianBlur(SpriteMultiPath xBlur, RenderTarget xBlurTarget, SpriteMultiPath yBlur, RenderTarget yBlurTarget);
	void GaussianBlur(XMFLOAT2 textureSize, float blurAmount, int blurCount, int targetTextureID, RenderTarget& exportTarget);
	//ガウスぼかしのぼかし量を設定
	void SetGaussianAmount(GaussianSprite& xBlur, GaussianSprite& yBlur, float amount);
	//重みの計算
	void CalcWeightsTableFromGaussian(vector<float>& weightsTbl, int sizeOfWeightsTbl, float sigma);

};