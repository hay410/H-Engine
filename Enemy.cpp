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
	//�O�ς��g���č��E���������
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
	//���b�N�I�����͈ړ����x��x������
	isLockOn = false;
	//�{�^�����L�[�������Ă�Ԃ̓��b�N�I����ԂƂ���
	if (Input::Instance()->isPad(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKey(DIK_LSHIFT)) { isLockOn = true; }
	//���b�N�I����ԂɈڍs�����Ƃ��X�s�[�h��ύX(�P��̂�)
	if (Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKeyTrigger(DIK_LSHIFT)) { speed = WALK_SPEED; }
	//���b�N�I������߂��Ƃ��͈ړ����x��߂�
	if (Input::Instance()->isPadRelease(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKeyRelease(DIK_LSHIFT)) { speed = MAX_SPEED; }

	forwardVec = previousForwardVec;

}

//�X�E�F�C(���)
void Enemy::Sway()
{
	//���͏��𓾂Ă���
	bool input = false;
	if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_A)) {
		input = true;
	}

	//�L�[��������Ă��Ă��X�E�F�C���s���Ă��Ȃ���΃X�E�F�C��������
	if (input && !isSway) {
		isSway = true;
		//���͂����Ƃ��ɑ��x��ύX(1��̂�)
		speed = SWAY_SPEED;
	}

	//�X�E�F�C���̏���
	if (isSway) {
		//���x�����X�Ɍ��炷
		speed -= 2.0f;
		//���@�����b�N�I����Ԃ̏ꍇ�͕����A�����łȂ��ꍇ�͑���̑��x�܂Ŗ߂�
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

				//�U���h���̓��͂����
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

				//�U���h���̓��͂����
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
