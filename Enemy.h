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
	const float MAX_SPEED = 1.0f;				//通常の移動速度
	const float SWAY_SPEED = 18.0f;				//スウェイ時の速度
	const float WALK_SPEED = 0.6f;				//歩きの速度
	const float ADD_ANGLE = 0.02f;				//角度に足す量
	const float WALK_DISTANCE = 50.0f;			//歩きから攻撃に移行する距離
	const float RUN_DISTANCE = 200.0f;			//走りから歩きに移行する距離
	const float SENSE_DISTANCE = 500.0f;		//プレイヤーを感知する距離
	const float RADIUS = 20.0f;					//半径
	const int	MAX_STATE_TIMER = 60;			//状態を変更するタイマー
	const int	MAX_GUARD_TIMER = 300;			//ガード状態のタイマー
	const float ATTACK_RADIUS = 20.0f;			//攻撃の半径
	const float ATTACK_RANGE = 35.0f;			//攻撃の距離
	const float	MAX_HP = 70.0f;				//最大HP
	const float	REDUCTION_RATE = 90.0f;			//ガードがダメージを軽減する割合(%)

	//弱パンチ
	const int	MAX_JAB_START_TIMER = 12;		//発生フレーム
	const int	MAX_JAB_HIT_TIMER = 6;			//判定フレーム
	const int	MAX_JAB_END_TIMER = 30;			//後隙フレーム
	const int	JAB_DAMAGE = 15;				//ダメージ量
	const float JAB_KNOCKBACK_POWER = 3.0f;		//ノックバックの強さ
	const float JAB_STEP_RANGE = 3.0f;			//ステップの距離

	//強パンチ
	const int	MAX_HOOK_START_TIMER = 8;		//発生フレーム
	const int	MAX_HOOK_HIT_TIMER = 6;			//判定フレーム
	const int	MAX_HOOK_END_TIMER = 30;		//後隙フレーム
	const int	HOOK_DAMAGE = 20;				//ダメージ量
	const float HOOK_KNOCKBACK_POWER = 5.0f;	//ノックバックの強さ
	const float HOOK_STEP_RANGE = 6.0f;			//ステップの距離

	//強強パンチ
	const int	MAX_UPPER_START_TIMER = 12;		//発生フレーム
	const int	MAX_UPPER_HIT_TIMER = 6;		//判定フレーム
	const int	MAX_UPPER_END_TIMER = 40;		//後隙フレーム
	const int	UPPER_DAMAGE = 35;				//ダメージ量
	const float UPPER_KNOCKBACK_POWER = 18.0f;	//ノックバックの強さ
	const float UPPER_STEP_RANGE = 9.0f;			//ステップの距離

	enum class STATE {
		WAIT,
		ATTACK,
		SWAY,
		GUARD,
		MOVE,
	};

	//メンバ変数
	//プレイヤーモデルのデータ
	Object3D object;			//モデル
	Object3D sphere;			//球
	Vec3 position;				//座標
	float radius;				//半径
	float speed;				//速度
	Vec3 forwardVec;			//正面ベクトル
	Vec3 previousForwardVec;	//１フレーム前の正面ベクトル
	float angle;				//向き
	bool isSway;				//スウェイ中か
	bool isGuard;				//ガード中か
	int guardTimer;				//ガード用のタイマー
	bool isHit;					//攻撃判定があるときのみ上がるフラグ
	bool isAttack;
	bool isAlive;				//生存フラグ
	bool availableAttack;		//攻撃可能
	int random;					//乱数
	STATE state;				//状態
	int stateTimer;				//行動間隔
	float HP;						//HP
	int damage;					//プレイヤーに与えるダメージ量
	bool is1Hit;

	//ノックバック用
	bool isKnockBack;
	float kBackVel;				//自分のノックバックに使う加速度
	float valueKBackVel;		//敵をノックバックさせるために敵に渡す加速度

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

	void KnockBack(const Vec3& attackVec);


public:

	//コンストラクタ
	Enemy();

	//初期化
	void Init();

	//生成
	void Generate(const Vec3& position, const Vec3& playerPos);

	//更新
	void Update(const Vec3& playerPos, const Vec3& attackVec);

	//描画
	void Draw();

	//ダメージ(HPのセッタのようなもの)
	void Damage(float damage);

	//死亡処理
	void Dead();

	//ゲッタ
	Vec3 GetPos() { return position; }
	bool GetIsAlive() { return isAlive; }
	float GetRadius() { return radius; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	float GetSpeed() { return speed; }
	Vec3 GetForwardVec() { return forwardVec; }
	Vec3 GetAttackPos() { return attackPos; }
	float GetAttackRadius() { return ATTACK_RADIUS; }
	bool GetIsHit() { return isHit; }
	int GetDamage() { return damage; }
	float GetValueKBackVel() { return valueKBackVel; }
	bool GetIs1Hit() { return is1Hit; }

	//セッタ
	void SetPos(const Vec3& value) { position = value; }
	void SetSpeed(float value) { this->speed = value; }
	void SetIsKnockBack(bool value) { isKnockBack = value; }
	void SetIs1Hit(bool value) { is1Hit = value; }
	void SetkBackVel(float value) { kBackVel = value; }
};