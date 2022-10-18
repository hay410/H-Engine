#include "MultiPath.h"
#include "Enum.h"

Gaussian MultiPath::gaussian = {};

void MultiPath::ResourceBarrierBefore(RenderTarget renderTarget)
{
	DirectXBase::Instance()->cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.renderTargetTexture.Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
}

void MultiPath::ResourceBarrierAfter(RenderTarget renderTarget)
{
	DirectXBase::Instance()->cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.renderTargetTexture.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
}

void MultiPath::ResourceBarriersAfter(UINT num, RenderTarget* renderTargets[])
{
	for (UINT i = 0; i < num; ++i) {
		ResourceBarrierAfter(*renderTargets[i]);
	}
}

void MultiPath::ClearRtvDsv(RenderTarget renderTarget)
{
	//レンダーターゲットをクリア
	DirectXBase::Instance()->cmdList->ClearRenderTargetView(renderTarget.rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart(), renderTarget.rtvClearColor, 0, nullptr);

	if (renderTarget.HasDepthStencil()) {
		//深度をクリア
		DirectXBase::Instance()->cmdList->ClearDepthStencilView(renderTarget.dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, renderTarget.dsvClearColor,
			0, 0, nullptr);
	}
}

void MultiPath::SetRenderTargetAndClear(RenderTarget renderTarget)
{
	//リソースバリア
	ResourceBarrierBefore(renderTarget);
	//レンダーターゲットをセッティング
	DirectXBase::Instance()->cmdList->OMSetRenderTargets(1, &renderTarget.rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
		FALSE, &renderTarget.dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart());
	//クリア
	ClearRtvDsv(renderTarget);
}

void MultiPath::SetRenderTarget(RenderTarget renderTarget)
{
	//リソースバリア
	ResourceBarrierBefore(renderTarget);
	//レンダーターゲットをセッティング
	DirectXBase::Instance()->cmdList->OMSetRenderTargets(1, &renderTarget.rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
		FALSE, &renderTarget.dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart());
}

void MultiPath::SetRenderTargetsAndClear(UINT num, RenderTarget* renderTargets[])
{
	//リソースバリア
	for (UINT i = 0; i < num; ++i) {
		ResourceBarrierBefore(*renderTargets[i]);
	}

	//レンダーターゲットをセット
	D3D12_CPU_DESCRIPTOR_HANDLE rtDSHandleTbl[32];
	int rtNo = 0;
	for (UINT rtNo = 0; rtNo < num; rtNo++) {
		rtDSHandleTbl[rtNo] = renderTargets[rtNo]->rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
	}
	if (renderTargets[0]->HasDepthStencil()) {
		//深度バッファがある。
		D3D12_CPU_DESCRIPTOR_HANDLE dsDS = renderTargets[0]->dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, &dsDS);
	}
	else {
		//深度バッファがない。
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, nullptr);
	}

	//クリア
	for (UINT i = 0; i < num; ++i) {
		ClearRtvDsv(*renderTargets[i]);
	}
}

void MultiPath::SetRenderTargets(UINT num, RenderTarget* renderTargets[])
{
	//リソースバリア
	for (UINT i = 0; i < num; ++i) {
		ResourceBarrierBefore(*renderTargets[i]);
	}

	//レンダーターゲットをセット
	D3D12_CPU_DESCRIPTOR_HANDLE rtDSHandleTbl[32];
	int rtNo = 0;
	for (UINT rtNo = 0; rtNo < num; rtNo++) {
		rtDSHandleTbl[rtNo] = renderTargets[rtNo]->rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
	}
	if (renderTargets[0]->HasDepthStencil()) {
		//深度バッファがある。
		D3D12_CPU_DESCRIPTOR_HANDLE dsDS = renderTargets[0]->dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, &dsDS);
	}
	else {
		//深度バッファがない。
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, nullptr);
	}

}

void MultiPath::GaussianBlur(XMFLOAT2 textureSize, float blurAmount, int targetTextureID, RenderTarget& exportTarget)
{
	/*-----ぼかし量を設定-----*/
	SetGaussianAmount(gaussian.gaussXSprite, gaussian.gaussYSprite, blurAmount);

	/*-----ブラーの描画テクスチャを設定-----*/
	gaussian.gaussXSprite.ChangeTextureID(targetTextureID, 0);
	gaussian.gaussYSprite.ChangeTextureID(gaussian.gaussX.textureID, 0);

	/*-----一回目のぼかしをかける-----*/
	//レンダーターゲットを横ブラーに設定
	MultiPath::Instance()->SetRenderTargetAndClear(gaussian.gaussX);
	//レンダーターゲットに描画
	gaussian.gaussXSprite.ChangePosition(XMFLOAT3(textureSize.x / 2.0f, textureSize.y / 2.0f, 10));
	//ObjectManager::Instance()->ChangeScale(gaussian.gaussXSprite.scaleMat, XMFLOAT3(1,1, 1));
	gaussian.gaussXSprite.Draw();
	//レンダーターゲットへの書き込み完了待ち
	MultiPath::Instance()->ResourceBarrierAfter(gaussian.gaussX);
	//レンダーターゲットを縦ブラーに設定
	gaussian.gaussYSprite.ChangePosition(XMFLOAT3(textureSize.x / 2.0f, textureSize.y / 2.0f, 10));
	//ObjectManager::Instance()->ChangeScale(gaussian.gaussYSprite.scaleMat, XMFLOAT3(1,1, 1));
	MultiPath::Instance()->SetRenderTargetAndClear(gaussian.gaussY);
	//レンダーターゲットに描画
	gaussian.gaussYSprite.Draw();
	//レンダーターゲットへの書き込み完了待ち
	MultiPath::Instance()->ResourceBarrierAfter(gaussian.gaussY);

	/*-----横ブラーの描画テクスチャを再設定-----*/
	gaussian.gaussXSprite.ChangeTextureID(gaussian.gaussY.textureID, 0);


	/*-----最終的にボケた画像をエクスポートターゲットに描画-----*/
	//レンダーターゲットをエクスポートターゲットに設定
	MultiPath::Instance()->SetRenderTargetAndClear(exportTarget);
	//大きさを設定
	gaussian.gaussXSprite.ChangePosition(XMFLOAT3(textureSize.x / 2.0f, textureSize.y / 2.0f, 10));
	//ObjectManager::Instance()->ChangeScale(gaussian.gaussXSprite.scaleMat, XMFLOAT3(1,1, 1));
	//レンダーターゲットに描画
	gaussian.gaussXSprite.ChangeTextureID(gaussian.gaussY.textureID, 0);
	gaussian.gaussXSprite.Draw();
	//大きさを再設定
	gaussian.gaussXSprite.ChangePosition(XMFLOAT3(window_width / 2.0f, window_height / 2.0f, 10));
	//レンダーターゲットへの書き込み完了待ち
	MultiPath::Instance()->ResourceBarrierAfter(exportTarget);
}

void MultiPath::SetGaussianAmount(GaussianSprite& xBlur, GaussianSprite& yBlur, float amount)
{
	//重みテーブルを計算する
	vector<float> weights;
	weights.resize(amount);
	CalcWeightsTableFromGaussian(weights, NUM_GAUSS_WEIGHT, amount);
	//重みを代入
	xBlur.ChangeConstBufferDataB1(weights);
	yBlur.ChangeConstBufferDataB1(weights);
}

void MultiPath::CalcWeightsTableFromGaussian(vector<float>& weightsTbl, int sizeOfWeightsTbl, float sigma)
{
	// 重みの合計を記録する変数を定義する
	float total = 0;

	// ここからガウス関数を用いて重みを計算している
	// ループ変数のxが基準テクセルからの距離
	for (int x = 0; x < sizeOfWeightsTbl; x++)
	{
		weightsTbl.at(x) = expf(-0.5f * (float)(x * x) / sigma);
		total += 2.0f * weightsTbl.at(x);
	}

	// 重みの合計で除算することで、重みの合計を1にしている
	for (int i = 0; i < sizeOfWeightsTbl; i++)
	{
		weightsTbl.at(i) /= total;
	}
}

void Gaussian::Init()
{
	//横ブラー用のレンダーターゲット
	gaussX.Create(window_width, window_height, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	//縦ブラー用のレンダーターゲット
	gaussY.Create(window_width, window_height, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);

	//横ブラー用のスプライト
	gaussXSprite.GenerateSpecifyTextureID(XMFLOAT3(window_width / 2.0f, window_height / 2.0f, 10), XMFLOAT2(window_width / 2.0f, window_height / 2.0f), PROJECTIONID_UI, PIPELINE_MULTIPATH_GAUSSIAN_X_ALPHA, gaussY.textureID);
	//縦ブラー用のスプライト
	gaussYSprite.GenerateSpecifyTextureID(XMFLOAT3(window_width / 2.0f, window_height / 2.0f, 10), XMFLOAT2(window_width / 2.0f, window_height / 2.0f), PROJECTIONID_UI, PIPELINE_MULTIPATH_GAUSSIAN_Y_ALPHA, gaussX.textureID);
}
