#include"Player.h"
#include"HHelper.h"

Player::Player()
{
	object.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Knight", L"Resources/Object/Knight/color.png");
	sphere.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "Ball", L"Resources/white1x1.png");
	position = XMFLOAT3( 0, 0, 0);
	object.ChangeScale({ 20,20,20 });
	sphere.ChangeScale({ 10,10,10 });
	forwardVec = Vec3(0, 0, 1);
	//angle = 0;
	previousForwardVec = forwardVec;
	speed = MAX_SPEED;
	isSway = false;
	isLockOn = false;
	isGuard = false;
	isJab = false;
	isAlive = true;
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

void Player::Move()
{
	float angle;
	//コントローラー入力
	XMFLOAT2 leftStick = {};
	leftStick.x = Input::Instance()->isPadThumb(XINPUT_THUMB_LEFTSIDE);
	if (fabs(leftStick.x) <= 0.1f) { leftStick.x = 0; }
	leftStick.y = Input::Instance()->isPadThumb(XINPUT_THUMB_LEFTVERT);
	if (fabs(leftStick.y) <= 0.1f) { leftStick.y = 0; }
	
	//キーボード入力
	if (Input::Instance()->isKey(DIK_W)) { leftStick.y = 1.0f; }
	if (Input::Instance()->isKey(DIK_S)) { leftStick.y = -1.0f; }
	if (Input::Instance()->isKey(DIK_A)) { leftStick.x = -1.0f; }
	if (Input::Instance()->isKey(DIK_D)) { leftStick.x = 1.0f; }

	
	{
		//カメラの正面ベクトル、右ベクトル、入力情報から自機の移動をさせる
		Vec3 cameraForwardVec = Camera::Instance()->forwardVec;
		cameraForwardVec.y = 0;
		cameraForwardVec.Normalize();
		
		//カメラの正面ベクトルから右ベクトルを得る
		Vec3 rightVec = Vec3(cameraForwardVec.z, 0, -cameraForwardVec.x);
		
		//入力情報と速度からXZそれぞれの移動量を求める
		float amountX = leftStick.x * speed;
		float amountZ = leftStick.y * speed;

		//求めた移動量から自機の座標を移動させる
		position += rightVec * amountX;
		position += cameraForwardVec * amountZ;

		if (position.x >= 1000) {
			position.x = 999.99f;
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
		

		//入力情報をXZ軸平面のベクトルにする
		Vec3 inputVec = Vec3(leftStick.x, 0, leftStick.y);
		//基準となるベクトル
		Vec3 basicVec = Vec3(1, 0, 0);

		//入力ベクトル存在するとき
		if (inputVec.Length() != 0) {
			
			//入力ベクトルを正規化
			inputVec.Normalize();
			
			//カメラの正面ベクトルと基準ベクトルの角度を求める
			angle = cameraForwardVec.Dot(basicVec);
			angle = acos(angle);
			
			//上で得た角度から入力ベクトルをy軸回転させる
			forwardVec.x = inputVec.x * sinf(angle) + inputVec.z * cosf(angle);
			forwardVec.z = -inputVec.x * cosf(angle) + inputVec.z * sinf(angle);
			forwardVec.Normalize();

			//オブジェクトの回転を初期化
			object.InitRotation();

			//自機の正面ベクトルとカメラの正面ベクトルの角度を求める
			angle = forwardVec.Dot(Vec3(1, 0, 0));
			angle = acos(angle);

			if (inputVec.z < 0) {
				object.ChangeRotation({ 0,angle,0 });
			}
			else {
				object.ChangeRotation({ 0,HHelper::H_2PI_F - angle,0 });
			}
		}
	
		//ロックオン時は歩かせる
		Walk();

		previousForwardVec = forwardVec;
	}
}

void Player::Walk()
{
	//ロックオン中は移動速度を遅くする
	isLockOn = false;
	//ボタンかキーを押してる間はロックオン状態とする
	if (Input::Instance()->isPad(XINPUT_GAMEPAD_RIGHT_SHOULDER)|| Input::Instance()->isKey(DIK_LSHIFT)) { isLockOn = true; }
	if (isLockOn && !isSway) {
		speed = WALK_SPEED;
	}
	if (!isLockOn && !isSway) {
		speed = MAX_SPEED;
	}
	////ロックオン状態に移行したときスピードを変更(１回のみ)
	//if (Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKeyTrigger(DIK_LSHIFT)) { speed = WALK_SPEED; }
	////ロックオンをやめたときは移動速度を戻す
	//if (Input::Instance()->isPadRelease(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::Instance()->isKeyRelease(DIK_LSHIFT)) { speed = MAX_SPEED; }

	//forwardVec = previousForwardVec;

}

//スウェイ(回避)
void Player::Sway()
{
	//入力情報を得ておく
	bool input = false;
	if (Input::Instance()->isKeyTrigger(DIK_TAB) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_A)) {
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

void Player::Guard()
{
	isGuard = false;
	if (Input::Instance()->isKey(DIK_E) || Input::Instance()->isPad(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		isGuard = true;
		speed = 0;
	}
	//ロックオンをやめたときは移動速度を戻す
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
			jabHitTimer++;
			isHit = true;
		}
		else {
			if (jabEndTimer < MAX_JAB_END_TIMER) {
				jabEndTimer++;

				//攻撃派生の入力を取る
				if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
					isHook = true;
				}
			}
			else {
				isJab = false;
				jabStartTmier = 0;
				jabHitTimer = 0;
				jabEndTimer = 0;
				speed = MAX_SPEED;
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
			hookHitTimer++;
			isHit = true;
		}
		else {
			if (hookEndTimer < MAX_HOOK_END_TIMER) {
				hookEndTimer++;

				//攻撃派生の入力を取る
				if (Input::Instance()->isKeyTrigger(DIK_SPACE) || Input::Instance()->isPadTrigger(XINPUT_GAMEPAD_X)) {
					isUpper = true;
				}
			}
			else {
				isHook = false;
				hookStartTmier = 0;
				hookHitTimer = 0;
				hookEndTimer = 0;
				speed = MAX_SPEED;
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
				speed = MAX_SPEED;
			}
		}

	}
}

void Player::Init()
{
	position = Vec3(-1000, -50, 0);
}

void Player::Update()
{
	bodySphere.center = position.ConvertXMVECTOR();
	object.ChangePosition(position.ConvertXMFLOAT3());
	attackPos = position + forwardVec * ATTACK_RANGE;
	attackPos.y += 30;
	attackSphere.center = attackPos.ConvertXMVECTOR();
	sphere.ChangePosition(attackPos.ConvertXMFLOAT3());
	Move();
	Sway();
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
