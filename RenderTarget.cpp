#include "RenderTarget.h"
#include "TextureManager.h"

bool RenderTarget::Create(int w, int h, int mipLevel, int arraySize, DXGI_FORMAT colorFormat, DXGI_FORMAT depthStencilFormat, float clearColor[4])
{
	this->width = w;
	this->height = h;
	//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬����B
	if (!CreateRenderTargetTexture(w, h, mipLevel, arraySize, colorFormat, clearColor)) {
		//	TK_ASSERT(false, "�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B");
		MessageBoxA(nullptr, "�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B", "�G���[", MB_OK);
		return false;
	}
	//�[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`�����쐬����B
	if (depthStencilFormat != DXGI_FORMAT_UNKNOWN) {
		if (!CreateDepthStencilTexture(w, h, depthStencilFormat)) {
			MessageBoxA(nullptr, "�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B", "�G���[", MB_OK);
			return false;
		}
	}
	if (!CreateDescriptorHeap()) {
		//�f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
		MessageBoxA(nullptr, "�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`���̍쐬�Ɏ��s���܂����B", "�G���[", MB_OK);
		return false;
	}
	//�f�B�X�N���v�^���쐬����B
	CreateDescriptor();
	if (clearColor) {
		memcpy(rtvClearColor, clearColor, sizeof(rtvClearColor));
	}
	return true;
}

bool RenderTarget::CreateDescriptorHeap()
{
	//RTV�p�̃f�B�X�N���v�^�q�[�v���쐬����B
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = 1;					//MiniEngine���Ƃ悭�킩��Ȃ��l�����Ă����̂ŁA�Ƃ肠����1������B�o�O������v�m�F https://github.com/shoeisha-books/hlsl-grimoire-sample/blob/main/MiniEngine/RenderTarget.cpp
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DirectXBase::Instance()->dev->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&rtvHeap));
	if (rtvHeap == nullptr) {
		//RTV�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
		return false;
	}
	//�f�B�X�N���v�^�̃T�C�Y���擾�B
	rtvDescriptorSize = DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	if (depthStencilTexture) {
		//DSV�p�̃f�B�X�N���v�^�q�[�v���쐬����B
		desc.NumDescriptors = 1;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		DirectXBase::Instance()->dev->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&dsvHeap));
		if (dsvHeap == nullptr) {
			//DSV�p�̃f�B�X�N���v�^�q�[�v�̍쐬�Ɏ��s�����B
			return false;
		}
		//�f�B�X�N���v�^�̃T�C�Y���擾�B
		dsvDescriptorSize = DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	}
	return true;
}

bool RenderTarget::CreateRenderTargetTexture(int w, int h, int mipLevel, int arraySize, DXGI_FORMAT format, float clearColor[4])
{
	textureID = TextureManager::Instance()->CreateRenderTargetTexture(w, h, mipLevel, arraySize, format, clearColor);
	renderTargetTexture = TextureManager::Instance()->GetTexture(textureID).texBuff;

	return true;
}

bool RenderTarget::CreateDepthStencilTexture(int w, int h, DXGI_FORMAT format)
{
	D3D12_CLEAR_VALUE dsvClearValue;
	dsvClearValue.Format = format;
	dsvClearValue.DepthStencil.Depth = 1.0f;
	dsvClearValue.DepthStencil.Stencil = 0;

	CD3DX12_RESOURCE_DESC desc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<UINT>(w),
		static_cast<UINT>(h),
		1,
		1,
		format,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

	auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	auto hr = DirectXBase::Instance()->dev->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&dsvClearValue,
		IID_PPV_ARGS(&depthStencilTexture)
	);
	if (FAILED(hr)) {
		//�[�x�X�e���V���o�b�t�@�̍쐬�Ɏ��s�B
		return false;
	}
	return true;
}

void RenderTarget::CreateDescriptor()
{
	//�J���[�e�N�X�`���̃f�B�X�N���v�^���쐬�B
	auto rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	DirectXBase::Instance()->dev->CreateRenderTargetView(TextureManager::Instance()->GetTexture(textureID).texBuff.Get(), nullptr, rtvHandle);
	if (depthStencilTexture) {
		//�[�x�e�N�X�`���̃f�B�X�N���v�^���쐬
		auto dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
		DirectXBase::Instance()->dev->CreateDepthStencilView(depthStencilTexture.Get(), nullptr, dsvHandle);
	}
}
