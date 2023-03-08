#pragma once
#include "Object3D.h"

struct AttackInfo {
	bool isAttack;
	int insidenceFrame;		//発生フレーム
	int detectionFrame;		//判定フレーム
	int rigidityFrame;		//硬直フレーム
	int damageAmount;		//ダメージ量
	float knockBackPower;	//ノックバック力
	float stepDistance;		//ステップ距離
	Vec3 startVec;			//開始ベクトル
	Vec3 endVec;			//終了ベクトル
	AttackInfo() {
		isAttack = false;
		insidenceFrame = 0;
		detectionFrame = 0;
		rigidityFrame = 0;
		damageAmount = 0;
		knockBackPower = 0.0f;
		stepDistance = 0.0f;
		startVec = Vec3();
		endVec = Vec3();
	}
};

enum class ATTACK_INFO
{
	INSIDENCE_FRAME,
	DETECTION_FRAME,
	RIGIDITY_FRAME,
	DAMAGE_AMOUNT,
	KNOCKBACK_POWER,
	STEP_DISTANCE,
	STARTVEC_X,
	STARTVEC_Y,
	STARTVEC_Z,
	ENDVEC_X,
	ENDVEC_Y,
	ENDVEC_Z,
};


class Melee
{
public:


private:
	//静的メンバ変数
	static Object3D melee_;
	static Vec3 playerForwardVec_;
	static Vec3 playerPos_;

	//メンバ変数
	Vec3 position_;
	bool isMelee_;
	string name_;
	int startTimer_;
	int hitTimer_;
	int endTimer_;
	Vec3 startVec_;
	Vec3 endVec_;
	Vec3 edgeVec_ = Vec3(0, 1.0, 0);
	Vec3 directionVec_ = Vec3(1.0, 0, 0);

public:
	

	Melee();
	static void Load();
	static void CommonUpdate(const Vec3& pPos, const Vec3& pFVec);
	void Update(const AttackInfo& attackInfo);
	void Draw();
};