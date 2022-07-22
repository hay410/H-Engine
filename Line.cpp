#include "Line.h"
#include "DirectXBase.h"
#include "TextureManager.h"
#include "Camera.h"

void Line::Generate(const XMFLOAT3& pos1, const XMFLOAT3& pos2, const XMFLOAT4& color, int projectionID, int piplineID)
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

	//�e�N�X�`�������[�h
	textureID.push_back(TextureManager::Instance()->CreateTexture(color));

	//���_�o�b�t�@�̐���
	Vertex vertexBuff;
	vertexBuff.pos = pos1;	//����
	vertexBuff.uv = XMFLOAT2(0, 0);
	vertex.push_back(vertexBuff);
	vertexBuff.pos = pos2;		//����
	vertexBuff.uv = XMFLOAT2(0, 0);
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

	//�s���������
	this->projectionID = projectionID;
	rotationMat = XMMatrixIdentity();
	scaleMat = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	positionMat = XMMatrixIdentity();
	this->pos1 = pos1;
	this->pos2 = pos2;

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

}

void Line::Draw()
{
	//��\����Ԃ�������`�揈�����s��Ȃ�
	if (isDisplay == false) return;

	//�p�C�v���C���ƃ��[�g�V�O�l�`���̐ݒ�
	PipelineManager::Instance()->SetPipeline(pipelineID);

	// �萔�o�b�t�@B0�\���̂��}�b�v����
	MapConstDataB0(constBuffB0, constBufferDataB0);

	//�萔�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	//�f�B�X�N���v�^�q�[�v�ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps2[] = { TextureManager::Instance()->GetDescHeap().Get() };
	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps2), ppHeaps2);
	//�V�F�[�_�[���\�[�X�r���[�ݒ�R�}���h
	for (int i = 0; i < textureID.size(); ++i) {
		DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(i + 1, TextureManager::Instance()->GetSRV(textureID[0]));
	}

	//���_�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�`��R�}���h
	//DirectXBase::cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);		//�����̈�����ς��邱�ƂŒ��_�𗘗p���Ăǂ�Ȑ}�`��`������ݒ�ł��� ����3_3
	DirectXBase::Instance()->cmdList->DrawInstanced(vertex.size(), 1, 0, 0);
}

void Line::ChangeVertexPos(const XMFLOAT3& pos1, const XMFLOAT3& pos2)
{
	vertex[0].pos = pos1;
	vertex[1].pos = pos2;

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

	this->pos1 = pos1;
	this->pos2 = pos2;
}
