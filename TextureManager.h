#pragma once
#include "Singleton.h"
#include <wrl/client.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <vector>
#include <DirectXTex.h>
#include "DescriptorHeapManager.h"


struct Texture {
	LPCWSTR fileName;				//�t�@�C����
	int IDNum;						//���ʔԍ�
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;	//�e�N�X�`���o�b�t�@
	//�ȉ��͕K���K�v�ł͂Ȃ�����������֗�
	DirectX::TexMetadata metadata;			//�摜�̃T�C�Y�ȂǁA�e�N�X�`���Ƃ��Ă̊e��񂪓���
	DirectX::ScratchImage* scratchImg;
	DirectX::Image* image;					//�r�b�g�}�b�v�`���ł̉摜�f�[�^�̂��̂��̂̃A�h���X������
	DirectX::XMFLOAT4 colorData;				//�F���w�肵�ăe�N�X�`���𐶐�����ہA���̃e�N�X�`�����ǂ̐F�Ȃ̂���n�����߂̕ϐ�
};

class TextureManager : public Singleton<TextureManager> {

private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescHeap;
	std::vector<Texture> texture;
	std::vector<int> descriptorHeadMgrIndex;		// DescriptorHeapMgr��ł̕ۑ���C���f�b�N�X�B
	//�R���X�g���N�^
	friend Singleton<TextureManager>;
	TextureManager();

public:
	//�摜�����[�h���Ď��ʔԍ���Ԃ��֐��A���[�h�ς݂������环�ʔԍ���Ԃ��B
	int LoadTexture(LPCWSTR fileName);
	//�摜�����[�h���Ď��ʔԍ���Ԃ��֐��A���[�h�ς݂������环�ʔԍ���Ԃ��B
	int LoadTextureInDescriptorHeapMgr(LPCWSTR fileName);
	//�摜�𐶐����Ď��ʔԍ���Ԃ��֐�
	int CreateTexture(DirectX::XMFLOAT4 color);
	//�����_�[�^�[�Q�b�g�p�̃e�N�X�`���𐶐����Ď��ʔԍ���Ԃ��֐�
	int CreateRenderTargetTexture(int width, int height, int mipLevel, int arraySize, DXGI_FORMAT format, float clearColor[4]);
	//���ʔԍ��̏��Ԃ̃V�F�[�_�[���\�[�X�r���[��Ԃ��B
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRV(int IDNum);
	//�f�B�X�N���v�^�q�[�v��Ԃ��B
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDescHeap();
	//�w��̔ԍ��̃e�N�X�`����Ԃ��B
	Texture GetTexture(int ID);

};