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

	const int	MAX_JAB_START_TIMER = 12;
	const int	MAX_JAB_HIT_TIMER = 6;
	const int	MAX_JAB_END_TIMER = 30;
	const int	JAB_DAMAGE = 20;				//ダメージ量
	const float JAB_KNOCKBACK_POWER = 3.0f;		//ノックバックの強さ
	const float JAB_STEP_RANGE = 3.0f;

	const int	MAX_HOOK_START_TIMER = 8;
	const int	MAX_HOOK_HIT_TIMER = 6;
	const int	MAX_HOOK_END_TIMER = 30;
	const int	HOOK_DAMAGE = 30;				//ダメージ量
	const float HOOK_KNOCKBACK_POWER = 5.0f;	//ノックバックの強さ
	const float HOOK_STEP_RANGE = 6.0f;

	const int	MAX_UPPER_START_TIMER = 12;
	const int	MAX_UPPER_HIT_TIMER = 6;
	const int	MAX_UPPER_END_TIMER = 40;
	const int	UPPER_DAMAGE = 50;				//ダメージ量
	const float UPPER_KNOCKBACK_POWER = 18.0f;	//ノックバックの強さ
	const float UPPER_STEP_RANGE = 9.0f;

	const float RADIUS = 40.0f;
	const float ATTACK_RADIUS = 20.0f;
	const float ATTACK_RANGE = 35.0f;
	const int	MAX_HP = 300;

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
	int HP;
	int damage;
	bool is1Hit;
	float stepSpeed;

	//ノックバック用
	bool isKnockBack;
	float kBackVel;			//自分のノックバックに使う加速度
	float valueKBackVel;	//敵をノックバックさせるために敵に渡す加速度

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
	void Move();

	void Walk();

	void Sway();

	void Guard();

	void Attack();

	void Jab();

	void Hook();

	void Upper();

	void KnockBack(const Vec3& attackVec);

public:
	
	//コンストラクタ
	Player();
	
	//初期化
	void Init();
	
	//更新
	void Update(const Vec3& attackVec);
	
	//描画
	void Draw();

	//ダメージ(HPのセッタのようなもの)
	void Damage(int damage);

	//死亡処理
	void Dead();

	//ゲッタ
	Vec3 GetPos() { return position; }
	float GetRadius() { return radius; }
	bool GetIsAlive() { return isAlive; }
	bool GetIsHit() { return isHit; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	Vec3 GetAttackPos() { return attackPos; }
	float GetDamage() { return damage; }
	float GetAttackRadius() { return ATTACK_RADIUS; }
	bool GetIs1Hit() { return is1Hit; }
	Vec3 GetAttackVec() { return attackVec; }
	float GetValueKBackVel() { return valueKBackVel; }

	//セッタ
	void SetPos(const Vec3& value) { position = value; }
	void SetIsKnockBack(bool value) { isKnockBack = value; }
	void SetIs1Hit(bool value) { is1Hit = value; }
	void SetkBackVel(float value) { kBackVel = value; }
};