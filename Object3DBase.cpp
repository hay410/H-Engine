#include "Object3DBase.h"
#include "DirectXBase.h"

void Object3DBase::MapVertexData()
{
	Vertex* vertMap = nullptr;
	vertBuff->Map(0, nullptr, (void**)&vertMap);
	// �S���_�ɑ΂���
	for (int i = 0; i < vertex.size(); ++i)
	{
		vertMap[i] = vertex.at(i);   // ���W���R�s�[
	}
	// �}�b�v������
	vertBuff->Unmap(0, nullptr);
}

short Object3DBase::AddConstBuffer(const int& dataSize, const string& structName)
{

	/*-- �萔�o�b�t�@��ǉ����� --*/

	// �Ō���Ƀf�[�^��ǉ��B
	constBufferData.push_back(Microsoft::WRL::ComPtr<ID3D12Resource>());

	// ���O�f�[�^��ۑ��B
	constBufferDataName.push_back(structName);

	// �Ō���ɒǉ����ꂽ�f�[�^�ɒl������B
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((dataSize + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBufferData[constBufferData.size() - 1])
	);

	int offset = isLighting ? 2 : 0;
	// �萔�o�b�t�@�r���[�ɃZ�b�g
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		constDescHeap->GetCPUDescriptorHandleForHeapStart(), offset + constBufferData.size(), DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = constBufferData[constBufferData.size() - 1]->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBufferData[constBufferData.size() - 1]->GetDesc().Width;
	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	return constBufferData.size() - 1;
}

bool Object3DBase::TransData(const short& handle, const void* data, const int& dataSize, const string& structName)
{

	/*-- �ǉ����ꂽ�萔�o�b�t�@�̓]������ --*/

	// �z��O�A�N�Z�X��j�~����B
	if (handle >= constBufferData.size() || handle < 0) assert(0);

	// �ۑ����ꂽ���O�Ǝ󂯎�������O���Ⴉ�����珈�����s��Ȃ��B
	if (constBufferDataName[handle] != structName) assert(0);

	// �����܂ŗ�����]���������s���B
	void* constMap = nullptr;
	HRESULT result = constBufferData[handle]->Map(0, nullptr, (void**)&constMap);

	if (result == S_OK) {

		memcpy(constMap, data, dataSize);

	}

	constBufferData[handle]->Unmap(0, nullptr);

	if (result == S_OK) {

		return true;

	}
	else {

		return false;

	}

}
