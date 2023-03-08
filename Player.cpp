#include"Player.h"
#include"HHelper.h"
#include<fstream>
#include<sstream>

Player::Player()
{
	object.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Body", L"Resources/Object/Body/Body.png");
	//object.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_LIGHT_ALPHA, "Body", L"Resources/Object/Body/Body.png");
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

	insidenceFrame = 0;
	detectionFrame = 0;
	rigidityFrame = 0;

		
	isKnockBack = false;
	kBackVel = 0.0f;
	HP = MAX_HP;
	stepSpeed = 0.0f;
	stunTimer = 0;

	LoadAttackInfoFromCSV();
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

	bool isAllAttackFalse = true;
	for (int i = 0; i < attackInfo.size(); i++) {
		if (attackInfo[i].isAttack == false)continue;
		isAllAttackFalse = false;
	}

	if (isAllAttackFalse) {
		if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
			if (!isKnockBack)
				attackInfo[0].isAttack = true;
		}
	}

	for (int i = 0; i < attackInfo.size(); i++) {
		if (!attackInfo[i].isAttack)continue;

		if (insidenceFrame < attackInfo[i].insidenceFrame) {
			insidenceFrame++;
		}
		else {
			speed = 0.0f;
			if (detectionFrame < attackInfo[i].detectionFrame) {

				if (stepSpeed >= 0.0f) {
					stepSpeed = attackInfo[i].stepDistance;
					Vec3 stepVec = forwardVec * stepSpeed;
					position += stepVec;
					stepSpeed -= 2.0f;
				}

				detectionFrame++;
				isHit = true;
				damage = attackInfo[i].damageAmount;
				valueKBackVel = attackInfo[i].knockBackPower;
				attackVec = forwardVec;
			}
			else {
				if (rigidityFrame < attackInfo[i].rigidityFrame) {
					rigidityFrame++;

					if (i < attackInfo.size() - 1) {
						//�U���h���̓��͂����
						if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
							attackInfo[i + 1].isAttack = true;
							attackInfo[i].isAttack = false;
							insidenceFrame = 0;
							detectionFrame = 0;
							rigidityFrame = 0;
							stepSpeed = 0.0f;
						}
					}
				}
				else {
					attackInfo[i].isAttack = false;
					insidenceFrame = 0;
					detectionFrame = 0;
					rigidityFrame = 0;
					speed = MAX_SPEED;
					is1Hit = true;
					stepSpeed = 0.0f;
				}
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

void Player::LoadAttackInfoFromCSV()
{
	ifstream ifs("Resources/CSV/AttackInfo.csv");
	string str = "";
	int i = 0, j = 0;

	if (!ifs) {
		assert(0);
	}
	
	while (getline(ifs, str))
	{
		string tmp = "";
		istringstream stream(str);

		AttackInfo a;

		// ��؂蕶�����Ȃ��Ȃ�܂ŕ�������؂��Ă���
		while (getline(stream, tmp, ','))
		{
			// ��؂�ꂽ������tmp�ɓ���
			switch (j)
			{
				case static_cast<int>(ATTACK_INFO::INSIDENCE_FRAME) :
					a.insidenceFrame = atoi(tmp.c_str());
					break;
				case static_cast<int>(ATTACK_INFO::DETECTION_FRAME) :
					a.detectionFrame = atoi(tmp.c_str());
					break;
				case static_cast<int>(ATTACK_INFO::RIGIDITY_FRAME) :
					a.rigidityFrame = atoi(tmp.c_str());
					break;
				case static_cast<int>(ATTACK_INFO::DAMAGE_AMOUNT) :
					a.damageAmount = atoi(tmp.c_str());
					break;
				case static_cast<int>(ATTACK_INFO::KNOCKBACK_POWER) :
					a.knockBackPower = atoi(tmp.c_str());
					break;
				case static_cast<int>(ATTACK_INFO::STEP_DISTANCE) :
					a.stepDistance = atoi(tmp.c_str());
					break;
				case static_cast<int>(ATTACK_INFO::STARTVEC_X) :
					a.startVec.x = static_cast<float>(atoi(tmp.c_str()));
					break;
				case static_cast<int>(ATTACK_INFO::STARTVEC_Y) :
					a.startVec.y = static_cast<float>(atoi(tmp.c_str()));
					break;
				case static_cast<int>(ATTACK_INFO::STARTVEC_Z) :
					a.startVec.z = static_cast<float>(atoi(tmp.c_str()));
					break;
				case static_cast<int>(ATTACK_INFO::ENDVEC_X) :
					a.endVec.x = static_cast<float>(atoi(tmp.c_str()));
					break;
				case static_cast<int>(ATTACK_INFO::ENDVEC_Y) :
					a.endVec.y = static_cast<float>(atoi(tmp.c_str()));
					break;
				case static_cast<int>(ATTACK_INFO::ENDVEC_Z) :
					a.endVec.z = static_cast<float>(atoi(tmp.c_str()));
					break;

				default:
					break;
			}
			j++;
		}
		attackInfo.push_back(a);

		j = 0;
		i++;  // ���̐l�̔z��Ɉڂ�
	}
	attackInfo.erase(attackInfo.begin());
}

void Player::Init()
{
	position = Vec3(-900, -20, 0);
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
