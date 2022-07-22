//#pragma once
//#pragma once
//#include "TextureManager.h"
//#include "ShapeManager.h"
//#include <d3dcompiler.h>
//#include "Camera.h"
//#include "FbxModelLoader.h"
//
//#pragma comment(lib,"d3dcompiler.lib")
//
//const int ConeVertexNum = 30;
//
//class ObjectManager :public Singleton<ObjectManager>
//{
//public:
//	ComPtr<ID3D12PipelineState> pipelinestate;
//	ComPtr<ID3D12RootSignature> rootsignature;
//	//�R���X�g���N�^
//	ObjectManager();
//	friend Singleton<ObjectManager>;
//
//	/*------------������-------------*/
//
//	//�����̏�����
//	Object3D InitBox(XMFLOAT3 pos, XMFLOAT3 size, int projectionID, LPCWSTR fileName);
//
//	//���p��������
//	Object3D InitCone(XMFLOAT3 pos, int projectionID, XMFLOAT4 color, LPCWSTR fileName);
//
//	//�~���̏���������
//	Object3D InitCylinder(XMFLOAT3 pos, float radius, float height, int projectionID, XMFLOAT4 color, LPCWSTR fileName = 0);
//
//	//���̏���������
//	Object3D InitSphere(XMFLOAT3 pos, float radius, int projectionID, XMFLOAT4 color, LPCWSTR fileName = 0);
//
//	Object3D Init3DObject(XMFLOAT3 pos, int projectionID, LPCWSTR texFileName, const char* objFileName);
//
//
//	Object3D InitFdxModel(XMFLOAT3 pos, int projectionID, const char* fbxFileName);
//
//	void CommonInit(int blend, D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType);
//
//	/*-------------------------------*/
//
//	/*-------------�`��--------------*/
//
//	//���ʂ̕`�揈��
//	void CommonDraw(D3D12_PRIMITIVE_TOPOLOGY topology);
//
//	//�X�v���C�g�ʂ̕`�揈��
//	void Draw(Object3D& objectBuff);
//
//	/*-------------------------------*/
//
//	/*-----------�s��ϊ�------------*/
//
//	//�X�P�[�����O
//	void ChangeScale(Object3D& objectBuff, XMFLOAT3 scale);
//
//	//��]
//	void ChangeRotation(Object3D& objectBuff, XMFLOAT3 rotation);
//
//	//���s�ړ�(���)
//	void ChangePosition(Object3D& objectBuff, XMFLOAT3 position);
//
//	//���s�ړ�(���Z)
//	void ChangePositionAdd(Object3D& objectBuff, XMFLOAT3 position);
//
//	/*-------------------------------*/
//};