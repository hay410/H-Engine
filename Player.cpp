#include"Player.h"
#include"HHelper.h"
#include<fstream>
#include<sstream>

Player::Player()
{
	object_.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Body", L"Resources/Object/Body/Body.png");
	//object.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_LIGHT_ALPHA, "Body", L"Resources/Object/Body/Body.png");
	sphere.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "Ball", L"Resources/white1x1.png");

	position_ = XMFLOAT3( 0, 0, 0);
	object_.ChangeScale({ 1.5,1.5,1.5 });
	sphere.ChangeScale({ 10,10,10 });
	forwardVec_ = Vec3(0, 0, 1);
	radius_ = 20.0f;
	previousForwardVec_ = forwardVec_;
	speed_ = MAX_SPEED;
	isSway_ = false;
	isLockOn_ = false;
	isGuard_ = false;
	isAlive_ = true;
	is1Hit_ = true;

	insidenceFrame_ = 0;
	detectionFrame_ = 0;
	rigidityFrame_ = 0;

		
	isKnockBack_ = false;
	kBackVel_ = 0.0f;
	HP_ = MAX_HP;
	stepSpeed_ = 0.0f;
	stunTimer_ = 0;

	LoadAttackInfoFromCSV();
}

void Player::Move()
{
	float angle;
	//�R���g���[���[����
	XMFLOAT2 leftStick = { 0.0f,0.0f };
	if (!isKnockBack_) {
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
		float amountX = leftStick.x * speed_;
		float amountZ = leftStick.y * speed_;

		//���߂��ړ��ʂ��玩�@�̍��W���ړ�������
		position_ += rightVec * amountX;
		position_ += cameraForwardVec * amountZ;

		position_.x = HHelper::clamp(-1000, position_.x, 2500);
		position_.z = HHelper::clamp(-410, position_.z, 410);
		

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

			forwardVec_.x = inputVec.x * sinf(angle) + inputVec.z * cosf(angle);
			forwardVec_.z = -inputVec.x * cosf(angle) + inputVec.z * sinf(angle);
			forwardVec_.Normalize();

			//�I�u�W�F�N�g�̉�]��������
			object_.InitRotation();

			//���@�̐��ʃx�N�g���ƃJ�����̐��ʃx�N�g���̊p�x�����߂�
			angle = forwardVec_.Dot(Vec3(1, 0, 0));
			angle = acos(angle);

			if (inputVec.z < 0) {
				object_.ChangeRotation({ 0,angle,0 });
			}
			else {
				object_.ChangeRotation({ 0,HHelper::H_2PI_F - angle,0 });
			}
		}
	
		//���b�N�I�����͕�������
		Walk();

		previousForwardVec_ = forwardVec_;
	}
}

void Player::Walk()
{
	//���b�N�I�����͈ړ����x��x������
	isLockOn_ = false;
	//�{�^�����L�[�������Ă�Ԃ̓��b�N�I����ԂƂ���
	if (Input::Instance()->isPad(XINPUT_GAMEPAD_RIGHT_SHOULDER)|| Input::Instance()->isKey(DIK_LSHIFT)) {
		isLockOn_ = true;

		//Vec3 directtionVec = Vec3(enemyNearPos - position);
		//float distance = directtionVec.Length();

		//if (distance <= LOCKON_RANGE) {
		//	directtionVec.Normalize();
		//	forwardVec = directtionVec;
		//}
	}
	if (isLockOn_ && !isSway_) {
		speed_ = WALK_SPEED;
	}
	if (!isLockOn_ && !isSway_) {
		speed_ = MAX_SPEED;
	}
}

void Player::Sway()
{
	//���͏��𓾂Ă���
	bool input = false;
	if (Input::Instance()->isKeyTrigger(DIK_TAB) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_A)) {
		if (!isKnockBack_)
			input = true;
	}

	//�L�[��������Ă��Ă��X�E�F�C���s���Ă��Ȃ���΃X�E�F�C��������
	if (input && !isSway_) {
		isSway_ = true;
		//���͂����Ƃ��ɑ��x��ύX(1��̂�)
		speed_ = SWAY_SPEED;
	}

	//�X�E�F�C���̏���
	if (isSway_) {
		//���x�����X�Ɍ��炷
		speed_ -= 2.0f;
		//���@�����b�N�I����Ԃ̏ꍇ�͕����A�����łȂ��ꍇ�͑���̑��x�܂Ŗ߂�
		if (!isLockOn_) {
			if (speed_ <= MAX_SPEED) {
				speed_ = MAX_SPEED;
				isSway_ = false;
			}
		}
		else
		{
			if (speed_ <= WALK_SPEED) {
				speed_ = WALK_SPEED;
				isSway_ = false;
			}
		}
	}
}

void Player::Guard()
{
	isGuard_ = false;
	if (Input::Instance()->isKey(DIK_E) || Input::Instance()->isPad(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		if (!isKnockBack_) {
			isGuard_ = true;
			speed_ = 0;
		}
	}
	//���b�N�I������߂��Ƃ��͈ړ����x��߂�
	if (Input::Instance()->isPadRelease(XINPUT_GAMEPAD_LEFT_SHOULDER) || Input::Instance()->isKeyRelease(DIK_E)) { speed_ = MAX_SPEED; }
}

void Player::Attack()
{
	isHit_ = false;

	bool isAllAttackFalse = true;
	for (int i = 0; i < attackInfo.size(); i++) {
		if (attackInfo[i].isAttack == false)continue;
		isAllAttackFalse = false;
	}

	if (isAllAttackFalse) {
		if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
			if (!isKnockBack_)
				attackInfo[0].isAttack = true;
		}
	}

	for (int i = 0; i < attackInfo.size(); i++) {
		if (!attackInfo[i].isAttack)continue;

		if (insidenceFrame_ < attackInfo[i].insidenceFrame) {
			insidenceFrame_++;
		}
		else {
			speed_ = 0.0f;
			if (detectionFrame_ < attackInfo[i].detectionFrame) {

				if (stepSpeed_ >= 0.0f) {
					stepSpeed_ = attackInfo[i].stepDistance;
					Vec3 stepVec = forwardVec_ * stepSpeed_;
					position_ += stepVec;
					stepSpeed_ -= 2.0f;
				}

				detectionFrame_++;
				isHit_ = true;
				damage_ = attackInfo[i].damageAmount;
				valueKBackVel_ = attackInfo[i].knockBackPower;
				attackVec = forwardVec_;
			}
			else {
				if (rigidityFrame_ < attackInfo[i].rigidityFrame) {
					rigidityFrame_++;

					if (i < attackInfo.size() - 1) {
						//�U���h���̓��͂����
						if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
							attackInfo[i + 1].isAttack = true;
							attackInfo[i].isAttack = false;
							insidenceFrame_ = 0;
							detectionFrame_ = 0;
							rigidityFrame_ = 0;
							stepSpeed_ = 0.0f;
						}
					}
				}
				else {
					attackInfo[i].isAttack = false;
					insidenceFrame_ = 0;
					detectionFrame_ = 0;
					rigidityFrame_ = 0;
					speed_ = MAX_SPEED;
					is1Hit_ = true;
					stepSpeed_ = 0.0f;
				}
			}
		}
	}
}

void Player::KnockBack(const Vec3& attackVec)
{
	//�X�E�F�C���̏���
	if (isKnockBack_) {
		Vec3 kBackVec = attackVec * kBackVel_;
		//���x�����X�Ɍ��炷
		kBackVel_ -= 2.0f;
		stunTimer_++;

		if (kBackVel_ <= 0.0f) {
			kBackVel_ = 0.0f;
		}

		if (stunTimer_ > MAX_STUN_TIMER) {
			isKnockBack_ = false;
			stunTimer_ = 0;
		}

		position_ += kBackVec;
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
				case INSIDENCE_FRAME :
					a.insidenceFrame = atoi(tmp.c_str());
					break;
				case DETECTION_FRAME :
					a.detectionFrame = atoi(tmp.c_str());
					break;
				case RIGIDITY_FRAME :
					a.rigidityFrame = atoi(tmp.c_str());
					break;
				case DAMAGE_AMOUNT :
					a.damageAmount = atoi(tmp.c_str());
					break;
				case KNOCKBACK_POWER :
					a.knockBackPower = atoi(tmp.c_str());
					break;
				case STEP_DISTANCE :
					a.stepDistance = atoi(tmp.c_str());
					break;
				case STARTVEC_X :
					a.startVec.x = static_cast<float>(atoi(tmp.c_str()));
					break;
				case STARTVEC_Y :
					a.startVec.y = static_cast<float>(atoi(tmp.c_str()));
					break;
				case STARTVEC_Z :
					a.startVec.z = static_cast<float>(atoi(tmp.c_str()));
					break;
				case ENDVEC_X :
					a.endVec.x = static_cast<float>(atoi(tmp.c_str()));
					break;
				case ENDVEC_Y :
					a.endVec.y = static_cast<float>(atoi(tmp.c_str()));
					break;
				case ENDVEC_Z :
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
	position_ = Vec3(-900, -20, 0);
}

void Player::Update(const Vec3& attackVec, const Vec3& enemyNearPos)
{	
	this->enemyNearPos_ = enemyNearPos;
	bodySphere.center = position_.ConvertXMVECTOR();
	object_.ChangePosition(position_.ConvertXMFLOAT3());
	attackPos = position_ + forwardVec_ * ATTACK_RANGE;
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
	object_.Draw();
	if (isHit_) {
		sphere.Draw();
	}
}

void Player::Damage(int damage)
{
	HP_ -= damage;
	stunTimer_ = 0;
	if (HP_ <= 0) {
		Dead();
	}
}

void Player::Dead()
{
	isAlive_ = false;
}
