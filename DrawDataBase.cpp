#include "DrawDataBase.h"
#include "Camera.h"
#include "Enum.h"
#include "HVec.h"

void DrawDataBase::ChangeScale(XMFLOAT3 amount)
{
	scaleMat = XMMatrixScaling(amount.x, amount.y, amount.z);
}

void DrawDataBase::ChangeScale(float x, float y, float z)
{
	scaleMat = XMMatrixScaling(x, y, z);
}

void DrawDataBase::ChangeRotation(XMFLOAT3 amount)
{
	XMMATRIX buff = XMMatrixIdentity();
	buff *= XMMatrixRotationZ(amount.z);
	buff *= XMMatrixRotationX(amount.x);
	buff *= XMMatrixRotationY(amount.y);
	rotationMat = buff * rotationMat;
}
void DrawDataBase::ChangeRotation(float x, float y, float z)
{
	XMMATRIX buff = XMMatrixIdentity();
	buff *= XMMatrixRotationZ(z);
	buff *= XMMatrixRotationX(x);
	buff *= XMMatrixRotationY(y);
	rotationMat = buff * rotationMat;
}

void DrawDataBase::InitRotation()
{
	rotationMat = XMMatrixIdentity();
}

void DrawDataBase::AssignmentRotationMat(XMMATRIX amount)
{
	rotationMat = amount;
}

void DrawDataBase::ChangePosition(XMFLOAT3 amount)
{
	positionMat = XMMatrixTranslation(amount.x, amount.y, amount.z);
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);
}

void DrawDataBase::ChangePosition(float x, float y, float z)
{
	positionMat = XMMatrixTranslation(x, y, z);
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);
}

void DrawDataBase::MulRotationMat(XMMATRIX rotationMat)
{
	this->rotationMat *= rotationMat;
}

void DrawDataBase::ChangePositionAdd(XMFLOAT3 amount)
{
	positionMat *= XMMatrixTranslation(amount.x, amount.y, amount.z);
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);
}
void DrawDataBase::ChangePositionAdd(float x, float y, float z)
{
	positionMat *= XMMatrixTranslation(x, y, z);
	pos = XMFLOAT3(positionMat.r[3].m128_f32[0], positionMat.r[3].m128_f32[1], positionMat.r[3].m128_f32[2]);
}


void DrawDataBase::AssignmentWorldMatrix(const XMMATRIX& posMat, const XMMATRIX& scaleMat, const XMMATRIX& rotationMat)
{
	this->positionMat = posMat;
	this->scaleMat = scaleMat;
	this->rotationMat = rotationMat;
}

void DrawDataBase::DoNotDisplay()
{
	isDisplay = false;
}

void DrawDataBase::DisplayOnScreen()
{
	isDisplay = true;
}

bool DrawDataBase::GetIsDisplay()
{
	return isDisplay;
}

void DrawDataBase::ChangeTextureID(int textureID, int index)
{
	int indexBuff = index;

	// �C���f�b�N�X��0��艺��������0�ɂ���B
	if (indexBuff < 0) indexBuff = 0;

	// �C���f�b�N�X��textureID�R���e�i���傫��������ő�l�ɂ���B
	if (indexBuff > this->textureID.size() - 1) indexBuff = this->textureID.size() - 1;

	//�w��̃C���f�b�N�X�̃e�N�X�`��ID��ύX����B
	this->textureID.at(indexBuff) = textureID;
}

void DrawDataBase::AddTextureID(int textureID)
{
	// textureID��ǉ��B
	this->textureID.push_back(textureID);
}

void DrawDataBase::ClearTextureID()
{
	textureID.clear();
}

void DrawDataBase::MapConstDataB0(ComPtr<ID3D12Resource> constBuffB0, const ConstBufferDataB0& constBufferDataB0)
{

	// �]������s���LightCamera�̈�������ŕς���B
	XMMATRIX matProjection;
	XMMATRIX matPerspective;
	XMMATRIX matView;
	Vec3 eye;
	Vec3 target;
	Vec3 up;

	XMMATRIX matViewProjShadowMap;


	matProjection = Camera::Instance()->matProjection;
	matPerspective = Camera::Instance()->matPerspective;
	matView = Camera::Instance()->matView;
	eye = Camera::Instance()->eye;
	target = Camera::Instance()->target;
	up = Camera::Instance()->up;



	//�萔�o�b�t�@�ւ̃f�[�^�]��
	ConstBufferDataB0* constMap = nullptr;
	HRESULT result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	//���eID��backGournd�̏ꍇ�͕��s���e�ϊ����s��
	if (projectionID == PROJECTIONID_UI) {
		//���[���h�s��̍X�V
		XMMATRIX matWorld = XMMatrixIdentity();
		matWorld *= scaleMat;
		matWorld *= rotationMat;
		matWorld *= positionMat;
		constMap->mat.world = matWorld;
		constMap->mat.viewproj = Camera::Instance()->matProjection;								//���s���e�ϊ�
		constMap->eye = Camera::Instance()->eye;
		constMap->color = constBufferDataB0.color;
	}
	//���eID��object�̏ꍇ�͂��낢��ȕϊ����s��
	else if (projectionID == PROJECTIONID_OBJECT) {
		//���[���h�s��̍X�V
		XMMATRIX matWorld = XMMatrixIdentity();
		matWorld *= scaleMat;
		matWorld *= rotationMat;
		matWorld *= positionMat;
		constMap->mat.world = matWorld;												//���[���h�ϊ� * �r���[�ϊ� * �������e�ϊ�
		constMap->mat.viewproj = matView * matPerspective;
		constMap->eye = eye;
		constMap->color = constBufferDataB0.color;
	}
	//�r���{�[�h�̏ꍇ
	else if (projectionID == PROJECTIONID_BILLBOARD) {
		//���_���W
		XMVECTOR eyePosition = eye.ConvertXMVECTOR();
		//�����_���W
		XMVECTOR targetPosition = target.ConvertXMVECTOR();
		//(����)�����
		XMVECTOR upVector = up.ConvertXMVECTOR();
		//�J����Z��
		XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
		//0�x�N�g�����ƌ�������܂�Ȃ��̂ŏ��O
		assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
		assert(!XMVector3IsInfinite(cameraAxisZ));
		assert(!XMVector3Equal(upVector, XMVectorZero()));
		assert(!XMVector3IsInfinite(upVector));
		//�x�N�g���𐳋K��
		cameraAxisZ = XMVector3Normalize(cameraAxisZ);
		//�J������X������(�E����)
		XMVECTOR cameraAxisX{};
		//X���͏����->Z���̊O�ςŋ��܂�
		cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
		//�x�N�g���𐳋K��
		cameraAxisX = XMVector3Normalize(cameraAxisX);
		//�J������Y��(�����)
		XMVECTOR cameraAxisY{};
		//Y����Z��->X���̊O�ςŋ��߂�
		cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
		//�x�N�g���𐳋K��
		cameraAxisY = XMVector3Normalize(cameraAxisY);
		//�J������]�s��
		XMMATRIX matCameraRot;
		//�J�������W�n->���[���h���W�n�̕Ԋҍs��
		matCameraRot.r[0] = cameraAxisX;
		matCameraRot.r[1] = cameraAxisY;
		matCameraRot.r[2] = cameraAxisZ;
		matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
		//�]�n�ɂ��t�s��(�t��])���v�Z
		XMMATRIX matView = XMMatrixTranspose(matCameraRot);
		//���_���W��-1�����������W
		XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
		//�J�����̈ʒu���烏�[���h���_�ւ̃x�N�g��(�J�������W�n)
		XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);		//X����
		XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);		//Y����
		XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);		//Z����
		//��̃x�N�g���ɂ܂Ƃ߂�
		XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
		//�r���[�s��ɕ��s�ړ�����ݒ�
		matView.r[3] = translation;

		//�r���{�[�h�s��
		XMMATRIX billboardMat = XMMatrixIdentity();
		billboardMat.r[0] = cameraAxisX;
		billboardMat.r[1] = cameraAxisY;
		billboardMat.r[2] = cameraAxisZ;
		billboardMat.r[3] = XMVectorSet(0, 0, 0, 1);
		//���[���h�s��̍X�V
		XMMATRIX matWorld = XMMatrixIdentity();
		matWorld *= billboardMat;
		matWorld *= scaleMat;
		matWorld *= rotationMat;
		matWorld *= positionMat;
		constMap->mat.world = matWorld;												//���[���h�ϊ� * �r���[�ϊ� * �������e�ϊ�
		constMap->mat.viewproj = matView * matPerspective;
		constMap->eye = eye;
		constMap->color = constBufferDataB0.color;
	}
	constBuffB0->Unmap(0, nullptr);
}