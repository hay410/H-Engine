#pragma once
#include "DirectXBase.h"

class RenderTarget {
public:
	int textureID = 0;
	ComPtr<ID3D12Resource> renderTargetTexture = nullptr;		//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ComPtr<ID3D12Resource> depthStencilTexture = nullptr;		//�[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`���B
	ComPtr<ID3D12DescriptorHeap> rtvHeap = nullptr;				//�����_�[�^�[�Q�b�g�r���[�p�̃f�B�X�N���v�^�q�[�v�B
	ComPtr<ID3D12DescriptorHeap> dsvHeap = nullptr;				//�[�x�X�e���V���o�b�t�@�r���[�̃f�B�X�N���v�^�q�[�v�B
	UINT rtvDescriptorSize = 0;									//�t���[���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
	UINT dsvDescriptorSize = 0;									//�[�x�X�e���V���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
	int width = 0;												//�����_�[�^�[�Q�b�g�̕��B
	int height = 0;												//�����_�[�^�[�Q�b�g�̍����B
	float rtvClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };		//�����_�[�^�[�Q�b�g�r���[�̃N���A�J���[�B
	float dsvClearColor = 1.0f;									//DSV�̃N���A�J���[�B

	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~RenderTarget() {};

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̍쐬�B
	/// </summary>
	/// <param name="w">�����_�[�^�[�Q�b�g�̕�</param>
	/// <param name="h">�����_�[�^�[�Q�b�g�̍���</param>
	/// <param name="mipLevel">�~�b�v�}�b�v���x���B0���w�肵���ꍇ�̓~�b�v�}�b�v���T�|�[�g����Ă���GPU�ł�1*1�s�N�Z���܂ł̃~�b�v�}�b�v���쐬�����B</param>
	/// <param name="arraySize">�e�N�X�`���z��̃T�C�Y</param>
	/// <param name="colorFormat">�J���[�o�b�t�@�̃t�H�[�}�b�g�B</param>
	/// <param name="depthStencilFormat">�[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B</param>
	/// <returns>true���Ԃ��Ă�����쐬����</returns>
	bool Create(
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat,
		float clearColor[4] = nullptr
	);

	/// <summary>
	/// �f�B�X�N���v�^�q�[�v���쐬�B
	/// </summary>
	/// <returns></returns>
	bool CreateDescriptorHeap();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬�B
	/// </summary>
	/// <param name="w">�e�N�X�`���̕�</param>
	/// <param name="h">�e�N�X�`���̍���</param>
	/// <param name="mipLevel">�~�b�v�}�b�v���x��</param>
	/// <param name="arraySize">�e�N�X�`���z��̃T�C�Y</param>
	/// <param name="format">�e�N�X�`���̃t�H�[�}�b�g</param>
	/// <returns>true���Ԃ��Ă����琬���B</returns>
	bool CreateRenderTargetTexture(
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT format,
		float clearColor[4]
	);

	/// <summary>
	/// �[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`�����쐬�B
	/// </summary>
	/// <param name="w">�e�N�X�`���̕�</param>
	/// <param name="h">�e�N�X�`���̍���</param>
	/// <param name="format">�e�N�X�`���̃t�H�[�}�b�g</param>
	/// <returns>true���Ԃ��Ă����琬��</returns>
	bool CreateDepthStencilTexture(
		int w,
		int h,
		DXGI_FORMAT format);

	/// <summary>
	/// �f�B�X�N���v�^�̍쐬�B
	/// </summary>
	/// <param name="d3dDevice">D3D�f�o�C�X</param>
	/// <returns>true���Ԃ��Ă����琬���B</returns>
	void CreateDescriptor();

	//�[�x�o�b�t�@�������Ă��邩 �����Ă�����true
	bool HasDepthStencil() { return depthStencilTexture != nullptr; }
};
