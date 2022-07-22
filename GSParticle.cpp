#include "GSParticle.h"
#include "Camera.h"
#include "TextureManager.h"
#include "DirectXBase.h"

void GSParticle::CommonGenerate(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int pipelineID, int instanceCount)
{

	//�p�C�v�����̖��O�̕ۑ�
	this->pipelineID = pipelineID;

	//�ݒ�\����
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//�V�F�[�_�[���猩����
	descHeapDesc.NumDescriptors = 1;										//CBV1��
	//�f�B�X�N���v�^�q�[�v�̐���
	DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&constDescHeap));

	//���_�o�b�t�@�̐���
	vertex = {};

	//���_�o�b�t�@�r���[�̐���
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(XMFLOAT3)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);

	//���_�o�b�t�@�r���[�̐ݒ�
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(XMFLOAT3);
	vbView.StrideInBytes = sizeof(XMFLOAT3);

	/*-----�萔�o�b�t�@�̐���-----*/
	result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(GSConstBufferDataB0) * instanceCount + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0)
	);

	//�s���������
	rotationMat = XMMatrixIdentity();
	scaleMat = XMMatrixScaling(size.x, size.y, 1.0f);
	positionMat = XMMatrixTranslation(pos.x, pos.y, pos.z);

	//�}�b�v�������s��
	XMFLOAT3* vertMap = nullptr;
	vertBuff->Map(0, nullptr, (void**)&vertMap);
	vertMap = &vertex;		//���W���R�s�[
	//�}�b�v������
	vertBuff->Unmap(0, nullptr);

	//CBV�f�B�X�N���v�^�q�[�v�̐擪�A�h���X���擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = constBuffB0->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuffB0->GetDesc().Width;
	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	//�萔�o�b�t�@�ւ̃f�[�^�]��
	GSConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	XMMATRIX matWorld = XMMatrixIdentity();
	matWorld *= scaleMat;
	matWorld *= rotationMat;
	matWorld *= positionMat;
	constMap->mat = matWorld * Camera::Instance()->matView * Camera::Instance()->matPerspective;	//���[���h�ϊ� * �r���[�ϊ� * �������e�ϊ�
	constBuffB0->Unmap(0, nullptr);

}

void GSParticle::GenerateForTexture(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, LPCWSTR fileName, int instanceCount)
{

	// �e�N�X�`�������[�h
	textureID.push_back(TextureManager::Instance()->LoadTexture(fileName));

	// ���ʂ̐����������s��
	CommonGenerate(centerPos, size, projectionID, piplineID, instanceCount);
}

void GSParticle::GenerateForColor(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, XMFLOAT4 color, int instanceCount)
{
	// �e�N�X�`�������[�h
	textureID.push_back(TextureManager::Instance()->CreateTexture(color));

	// ���ʂ̐����������s��
	CommonGenerate(centerPos, size, projectionID, piplineID, instanceCount);
}

void GSParticle::GenerateSpecifyTextureID(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, int textureID, int instanceCount)
{
	// �e�N�X�`�������[�h
	this->textureID.push_back(textureID);

	// ���ʂ̐����������s��
	CommonGenerate(centerPos, size, projectionID, piplineID, instanceCount);
}

void GSParticle::Draw()
{
	//�p�C�v���C���ƃ��[�g�V�O�l�`���̐ݒ�
	PipelineManager::Instance()->SetPipeline(pipelineID);

	//�萔�o�b�t�@�ւ̃f�[�^�]��
	GSConstBufferDataB0* constMap = nullptr;
	HRESULT result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	//���[���h�s��̍X�V
	XMMATRIX matWorld = XMMatrixIdentity();
	matWorld *= scaleMat;
	matWorld *= rotationMat;
	matWorld *= positionMat;
	constMap->mat = matWorld * Camera::Instance()->matView * Camera::Instance()->matPerspective;		//���[���h�ϊ� * �r���[�ϊ� * �������e�ϊ�
	constMap->color = constBufferDataB0.color;
	constBuffB0->Unmap(0, nullptr);

	//�萔�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	//�f�B�X�N���v�^�q�[�v�ݒ�R�}���h		�X�v���C�g���e�N�X�`���̃f�[�^�������Ă����ꍇ�̂ݐݒ�R�}���h�����s����
	ID3D12DescriptorHeap* ppHeaps2[] = { TextureManager::Instance()->GetDescHeap().Get() };
	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps2), ppHeaps2);
	//�V�F�[�_�[���\�[�X�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(1, TextureManager::Instance()->GetSRV(textureID[0]));

	//���_�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�`��R�}���h
	DirectXBase::Instance()->cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	DirectXBase::Instance()->cmdList->DrawInstanced(1, 1, 0, 0);

}

void GSParticle::DrawInstance(vector<GSConstBufferDataB0> instanceData)
{
	int instanceCount = instanceData.size();

	//�p�C�v���C���ƃ��[�g�V�O�l�`���̐ݒ�
	PipelineManager::Instance()->SetPipeline(pipelineID);

	//�萔�o�b�t�@�ւ̃f�[�^�]��
	GSConstBufferDataB0* constMap = nullptr;
	HRESULT result = constBuffB0->Map(0, nullptr, (void**)&constMap);

	for (int index = 0; index < instanceCount; ++index) {

		//���[���h�s��̍X�V
		XMMATRIX matWorld = XMMatrixIdentity();
		matWorld *= scaleMat;
		matWorld *= rotationMat;
		matWorld *= positionMat;
		constMap[index].mat = instanceData[index].mat * Camera::Instance()->matView * Camera::Instance()->matPerspective;		//���[���h�ϊ� * �r���[�ϊ� * �������e�ϊ�
		constMap[index].color = instanceData[index].color;

	}

	constBuffB0->Unmap(0, nullptr);

	//�萔�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	//�f�B�X�N���v�^�q�[�v�ݒ�R�}���h		�X�v���C�g���e�N�X�`���̃f�[�^�������Ă����ꍇ�̂ݐݒ�R�}���h�����s����
	ID3D12DescriptorHeap* ppHeaps2[] = { TextureManager::Instance()->GetDescHeap().Get() };
	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps2), ppHeaps2);
	//�V�F�[�_�[���\�[�X�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(1, TextureManager::Instance()->GetSRV(textureID[0]));

	//���_�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�`��R�}���h
	DirectXBase::Instance()->cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	DirectXBase::Instance()->cmdList->DrawInstanced(1, instanceCount, 0, 0);

}
