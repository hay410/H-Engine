#pragma once
#include"struct.h"
#include"fbxsdk.h"
#include<DirectXTex.h>

class FbxModel
{
public://�萔
	//�{�[���C���f�b�N�X�̍ő�
	static const int MAX_BONE_INDICES = 4;

	//�t�����h�N���X
	friend class FbxModelLoader;

	struct VertexFbx
	{
		XMFLOAT3 pos;		//���W
		XMFLOAT3 normal;	//�@��
		XMFLOAT2 uv;		//uv���W
		UINT boneIndex[MAX_BONE_INDICES];
		float boneWeight[MAX_BONE_INDICES];
	};

	//�{�[���\����
	struct Bone
	{
		//���O
		string name;
		//�����p���̋t�s��
		XMMATRIX invInitialPose;
		//�N���X�^�[
		FbxCluster* fbxCluster;
		//�R���X�g���N�^
		Bone(const string& name) {
			this->name = name;
		}

	};


private:
	//���f����
	string name;
	//�m�[�h�z��
	vector<Node> nodes;

	//���b�V�������m�[�h
	Node* meshNode = nullptr;

	//Fbx�V�[��
	FbxScene* fbxScene = nullptr;

	//���_�ۑ���̃I�u�W�F�N�g
	//Object3D objectBuff;

	//���_�f�[�^�z��
	vector<VertexFbx> vertices;
	//�C���f�b�N�X�z��
	vector<unsigned short>indices;
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};


	//�A���r�G���g�W��
	XMFLOAT3 ambient = { 1,1,1 };
	//�f�B�t���[�Y�W��
	XMFLOAT3 diffuse = { 1,1,1 };
	//�e�N�X�`�����^�f�[�^
	TexMetadata metadata = {};
	//�X�N���b�`�C���[�W
	ScratchImage scratchImg = {};

	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;

	//SRV�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	//�{�[���z��
	vector<Bone> bones;

	//�o�b�t�@����
	void CreateBuffers(ComPtr<ID3D12Device>);
public:
	//�f�X�g���N�^
	~FbxModel();

	//�`��
	void Draw();

	//���f���̕ό`�s��擾
	const XMMATRIX& GetModelTransform() { return meshNode->globalTransform; }

	vector<Bone>& GetBones() { return bones; }

	FbxScene* GetFbxScene() { return fbxScene; }
};