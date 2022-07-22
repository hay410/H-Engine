#include "GaussianSprite.h"
#include "TextureManager.h"
#include "DirectXBase.h"
#include "struct.h"

void GaussianSprite::CommonGenerate(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID)
{
	//�p�C�v�����̖��O�̕ۑ�
	this->pipelineID = piplineID;

	//�ݒ�\����
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//�V�F�[�_�[���猩����
	descHeapDesc.NumDescriptors = 2;										//CBV2��
	//�f�B�X�N���v�^�q�[�v�̐���
	DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&constDescHeap));

	//���_�o�b�t�@�̐���
	Vertex vertexBuff;
	vertexBuff.pos = XMFLOAT3(-size.x, size.y, 10);		//����
	vertexBuff.uv = XMFLOAT2(0, 1);
	vertex.push_back(vertexBuff);
	vertexBuff.pos = XMFLOAT3(-size.x, -size.y, 10);	//����
	vertexBuff.uv = XMFLOAT2(0, 0);
	vertex.push_back(vertexBuff);
	vertexBuff.pos = XMFLOAT3(size.x, size.y, 10);		//�E��
	vertexBuff.uv = XMFLOAT2(1, 1);
	vertex.push_back(vertexBuff);
	vertexBuff.pos = XMFLOAT3(size.x, -size.y, 10);		//�E��
	vertexBuff.uv = XMFLOAT2(1, 0);
	vertex.push_back(vertexBuff);

	//���_�o�b�t�@�r���[�̐���
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(vertex.size() * sizeof(Vertex)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);

	//���_�o�b�t�@�r���[�̐ݒ�
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = vertex.size() * sizeof(Vertex);
	vbView.StrideInBytes = sizeof(Vertex);

	/*-----�萔�o�b�t�@�̐���-----*/
	result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0)
	);
	result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataMultiPath) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB1)
	);

	//�s���������
	projectionID = projectionID;
	rotationMat = XMMatrixIdentity();
	scaleMat = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	positionMat = XMMatrixTranslation(centerPos.x, centerPos.y, centerPos.z);
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);

	//�}�b�v�������s��
	Vertex* vertMap = nullptr;
	vertBuff->Map(0, nullptr, (void**)&vertMap);
	// �S���_�ɑ΂���
	for (int i = 0; i < vertex.size(); ++i)
	{
		vertMap[i] = vertex.at(i);   // ���W���R�s�[
	}
	// �}�b�v������
	vertBuff->Unmap(0, nullptr);

	/*-----CBV�f�B�X�N���v�^�q�[�v�̐��� �萔�o�b�t�@�̏���GPU�ɓ`���邽�߂̒萔�o�b�t�@�r���[�p-----*/
	//CBV�f�B�X�N���v�^�q�[�v�̐擪�A�h���X���擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = constBuffB0->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuffB0->GetDesc().Width;
	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
	//�Q�ڂ𐶐�
	basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		constDescHeap->GetCPUDescriptorHandleForHeapStart(), 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	cbvDesc.BufferLocation = constBuffB1->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuffB1->GetDesc().Width;
	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
}

void GaussianSprite::GenerateForTexture(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, LPCWSTR fileName)
{
	// �e�N�X�`�������[�h
	textureID.push_back(TextureManager::Instance()->LoadTexture(fileName));

	// ����������
	CommonGenerate(centerPos, size, projectionID, piplineID);
}

void GaussianSprite::GenerateForColor(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, XMFLOAT4 color)
{
	// �e�N�X�`�������[�h
	textureID.push_back(TextureManager::Instance()->CreateTexture(color));

	// ����������
	CommonGenerate(centerPos, size, projectionID, piplineID);
}

void GaussianSprite::GenerateSpecifyTextureID(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, int textureID)
{
	// �e�N�X�`�������[�h
	this->textureID.push_back(textureID);

	// ����������
	CommonGenerate(centerPos, size, projectionID, piplineID);
}

void GaussianSprite::Draw()
{
	// ��\����Ԃ�������`�揈�����s��Ȃ�
	if (isDisplay == false) return;

	// �p�C�v���C���ƃ��[�g�V�O�l�`���̐ݒ�
	PipelineManager::Instance()->SetPipeline(pipelineID);

	// �萔�o�b�t�@B0�\���̂��}�b�v����
	MapConstDataB0(constBuffB0, constBufferDataB0);

	// �萔�o�b�t�@1�ւ̃f�[�^�]��
	ConstBufferDataMultiPath* constMap2 = nullptr;
	HRESULT result = constBuffB1->Map(0, nullptr, (void**)&constMap2);
	//constBufferDataB1.gaussianWeight[0] = {};
	//constBufferDataB1.gaussianWeight[1] = {};
	constMap2->gaussianWeight[0] = constBufferDataB1.gaussianWeight[0];
	constMap2->gaussianWeight[1] = constBufferDataB1.gaussianWeight[1];
	constBuffB1->Unmap(0, nullptr);

	// ���W��ۑ����Ă���
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);

	// �萔�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());

	// �f�B�X�N���v�^�q�[�v�ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps2[] = { TextureManager::Instance()->GetDescHeap().Get() };
	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps2), ppHeaps2);

	// �V�F�[�_�[���\�[�X�r���[�ݒ�R�}���h
	for (int i = 0; i < textureID.size(); ++i) {
		DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(i + 2, TextureManager::Instance()->GetSRV(textureID[i]));
	}

	// ���_�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &vbView);

	// �`��R�}���h
	DirectXBase::Instance()->cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	DirectXBase::Instance()->cmdList->DrawInstanced(vertex.size(), 1, 0, 0);
}

void GaussianSprite::ChangeConstBufferDataB1(vector<float> amount)
{
	constBufferDataB1.gaussianWeight[0] = { amount[0],amount[1],amount[2],amount[3] };
	constBufferDataB1.gaussianWeight[1] = { amount[4],amount[5],amount[6],amount[7] };
}
