#include"Player.h"
#include"HHelper.h"

Player::Player()
{
	object.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Body", L"Resources/Object/Body/Body.png");
	sphere.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "Ball", L"Resources/white1x1.png");
	position = XMFLOAT3( 0, 0, 0);
	object.ChangeScale({ 1.5,1.5,1.5 });
	sphere.ChangeScale({ 10,10,10 });
	forwardVec = Vec3(0, 0, 1);
	radius = 20.0f;
	previousForwardVec = forwardVec;
	speed = MAX_SPEED;
	isSway = false;
	isLockOn = false;
	isGuard = false;
	isAlive = true;
	is1Hit = true;

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
		
	isKnockBack = false;
	kBackVel = 0.0f;
	HP = MAX_HP;
	stepSpeed = 0.0f;
	stunTimer = 0;
}

void Player::Move()
{
	float angle;
	//�R���g���[���[����
	XMFLOAT2 leftStick = { 0.0f,0.0f };
	if (!isKnockBack) {
		leftStick.x = Input::Instance()->isPadThumb(XINPUT_THUMB_LEFTSIDE);
		if (fabs(leftStick.x) <= 0.1f) { leftStick.x = 0; }
		leftStick.y = Input::Instance()->isPadThumb(XINPUT_THUMB_LEFTVERT);
		if (fabs(leftStick.y) <= 0.1f) { leftStick.y = 0; }

		//�L�[�{�[�h����
		if (Input::Instance()->isKey(DIK_W)) { leftStick.y = 1.0f; }
		if (Input::Instance()->isKey(DIK_S)) { leftStick.y = -1.0f; }
		if (Input::Instance()->isKey(DIK_A)) { leftStick.x = -1.0f; }
		if (Input::Instance()->isKey(DIK_D)) { leftStick.x = 1.0f; }
	}
	
	{
		//�J�����̐��ʃx�N�g���A�E�x�N�g���A���͏�񂩂玩�@�̈ړ���������
		Vec3 cameraForwardVec = Camera::Instance()->forwardVec;
		cameraForwardVec.y = 0;
		cameraForwardVec.Normalize();
		
		//�J�����̐��ʃx�N�g������E�x�N�g���𓾂�
		Vec3 rightVec = Vec3(cameraForwardVec.z, 0, -cameraForwardVec.x);
		
		//���͏��Ƒ��x����XZ���ꂼ��̈ړ��ʂ����߂�
		float amountX = leftStick.x * speed;
		float amountZ = leftStick.y * speed;

		//���߂��ړ��ʂ��玩�@�̍��W���ړ�������
		position += rightVec * amountX;
		position += cameraForwardVec * amountZ;

		if (position.x >= 2500) {
			position.x = 2499.99f;
		}
		if (position.x <= -1000) {
			position.x = -999.99f;
		}
		if (position.z <= -410) {
			position.z = -409.99f;
		}
		if (position.z >= 410) {
			position.z = 409.99f;
		}
		

		//���͏���XZ�����ʂ̃x�N�g���ɂ���
		Vec3 inputVec = Vec3(leftStick.x, 0, leftStick.y);
		//��ƂȂ�x�N�g��
		Vec3 basicVec = Vec3(1, 0, 0);

		//���̓x�N�g�����݂���Ƃ�
		if (inputVec.Length() != 0) {
			
			//���̓x�N�g���𐳋K��
			inputVec.Normalize();
			
			//�J�����̐��ʃx�N�g���Ɗ�x�N�g���̊p�x�����߂�
			angle = cameraForwardVec.Dot(basicVec);
			angle = acos(angle);
			
			//��œ����p�x������̓x�N�g����y����]������
			if (cameraForwardVec.z < 0)angle *= -1;

			forwardVec.x = inputVec.x * sinf(angle) + inputVec.z * cosf(angle);
			forwardVec.z = -inputVec.x * cosf(angle) + inputVec.z * sinf(angle);
			forwardVec.Normalize();

			//�I�u�W�F�N�g�̉�]��������
			object.InitRotation();

			//���@�̐��ʃx�N�g���ƃJ�����̐��ʃx�N�g���̊p�x�����߂�
			angle = forwardVec.Dot(Vec3(1, 0, 0));
			angle = acos(angle);

			if (inputVec.z < 0) {
				object.ChangeRotation({ 0,angle,0 });
			}
			else {
				object.ChangeRotation({ 0,HHelper::H_2PI_F - angle,0 });
			}
		}
	
		//���b�N�I�����͕�������
		Walk();

		previousForwardVec = forwardVec;
	}
}

void Player::Walk()
{
	//���b�N�I�����͈ړ����x��x������
	isLockOn = false;
	//�{�^�����L�[�������Ă�Ԃ̓��b�N�I����ԂƂ���
	if (Input::Instance()->isPad(XINPUT_GAMEPAD_RIGHT_SHOULDER)|| Input::Instance()->isKey(DIK_LSHIFT)) {
		isLockOn = true;

		//Vec3 directtionVec = Vec3(enemyNearPos - position);
		//float distance = directtionVec.Length();

		//if (distance <= LOCKON_RANGE) {
		//	directtionVec.Normalize();
		//	forwardVec = directtionVec;
		//}
	}
	if (isLockOn && !isSway) {
		speed = WALK_SPEED;
	}
	if (!isLockOn && !isSway) {
		speed = MAX_SPEED;
	}
}

//�X�E�F�C(���)
void Player::Sway()
{
	//���͏��𓾂Ă���
	bool input = false;
	if (Input::Instance()->isKeyTrigger(DIK_TAB) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_A)) {
		if (!isKnockBack)
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

void Player::Guard()
{
	isGuard = false;
	if (Input::Instance()->isKey(DIK_E) || Input::Instance()->isPad(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		if (!isKnockBack) {
			isGuard = true;
			speed = 0;
		}
	}
	//���b�N�I������߂��Ƃ��͈ړ����x��߂�
	if (Input::Instance()->isPadRelease(XINPUT_GAMEPAD_LEFT_SHOULDER) || Input::Instance()->isKeyRelease(DIK_E)) { speed = MAX_SPEED; }
}

void Player::Attack()
{
	isHit = false;
	Jab();
	Hook();
	Upper();
}

void Player::Jab()
{
	if (!isHook && !isUpper) {
		if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
			if (!isKnockBack)
				isJab = true;
		}
	}

	if (!isJab)return;

	if (jabStartTmier < MAX_JAB_START_TIMER) {
		jabStartTmier++;
	}
	else {
		speed = 0.0f;
		if (jabHitTimer < MAX_JAB_HIT_TIMER) {

			if (stepSpeed >= 0.0f) {
				stepSpeed = JAB_STEP_RANGE;
				Vec3 stepVec = forwardVec * stepSpeed;
				position += stepVec;
				stepSpeed -= 2.0f;
			}

			jabHitTimer++;
			isHit = true;
			damage = JAB_DAMAGE;
			valueKBackVel = JAB_KNOCKBACK_POWER;
			attackVec = forwardVec;
		}
		else {
			if (jabEndTimer < MAX_JAB_END_TIMER) {
				jabEndTimer++;

				//�U���h���̓��͂����
				if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
					isHook = true;
					stepSpeed = 0.0f;
				}
			}
			else {
				isJab = false;
				jabStartTmier = 0;
				jabHitTimer = 0;
				jabEndTimer = 0;
				speed = MAX_SPEED;
				is1Hit = true;
				stepSpeed = 0.0f;
			}
		}
	}
}

void Player::Hook()
{
	if (!isHook)return;

	if (hookStartTmier < MAX_HOOK_START_TIMER) {
		hookStartTmier++;
	}
	else {
		speed = 0.0f;
		if (hookHitTimer < MAX_HOOK_HIT_TIMER) {
			if (stepSpeed >= 0.0f) {
				stepSpeed = HOOK_STEP_RANGE;
				Vec3 stepVec = forwardVec * stepSpeed;
				position += stepVec;
				stepSpeed -= 2.0f;
			}

			hookHitTimer++;
			isHit = true;
			damage = HOOK_DAMAGE;
			valueKBackVel = HOOK_KNOCKBACK_POWER;
			attackVec = forwardVec;
		}
		else {
			if (hookEndTimer < MAX_HOOK_END_TIMER) {
				hookEndTimer++;

				//�U���h���̓��͂����
				if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
					isUpper = true;
					stepSpeed = 0.0f;
				}
			}
			else {
				isHook = false;
				hookStartTmier = 0;
				hookHitTimer = 0;
				hookEndTimer = 0;
				speed = MAX_SPEED;
				is1Hit = true;
				stepSpeed = 0.0f;
			}
		}
	}
}

void Player::Upper()
{
	if (!isUpper)return;

	if (upperStartTmier < MAX_HOOK_START_TIMER) {
		upperStartTmier++;
	}
	else {
		speed = 0.0f;
		if (upperHitTimer < MAX_HOOK_HIT_TIMER) {
			if (stepSpeed >= 0.0f) {
				stepSpeed = UPPER_STEP_RANGE;
				Vec3 stepVec = forwardVec * stepSpeed;
				position += stepVec;
				stepSpeed -= 2.0f;
			}

			upperHitTimer++;
			isHit = true;
			damage = UPPER_DAMAGE;
			valueKBackVel = UPPER_KNOCKBACK_POWER;
			attackVec = forwardVec;
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
				speed = MAX_SPEED;
				is1Hit = true;
				stepSpeed = 0.0f;
			}
		}

	}
}

void Player::KnockBack(const Vec3& attackVec)
{
	//�X�E�F�C���̏���
	if (isKnockBack) {
		Vec3 kBackVec = attackVec * kBackVel;
		//���x�����X�Ɍ��炷
		kBackVel -= 2.0f;
		stunTimer++;

		if (kBackVel <= 0.0f) {
			kBackVel = 0.0f;
		}

		if (stunTimer > MAX_STUN_TIMER) {
			isKnockBack = false;
			stunTimer = 0;
		}

		position += kBackVec;
	}
	//else
	//{
	//	kBackVel = SWAY_SPEED;
	//}
}

void Player::Init()
{
	position = Vec3(-1000, -20, 0);
}

void Player::Update(const Vec3& attackVec, const Vec3& enemyNearPos)
{	
	this->enemyNearPos = enemyNearPos;
	bodySphere.center = position.ConvertXMVECTOR();
	object.ChangePosition(position.ConvertXMFLOAT3());
	attackPos = position + forwardVec * ATTACK_RANGE;
	attackPos.y += 10;
	attackSphere.center = attackPos.ConvertXMVECTOR();
	sphere.ChangePosition(attackPos.ConvertXMFLOAT3());
	Move();
	Sway();
	KnockBack(attackVec);
	Attack();
	Guard();
}

void Player::Draw()
{
	object.Draw();
	if (isHit) {
		sphere.Draw();
	}
}

void Player::Damage(int damage)
{
	HP -= damage;
	stunTimer = 0;
	if (HP <= 0) {
		Dead();
	}
}

void Player::Dead()
{
	isAlive = false;
}
