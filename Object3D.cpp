#include "Object3D.h"
#include "TextureManager.h"
#include "ModelLoader.h"
#include "Enum.h"
#include "Camera.h"
#include "LightManager.h"
#include "DirectXBase.h"

void Object3D::Generate(XMFLOAT3 centerPos, int projectionID, int pipelineID, string modelName, wchar_t* textureFileName, bool isSmoothing)
{
	// �e�ϐ���������
	isAlreadyMapB1 = false;

	// �p�C�v�����̖��O�̕ۑ�
	this->pipelineID = pipelineID;

	// �p�C�v���C����ID�ɂ���ă��C�e�B���O�̃}�b�v�������s�����ǂ����̃t���O���X�V����B
	if (pipelineID == PIPELINE_OBJECT_LIGHT_ALPHA ||
		pipelineID == PIPELINE_OBJECT_NOLIGHT_ALPHA ||
		pipelineID == PIPELINE_OBJECT_TOONSHADER_ALPHA) {

		// ���C�e�B���O��������B�萔�o�b�t�@b1b2�𑗂�B
		isLighting = true;

	}
	else {

		// ���C�e�B���O�������Ȃ��B
		isLighting = false;

	}

	// �ݒ�\����
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			// �V�F�[�_�[���猩����
	descHeapDesc.NumDescriptors = 32;										// CBV3��
	// �f�B�X�N���v�^�q�[�v�̐���
	HRESULT resultBuff = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&constDescHeap));

	////string directoryTextureFileName = directoryPath + modelName + "/" + textureFileName;
	//wchar_t* LdirectoryTextureFileName = LdirectoryPath;
	//wcscat_s(*LdirectoryTextureFileName, sizeof(LdirectoryTextureFileName), textureFileName);
	////ConvertStringToWchar_t(directoryTextureFileName, LdirectoryTextureFileName, 100);

	// �e�N�X�`�������[�h
	textureID.push_back(TextureManager::Instance()->LoadTexture(textureFileName));

	// obj�t�@�C�������[�h
	string modelFileName = modelName + "/" + modelName + ".obj";

	ObjectData objectDataBuffer;
	ModelLoader::LoadObj(directoryPath, modelFileName, objectDataBuffer, isSmoothing);

	// ���[�h�������_�f�[�^����
	int vertexSize = objectDataBuffer.vertex.size();
	DrawDataBase::Vertex vertDeliveryDataBuffer;
	for (int i = 0; i < vertexSize; ++i) {
		vertDeliveryDataBuffer.normal = objectDataBuffer.vertex[i].normal;
		vertDeliveryDataBuffer.pos = objectDataBuffer.vertex[i].pos;
		vertDeliveryDataBuffer.uv = objectDataBuffer.vertex[i].uv;
		vertex.push_back(vertDeliveryDataBuffer);
	}

	// ���[�h�������_�C���f�b�N�X�f�[�^����
	int indexSize = objectDataBuffer.index.size();
	for (int i = 0; i < indexSize; ++i) {
		index.push_back(objectDataBuffer.index[i]);
	}

	// ���[�h�����}�e���A������
	constBufferDataB1 = objectDataBuffer.constBufferDataB1;

	// ���_�o�b�t�@�̐���
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(vertex.size() * sizeof(Vertex)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	// ���_�o�b�t�@�r���[�̐ݒ�
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = vertex.size() * sizeof(Vertex);
	vbView.StrideInBytes = sizeof(Vertex);

	/*-----���_�C���f�b�N�X�o�b�t�@�̐ݒ�-----*/
	result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(index.size() * sizeof(unsigned short)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	// ���_�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = index.size() * sizeof(unsigned short);

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
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB1)
	);
	result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB2) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB2)
	);

	// �s���������
	this->projectionID = projectionID;
	rotationMat = XMMatrixIdentity();
	scaleMat = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	positionMat = XMMatrixTranslation(centerPos.x, centerPos.y, centerPos.z);
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);

	// �}�b�v�������s��
	Vertex* vertMap = nullptr;
	vertBuff->Map(0, nullptr, (void**)&vertMap);
	// �S���_�ɑ΂���
	for (int i = 0; i < vertex.size(); ++i)
	{
		vertMap[i] = vertex.at(i);   //  ���W���R�s�[
	}
	// �}�b�v������
	vertBuff->Unmap(0, nullptr);

	// 3D�Œ��_�C���f�b�N�X������Ȃ�o�b�t�@�̃f�[�^�]�����s��
	if (index.size() > 0) {
		unsigned short* indexMap = nullptr;
		HRESULT result = indexBuff->Map(0, nullptr, (void**)&indexMap);
		for (int i = 0; i < index.size(); ++i) {
			indexMap[i] = index.at(i);
		}
		indexBuff->Unmap(0, nullptr);
	}

	/*-----CBV�f�B�X�N���v�^�q�[�v�̐��� �萔�o�b�t�@�̏���GPU�ɓ`���邽�߂̒萔�o�b�t�@�r���[�p-----*/
	// CBV�f�B�X�N���v�^�q�[�v�̐擪�A�h���X���擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = constBuffB0->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuffB0->GetDesc().Width;
	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		constDescHeap->GetCPUDescriptorHandleForHeapStart(), 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	cbvDesc.BufferLocation = constBuffB1->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuffB1->GetDesc().Width;
	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		constDescHeap->GetCPUDescriptorHandleForHeapStart(), 2, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	cbvDesc.BufferLocation = constBuffB2->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuffB2->GetDesc().Width;
	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	// �萔�o�b�t�@�ւ̃f�[�^�]��(�s��Ǝ��_���W�֌W)
	ConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	constMap->eye = Camera::Instance()->eye;
	constBuffB0->Unmap(0, nullptr);

	// ���C�e�B���O�����Ă��Ȃ���Ԃ������烉�C�e�B���O���s��Ȃ�
	if (isLighting) {

		// B1���܂��}�b�v�������Ă��Ȃ�������}�b�v�������s��
		if (!isAlreadyMapB1) {

			// �萔�o�b�t�@�ւ̃f�[�^�]��(�}�e���A���֌W)
			ConstBufferDataB1* constMap1 = nullptr;
			result = constBuffB1->Map(0, nullptr, (void**)&constMap1);
			// �]���������s���B
			memcpy(constMap1, &constBufferDataB1, sizeof(ConstBufferDataB1));

			// B1���}�b�v�����������Ƃ��L�^����
			isAlreadyMapB1 = true;

		}

		// �萔�o�b�t�@�ւ̃f�[�^�]��(���C�g�֌W)
		ConstBufferDataB2* constMap2 = nullptr;
		result = constBuffB2->Map(0, nullptr, (void**)&constMap2);
		for (int i = 0; i < DIRLIGHT_NUM; ++i) {
			constMap2->dirlights[i] = LightManager::Instance()->dirlights[i];
		}
		for (int i = 0; i < POINTLIGHT_NUM; ++i) {
			constMap2->pointlights[i] = LightManager::Instance()->pointlights[i];
		}
		for (int i = 0; i < SPOTLIGHT_NUM; ++i) {
			constMap2->spotlights[i] = LightManager::Instance()->spotlights[i];
		}
		constBuffB2->Unmap(0, nullptr);

	}

}

void Object3D::Draw()
{
	// ��\����Ԃ�������`�揈�����s��Ȃ�
	if (isDisplay == false) return;

	// �p�C�v���C���ƃ��[�g�V�O�l�`���̐ݒ�
	PipelineManager::Instance()->SetPipeline(pipelineID);

	// �萔�o�b�t�@b0�̃}�b�v�������s��
	MapConstDataB0(constBuffB0, constBufferDataB0);

	// ���C�e�B���O���s���ꍇ�̂݃}�b�v�������s��
	if (isLighting) {

		// B1���܂��}�b�v�������Ă��Ȃ�������}�b�v�������s��
		if (!isAlreadyMapB1) {

			// �萔�o�b�t�@b1�̃}�b�v�������s��
			ConstBufferDataB1* constMap1 = nullptr;
			HRESULT result = constBuffB1->Map(0, nullptr, (void**)&constMap1);

			// �]���������s���B
			memcpy(constMap1, &constBufferDataB1, sizeof(ConstBufferDataB1));

			constBuffB1->Unmap(0, nullptr);

			// B1���}�b�v�����������Ƃ��L�^����
			isAlreadyMapB1 = true;

		}

		// �萔�o�b�t�@b2�̃}�b�v�������s��
		ConstBufferDataB2* constMap2 = nullptr;
		HRESULT result = constBuffB2->Map(0, nullptr, (void**)&constMap2);

		for (int i = 0; i < DIRLIGHT_NUM; ++i) {
			constMap2->dirlights[i] = LightManager::Instance()->dirlights[i];
		}
		for (int i = 0; i < POINTLIGHT_NUM; ++i) {
			constMap2->pointlights[i] = LightManager::Instance()->pointlights[i];
		}
		for (int i = 0; i < SPOTLIGHT_NUM; ++i) {
			constMap2->spotlights[i] = LightManager::Instance()->spotlights[i];
		}

		constBuffB2->Unmap(0, nullptr);

	}

	// ���W��ۑ����Ă���
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);

	// �萔�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	// SRV�ɑ����I�t�Z�b�g�̒l���v�Z
	int offsetSRV = 0;

	// ���C�e�B���O���s��Ȃ��ꍇ�͒萔�o�b�t�@�r���[��ݒ肵�Ȃ�
	if (isLighting) {

		DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());
		DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(2, constBuffB2->GetGPUVirtualAddress());

		offsetSRV = 3;

	}
	else {

		offsetSRV = 1;

	}

	// �ǉ����ꂽ�萔�o�b�t�@�̐�
	const int ADD_CONSTBUFFER_AMOUNT = constBufferData.size();

	// �ǉ����ꂽ�萔�o�b�t�@���Z�b�g����B
	for (int index = 0; index < ADD_CONSTBUFFER_AMOUNT; ++index) {

		DirectXBase::Instance()->cmdList->SetGraphicsRootConstantBufferView(offsetSRV + index, constBufferData[index]->GetGPUVirtualAddress());

	}

	// �萔�o�b�t�@���ǉ�����Ă��镪�I�t�Z�b�g�����炷�B
	offsetSRV += ADD_CONSTBUFFER_AMOUNT;

	// �f�B�X�N���v�^�q�[�v�ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps2[] = { TextureManager::Instance()->GetDescHeap().Get() };
	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps2), ppHeaps2);
	// �V�F�[�_�[���\�[�X�r���[�ݒ�R�}���h
	for (int i = 0; i < textureID.size(); ++i) {
		DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(i + offsetSRV, TextureManager::Instance()->GetSRV(textureID[i]));
	}

	// ���_�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &vbView);

	// ���_�C���f�b�N�X�o�b�t�@�r���[�ݒ�R�}���h
	DirectXBase::Instance()->cmdList->IASetIndexBuffer(&ibView);

	// �`��R�}���h
	DirectXBase::Instance()->cmdList->DrawIndexedInstanced(index.size(), 1, 0, 0, 0);
}

void Object3D::SetPiplineID(int pipelineID)
{
	// �p�C�v���C����ID�ɂ���ă��C�e�B���O�̃}�b�v�������s�����ǂ����̃t���O���X�V����B
	if (pipelineID == PIPELINE_OBJECT_LIGHT_ALPHA ||
		pipelineID == PIPELINE_OBJECT_NOLIGHT_ALPHA ||
		pipelineID == PIPELINE_OBJECT_TOONSHADER_ALPHA) {

		// ���C�e�B���O��������B�萔�o�b�t�@b1b2�𑗂�B
		isLighting = true;

	}
	else {

		// ���C�e�B���O�������Ȃ��B
		isLighting = false;

	}

	// �p�C�v���C��ID���X�V
	this->pipelineID = pipelineID;

}
