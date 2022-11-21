#include"Enemy.h"
#include"HHelper.h"

Enemy::Enemy()
{
	object.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "King", L"Resources/Object/King/color.png");
	position = XMFLOAT3(0, 0, 0);
	object.ChangeScale({ 20,20,20 });
	forwardVec = Vec3(0, 0, 1);
	//angle = 0;
	radius = RADIUS;
	previousForwardVec = forwardVec;
	speed = MAX_SPEED;
	isSway = false;
	isLockOn = false;
	isGuard = false;
	isAlive = false;
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
}

void Enemy::Generate(const Vec3& position,const Vec3&playerPos)
{
	this->position = position;
	angle = atan2(playerPos.x - position.x, playerPos.z - position.z);
	isAlive = true;
}

void Enemy::Move(const Vec3& playerPos)
{
	//外積を使って左右判定をする
	float crossBuff = HHelper::Cross2D(XMFLOAT2(playerPos.x - position.x, playerPos.z - position.z), XMFLOAT2(sinf(angle), cosf(angle)));
	if (crossBuff > 0) {
		angle += ADD_ANGLE;
	}
	else if (crossBuff < 0) {
		angle -= ADD_ANGLE;
	}

	position += XMFLOAT3(sinf(angle) * speed, 0, cosf(angle) * speed);
}

void Enemy::Walk()
{
	//ロックオン中は移動速度を遅くする
	isLockOn = false;
	//ボタンかキーを押してる間はロックオン状態とする
	if (Input::Instance()->isPad(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKey(DIK_LSHIFT)) { isLockOn = true; }
	//ロックオン状態に移行したときスピードを変更(１回のみ)
	if (Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKeyTrigger(DIK_LSHIFT)) { speed = WALK_SPEED; }
	//ロックオンをやめたときは移動速度を戻す
	if (Input::Instance()->isPadRelease(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKeyRelease(DIK_LSHIFT)) { speed = MAX_SPEED; }

	forwardVec = previousForwardVec;

}

//スウェイ(回避)
void Enemy::Sway()
{
	//入力情報を得ておく
	bool input = false;
	if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_A)) {
		input = true;
	}

	//キーが押されていてかつスウェイを行っていなければスウェイをさせる
	if (input && !isSway) {
		isSway = true;
		//入力したときに速度を変更(1回のみ)
		speed = SWAY_SPEED;
	}

	//スウェイ中の処理
	if (isSway) {
		//速度を徐々に減らす
		speed -= 2.0f;
		//自機がロックオン状態の場合は歩き、そうでない場合は走りの速度まで戻す
		if (!isLockOn) {
			if (speed <= MAX_SPEED) {
				speed = MAX_SPEED;
				isSway = false;
			}
		}
		else
		{
			if (speed <= WALK_SPEED) {
				speed = WALK_SPEED;
				isSway = false;
			}
		}
	}
}

void Enemy::Guard()
{
	isGuard = false;
	if (Input::Instance()->isKey(DIK_E) || Input::Instance()->isPad(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		isGuard = true;
	}
}

void Enemy::Attack()
{
	isHit = false;
	Jab();
	Hook();
	Upper();
}

void Enemy::Jab()
{
	if (!isHook && !isUpper) {
		if (Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
			isJab = true;
		}
	}

	if (!isJab)return;

	if (jabStartTmier < MAX_JAB_START_TIMER) {
		jabStartTmier++;
	}
	else {
		if (jabHitTimer < MAX_JAB_HIT_TIMER) {
			jabHitTimer++;
			isHit = true;
		}
		else {
			if (jabEndTimer < MAX_JAB_END_TIMER) {
				jabEndTimer++;

				//攻撃派生の入力を取る
				if (Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
					isHook = true;
				}
			}
			else {
				isJab = false;
				jabStartTmier = 0;
				jabHitTimer = 0;
				jabEndTimer = 0;
			}
		}

	}
}

void Enemy::Hook()
{
	if (!isHook)return;

	if (hookStartTmier < MAX_HOOK_START_TIMER) {
		hookStartTmier++;
	}
	else {
		if (hookHitTimer < MAX_HOOK_HIT_TIMER) {
			hookHitTimer++;
			isHit = true;
		}
		else {
			if (hookEndTimer < MAX_HOOK_END_TIMER) {
				hookEndTimer++;

				//攻撃派生の入力を取る
				if (Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
					isUpper = true;
				}
			}
			else {
				isHook = false;
				hookStartTmier = 0;
				hookHitTimer = 0;
				hookEndTimer = 0;
			}
		}

	}
}

void Enemy::Upper()
{
	if (!isUpper)return;

	if (upperStartTmier < MAX_HOOK_START_TIMER) {
		upperStartTmier++;
	}
	else {
		if (upperHitTimer < MAX_HOOK_HIT_TIMER) {
			upperHitTimer++;
			isHit = true;
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
			}
		}

	}
}

void Enemy::Init()
{
	position = Vec3(0, 0, 0);
}

void Enemy::Update(const Vec3& playerPos)
{
	if (!isAlive)return;

	Vec3 pVec = position - playerPos;
	float pLength = pVec.Length();
	if (pLength >= WALK_DISTANCE && pLength <= RUN_DISTANCE) {
		speed = WALK_SPEED;
	}
	else if (pLength >= RUN_DISTANCE) {
		speed = MAX_SPEED;
	}
	else if (pLength <= WALK_DISTANCE) {
		speed = 0.0f;
		availableAttack = true;
	}

	XMFLOAT3 pos = position.ConvertXMFLOAT3();
	bodySphere.center = XMLoadFloat3(&pos);
	object.ChangePosition(pos);
	Move(playerPos);
	//Sway();
	//Guard();
}

void Enemy::Draw()
{
	if (!isAlive)return;
	object.Draw();
}

void Enemy::Dead()
{
	isAlive = false;
}
