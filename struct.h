#pragma once

#include <string>
#include <DirectXMath.h>
#include <vector>
#include <xaudio2.h>
#include <wrl.h>
#include <d3d12.h>
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_dx12.h"
//#include "imgui/imgui_impl_win32.h"

#pragma comment(lib,"xaudio2.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

#define SUBONE(x) x - 1

//#define GetRand(x) (float)(rand() % (x + 1)) - (x / 2.0f)
//#define GetRandPlus(x) (float)(rand() % (x + 1))

#pragma comment(lib,"winmm.lib")

//�C���X�^���V���O�`�������ۂ̍ő吔
const int INSTANCE_COUNT = 600;

//���_�f�[�^�\����
struct Vertex {
	XMFLOAT3 pos;			//xyz���W
	XMFLOAT3 normal;		//�@��
	XMFLOAT2 uv;			//uv���W
};

//�V�F�[�_�[���ɓn�����߂̍s��f�[�^
struct MatrixData {
	XMMATRIX world;			//��]��������ړ��������肷��s��
	XMMATRIX viewproj;		//�r���[�ƃv���W�F�N�V���������s��
};

//�萔�o�b�t�@�\����b0
struct ConstBufferDataB0 {
	MatrixData mat;			//�s��
	XMFLOAT4 color = { 1,1,1,1 };			//�F�f�[�^
	XMFLOAT3 eye;			//�J�������W
	float pad1;
};
struct GSConstBufferDataB0 {
	XMMATRIX world;			//��]��������ړ��������肷��s��
	XMFLOAT4 color = { 1,1,1,1 };			//�F�f�[�^
};
//�萔�o�b�t�@�\����b1
struct ConstBufferDataB1 {
	XMFLOAT3 ambient;		//�A���r�G���g�W��
	float pad1;				//�p�f�B���O
	XMFLOAT3 diffuse;		//�f�B�t���[�Y�W��
	float pad2;				//�p�f�B���O
	XMFLOAT3 specular;		//�X�y�L�����[�W��
	float alpha;			//�A���t�@
	XMFLOAT3 pad3;			//�p�f�B���O
};

/*-----���C�g�֌W-----*/
//�e���C�g�̐�
const int POINTLIGHT_NUM = 120;
const int DIRLIGHT_NUM = 1;
const int SPOTLIGHT_NUM = 1;
const int CIRCLESHADOW_NUM = 120;
//�_�����p�̍\����
struct PointLightData {
	XMFLOAT3 lightpos;				//���C�g���W
	float pad1;
	XMFLOAT3 lightcolor;			//���C�g�F
	float pad2;
	XMFLOAT3 lightatten;			//���C�g���������W��
	unsigned int active = 0;		//�A�N�e�B�u�t���O
};
//�ʌ����p�̍\����
struct DirLightData {
	XMFLOAT3 lightvec;				//���C�g�̕����x�N�g��
	float pad1;
	XMFLOAT3 lightcolor;			//���C�g�F
	unsigned int active = 0;		//�A�N�f�B�u�t���O
};
//�X�|�b�g���C�g�p�̍\����
struct SpotLightData {
	XMVECTOR lightv;				//���C�g�̕����x�N�g��
	XMFLOAT3 lightpos;				//���C�g���W
	float pad1;
	XMFLOAT3 lightcolor;			//���C�g�F
	float pad2;
	XMFLOAT3 lightatten;			//���C�g���������W��
	float pad3;
	XMFLOAT2 lightfactoranglecos;	//���C�g�p�x�����W��
	unsigned int active = 0;		//�A�N�e�B�u�t���O
	float pad4;
};
//�V���h�E���C�g�p�̍\����
struct CircleShadowData {
	XMVECTOR dir;					//�e�̓��e������\���P�ʃx�N�g��
	XMFLOAT3 centerpos;				//�����Ղ�e�̎�̂̍��W
	float distanceCasterLight;		//�����Ղ�e�̎�̂̍��W�ƃV���h�E���C�g�����̋���
	XMFLOAT3 atten;					//���������Ɏg�����l
	float pad3;
	XMFLOAT2 facterAngleCos;		//�����J�n�p�x�ƏI���p�x
	unsigned int active;			//�A�N�e�B�u�t���O
	float pad4;
};
//�萔�o�b�t�@b
struct ConstBufferDataB2 {
	PointLightData pointlights[POINTLIGHT_NUM];			//�_����
	DirLightData dirlights[DIRLIGHT_NUM];				//�ʌ���
	SpotLightData spotlights[SPOTLIGHT_NUM];			//�X�|�b�g���C�g
	//CircleShadowData circleShadowData[CIRCLESHADOW_NUM];//�ۉe����
};
struct ConstBufferDataB2Shadow {
	PointLightData pointlights[POINTLIGHT_NUM];			//�_����
	DirLightData dirlights[DIRLIGHT_NUM];				//�ʌ���
	SpotLightData spotlights[SPOTLIGHT_NUM];			//�X�|�b�g���C�g
	CircleShadowData circleShadowData[CIRCLESHADOW_NUM];//�ۉe����
};


//��{�I�ȕ`��f�[�^
struct BasicDrawingData {
	bool isDisplay = true;						//�`�悷�邩�ǂ���
	vector<int> textureID;						//�e�N�X�`����ID�i���o�[
	int projectionID;							//�ǂ̓��e�����邩��ID
	int piplineID;								//�g�p����p�C�v���C���̖��O
};

//���C���p�f�[�^�\����
//struct Line {
//	/*-----�e���{�f�[�^-----*/
//	BasicDrawingData basicdata;					//��{�I�ȕ`��f�[�^
//	/*-----���_�f�[�^�֌W-----*/
//	vector<Vertex> vertex;						//���_
//	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
//	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
//	/*-----�萔�f�[�^�֌W-----*/
//	ConstBufferDataB0 constBufferDataB0;		//�萔 �s��⎋�_���W�A�J���[�Ȃ�
//	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
//	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�p�f�B�X�N���v�^�q�[�v
//	/*-----�e��s��-----*/
//	XMMATRIX scaleMat;							//�X�P�[�����O�s��
//	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
//	XMMATRIX positionMat;						//���W�s��
//	/*-----�f�o�b�Oor�����蔻��p-----*/
//	XMFLOAT3 pos1;								//���W
//	XMFLOAT3 pos2;								//���W
//};

//2D�X�v���C�g�p�f�[�^�\����
//struct Sprite {
//	/*-----�e���{�f�[�^-----*/
//	BasicDrawingData basicdata;					//��{�I�ȕ`��f�[�^
//	/*-----���_�f�[�^�֌W-----*/
//	vector<Vertex> vertex;						//���_
//	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
//	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
//	/*-----�萔�f�[�^�֌W-----*/
//	ConstBufferDataB0 constBufferDataB0;		//�萔 �s��⎋�_���W�A�J���[�Ȃ�
//	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
//	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�p�f�B�X�N���v�^�q�[�v
//	/*-----�e��s��-----*/
//	XMMATRIX scaleMat;							//�X�P�[�����O�s��
//	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
//	XMMATRIX positionMat;						//���W�s��
//	/*-----�f�o�b�Oor�����蔻��p-----*/
//	XMFLOAT3 pos;								//���W
//};


struct SpriteMultiTexture {
	/*-----�e���{�f�[�^-----*/
	bool isDisplay = true;						//�`�悷�邩�ǂ���
	vector<int> textureID;						//�e�N�X�`����ID�i���o�[
	int projectionID;							//�ǂ̓��e�����邩��ID
	int piplineID;								//�g�p����p�C�v���C���̖��O
	/*-----���_�f�[�^�֌W-----*/
	vector<Vertex> vertex;						//���_
	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
	/*-----�萔�f�[�^�֌W-----*/
	ConstBufferDataB0 constBufferDataB0;		//�萔 �s��⎋�_���W�A�J���[�Ȃ�
	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�p�f�B�X�N���v�^�q�[�v
	/*-----�e��s��-----*/
	XMMATRIX scaleMat;							//�X�P�[�����O�s��
	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
	XMMATRIX positionMat;						//���W�s��
	/*-----�f�o�b�Oor�����蔻��p-----*/
	XMFLOAT3 pos;								//���W
};

//�}���`�p�X�����_�����O�p�̒萔�\����
struct ConstBufferDataMultiPath {
	XMFLOAT4 gaussianWeight[2];					//�K�E�X�t�B���^�[�Ɏg�p����d��
	float pad1;
};

//�}���`�p�X�����_�����O�p�f�[�^�\����
//struct SpriteMultiPath {
//	/*-----�e���{�f�[�^-----*/
//	BasicDrawingData basicdata;					//��{�I�ȕ`��f�[�^
//	/*-----���_�f�[�^�֌W-----*/
//	vector<Vertex> vertex;						//���_
//	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
//	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
//	/*-----�萔�f�[�^�֌W-----*/
//	ConstBufferDataB0 constBufferDataB0;		//�萔 �s��⎋�_���W�A�J���[�Ȃ�
//	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
//	ConstBufferDataMultiPath constBufferDataB1;	//�萔 �}���`�p�X�����_�����O�Ɏg�p����e���
//	ComPtr<ID3D12Resource> constBuffB1;			//�萔�o�b�t�@
//	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�p�f�B�X�N���v�^�q�[�v
//	/*-----�e��s��-----*/
//	XMMATRIX scaleMat;							//�X�P�[�����O�s��
//	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
//	XMMATRIX positionMat;						//���W�s��
//	/*-----�f�o�b�Oor�����蔻��p-----*/
//	XMFLOAT3 pos;								//���W
//};

//3D�I�u�W�F�N�g�p�f�[�^�\����
//struct Object3DData {
//	/*-----�e���{�f�[�^-----*/
//	BasicDrawingData basicdata;					//��{�I�ȕ`��f�[�^
//	/*-----���_�f�[�^�֌W-----*/
//	vector<Vertex> vertex;						//���_
//	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
//	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
//	vector<unsigned short> index;				//���_�C���f�b�N�X
//	ComPtr<ID3D12Resource> indexBuff;			//���_�C���f�b�N�X�o�b�t�@
//	D3D12_INDEX_BUFFER_VIEW ibView;				//���_�C���f�b�N�X�o�b�t�@�r���[
//	/*-----�萔�f�[�^�֌W-----*/
//	ConstBufferDataB0 constBuffDataB0;			//�萔1	�s��Ȃ�
//	ConstBufferDataB1 constBuffDataB1;			//�萔2	�}�e���A���Ȃ�
//	ConstBufferDataB2 constBuffDataB2;			//�萔3	���C�g�Ȃ�
//	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB1;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB2;			//�萔�o�b�t�@
//	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�f�B�X�N���v�^�q�[�v
//	/*-----�e��s��-----*/
//	XMMATRIX scaleMat;							//�X�P�[�����O�s��
//	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
//	XMMATRIX positionMat;						//���W�s��
//	/*-----�f�o�b�Oor�����蔻��p-----*/
//	XMFLOAT3 pos;								//���W
//	float radius;								//���a
//};

////3D�I�u�W�F�N�g�p�f�[�^�\����
//struct Object3D {
//	/*-----�e���{�f�[�^-----*/
//	BasicDrawingData basicdata;					//��{�I�ȕ`��f�[�^
//	/*-----���_�f�[�^�֌W-----*/
//	vector<Vertex> vertex;						//���_
//	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
//	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
//	vector<unsigned short> index;				//���_�C���f�b�N�X
//	ComPtr<ID3D12Resource> indexBuff;			//���_�C���f�b�N�X�o�b�t�@
//	D3D12_INDEX_BUFFER_VIEW ibView;				//���_�C���f�b�N�X�o�b�t�@�r���[
//	/*-----�萔�f�[�^�֌W-----*/
//	ConstBufferDataB0 constBuffDataB0;			//�萔1	�s��Ȃ�
//	ConstBufferDataB1 constBuffDataB1;			//�萔2	�}�e���A���Ȃ�
//	ConstBufferDataB2 constBuffDataB2;			//�萔3	���C�g�Ȃ�
//	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB1;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB2;			//�萔�o�b�t�@
//	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�f�B�X�N���v�^�q�[�v
//	/*-----�e��s��-----*/
//	XMMATRIX scaleMat;							//�X�P�[�����O�s��
//	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
//	XMMATRIX positionMat;						//���W�s��
//	/*-----�f�o�b�Oor�����蔻��p-----*/
//	XMFLOAT3 pos;								//���W
//	float radius;								//���a
//};
////3D�I�u�W�F�N�g�p�f�[�^�\����
//struct Object3DShadow {
//	/*-----�e���{�f�[�^-----*/
//	BasicDrawingData basicdata;					//��{�I�ȕ`��f�[�^
//	/*-----���_�f�[�^�֌W-----*/
//	vector<Vertex> vertex;						//���_
//	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
//	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
//	vector<unsigned short> index;				//���_�C���f�b�N�X
//	ComPtr<ID3D12Resource> indexBuff;			//���_�C���f�b�N�X�o�b�t�@
//	D3D12_INDEX_BUFFER_VIEW ibView;				//���_�C���f�b�N�X�o�b�t�@�r���[
//	/*-----�萔�f�[�^�֌W-----*/
//	ConstBufferDataB0 constBuffDataB0;			//�萔1	�s��Ȃ�
//	ConstBufferDataB1 constBuffDataB1;			//�萔2	�}�e���A���Ȃ�
//	ConstBufferDataB2Shadow constBuffDataB2;			//�萔3	���C�g�Ȃ�
//	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB1;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB2;			//�萔�o�b�t�@
//	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�f�B�X�N���v�^�q�[�v
//	/*-----�e��s��-----*/
//	XMMATRIX scaleMat;							//�X�P�[�����O�s��
//	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
//	XMMATRIX positionMat;						//���W�s��
//	/*-----�f�o�b�Oor�����蔻��p-----*/
//	XMFLOAT3 pos;								//���W
//	float radius;								//���a
//};
//�C���X�^���V���O�`��p �`�[�����삪�I�������C���X�^���V���O�`��p�̒萔�o�b�t�@�Ƃ��ėp�ӂ���
//struct Object3DInstance {
//	/*-----�e���{�f�[�^-----*/
//	BasicDrawingData basicdata;					//��{�I�ȕ`��f�[�^
//	/*-----���_�f�[�^�֌W-----*/
//	vector<Vertex> vertex;						//���_
//	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
//	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
//	vector<unsigned short> index;				//���_�C���f�b�N�X
//	ComPtr<ID3D12Resource> indexBuff;			//���_�C���f�b�N�X�o�b�t�@
//	D3D12_INDEX_BUFFER_VIEW ibView;				//���_�C���f�b�N�X�o�b�t�@�r���[
//	/*-----�萔�f�[�^�֌W-----*/
//	ConstBufferDataB0 constBuffDataB0;			//�萔1	�s��Ȃ�
//	ConstBufferDataB1 constBuffDataB1;			//�萔2	�}�e���A���Ȃ�
//	ConstBufferDataB2 constBuffDataB2;			//�萔3	���C�g�Ȃ�
//	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB1;			//�萔�o�b�t�@
//	ComPtr<ID3D12Resource> constBuffB2;			//�萔�o�b�t�@
//	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�f�B�X�N���v�^�q�[�v
//	/*-----�e��s��-----*/
//	XMMATRIX scaleMat;							//�X�P�[�����O�s��
//	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
//	XMMATRIX positionMat;						//���W�s��
//	/*-----�f�o�b�Oor�����蔻��p-----*/
//	XMFLOAT3 pos;								//���W
//	float radius;								//���a
//};

//ModelDataManager��Object3D�Ԃ̃f�[�^�̎󂯓n���p�֐�
struct ObjectData {
	vector<Vertex> vertex;
	vector<UINT> index;
	ConstBufferDataB1 constBufferDataB1;
};

//GS�p�[�e�B�N���p�f�[�^�\����
struct GSParticleData {
	int textureID;								//�e�N�X�`����ID�i���o�[
	int piplineID;								//�g���p�C�v���C���̖��O
	XMFLOAT3 vertex;
	ComPtr<ID3D12Resource> vertBuff;			//���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView;			//���_�o�b�t�@�r���[
	GSConstBufferDataB0 constBuffDataB0;		//�萔1	�s��Ȃ�
	ComPtr<ID3D12Resource> constBuffB0;			//�萔�o�b�t�@
	ComPtr<ID3D12DescriptorHeap> constDescHeap;	//CBV�f�B�X�N���v�^�q�[�v
	XMMATRIX scaleMat;							//�X�P�[�����O�{��
	XMMATRIX rotationMat;						//��]�s��(�W�ϒl)
	XMMATRIX positionMat;						//���W�s��
	/*-----�f�o�b�Oor�����蔻��p-----*/
	XMFLOAT3 pos;								//���W
};

//�}�e���A��
struct Material {
	string name;								//�}�e���A����
	string textureName;							//�e�N�X�`���̖��O
	XMFLOAT3 ambient = { 0.3f,0.3f,0.3f };		//�A���r�G���g�e���x
	XMFLOAT3 diffuse = { 0.3f,0.3f,0.3f };		//�f�B�t���[�Y�e���x
	XMFLOAT3 specular = { 0.3f,0.3f,0.3f };		//�X�y�L�����[�e���x
	float alpha;								//�A���t�@
};

//model�̃f�[�^�\����
struct ModelData {
	string modelName;							//���f���t�@�C����
	Material material;					//�}�e���A��
	vector<unsigned short> index;		//���_�C���f�b�N�X
	vector<Vertex> vertex;				//���_
	bool isSmoothing;							//�@�����X���[�Y�ɂ��邩�ǂ���
};

//3D�}�`�f�[�^�\����
struct ShapeData {
	int dataID;									//�}�`����ID
	vector<unsigned short> index;				//���_�C���f�b�N�X
	vector<Vertex> vertex;						//���_
};

struct Node {
	// ���O
	std::string name;
	// ���[�J���X�P�[��
	DirectX::XMVECTOR scaling = { 1.0f,1.0f,1.0f,0.0f };
	// ���[�J����]�p
	DirectX::XMVECTOR rotation = { 0.0f,0.0f,0.0f,0.0f };
	// ���[�J���ړ�
	DirectX::XMVECTOR translation = { 0.0f,0.0f,0.0f,1.0f };
	// ���[�J���ϊ��s��
	DirectX::XMMATRIX transform;
	// �O���[�o���ϊ��s��
	DirectX::XMMATRIX globalTransform;
	// �e�m�[�h
	Node* parent;
};

/*
�e�N�X�`���N���X
�E�t�@�C�����A���ʔԍ��A�e�N�X�`���o�b�t�@�������Ă���\����
*/
//struct Texture {
//	LPCWSTR fileName;				//�t�@�C����
//	int IDNum;						//���ʔԍ�
//	ComPtr<ID3D12Resource> texBuff;	//�e�N�X�`���o�b�t�@
//	//�ȉ��͕K���K�v�ł͂Ȃ�����������֗�
//	TexMetadata metadata;			//�摜�̃T�C�Y�ȂǁA�e�N�X�`���Ƃ��Ă̊e��񂪓���
//	ScratchImage* scratchImg;
//	Image* image;					//�r�b�g�}�b�v�`���ł̉摜�f�[�^�̂��̂��̂̃A�h���X������
//	XMFLOAT4 colorData;				//�F���w�肵�ăe�N�X�`���𐶐�����ہA���̃e�N�X�`�����ǂ̐F�Ȃ̂���n�����߂̕ϐ�
//};

//���C�\����
struct Ray {
	XMVECTOR pos;
	XMVECTOR dir;
};
//uv�p�\����
struct UVs {
	XMFLOAT2 leftUp;		//����
	XMFLOAT2 leftDown;		//����
	XMFLOAT2 rightDown;		//�E��
	XMFLOAT2 rightUp;		//�E��
};

//�T�E���h�֌W�̍\����
//�`�����N�w�b�_
struct ChunkHeader {
	char id[4];		//�`�����N����ID
	int32_t size;	//�`�����N�T�C�Y
};
//RIFF�w�b�_�`�����N
struct RiffHeader {
	ChunkHeader chunk;	//"RIFF"
	char type[4];	//"WAVE
};
//FMT�`�����N
struct FormatChunk {
	ChunkHeader chunk;		//"fmt"
	WAVEFORMATEX fmt;	//�g�`�t�H�[�}�b�g
};

//�����f�[�^
struct SoundData {
	WAVEFORMATEX wfex;			//�g�`�t�H�[�}�b�g
	BYTE* pBuffer;				//�o�b�t�@�̐擪�A�h���X
	unsigned int bufferSize;	//�o�b�t�@�̃T�C�Y
	IXAudio2SourceVoice* source;
	float volume;
};