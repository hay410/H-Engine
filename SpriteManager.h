//#pragma once
//#include "TextureManager.h"
//#include <d3dcompiler.h>
//#include"Camera.h"
//
//#pragma comment(lib,"d3dcompiler.lib")
//
//const int ConeVertexNum = 30;
//
//class SpriteManager :public Singleton<SpriteManager>
//{
//public:
//	ComPtr<ID3D12PipelineState> pipelinestate;
//	ComPtr<ID3D12RootSignature> rootsignature;
//	//�R���X�g���N�^
//	SpriteManager();
//	friend Singleton<SpriteManager>;
//
//	/*------------������-------------*/
//
//	//2D������
//	Sprite InitSprite(XMFLOAT3 pos, XMFLOAT2 size, int projectionID, LPCWSTR fileName);
//
//	//���ʂ̏���������
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
//	void Draw(Sprite& sprite);
//
//	/*-------------------------------*/
//
//	/*-----------�s��ϊ�------------*/
//	
//	//�X�P�[�����O
//	void ChangeScale(Sprite& sprite, XMFLOAT3 scale);
//
//	//��]
//	void ChangeRotation(Sprite& sprite, XMFLOAT3 rotation);
//	
//	//���s�ړ�(���)
//	void ChangePosition(Sprite& sprite, XMFLOAT3 position);
//	
//	//���s�ړ�(���Z)
//	void ChangePositionAdd(Sprite& sprite, XMFLOAT3 position);
//
//	/*-------------------------------*/
//
//	/*-------------------------------*/
//};