#include "TextureManager.h"
#include "DirectXBase.h"
#include<DirectXTex.h>

TextureManager::TextureManager() {
	//�f�B�X�N���v�^�q�[�v�̐���
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;		//�V�F�[�_�[���猩����
	descHeapDesc.NumDescriptors = 512;									//SRV256��
	//�f�B�X�N���v�^�q�[�v�̐���
	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&srvDescHeap));
}

int TextureManager::LoadTexture(LPCWSTR fileName) {
	//�t�@�C�������[�h�ς݂����`�F�b�N
	if (texture.size() > 0) {
		for (int i = 0; i < texture.size(); ++i) {
			//���[�h���Ă������环�ʔԍ���Ԃ�
			if (texture.at(i).fileName == fileName) {
				return texture.at(i).IDNum;
			}
		}
	}


	//���[�h���Ă��Ȃ������烍�[�h����
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImg;
	HRESULT result = LoadFromWICFile(
		fileName,
		DirectX::WIC_FLAGS::WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	const DirectX::Image* img = scratchImg.GetImage(0, 0, 0);

	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//�e�N�X�`���o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	result = DirectXBase::Instance()->dev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texbuff));

	//�f�[�^�]��
	result = texbuff->WriteToSubresource(
		0,
		nullptr,							//�S�̈�R�s�[
		img->pixels,						//���f�[�^�̐擪�A�h���X
		(UINT)img->rowPitch,				//�ꃉ�C���̃T�C�Y
		(UINT)img->slicePitch				//�����܂��̃T�C�Y
	);

	//�e�N�X�`���z��̍Ō���Ƀ��[�h�����e�N�X�`�������L�^
	Texture proTexture{};
	proTexture.fileName = fileName;
	proTexture.IDNum = texture.size();
	proTexture.metadata = metadata;
	proTexture.scratchImg = &scratchImg;
	proTexture.texBuff = texbuff;
	texture.emplace_back(proTexture);
	descriptorHeadMgrIndex.emplace_back(-1);

	//�f�B�X�N���v�^�q�[�v�̃A�h���X���擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		srvDescHeap->GetCPUDescriptorHandleForHeapStart(), texture.size() - 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//�V�F�[�_�[���\�[�X�r���[�̐���
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//�q�[�v�ɃV�F�[�_�[���\�[�X�r���[����
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	return texture.at(texture.size() - 1).IDNum;
}

int TextureManager::LoadTextureInDescriptorHeapMgr(LPCWSTR fileName)
{
	//�t�@�C�������[�h�ς݂����`�F�b�N
	if (texture.size() > 0) {
		for (int i = 0; i < texture.size(); ++i) {
			//���[�h���Ă������环�ʔԍ���Ԃ�
			if (texture.at(i).fileName == fileName) {
				return descriptorHeadMgrIndex[i];
			}
		}
	}

	// �e�N�X�`���f�[�^��ۑ�
	Texture tex
	{};
	tex.fileName = fileName;

	//���[�h���Ă��Ȃ������烍�[�h����
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImg;
	HRESULT result = LoadFromWICFile(
		fileName,
		DirectX::WIC_FLAGS::WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	const DirectX::Image* img = scratchImg.GetImage(0, 0, 0);

	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//�e�N�X�`���o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	result = DirectXBase::Instance()->dev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texbuff));

	//�f�[�^�]��
	result = texbuff->WriteToSubresource(
		0,
		nullptr,							//�S�̈�R�s�[
		img->pixels,						//���f�[�^�̐擪�A�h���X
		(UINT)img->rowPitch,				//�ꃉ�C���̃T�C�Y
		(UINT)img->slicePitch				//�����܂��̃T�C�Y
	);

	//�e�N�X�`���z��̍Ō���Ƀ��[�h�����e�N�X�`�������L�^
	tex.IDNum = texture.size();
	tex.metadata = metadata;
	tex.scratchImg = &scratchImg;
	tex.texBuff = texbuff;
	texture.emplace_back(tex);
	descriptorHeadMgrIndex.emplace_back(DescriptorHeapManager::Instance()->GetHead());

	//�f�B�X�N���v�^�q�[�v�̃A�h���X���擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		DescriptorHeapManager::Instance()->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), DescriptorHeapManager::Instance()->GetHead(), DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//�V�F�[�_�[���\�[�X�r���[�̐���
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//�q�[�v�ɃV�F�[�_�[���\�[�X�r���[����
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	// �f�B�X�N���v�^�q�[�v���C���N�������g
	DescriptorHeapManager::Instance()->IncrementHead();

	return DescriptorHeapManager::Instance()->GetHead() - 1;
}

int TextureManager::CreateTexture(DirectX::XMFLOAT4 color)
{
	//�����F�̃e�N�X�`�������łɐ����ς݂����`�F�b�N����
	for (int i = 0; i < texture.size(); ++i) {
		if (texture.at(i).fileName == L"selfTexture" && texture.at(i).colorData.x == color.x && texture.at(i).colorData.y == color.y &&
			texture.at(i).colorData.z == color.z && texture.at(i).colorData.w == color.w) {
			//���łɐ������Ă���e�N�X�`���Ȃ̂�SRV�q�[�v�̔ԍ���Ԃ�
			return i;
		}
	}

	//�摜�f�[�^���쐬����
	const int texWidth = 256;
	const int imageDataCount = texWidth * texWidth;
	//�摜�C���[�W�f�[�^�z��
	DirectX::XMFLOAT4* imageData = new DirectX::XMFLOAT4[imageDataCount];

	//�S�s�N�Z���̐F��������
	for (int i = 0; i < imageDataCount; ++i) {
		imageData[i].x = color.x;
		imageData[i].y = color.y;
		imageData[i].z = color.z;
		imageData[i].w = color.w;
	}

	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		texWidth,
		(UINT)texWidth,
		(UINT16)1,
		(UINT16)1);

	//�e�N�X�`���o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texbuff));

	//�f�[�^�]��
	result = texbuff->WriteToSubresource(
		0,
		nullptr,							//�S�̈�R�s�[
		imageData,							//���f�[�^�̐擪�A�h���X
		sizeof(DirectX::XMFLOAT4) * texWidth,		//�ꃉ�C���̃T�C�Y
		sizeof(DirectX::XMFLOAT4) * imageDataCount	//�����܂��̃T�C�Y
	);

	//�e�N�X�`���z��̍Ō���Ƀ��[�h�����e�N�X�`�������L�^
	Texture proTexture{};
	proTexture.fileName = L"selfTexture";
	proTexture.IDNum = texture.size();
	proTexture.metadata = {};
	proTexture.scratchImg = {};
	proTexture.texBuff = texbuff;
	proTexture.colorData = color;
	texture.push_back(proTexture);

	//�f�B�X�N���v�^�q�[�v�̃A�h���X���擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		srvDescHeap->GetCPUDescriptorHandleForHeapStart(), texture.size() - 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//�V�F�[�_�[���\�[�X�r���[�̐���
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//�q�[�v�ɃV�F�[�_�[���\�[�X�r���[����
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	delete[] imageData;

	return texture.at(texture.size() - 1).IDNum;
}

int TextureManager::CreateRenderTargetTexture(int width, int height, int mipLevel, int arraySize, DXGI_FORMAT format, float clearColor[4])
{
	//�摜�f�[�^���쐬����
	const int texWidth = width;
	const int texHeight = height;
	const int imageDataCount = texWidth * texHeight;
	//�摜�C���[�W�f�[�^�z��
	DirectX::XMFLOAT4* imageData = new DirectX::XMFLOAT4[imageDataCount];

	//�S�s�N�Z���̐F��������
	for (int i = 0; i < imageDataCount; ++i) {
		imageData[i].x = 0;
		imageData[i].y = 0;
		imageData[i].z = 0;
		imageData[i].w = 0;
	}

	////���\�[�X�ݒ�
	//CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
	//	DXGI_FORMAT_R32G32B32A32_FLOAT,
	//	texWidth,
	//	(UINT)texHeight,
	//	(UINT16)1,
	//	(UINT16)1);

	CD3DX12_RESOURCE_DESC desc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<UINT>(width),
		static_cast<UINT>(height),
		arraySize,
		mipLevel,
		format,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	D3D12_CLEAR_VALUE clearValue;
	clearValue.Format = format;
	if (clearColor != nullptr) {
		clearValue.Color[0] = clearColor[0];
		clearValue.Color[1] = clearColor[1];
		clearValue.Color[2] = clearColor[2];
		clearValue.Color[3] = clearColor[3];
	}
	else {
		clearValue.Color[0] = 0.0f;
		clearValue.Color[1] = 0.0f;
		clearValue.Color[2] = 0.0f;
		clearValue.Color[3] = 1.0f;
	}

	//�e�N�X�`���o�b�t�@�̐���
	auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_COMMON,
		&clearValue,
		IID_PPV_ARGS(&texbuff)
	);

	//�f�[�^�]��
	//result = texbuff->WriteToSubresource(
	//	0,
	//	nullptr,							//�S�̈�R�s�[
	//	imageData,							//���f�[�^�̐擪�A�h���X
	//	sizeof(XMFLOAT4) * texWidth,		//�ꃉ�C���̃T�C�Y
	//	sizeof(XMFLOAT4) * imageDataCount	//�����܂��̃T�C�Y
	//);

	//�e�N�X�`���z��̍Ō���Ƀ��[�h�����e�N�X�`�������L�^
	Texture proTexture{};
	proTexture.fileName = L"selfTexture";
	proTexture.IDNum = texture.size();
	proTexture.metadata = {};
	proTexture.scratchImg = {};
	proTexture.texBuff = texbuff;
	proTexture.colorData = {};
	texture.push_back(proTexture);

	//�f�B�X�N���v�^�q�[�v�̃A�h���X���擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		srvDescHeap->GetCPUDescriptorHandleForHeapStart(), texture.size() - 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//�V�F�[�_�[���\�[�X�r���[�̐���
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = mipLevel;
	//�q�[�v�ɃV�F�[�_�[���\�[�X�r���[����
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	delete[] imageData;

	return texture.at(texture.size() - 1).IDNum;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetSRV(int IDNum) {
	D3D12_GPU_DESCRIPTOR_HANDLE basicHeapHandle = srvDescHeap->GetGPUDescriptorHandleForHeapStart();
	//������������A�h���X�����炷
	for (int i = 0; i < IDNum; ++i) {
		basicHeapHandle.ptr += DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}
	return basicHeapHandle;
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> TextureManager::GetDescHeap()
{
	return srvDescHeap;
}

Texture TextureManager::GetTexture(int ID)
{
	return texture.at(ID);
}
