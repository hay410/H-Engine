#pragma once
#include "Singleton.h"
#include "DirectXBase.h"
#include "Input.h"
#include "Camera.h"
#include "Object3D.h"
#include "Sprite.h"
#include "DescriptorHeapManager.h"
#include "LightManager.h"
#include "Collision.h"

class Player
{
private:
	//メンバ定数
	const float MAX_SPEED = 5.0f;
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
	const float RADIUS = 40.0f;
	const float ATTACK_RADIUS = 20.0f;
	const float ATTACK_RANGE = 35.0f;

	//メンバ変数
	//プレイヤーモデルのデータ
	Object3D object;
	Object3D sphere;
	Vec3 position;				//座標
	float radius;				//半径
	float speed;				//速度
	Vec3 forwardVec;			//正面ベクトル
	Vec3 previousForwardVec;	//１フレーム前の正面ベクトル
	bool isAlive;
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

	//当たり判定用
	Sphere bodySphere;
	Sphere attackSphere;
	Vec3 attackPos;
	
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
	void SetPos(const Vec3& pos) { position = pos; }
	float GetRadius() { return radius; }
	bool GetIsAlive() { return isAlive; }
	bool GetIsHit() { return isHit; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	Vec3 GetAttackPos() { return attackPos; }
	float GetAttackRadius() { return ATTACK_RADIUS; }
};