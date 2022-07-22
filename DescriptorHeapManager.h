#pragma once
#include "DirectXBase.h"
#include "Singleton.h"

class DescriptorHeapManager : public Singleton<DescriptorHeapManager>
{
private:

	/*----- �����o�ϐ� -----*/

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;	//CBV,SRV,UAV�p�f�B�X�N���v�^�q�[�v
	int head;										//�擪�̃C���f�b�N�X

	/*----- �萔 -----*/

	const int CBV_SRV_UAV_COUNT = 256;	//CBV,SRV,UAV�p�f�B�X�N���v�^�̐�


public:

	/*----- �����o�֐� -----*/

	//�f�B�X�N���v�^�q�[�v�̐����B
	void GenerateDescriptorHeap() {

		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			// �V�F�[�_�[���猩����
		descHeapDesc.NumDescriptors = CBV_SRV_UAV_COUNT;
		
		//�f�B�X�N���v�^�q�[�v�̐����B
		HRESULT resultBuff = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descriptorHeap));

		//�擪��������
		head = 0;
	}


	//�f�B�X�N���v�^�q�[�v�̃Q�b�^�B
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() { return descriptorHeap; }

	//�擪�̃Q�b�^
	const int& GetHead() { return head; }

	//�擪���C���N�������g
	inline void IncrementHead() { ++head; }

	//�w��̃C���f�b�N�X��CPU�n���h�����擾
	CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPUHandleIncrement(const int& index) {

		return CD3DX12_GPU_DESCRIPTOR_HANDLE(
			descriptorHeap.Get()->GetGPUDescriptorHandleForHeapStart(), index, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

	}
};