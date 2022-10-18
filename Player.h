#pragma once
#include "Singleton.h"
#include "DirectXBase.h"
#include "Input.h"
#include "Camera.h"
#include "Object3D.h"
#include "Sprite.h"
#include "DescriptorHeapManager.h"
#include "LightManager.h"

class Player
{
private:
	//メンバ定数
	const float MAX_SPEED = 6.0f;
	const float SWAY_SPEED = 24.0f;
	const float WALK_SPEED = 2.0f;
	const int MAX_JAB_START_TIMER = 12;
	const int MAX_JAB_HIT_TIMER = 6;
	const int MAX_JAB_END_TIMER = 30;
	const int MAX_HOOK_START_TIMER = 8;
	const int MAX_HOOK_HIT_TIMER = 6;
	const int MAX_HOOK_END_TIMER = 30;
	const int MAX_UPPER_START_TIMER = 12;
	const int MAX_UPPER_HIT_TIMER = 6;
	const int MAX_UPPER_END_TIMER = 40;

	//メンバ変数
	//プレイヤーモデルのデータ
	Object3D object;
	
	Vec3 position;				//座標
	float speed;				//速度
	Vec3 forwardVec;			//正面ベクトル
	Vec3 previousForwardVec;	//１フレーム前の正面ベクトル
	bool isSway;
	bool isLockOn;
	bool isGuard;
	bool isHit;					//攻撃判定があるときのみ上がるフラグ

	//弱パンチ
	bool isJab;
	int jabStartTmier;
	int jabHitTimer;
	int jabEndTimer;

	//強パンチ
	bool isHook;
	int hookStartTmier;
	int hookHitTimer;
	int hookEndTimer;
	
	//強強パンチ
	bool isUpper;
	int upperStartTmier;
	int upperHitTimer;
	int upperEndTimer;
	
	//メンバ関数
	void Move();

	void Walk();

	void Sway();

	void Guard();

	void Attack();

	void Jab();

	void Hook();

	void Upper();

public:
	
	//コンストラクタ
	Player();
	
	//初期化
	void Init();
	
	//更新
	void Update();
	
	//描画
	void Draw();

	//ゲッタ
	Vec3 GetPos() { return position; }
};