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
//	//コンストラクタ
//	ObjectManager();
//	friend Singleton<ObjectManager>;
//
//	/*------------初期化-------------*/
//
//	//立方体初期化
//	Object3D InitBox(XMFLOAT3 pos, XMFLOAT3 size, int projectionID, LPCWSTR fileName);
//
//	//○角錐初期化
//	Object3D InitCone(XMFLOAT3 pos, int projectionID, XMFLOAT4 color, LPCWSTR fileName);
//
//	//円柱の初期化処理
//	Object3D InitCylinder(XMFLOAT3 pos, float radius, float height, int projectionID, XMFLOAT4 color, LPCWSTR fileName = 0);
//
//	//球の初期化処理
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
//	/*-------------描画--------------*/
//
//	//共通の描画処理
//	void CommonDraw(D3D12_PRIMITIVE_TOPOLOGY topology);
//
//	//スプライト別の描画処理
//	void Draw(Object3D& objectBuff);
//
//	/*-------------------------------*/
//
//	/*-----------行列変換------------*/
//
//	//スケーリング
//	void ChangeScale(Object3D& objectBuff, XMFLOAT3 scale);
//
//	//回転
//	void ChangeRotation(Object3D& objectBuff, XMFLOAT3 rotation);
//
//	//平行移動(代入)
//	void ChangePosition(Object3D& objectBuff, XMFLOAT3 position);
//
//	//平行移動(加算)
//	void ChangePositionAdd(Object3D& objectBuff, XMFLOAT3 position);
//
//	/*-------------------------------*/
//};