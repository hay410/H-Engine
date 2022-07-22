#pragma once
#include"fbxsdk.h"
#include"struct.h"
#include"FbxModel.h"
#include"Singleton.h"

class FbxModelLoader :public Singleton<FbxModelLoader>
{
public:
	//�����o�萔
	static const string baseDirectory;

	//�����o�ϐ�
	
	//D3D12�f�o�C�X
	ComPtr<ID3D12Device> dev;

	//FBX�}�l�[�W���[
	FbxManager* fbxManager = nullptr;

	//FBX�C���|�[�^�[
	FbxImporter* fbxImporter = nullptr;

	//�e�N�X�`�����Ȃ��ꍇ�̕W���e�N�X�`���t�@�C����
	static const string defaultTextureFileName;

	//�����o�֐�
	//�R���X�g���N�^
	FbxModelLoader();
	friend Singleton<FbxModelLoader>;

	//������
	void Init(ComPtr<ID3D12Device> dev);

	//�I������
	void Fainalize();

	//�t�@�C�������烂�f����ǂݍ���
	FbxModel* LoadModelFromFile(const string& modelName);

	//�ċA�I�Ƀm�[�h�U�������
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent = nullptr);

	//���b�V���ǂݍ���
	void ParseMesh(FbxModel* model, FbxNode* fbxNode);

	//���_���ǂݎ��
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh);
	
	//�ʏ��ǂݎ��
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh);

	//�}�e���A���ǂݍ���
	void ParseMaterial(FbxModel* model, FbxNode* fbxNode);
	//�X�L�j���O���ǂݎ��
	void ParceSkin(FbxModel* model, FbxMesh* fbxMesh);

	//�e�N�X�`���ǂݎ��
	void LoadTexture(FbxModel* model, string& fileName);

	//�f�B���N�g�����܂񂾃t�@�C���p�X����t�@�C�����𒊏o����
	string ExtractFileName(const string& path);

	//FBX�̍s���XMMATRIX�ɕϊ�
	static void ConvertMatrixFromFbx(XMMATRIX* dst, const FbxAMatrix& src);

};