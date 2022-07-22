#pragma once
#include"struct.h"

namespace HHelper
{
	/*---- �֗��ϐ� ----*/

	static const int COLOR_MAX = 255;														//�F�̍ő�l
	static const XMFLOAT3 COLOR_RED_VIVID = XMFLOAT3(COLOR_MAX, 0, 0);						//RGB�U��؂�̐�
	static const XMFLOAT3 COLOR_GREEN_VIVID = XMFLOAT3(0, COLOR_MAX, 0);					//RGB�U��؂�̗�
	static const XMFLOAT3 COLOR_BLUE_VIVID = XMFLOAT3(0, 0, COLOR_MAX);						//RGB�U��؂�̐�
	static const XMFLOAT3 COLOR_CYAN_VIVID = XMFLOAT3(0, COLOR_MAX, COLOR_MAX);				//RGB�U��؂�̃V�A��
	static const XMFLOAT3 COLOR_MAGENTA_VIVID = XMFLOAT3(COLOR_MAX, 0, COLOR_MAX);			//RGB�U��؂�̃}�[���^
	static const XMFLOAT3 COLOR_YELLOW_VIVID = XMFLOAT3(COLOR_MAX, COLOR_MAX, 0);				//RGB�U��؂�̃C�G���[
	static const XMFLOAT3 COLOR_BLACK_VIVID = XMFLOAT3(0, 0, 0);							//RGB�U��؂�̍�
	static const XMFLOAT3 COLOR_WHITE_VIVID = XMFLOAT3(COLOR_MAX, COLOR_MAX, COLOR_MAX);	//RGB�U��؂�̔�

	static const float H_PI_F = 3.14159265359;												//�~���� 180�x
	static const float H_PI_DIV_F = H_PI_F / 2.0f;											//�~���� 90�x
	static const float H_PI_3DIV_F = H_PI_F + H_PI_3DIV_F;									//�~���� 270�x
	static const float H_2PI_F = H_PI_F * 2.0f;												//�~���� 360�x

	/*---- �֗��֐� ----*/

	//2D���W���ł̓�_�Ԃ̋��������߂�
	inline float Distance2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return sqrtf(powf(lhs.x - rhs.x, 2.0f) + powf(lhs.y - rhs.y, 2.0f));
	}
	//3D���W���ł̓�_�Ԃ̋��������߂�
	inline float Distance3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return sqrtf(powf(lhs.x - rhs.x, 2.0f) + powf(lhs.y - rhs.y, 2.0f) + powf(lhs.z - rhs.z, 2.0f));
	}

	//���ς����߂�
	inline float Dot2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	inline float Dot3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	//�O�ς����߂�
	inline float Cross2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}
	inline XMFLOAT3 Cross3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		//�^�C�v�~�X���Ă�\������
		return XMFLOAT3(lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x);
	}

	//�x�N�g���̒��������߂�
	inline float Length2D(const XMFLOAT2& rhs) {
		return sqrtf(Dot2D(rhs, rhs));
	}
	inline float Length3D(const XMFLOAT3& rhs) {
		return sqrtf(Dot3D(rhs, rhs));
	}

	//�x�N�g���𐳋K������
	inline XMFLOAT2 Normalize2D(const XMFLOAT2& rhs) {
		float len = Length2D(rhs);
		XMFLOAT2 buff = rhs;
		buff.x /= len;
		buff.y /= len;
		return buff;
	}
	inline XMFLOAT3 Normalize3D(const XMFLOAT3& rhs) {
		float len = Length3D(rhs);
		XMFLOAT3 buff = rhs;
		buff.x /= len;
		buff.y /= len;
		buff.z /= len;
		return buff;
	}

	//�����𑫂�
	inline XMFLOAT2 AddXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x + rhs.x, lhs.y + rhs.y);
	}
	inline XMFLOAT3 AddXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	//����������
	inline XMFLOAT2 SubXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x - rhs.x, lhs.y - rhs.y);
	}
	inline XMFLOAT3 SubXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		XMFLOAT3 buff = XMFLOAT3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);

		//����Ȃ�0�ɋ߂�������0�ɂ���
		if (fabs(buff.x) < 0.00001f) {
			buff.x = 0;
		}
		if (fabs(buff.y) < 0.00001f) {
			buff.y = 0;
		}
		if (fabs(buff.z) < 0.00001f) {
			buff.z = 0;
		}

		return buff;
	}

	//������������
	inline XMFLOAT2 MulXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x * rhs.x, lhs.y * rhs.y);
	}
	inline XMFLOAT3 MulXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	//����������
	inline XMFLOAT2 DivXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x / rhs.x, lhs.y / rhs.y);
	}
	inline XMFLOAT3 DivXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	//�����擾
	inline int GetRand(const int& min, const int& max) {
		return (rand() % (max - min + 1)) + min;
	}
	inline XMFLOAT3 GetRandXMFLOAT3(const int& min, const int& max) {
		return XMFLOAT3(GetRand(min, max), GetRand(min, max), GetRand(min, max));
	}

	////��ʒ���
	//inline XMFLOAT3 WindowCenterPos() {
	//	return XMFLOAT3(window_width / 2.0f, window_height / 2.0f, 0);
	//}

	////��ʃT�C�Y�̔���
	//inline XMFLOAT2 WindowHalfSize() {
	//	return XMFLOAT2(window_width / 2.0f, window_height / 2.0f);
	//}

	////���C��Object3D�̓����蔻��
	//inline bool RayToModelCollision(const Object3D& target, const Ray& ray, XMFLOAT3& impactPos, float& distance, XMFLOAT3& hitNormal) {
	//	//�������Ă���|���S���̃f�[�^��ۑ�����悤�ϐ�	�Փ˒n�_�A�����A�Փ˖ʂ̖@��
	//	vector<tuple<XMFLOAT3, float, XMFLOAT3>> buff{};

	//	float epsilon = 1.0e-5f;
	//	/*-----target����|���S���𔲂����-----*/
	//	vector<Porygon> targetPorygon;		//�|���S���ۑ��p�R���e�i

	//	//target�̃|���S�����ɍ��킹�ă��T�C�Y
	//	targetPorygon.resize(target.indices.size() / 3.0f);

	//	//�|���S���̒��g����
	//	for (int i = 0; i < targetPorygon.size(); ++i) {
	//		targetPorygon.at(i).p1 = target.vertices.at(target.indices.at(i * 3));
	//		targetPorygon.at(i).p2 = target.vertices.at(target.indices.at((i * 3) + 1));
	//		targetPorygon.at(i).p3 = target.vertices.at(target.indices.at((i * 3) + 2));
	//		targetPorygon.at(i).isActive = true;
	//	}

	//	/*-----�ۑ������|���S���̒��_���W�Ƀ��[���h�ϊ��s���������-----*/
	//	//���[���h�s��
	//	XMMATRIX matWorld = XMMatrixIdentity();
	//	matWorld *= target.matScale;
	//	matWorld *= target.matRot;
	//	matWorld *= target.matTrans;
	//	for (int i = 0; i < targetPorygon.size(); ++i) {
	//		//���_��ϊ�
	//		XMStoreFloat3(&targetPorygon.at(i).p1.pos, XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p1.pos), matWorld));
	//		XMStoreFloat3(&targetPorygon.at(i).p2.pos, XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p2.pos), matWorld));
	//		XMStoreFloat3(&targetPorygon.at(i).p3.pos, XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p3.pos), matWorld));
	//		//�@������]�s�񕪂����ϊ�
	//		XMStoreFloat3(&targetPorygon.at(i).p1.normal, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p1.normal), target.matRot)));
	//		XMStoreFloat3(&targetPorygon.at(i).p2.normal, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p2.normal), target.matRot)));
	//		XMStoreFloat3(&targetPorygon.at(i).p3.normal, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p3.normal), target.matRot)));
	//	}

	//	/*-----���C�̕����Ɩ@�������������Ȃ珜�O-----*/
	//	for (int i = 0; i < targetPorygon.size(); ++i) {
	//		//�܂���1�ڂ̒��_���`�F�b�N
	//		float kari = XMVector3Dot(XMLoadFloat3(&targetPorygon.at(i).p1.normal), ray.dir).m128_f32[0];
	//		if (XMVector3Dot(XMLoadFloat3(&targetPorygon.at(i).p1.normal), ray.dir).m128_f32[0] > -0.0001f) {
	//			//�����܂ŗ����犮�S�ɔ��Α��������Ă���̂ŁA�폜�t���O�����Ă�
	//			targetPorygon.at(i).isActive = false;
	//			continue;
	//		}
	//	}

	//	/*-----�|���S����3���_�Ƌ��E���̓����蔻����s���A���ȏ㋗�����������ꍇ�͏������΂�-----*/

	//	/*-----�|���S�����Ƃɓ����蔻��-----*/
	//	//���������̓|���S�����ƂɌv�Z����
	//	for (int i = 0; i < targetPorygon.size(); ++i) {
	//		/*-----���C�ƕ��ʂ̏Փ˓_���v�Z����-----*/

	//		//�|���S��������������Ă����玟�̏�����
	//		if (targetPorygon.at(i).isActive == false) continue;

	//		//���C�̊J�n�n�_���畽�ʂɂ��낵�������̒��������߂�
	//		XMFLOAT3 planeNorm = { -targetPorygon.at(i).p1.normal.x,-targetPorygon.at(i).p1.normal.y,-targetPorygon.at(i).p1.normal.z };
	//		float rayToOriginLength = XMVector3Dot(ray.pos, XMLoadFloat3(&planeNorm)).m128_f32[0];
	//		float planeToOriginLength = XMVector3Dot(XMLoadFloat3(&targetPorygon.at(i).p1.pos), XMLoadFloat3(&planeNorm)).m128_f32[0];
	//		//���_���畽�ʂɂ��낵�������̒���
	//		float perpendicularLine = rayToOriginLength - planeToOriginLength;

	//		//�O�p�֐��𗘗p���Ď��_����Փ˓X�܂ł̋��������߂�
	//		float dist = XMVector3Dot(XMLoadFloat3(&planeNorm), ray.dir).m128_f32[0];
	//		float impDistance = perpendicularLine / -dist;

	//		//distance��0�����̏ꍇ������Ă��Ȃ�
	//		/*if (impDistance < 0) {
	//			targetPorygon.at(i).isActive = false;
	//			continue;
	//		}*/

	//		//�Փ˒n�_
	//		XMFLOAT3 impactPoint = { ray.pos.m128_f32[0] + ray.dir.m128_f32[0] * impDistance,
	//								ray.pos.m128_f32[1] + ray.dir.m128_f32[1] * impDistance,
	//								ray.pos.m128_f32[2] + ray.dir.m128_f32[2] * impDistance };

	//		/*-----�Փ˓_���|���S���̓����ɂ��邩�𒲂ׂ�-----*/
	//		XMVECTOR m;

	//		/*��1�{��*/
	//		XMVECTOR impactToP1 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p1.pos.x - impactPoint.x, targetPorygon.at(i).p1.pos.y - impactPoint.y, targetPorygon.at(i).p1.pos.z - impactPoint.z));
	//		XMVECTOR P2ToP1 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p2.pos.x - targetPorygon.at(i).p1.pos.x, targetPorygon.at(i).p2.pos.y - targetPorygon.at(i).p1.pos.y, targetPorygon.at(i).p2.pos.z - targetPorygon.at(i).p1.pos.z));
	//		m = XMVector3Cross(impactToP1, P2ToP1);
	//		//���K��
	//		m = XMVector3Normalize(m);
	//		//�@���ƈ�v���Ă��邩���ׂ�
	//		float result = XMVector3Dot(m, XMLoadFloat3(&targetPorygon.at(i).p1.normal)).m128_f32[0];
	//		if (result <= 0) {
	//			//���ʂ�0�ȊO��������Փ˒n�_���|���S���̓����ł͂Ȃ��̂ŁA�Փ˂��Ă��Ȃ�
	//			targetPorygon.at(i).isActive = false;
	//			continue;
	//		}

	//		/*��2�{��*/
	//		XMVECTOR impactToP2 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p2.pos.x - impactPoint.x, targetPorygon.at(i).p2.pos.y - impactPoint.y, targetPorygon.at(i).p2.pos.z - impactPoint.z));
	//		XMVECTOR P3ToP2 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p3.pos.x - targetPorygon.at(i).p2.pos.x, targetPorygon.at(i).p3.pos.y - targetPorygon.at(i).p2.pos.y, targetPorygon.at(i).p3.pos.z - targetPorygon.at(i).p2.pos.z));
	//		m = XMVector3Cross(impactToP2, P3ToP2);
	//		//���K��
	//		m = XMVector3Normalize(m);
	//		//�@���ƈ�v���Ă��邩���ׂ�
	//		result = XMVector3Dot(m, XMLoadFloat3(&targetPorygon.at(i).p1.normal)).m128_f32[0];
	//		if (result <= 0) {
	//			//���ʂ�0�ȊO��������Փ˒n�_���|���S���̓����ł͂Ȃ��̂ŁA�Փ˂��Ă��Ȃ�
	//			targetPorygon.at(i).isActive = false;
	//			continue;
	//		}

	//		/*��3�{��*/
	//		XMVECTOR impactToP3 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p3.pos.x - impactPoint.x, targetPorygon.at(i).p3.pos.y - impactPoint.y, targetPorygon.at(i).p3.pos.z - impactPoint.z));
	//		XMVECTOR P1ToP3 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p1.pos.x - targetPorygon.at(i).p3.pos.x, targetPorygon.at(i).p1.pos.y - targetPorygon.at(i).p3.pos.y, targetPorygon.at(i).p1.pos.z - targetPorygon.at(i).p3.pos.z));
	//		m = XMVector3Cross(impactToP3, P1ToP3);
	//		//���K��
	//		m = XMVector3Normalize(m);
	//		//�@���ƈ�v���Ă��邩���ׂ�
	//		result = XMVector3Dot(m, XMLoadFloat3(&targetPorygon.at(i).p1.normal)).m128_f32[0];
	//		if (result <= 0) {
	//			//���ʂ�0�ȊO��������Փ˒n�_���|���S���̓����ł͂Ȃ��̂ŁA�Փ˂��Ă��Ȃ�
	//			targetPorygon.at(i).isActive = false;
	//			continue;
	//		}

	//		/*�����܂ŗ�����|���S���ɏՓ˂��Ă�I*/
	//		tuple<XMFLOAT3, float, XMFLOAT3> buffer{};
	//		get<0>(buffer) = impactPoint;
	//		get<1>(buffer) = impDistance;
	//		get<2>(buffer) = targetPorygon.at(i).p1.normal;
	//		buff.push_back(buffer);
	//	}

	//	//buff�̒l��1�ȏゾ�����狗�����ŏ��̗v�f������
	//	if (buff.size() >= 1) {
	//		//�������ŏ��̗v�f������
	//		int min = 0;
	//		float minDistance = 100000;
	//		for (int i = 0; i < buff.size(); ++i) {
	//			if (fabs(get<1>(buff.at(i))) < fabs(minDistance)) {
	//				minDistance = get<1>(buff.at(i));
	//				min = i;
	//			}
	//		}

	//		//���������ŏ��l��������return
	//		impactPos = get<0>(buff.at(min));
	//		distance = get<1>(buff.at(min));
	//		hitNormal = get<2>(buff.at(min));
	//		return true;
	//	}
	//	else {
	//		impactPos = { 0,0,0 };
	//		distance = 0;
	//		hitNormal = { 0,0,0 };
	//		return false;
	//	}
	//}

	//��ʓ��Ɏ��܂��Ă��邩�𔻒�
	//inline bool CheckInScreen(const XMFLOAT3& checkPos, const float& virtualWidth, const float& virtualHeight, const XMMATRIX& matView, const XMMATRIX& matPerspective) {
	//	float w = window_width / 2.0f;
	//	float h = window_height / 2.0f;
	//	XMMATRIX viewport = {
	//	w, 0, 0, 0,
	//	0, -h, 0, 0,
	//	0, 0, 1, 0,
	//	w, h, 0, 1
	//	};

	//	// �r���[�ϊ��ƃv���W�F�N�V�����ϊ�
	//	XMVECTOR worldPos = XMLoadFloat3(&checkPos);
	//	worldPos = XMVector3Transform(worldPos, matView);
	//	worldPos = XMVector3Transform(worldPos, matPerspective);

	//	XMFLOAT3 temp;
	//	XMStoreFloat3(&temp, worldPos);
	//	// z�Ŋ�����-1~1�͈̔͂Ɏ��߂�
	//	// �X�N���[���ϊ�
	//	XMVECTOR viewVec = XMVectorSet(temp.x / temp.z, temp.y / temp.z, 1.0f, 1.0f);
	//	viewVec = XMVector3Transform(viewVec, viewport);
	//	XMFLOAT3 pos{};
	//	XMStoreFloat3(&pos, viewVec);


	//	if (pos.x > -virtualWidth && pos.x < window_width + virtualWidth && pos.y > -virtualHeight && pos.y < window_height + virtualHeight) {

	//		return true;
	//	}
	//	else {

	//		return false;

	//	}
	//}

	//inline bool SphereCollision(Sprite left, Sprite right)
	//{
	//	//���[���h���W�n���s�񂩂�ǂݎ��
	//	XMFLOAT3 position1 = { left.matTrans.r[3].m128_f32[0],left.matTrans.r[3].m128_f32[1],left.matTrans.r[3].m128_f32[2] };
	//	XMFLOAT3 position2 = { right.matTrans.r[3].m128_f32[0],right.matTrans.r[3].m128_f32[1],right.matTrans.r[3].m128_f32[2] };
	//	//�Q�̍��W�̍�
	//	XMVECTOR position_sub = XMVectorSet(position1.x - position2.x,
	//		position1.y - position2.y,
	//		position1.z - position2.z,
	//		0);
	//	//�Q�̍��W�̋���
	//	position_sub = XMVector3Length(position_sub);
	//	float distance = position_sub.m128_f32[0];

	//	//���������a�̘a�ȉ��Ȃ炠�����Ă���
	//	if (distance <= left.radius + right.radius) {
	//		return true;
	//	}
	//	return false;
	//}
}