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
	//�����_�[�^�[�Q�b�g���N���A
	DirectXBase::Instance()->cmdList->ClearRenderTargetView(renderTarget.rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart(), renderTarget.rtvClearColor, 0, nullptr);

	if (renderTarget.HasDepthStencil()) {
		//�[�x���N���A
		DirectXBase::Instance()->cmdList->ClearDepthStencilView(renderTarget.dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, renderTarget.dsvClearColor,
			0, 0, nullptr);
	}
}

void MultiPath::SetRenderTargetAndClear(RenderTarget renderTarget)
{
	//���\�[�X�o���A
	ResourceBarrierBefore(renderTarget);
	//�����_�[�^�[�Q�b�g���Z�b�e�B���O
	DirectXBase::Instance()->cmdList->OMSetRenderTargets(1, &renderTarget.rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
		FALSE, &renderTarget.dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart());
	//�N���A
	ClearRtvDsv(renderTarget);
}

void MultiPath::SetRenderTarget(RenderTarget renderTarget)
{
	//���\�[�X�o���A
	ResourceBarrierBefore(renderTarget);
	//�����_�[�^�[�Q�b�g���Z�b�e�B���O
	DirectXBase::Instance()->cmdList->OMSetRenderTargets(1, &renderTarget.rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
		FALSE, &renderTarget.dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart());
}

void MultiPath::SetRenderTargetsAndClear(UINT num, RenderTarget* renderTargets[])
{
	//���\�[�X�o���A
	for (UINT i = 0; i < num; ++i) {
		ResourceBarrierBefore(*renderTargets[i]);
	}

	//�����_�[�^�[�Q�b�g���Z�b�g
	D3D12_CPU_DESCRIPTOR_HANDLE rtDSHandleTbl[32];
	int rtNo = 0;
	for (UINT rtNo = 0; rtNo < num; rtNo++) {
		rtDSHandleTbl[rtNo] = renderTargets[rtNo]->rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
	}
	if (renderTargets[0]->HasDepthStencil()) {
		//�[�x�o�b�t�@������B
		D3D12_CPU_DESCRIPTOR_HANDLE dsDS = renderTargets[0]->dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, &dsDS);
	}
	else {
		//�[�x�o�b�t�@���Ȃ��B
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, nullptr);
	}

	//�N���A
	for (UINT i = 0; i < num; ++i) {
		ClearRtvDsv(*renderTargets[i]);
	}
}

void MultiPath::SetRenderTargets(UINT num, RenderTarget* renderTargets[])
{
	//���\�[�X�o���A
	for (UINT i = 0; i < num; ++i) {
		ResourceBarrierBefore(*renderTargets[i]);
	}

	//�����_�[�^�[�Q�b�g���Z�b�g
	D3D12_CPU_DESCRIPTOR_HANDLE rtDSHandleTbl[32];
	int rtNo = 0;
	for (UINT rtNo = 0; rtNo < num; rtNo++) {
		rtDSHandleTbl[rtNo] = renderTargets[rtNo]->rtvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
	}
	if (renderTargets[0]->HasDepthStencil()) {
		//�[�x�o�b�t�@������B
		D3D12_CPU_DESCRIPTOR_HANDLE dsDS = renderTargets[0]->dsvHeap.Get()->GetCPUDescriptorHandleForHeapStart();
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, &dsDS);
	}
	else {
		//�[�x�o�b�t�@���Ȃ��B
		DirectXBase::Instance()->cmdList->OMSetRenderTargets(num, rtDSHandleTbl, FALSE, nullptr);
	}

}

void MultiPath::GaussianBlur(XMFLOAT2 textureSize, float blurAmount, int targetTextureID, RenderTarget& exportTarget)
{
	/*-----�ڂ����ʂ�ݒ�-----*/
	SetGaussianAmount(gaussian.gaussXSprite, gaussian.gaussYSprite, blurAmount);

	/*-----�u���[�̕`��e�N�X�`����ݒ�-----*/
	gaussian.gaussXSprite.ChangeTextureID(targetTextureID, 0);
	gaussian.gaussYSprite.ChangeTextureID(gaussian.gaussX.textureID, 0);

	/*-----���ڂ̂ڂ�����������-----*/
	//�����_�[�^�[�Q�b�g�����u���[�ɐݒ�
	MultiPath::Instance()->SetRenderTargetAndClear(gaussian.gaussX);
	//�����_�[�^�[�Q�b�g�ɕ`��
	gaussian.gaussXSprite.ChangePosition(XMFLOAT3(textureSize.x / 2.0f, textureSize.y / 2.0f, 10));
	//ObjectManager::Instance()->ChangeScale(gaussian.gaussXSprite.scaleMat, XMFLOAT3(1,1, 1));
	gaussian.gaussXSprite.Draw();
	//�����_�[�^�[�Q�b�g�ւ̏������݊����҂�
	MultiPath::Instance()->ResourceBarrierAfter(gaussian.gaussX);
	//�����_�[�^�[�Q�b�g���c�u���[�ɐݒ�
	gaussian.gaussYSprite.ChangePosition(XMFLOAT3(textureSize.x / 2.0f, textureSize.y / 2.0f, 10));
	//ObjectManager::Instance()->ChangeScale(gaussian.gaussYSprite.scaleMat, XMFLOAT3(1,1, 1));
	MultiPath::Instance()->SetRenderTargetAndClear(gaussian.gaussY);
	//�����_�[�^�[�Q�b�g�ɕ`��
	gaussian.gaussYSprite.Draw();
	//�����_�[�^�[�Q�b�g�ւ̏������݊����҂�
	MultiPath::Instance()->ResourceBarrierAfter(gaussian.gaussY);

	/*-----���u���[�̕`��e�N�X�`�����Đݒ�-----*/
	gaussian.gaussXSprite.ChangeTextureID(gaussian.gaussY.textureID, 0);


	/*-----�ŏI�I�Ƀ{�P���摜���G�N�X�|�[�g�^�[�Q�b�g�ɕ`��-----*/
	//�����_�[�^�[�Q�b�g���G�N�X�|�[�g�^�[�Q�b�g�ɐݒ�
	MultiPath::Instance()->SetRenderTargetAndClear(exportTarget);
	//�傫����ݒ�
	gaussian.gaussXSprite.ChangePosition(XMFLOAT3(textureSize.x / 2.0f, textureSize.y / 2.0f, 10));
	//ObjectManager::Instance()->ChangeScale(gaussian.gaussXSprite.scaleMat, XMFLOAT3(1,1, 1));
	//�����_�[�^�[�Q�b�g�ɕ`��
	gaussian.gaussXSprite.ChangeTextureID(gaussian.gaussY.textureID, 0);
	gaussian.gaussXSprite.Draw();
	//�傫�����Đݒ�
	gaussian.gaussXSprite.ChangePosition(XMFLOAT3(window_width / 2.0f, window_height / 2.0f, 10));
	//�����_�[�^�[�Q�b�g�ւ̏������݊����҂�
	MultiPath::Instance()->ResourceBarrierAfter(exportTarget);
}

void MultiPath::SetGaussianAmount(GaussianSprite& xBlur, GaussianSprite& yBlur, float amount)
{
	//�d�݃e�[�u�����v�Z����
	vector<float> weights;
	weights.resize(amount);
	CalcWeightsTableFromGaussian(weights, NUM_GAUSS_WEIGHT, amount);
	//�d�݂���
	xBlur.ChangeConstBufferDataB1(weights);
	yBlur.ChangeConstBufferDataB1(weights);
}

void MultiPath::CalcWeightsTableFromGaussian(vector<float>& weightsTbl, int sizeOfWeightsTbl, float sigma)
{
	// �d�݂̍��v���L�^����ϐ����`����
	float total = 0;

	// ��������K�E�X�֐���p���ďd�݂��v�Z���Ă���
	// ���[�v�ϐ���x����e�N�Z������̋���
	for (int x = 0; x < sizeOfWeightsTbl; x++)
	{
		weightsTbl.at(x) = expf(-0.5f * (float)(x * x) / sigma);
		total += 2.0f * weightsTbl.at(x);
	}

	// �d�݂̍��v�ŏ��Z���邱�ƂŁA�d�݂̍��v��1�ɂ��Ă���
	for (int i = 0; i < sizeOfWeightsTbl; i++)
	{
		weightsTbl.at(i) /= total;
	}
}

void Gaussian::Init()
{
	//���u���[�p�̃����_�[�^�[�Q�b�g
	gaussX.Create(window_width, window_height, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	//�c�u���[�p�̃����_�[�^�[�Q�b�g
	gaussY.Create(window_width, window_height, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_D32_FLOAT);

	//���u���[�p�̃X�v���C�g
	gaussXSprite.GenerateSpecifyTextureID(XMFLOAT3(window_width / 2.0f, window_height / 2.0f, 10), XMFLOAT2(window_width / 2.0f, window_height / 2.0f), PROJECTIONID_UI, PIPELINE_MULTIPATH_GAUSSIAN_X_ALPHA, gaussY.textureID);
	//�c�u���[�p�̃X�v���C�g
	gaussYSprite.GenerateSpecifyTextureID(XMFLOAT3(window_width / 2.0f, window_height / 2.0f, 10), XMFLOAT2(window_width / 2.0f, window_height / 2.0f), PROJECTIONID_UI, PIPELINE_MULTIPATH_GAUSSIAN_Y_ALPHA, gaussX.textureID);
}
