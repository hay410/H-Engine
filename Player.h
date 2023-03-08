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
#include "Melee.h"

class Player
{
private:
	//メンバ定数
	const float MAX_SPEED = 4.0f;				//通常のスピード
	const float SWAY_SPEED = 24.0f;				//スウェイのスピード
	const float WALK_SPEED = 2.5f;				//歩きのスピード
	const float RADIUS = 40.0f;					//半径
	const float ATTACK_RADIUS = 20.0f;			//攻撃の半径
	const float ATTACK_RANGE = 35.0f;			//攻撃の距離
	const int	MAX_HP = 300;					//最大HP
	const int	MAX_STUN_TIMER = 60;			//スタンの時間
	const float LOCKON_RANGE = 500.0f;			//ロックオンの距離

	const int	MAX_JAB_START_TIMER = 12;		//発生フレーム
	const int	MAX_JAB_HIT_TIMER = 6;			//判定フレーム
	const int	MAX_JAB_END_TIMER = 30;			//後隙フレーム
	const int	JAB_DAMAGE = 20;				//ダメージ量
	const float JAB_KNOCKBACK_POWER = 4.0f;		//ノックバックの強さ
	const float JAB_STEP_RANGE = 3.0f;			//ステップの距離

	const int	MAX_HOOK_START_TIMER = 8;		//発生フレーム
	const int	MAX_HOOK_HIT_TIMER = 6;			//判定フレーム
	const int	MAX_HOOK_END_TIMER = 30;		//後隙フレーム
	const int	HOOK_DAMAGE = 30;				//ダメージ量
	const float HOOK_KNOCKBACK_POWER = 6.0f;	//ノックバックの強さ
	const float HOOK_STEP_RANGE = 6.0f;			//ステップの距離

	const int	MAX_UPPER_START_TIMER = 12;		//発生フレーム
	const int	MAX_UPPER_HIT_TIMER = 6;			//判定フレーム
	const int	MAX_UPPER_END_TIMER = 40;		//後隙フレーム
	const int	UPPER_DAMAGE = 50;				//ダメージ量
	const float UPPER_KNOCKBACK_POWER = 24.0f;	//ノックバックの強さ
	const float UPPER_STEP_RANGE = 9.0f;		//ステップの距離


	//メンバ変数
	//プレイヤーモデルのデータ
	Object3D object;			//モデル
	Object3D sphere;			//球
	Vec3 position;				//座標
	float radius;				//半径
	float speed;				//速度
	Vec3 forwardVec;			//正面ベクトル
	Vec3 previousForwardVec;	//１フレーム前の正面ベクトル
	bool isAlive;				//生存フラグ
	bool isSway;				//スウェイフラグ
	bool isLockOn;				//ロックオンフラグ
	Vec3 enemyNearPos;			//一番近い敵の座標
	bool isGuard;				//ガードフラグ
	bool isHit;					//攻撃判定があるときのみ上がるフラグ
	int HP;						//ヒットポイント
	int damage;					//敵に与えるダメージ
	bool is1Hit;				//当たり判定トリガーフラグ
	float stepSpeed;			//攻撃時のステップの速度

	vector<AttackInfo> attackInfo;

	//ノックバック用
	bool isKnockBack;
	float kBackVel;			//自分のノックバックに使う加速度
	float valueKBackVel;	//敵をノックバックさせるために敵に渡す加速度
	int stunTimer;			//スタンのタイマー

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
	//移動
	void Move();

	//歩き
	void Walk();

	//スウェイ
	void Sway();

	//ガード
	void Guard();
	
	//攻撃
	void Attack();
	
	//弱パンチ
	void Jab();

	//強パンチ
	void Hook();

	//強強パンチ
	void Upper();

	//ノックバック
	void KnockBack(const Vec3& attackVec);

	//csvから攻撃情報を読み込み
	void LoadAttackInfoFromCSV();

public:
	
	//コンストラクタ
	Player();
	
	//初期化
	void Init();
	
	//更新
	void Update(const Vec3& attackVec, const Vec3& enemyNearPos);
	
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