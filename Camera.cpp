#include "Camera.h"
#include "Struct.h"
#include "HHelper.h"
#include "DirectXBase.h"
#include <d3d12.h>
#include "Input.h"

Camera::Camera() {
	eye = XMFLOAT3(0, 0, 0);		//視点座標		ゲームワールド内でのカメラ座標
	target = XMFLOAT3(0, 0, 0);		//注視点座標		ゲームワールド内でカメラが見ている座標
	up = XMFLOAT3(0, 1, 0);											//上方向ベクトル	ゲームワールド内でカメラから見て上方向を指すベクトル
	//matView = XMMatrixLookAtLH(eye.ConvertXMVECTOR(), target.ConvertXMVECTOR(), up.ConvertXMVECTOR());
	//XMStoreFloat3(&(forwardVec), XMVector3Normalize(XMLoadFloat3(&forwardVec)));
	angleOfView = 60.0f;
}

void Camera::GenerateMatView()
{
	matView = XMMatrixLookAtLH(eye.ConvertXMVECTOR(), target.ConvertXMVECTOR(), up.ConvertXMVECTOR());
	//透視投影変換行列
	matPerspective = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),				//画角(60度)
		(float)window_width / window_height,	//アスペクト比
		0.1f, 1000000.0f							//前端、奥端
	);
	//射影変換行列
	matProjection = XMMatrixOrthographicOffCenterLH(0, window_width, window_height, 0, 0.01f, 100000.0f);
}

void Camera::Init()
{
	eye = Vec3(0, 60, 200);
	target = Vec3(0, 0, 0);
	up = Vec3(0, 1, 0);
	rotationMat = XMMatrixIdentity();
	upRotationMat = XMMatrixIdentity();
	matView = XMMatrixLookAtLH(eye.ConvertXMVECTOR(), target.ConvertXMVECTOR(), up.ConvertXMVECTOR());
	matPerspective = {};
	matProjection = {};
	Camera::angleOfView = 60;
	angleXZ = 0;
	forwardVec = Vec3{ 0,0,1 };

}

void Camera::Update(const Vec3&pos)
{

	//forwardVec.x = cosf(angleXZ);
	//forwardVec.z = sinf(angleXZ);


	//// 視点が限界を超えないようにする。
	//if (1.0f < forwardVec.y) forwardVec.y = 1.0f;
	//if (forwardVec.y < -1.0f) forwardVec.y = -1.0f;

	//// 視点座標から視点点座標を求める。
	//const float EYE_TARGET = 100.0f;
	//target = eye + forwardVec * EYE_TARGET;

	// 上ベクトルを求める。
/*	if (Input::Instance()->isPad(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		forwardVec = Vec3(0, 0, 0) - pos;
		forwardVec.Normalize();
		forwardVec.x += 0.5f;
		forwardVec.y -= 0.3f;
		forwardVec.z += 0.5f;
		forwardVec.Normalize();
		eye = forwardVec * -200.0f;
		eye += pos;
		target = forwardVec * 200.0f;
		target += pos;
	}
	else */{
		XMFLOAT2 rightStick = {};
		rightStick.x = Input::Instance()->isPadThumb(XINPUT_THUMB_RIGHTSIDE);
		if (fabs(rightStick.x) <= 0.2f) { rightStick.x = 0; }
		rightStick.y = Input::Instance()->isPadThumb(XINPUT_THUMB_RIGHTVERT);
		if (fabs(rightStick.y) <= 0.2f) { rightStick.y = 0; }

		if (Input::Instance()->isKey(DIK_RIGHT)) { rightStick.x = 1.0f; }
		if (Input::Instance()->isKey(DIK_LEFT)) { rightStick.x = -1.0f; }
		if (Input::Instance()->isKey(DIK_UP)) { rightStick.y = 1.0f; }
		if (Input::Instance()->isKey(DIK_DOWN)) { rightStick.y = -1.0f; }


		angleXZ -= rightStick.x * ROT_UNIT;

		float rot_x = cosf(angleXZ) * 1.0f;
		float rot_y = sinf(angleXZ) * 1.0f;

		forwardVec = Vec3(rot_x, -0.3f, rot_y);
		forwardVec.Normalize();

		eye = forwardVec * -200.0f;
		eye += pos;
		target = forwardVec * 200.0f;
		target += pos;
	}
	//float add = rightStick.y * ADD_UNIT;
	//eye.y += add;
	//target -= add;

	//AddRotationXZ(rot);
}

void Camera::AddRotation(const float& RotX, const float& RotY, const float& RotZ)
{

	// カメラの回転行列を回転させる。
	DirectX::XMMATRIX buff = DirectX::XMMatrixIdentity();
	buff *= XMMatrixRotationZ(RotZ);
	buff *= XMMatrixRotationX(RotX);
	buff *= XMMatrixRotationY(RotY);

	rotationMat = buff * rotationMat;

}

void Camera::AddRotationXZ(const float& Rot)
{

	angleXZ += Rot;

}

void Camera::Move(const float& Speed)
{
	Vec3 forwardVecBuff = forwardVec;
	forwardVecBuff.y = 0;
	eye += forwardVecBuff * Speed;

}

Vec3 Camera::GetEyeVector()
{
	XMFLOAT3 returnBuff = HHelper::Normalize3D(XMFLOAT3(honraiTarget.x - honraiEye.x, honraiTarget.y - honraiEye.y, honraiTarget.z - honraiEye.z));
	return returnBuff;
}
