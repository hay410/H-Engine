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
	state = STATE::WAIT;
	stateTimer = 0;
	guardTimer = 0;
	HP = MAX_HP;
}

void Enemy::Generate(const Vec3& position,const Vec3&playerPos)
{
	this->position = position;
	angle = atan2(playerPos.x - position.x, playerPos.z - position.z);
	isAlive = true;
}

void Enemy::Move(const Vec3& playerPos)
{
	//�v���C���[�Ƃ̋����ɂ���ď�Ԃ�ς���
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

	//�O�ς��g���č��E���������
	float crossBuff = HHelper::Cross2D(XMFLOAT2(playerPos.x - position.x, playerPos.z - position.z), XMFLOAT2(sinf(angle), cosf(angle)));
	if (crossBuff > 0) {
		angle += ADD_ANGLE;
	}
	else if (crossBuff < 0) {
		angle -= ADD_ANGLE;
	}
	float storageAngle = angle;

	Sway();

	if(isSway) {
		if (random == 0) {
			angle += HHelper::H_PI_F / 2;
		}
		else {
			angle -= HHelper::H_PI_F / 2;
		}
	}

	position += Vec3(sinf(angle), 0, cosf(angle)) * speed;

	angle = storageAngle;
}

void Enemy::StateControl()
{
	if (availableAttack) {
		switch (state)
		{
		case STATE::WAIT:
			stateTimer++;
			if (stateTimer >= MAX_STATE_TIMER) {
				int random = HHelper::GetRand(1, 6);
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
			Attack();
			break;
		case STATE::SWAY:
			//�X�E�F�C���s���Ă��Ȃ���΃X�E�F�C��������
			if (!isSway) {
				isSway = true;
				//���͂����Ƃ��ɑ��x��ύX(1��̂�)
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
}

//�X�E�F�C(���)
void Enemy::Sway()
{
	//�X�E�F�C���̏���
	if (isSway) {
		//���x�����X�Ɍ��炷
		speed -= 2.0f;
		//���@�����b�N�I����Ԃ̏ꍇ�͕����A�����łȂ��ꍇ�͑���̑��x�܂Ŗ߂�
		
		if (speed <= MAX_SPEED) {
			speed = MAX_SPEED;
			isSway = false;
			state = STATE::WAIT;
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
			state = STATE::WAIT;
		}
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
		isJab = true;
	}

	if (!isJab)return;

	if (jabStartTmier < MAX_JAB_START_TIMER) {
		jabStartTmier++;
	}
	else {
		if (jabHitTimer < MAX_JAB_HIT_TIMER) {
			jabHitTimer++;
			isHit = true;
			damage = JAB_DAMAGE;
		}
		else {
			if (jabEndTimer < MAX_JAB_END_TIMER) {
				jabEndTimer++;

				//�U���h��
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
			hookHitTimer++;
			isHit = true;
			damage = HOOK_DAMAGE;
		}
		else {
			if (hookEndTimer < MAX_HOOK_END_TIMER) {
				hookEndTimer++;

				//�U���h���̓��͂����
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
				state = STATE::WAIT;
				is1Hit = true;
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
	StateControl();
	Move(playerPos);

	forwardVec = Vec3(playerPos - position);
	forwardVec.Normalize();

	XMFLOAT3 pos = position.ConvertXMFLOAT3();
	attackPos = position + attackVec * ATTACK_RANGE;
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

void Enemy::Damage(int damage)
{
	HP -= damage;
	if (HP <= 0) {
		Dead();
	}
}