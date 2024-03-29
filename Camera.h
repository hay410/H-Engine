#pragma once
#include <DirectXMath.h>
#include "Singleton.h"
#include "HVec.h"

using namespace DirectX;

class Camera : public Singleton<Camera> {
public:
	XMMATRIX matView;		//ビュー行列
	Vec3 eye;			//ゲームワールド内でのカメラ座標
	Vec3 target;			//ゲームワールド内でカメラが見ている座標
	Vec3 up;				//ゲームワールド内でカメラから見て上方向を指すベクトル

	Vec3 forwardVec;

	Vec3 honraiEye;		//本来あるべき視点座標
	Vec3 honraiTarget;	//本来あるべき注視点座標
	Vec3 honraiUp;		//本来あるべき上ベクトル

	XMMATRIX rotationMat;	//カメラの回転行列
	XMMATRIX upRotationMat;	//カメラの上方向ベクトルの回転行列

	XMMATRIX matPerspective;
	XMMATRIX matProjection;

	float angleOfView;		//画角

	float angleXZ;		// XZ平面での角度
	int sceneNum;

private:

	const float EYE_PLAYER_DISTANCE = 100;			//プレイヤーと視点の距離
	const float TARGET_PLAYER_DISTNACE = 50;		//プレイヤーと注視点の距離
	const float TARGET_UPPER = 50;					//ターゲットを上にずらす量
	const float MAX_ANGLEOFVIEW = 100.0f;						//最大画角
	const float ROT_UNIT = 0.05f;
	const float ADD_UNIT = 10.0f;

	enum SceneNum {
		TITLE_SCENE,				//タイトル画面
		GAME_SCENE,				//ゲーム画面
		END_SCENE				//エンド画面
	};

public:

	//コンストラクタ
	friend Singleton<Camera>;
	Camera();

	//初期化
	void Init();

	//ビュー行列生成
	void GenerateMatView();

	//更新処理
	void Update(const Vec3& pos);

	// 回転
	void AddRotation(const float& RotX, const float& RotY, const float& RotZ);
	void AddRotationXZ(const float& Rot);

	// 移動
	void Move(const float& Speed);

	//アクセッタ
	Vec3 GetEyeVector();
	XMMATRIX GetMatProjection() { return matProjection; }
	Vec3 GetEyePos() { return eye; }
	void SetEyePos(const Vec3& eye) { this->eye = eye; }
	void SetTargetPos(const Vec3& target) { this->target = target; }
	void SetSceneNum(int sceneNum) { this->sceneNum = sceneNum; }
};