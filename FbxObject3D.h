#pragma once
#include"FbxModel.h"
#include"Camera.h"

class FbxObject3d
{
public://�T�u�N���X�i�萔�o�b�t�@�j
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};

public://�萔
	//�{�[���̍ő吔
	static const int MAX_BONES = 32;

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

protected://�����o�ϐ�
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuffTransform;

	//�萔�o�b�t�@(�X�L��)
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffSkin;

private:
	//ID3D12�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D12Device> dev;
	//���[�g�V�O�l�`��
	static Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelinestate;

	//���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	//���[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	//���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	//���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	FbxModel* model = nullptr;

	//�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;




public://�����o�֐�
	//������
	void Init();

	//�O���t�B�b�N�X�p�C�v���C���̐ݒ�
	static void CreateGraphicsPipeline();

	//���t���[������
	void Update();

	//�`��
	void Draw();

	//���f���̃Z�b�g
	void SetModel(FbxModel* model) { this->model = model; }

	//setter
	static void SetDevice(Microsoft::WRL::ComPtr<ID3D12Device> dev) { FbxObject3d::dev = dev; }

	//�A�j���[�V�����J�n
	void PlayAnimation();

	//�Q�b�^
	XMFLOAT3& GetPosition() { return position; }

	void SetPosition(const XMFLOAT3& pos) { position = pos; }
};