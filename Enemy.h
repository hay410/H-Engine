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

class Enemy
{
private:
	//メンバ定数
	const float MAX_SPEED = 1.0f;
	const float SWAY_SPEED = 18.0f;
	const float WALK_SPEED = 0.6f;
	const int MAX_JAB_START_TIMER = 12;
	const int MAX_JAB_HIT_TIMER = 6;
	const int MAX_JAB_END_TIMER = 30;
	const int MAX_HOOK_START_TIMER = 8;
	const int MAX_HOOK_HIT_TIMER = 6;
	const int MAX_HOOK_END_TIMER = 30;
	const int MAX_UPPER_START_TIMER = 12;
	const int MAX_UPPER_HIT_TIMER = 6;
	const int MAX_UPPER_END_TIMER = 40;
	const float ADD_ANGLE = 0.02f;			//角度に足す量
	const float WALK_DISTANCE = 100.0f;
	const float RUN_DISTANCE = 200.0f;
	const float RADIUS = 20.0f;
	const int MAX_STATE_TIMER = 120;
	const int MAX_GUARD_TIMER = 300;
	const float ATTACK_RADIUS = 20.0f;
	const float ATTACK_RANGE = 35.0f;

	enum class STATE {
		WAIT,
		ATTACK,
		SWAY,
		GUARD,
	};

	//メンバ変数
	//プレイヤーモデルのデータ
	Object3D object;
	Object3D sphere;
	Vec3 position;				//座標
	float radius;
	float speed;				//速度
	Vec3 forwardVec;			//正面ベクトル
	Vec3 previousForwardVec;	//１フレーム前の正面ベクトル
	float angle;				//向き
	bool isSway;				//スウェイ中か
	bool isGuard;				//ガード中か
	int guardTimer;				//ガード用のタイマー
	bool isHit;					//攻撃判定があるときのみ上がるフラグ
	bool isAlive;				//生存フラグ
	bool availableAttack;		//攻撃可能
	int random;					//乱数
	STATE state;				//状態
	int stateTimer;				//行動間隔

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
	Vec3 attackVec;

	//メンバ関数
	void Move(const Vec3& playerPos);

	void StateControl();

	void Sway();

	void Guard();

	void Attack();

	void Jab();

	void Hook();

	void Upper();

public:

	//コンストラクタ
	Enemy();

	//初期化
	void Init();

	//生成
	void Generate(const Vec3& position, const Vec3& playerPos);

	//更新
	void Update(const Vec3& playerPos);

	//描画
	void Draw();

	//死亡処理
	void Dead();

	//ゲッタ
	Vec3 GetPos() { return position; }
	bool GetIsAlive() { return isAlive; }
	float GetRadius() { return radius; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	float GetSpeed() { return speed; }

	//セッタ
	void SetPos(const Vec3& pos) { position = pos; }
	void SetSpeed(float speed) { this->speed = speed; }
};