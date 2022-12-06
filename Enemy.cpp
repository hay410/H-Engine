#include"Enemy.h"
#include"HHelper.h"

Enemy::Enemy()
{
	object.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "King", L"Resources/Object/King/color.png");
	sphere.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "Ball", L"Resources/white1x1.png");
	position = XMFLOAT3(0, 0, 0);
	object.ChangeScale({ 20,20,20 });
	sphere.ChangeScale({ 10,10,10 });
	forwardVec = Vec3(0, 0, 1);
	//angle = 0;
	radius = RADIUS;
	previousForwardVec = forwardVec;
	speed = MAX_SPEED;

	isSway = false;
	isGuard = false;
	isAlive = false;
	isHit = false;

	isJab = false;
	jabStartTmier = 0;
	jabHitTimer = 0;
	jabEndTimer = 0;

	isHook = false;
	hookStartTmier = 0;
	hookHitTimer = 0;
	hookEndTimer = 0;

	isUpper = false;
	upperStartTmier = 0;
	upperHitTimer = 0;
	upperEndTimer = 0;

	availableAttack = false;
	isAttack = false;
	state = STATE::WAIT;
	stateTimer = 0;
	guardTimer = 0;
	HP = MAX_HP;

	isKnockBack = false;
	kBackVel = 0.0f;
}

void Enemy::Generate(const Vec3& position,const Vec3&playerPos)
{
	this->position = position;
	angle = atan2(playerPos.x - position.x, playerPos.z - position.z);
	HP = MAX_HP;
	isAlive = true;
}

void Enemy::Move(const Vec3& playerPos)
{
	//プレイヤーとの距離によって状態を変える
	if (!isSway) {
		Vec3 pVec = position - playerPos;
		float pLength = pVec.Length();
		if (pLength >= WALK_DISTANCE && pLength <= RUN_DISTANCE) {
			speed = WALK_SPEED;
			availableAttack = false;
		}
		else if (pLength >= RUN_DISTANCE) {
			speed = MAX_SPEED;
			availableAttack = false;
		}
		else if (pLength <= WALK_DISTANCE) {
			speed = 0.0f;
			availableAttack = true;
		}
	}

	if (state == STATE::MOVE) {
		//外積を使って左右判定をする
		float crossBuff = HHelper::Cross2D(XMFLOAT2(playerPos.x - position.x, playerPos.z - position.z), XMFLOAT2(sinf(angle), cosf(angle)));
		if (crossBuff > 0) {
			angle += ADD_ANGLE;
		}
		else if (crossBuff < 0) {
			angle -= ADD_ANGLE;
		}
		float storageAngle = angle;

		position += Vec3(sinf(angle), 0, cosf(angle)) * speed;

		angle = storageAngle;
	}
}

void Enemy::StateControl()
{
	
	isHit = false;

	if (availableAttack) {
		switch (state)
		{
		case STATE::MOVE:
			//break;を描かないことで1フレーム待たずに状態変更する
			state = STATE::WAIT;
		case STATE::WAIT:
			stateTimer++;
			if (stateTimer >= MAX_STATE_TIMER) {
				int random = HHelper::GetRand(1, 3);
				//int random = 1;
				switch (random)
				{
				case 1:
					state = STATE::ATTACK;
					break;
				case 2:
					state = STATE::SWAY;
					break;
				case 3:
					state = STATE::GUARD;
					break;
				default:
					state = STATE::ATTACK;
					break;
				}
				stateTimer = 0;
			}
			break;
		case STATE::ATTACK:
			attackVec = forwardVec;
			isAttack = true;
			break;
		case STATE::SWAY:
			//スウェイを行っていなければスウェイをさせる
			if (!isSway) {
				isSway = true;
				//入力したときに速度を変更(1回のみ)
				speed = SWAY_SPEED;
				random = HHelper::GetRand(0, 1);
			}
			break;
		case STATE::GUARD:
			isGuard = true;
			Guard();
			break;
		default:
			break;
		}
	}
	else {
		state = STATE::MOVE;
	}
}

//スウェイ(回避)
void Enemy::Sway()
{
	//スウェイ中の処理
	if (isSway) {
		//速度を徐々に減らす
		speed -= 2.0f;
		//自機がロックオン状態の場合は歩き、そうでない場合は走りの速度まで戻す
		
		if (speed <= MAX_SPEED) {
			speed = MAX_SPEED;
			isSway = false;
			state = STATE::MOVE;
		}

		//左右
		if (random == 0) {
			angle += HHelper::H_PI_F / 2;
		}
		else {
			angle -= HHelper::H_PI_F / 2;
		}
	}

}

void Enemy::Guard()
{
	if (isGuard) {
		guardTimer++;
		if (guardTimer >= MAX_GUARD_TIMER) {
			isGuard = false;
			speed = MAX_SPEED;
			state = STATE::MOVE;
		}
	}
}

void Enemy::Attack()
{
	if (!isAttack)return;
	Jab();
	Hook();
	Upper();
}

void Enemy::Jab()
{
	if (!isHook && !isUpper) {
		isJab = true;
	}

	if (!isJab)return;

	if (jabStartTmier < MAX_JAB_START_TIMER) {
		jabStartTmier++;
	}
	else {
		if (jabHitTimer < MAX_JAB_HIT_TIMER) {

			if (speed > 0.0f) {
				speed = JAB_KNOCKBACK_POWER;
				Vec3 stepVec = forwardVec * speed;
				position += stepVec;
				speed -= 2.0f;
			}

			jabHitTimer++;
			isHit = true;
			damage = JAB_DAMAGE;
			valueKBackVel = JAB_KNOCKBACK_POWER;
		}
		else {
			if (jabEndTimer < MAX_JAB_END_TIMER) {
				jabEndTimer++;

				//攻撃派生
				isHook = true;
			}
			else {
				isJab = false;
				jabStartTmier = 0;
				jabHitTimer = 0;
				jabEndTimer = 0;
				is1Hit = true;
			}
		}
	}
}

void Enemy::Hook()
{
	if (!isHook||isJab)return;

	if (hookStartTmier < MAX_HOOK_START_TIMER) {
		hookStartTmier++;
	}
	else {
		if (hookHitTimer < MAX_HOOK_HIT_TIMER) {

			if (speed >= 0.0f) {
				speed = HOOK_KNOCKBACK_POWER;
				Vec3 stepVec = forwardVec * speed;
				position += stepVec;
				speed -= 2.0f;
			}

			hookHitTimer++;
			isHit = true;
			damage = HOOK_DAMAGE;
			valueKBackVel = HOOK_KNOCKBACK_POWER;
		}
		else {
			if (hookEndTimer < MAX_HOOK_END_TIMER) {
				hookEndTimer++;

				//攻撃派生の入力を取る
				isUpper = true;
			}
			else {
				isHook = false;
				hookStartTmier = 0;
				hookHitTimer = 0;
				hookEndTimer = 0;
				is1Hit = true;
			}
		}
	}
}

void Enemy::Upper()
{
	if (!isUpper||isHook)return;

	if (upperStartTmier < MAX_HOOK_START_TIMER) {
		upperStartTmier++;
	}
	else {
		if (upperHitTimer < MAX_HOOK_HIT_TIMER) {
			upperHitTimer++;
			isHit = true;
			damage = UPPER_DAMAGE;
			valueKBackVel = UPPER_KNOCKBACK_POWER;
		}
		else {
			if (upperEndTimer < MAX_HOOK_END_TIMER) {
				upperEndTimer++;
			}
			else {
				isUpper = false;
				upperStartTmier = 0;
				upperHitTimer = 0;
				upperEndTimer = 0;
				state = STATE::MOVE;
				is1Hit = true;
				isAttack = false;
			}
		}
	}
}

void Enemy::KnockBack(const Vec3& attackVec)
{
	//スウェイ中の処理
	if (isKnockBack) {
		Vec3 kBackVec = attackVec * kBackVel;
		//速度を徐々に減らす
		kBackVel -= 2.0f;

		if (kBackVel <= 0.0f) {
			isKnockBack = false;
		}
		position += kBackVec;
	}
	else
	{
		kBackVel = SWAY_SPEED;
	}
}

void Enemy::Init()
{
	position = Vec3(0, 0, 0);
}

void Enemy::Update(const Vec3& playerPos, const Vec3& attackVec)
{
	if (!isAlive)return;
	Move(playerPos);
	StateControl();
	KnockBack(attackVec);
	Attack();
	Sway();

	forwardVec = Vec3(playerPos - position);
	forwardVec.Normalize();

	XMFLOAT3 pos = position.ConvertXMFLOAT3();
	attackPos = position + this->attackVec * ATTACK_RANGE;
	attackPos.y += 30;
	bodySphere.center = XMLoadFloat3(&pos);
	object.ChangePosition(pos);
	sphere.ChangePosition(attackPos.ConvertXMFLOAT3());
}

void Enemy::Draw()
{
	if (!isAlive)return;
	object.Draw();
	if (isHit) {
		sphere.Draw();
	}
}

void Enemy::Dead()
{
	isAlive = false;
}

void Enemy::Damage(float damage)
{
	//実際に与えるダメージ
	float actualDamage = damage;
	if (isGuard) {
		actualDamage *= (100 - REDUCTION_RATE) / 100;
	}
	HP -= damage;
	if (HP <= 0) {
		Dead();
	}
}