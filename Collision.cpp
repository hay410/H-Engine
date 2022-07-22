#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere &sphere, const Plane &plane, DirectX::XMVECTOR *inter)
{
	//���W�n�̌��_���狅�̒��S���W�ւ̋���
	XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
	//���ʂ̌��_���������Y���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	float dist = distV.m128_f32[0] - plane.distance;
	//�����̐�Βl�����a���傫����Γ������Ă��Ȃ�
	if (fabsf(dist) > sphere.radius) return false;

	//�^����_���v�Z
	if (inter)
	{
		//���ʏ�̍ŋߐړ_���A�^����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center;
	}
	return true;
}

void Collision::ClosestPtPoint2Triangle(const DirectX::XMVECTOR &point, const Triangle &triangle, DirectX::XMVECTOR *closest)
{
	//point��p0�̊O���̒��_�̈�ɂ��邩�ǂ����`�F�b�N
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	XMVECTOR p0_p2 = triangle.p2 - triangle.p0;
	XMVECTOR p0_pt = point - triangle.p0;

	XMVECTOR d1 = XMVector3Dot(p0_p1, p0_pt);
	XMVECTOR d2 = XMVector3Dot(p0_p2, p0_pt);

	if (d1.m128_f32[0] <= 0.0f &&
		d2.m128_f32[0] <= 0.0f)
	{
		//p0���ŋߖT
		*closest = triangle.p0;
		return;
	}

	//point��p1�̊O���̒��_�̈�́@���ɂ��邩�ǂ����`�F�b�N
	XMVECTOR p1_pt = point - triangle.p1;

	XMVECTOR d3 = XMVector3Dot(p0_p1, p1_pt);
	XMVECTOR d4 = XMVector3Dot(p0_p2, p1_pt);

	if (d3.m128_f32[0] >= 0.0f &&
		d4.m128_f32[0] <= d3.m128_f32[0])
	{
		//p1���ŋߖT
		*closest = triangle.p1;
		return;
	}

	//point��p0_p1�̕ϗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1.m128_f32[0] * d4.m128_f32[0] -
		d3.m128_f32[0] * d2.m128_f32[0];
	if (vc <= 0.0f &&
		d1.m128_f32[0] >= 0.0f &&
		d3.m128_f32[0] <= 0.0f)
	{
		float v = d1.m128_f32[0] / (d1.m128_f32[0] - d3.m128_f32[0]);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	//point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	XMVECTOR p2_pt = point - triangle.p2;

	XMVECTOR d5 = XMVector3Dot(p0_p1, p2_pt);
	XMVECTOR d6 = XMVector3Dot(p0_p2, p2_pt);
	if (d6.m128_f32[0] >= 0.0f &&
		d5.m128_f32[0] <= d6.m128_f32[0])
	{
		*closest = triangle.p2;
		return;
	}

	//point��p0_p2�̕ϗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5.m128_f32[0] * d2.m128_f32[0] -
		d1.m128_f32[0] * d6.m128_f32[0];

	if (vb <= 0.0f &&
		d2.m128_f32[0] >= 0.0f &&
		d6.m128_f32[0] <= 0.0f)
	{
		float w = d2.m128_f32[0] / (d2.m128_f32[0] - d6.m128_f32[0]);

		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	//point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3.m128_f32[0] * d6.m128_f32[0] -
		d5.m128_f32[0] * d4.m128_f32[0];

	if (va <= 0.0f &&
		(d4.m128_f32[0] - d3.m128_f32[0]) >= 0.0f &&
		(d5.m128_f32[0] - d6.m128_f32[0]) >= 0.0f)
	{
		float w = (d4.m128_f32[0] - d3.m128_f32[0]) /
			((d4.m128_f32[0] - d3.m128_f32[0]) +
				(d5.m128_f32[0] - d6.m128_f32[0]));

		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere &sphere, const Triangle &triangle, DirectX::XMVECTOR *inter)
{
	XMVECTOR p;
	//���̒��S�ɑ΂��鍷�ߐړX�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangle(sphere.center, triangle, &p);

	//�_p�Ƌ��̒��S�̍����x�N�g��
	XMVECTOR v = p - sphere.center;
	//�����̓������߂�
	//�i�����x�N�g�����m�̓��ς͎O�����̒藝�̃��[�c�̓����̎��ƈ�v����j
	v = XMVector3Dot(v, v);
	//���ƎO�p�`�̋��������a�ȉ��Ȃ瓖�����Ă��Ȃ�
	if (v.m128_f32[0] > sphere.radius * sphere.radius) return false;
	//�^����_���v�Z
	if (inter)
	{
		//�O�p�`��̍ŋߐړXp���^����_�Ƃ���
		*inter = p;
	}
	return true;
}

bool Collision::CheckRay2Plane(const Ray &ray, const Plane &plane, float *distance, DirectX::XMVECTOR *inter)
{
	const float epsilon = 1.0e-5f;	//�덷�z���p�̔����Ȓl

	//�ʖ@���Ɨ�̕����x�N�g���̓���
	float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];

	//���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon) { return false; }

	//�n�_�ƌ��_�̋����i���ʂ̖@�������j
	//�ʖ@���g���C�̎��_���W�i�ʒu�x�N�g���j�̓���
	float d2 = XMVector3Dot(plane.normal, ray.pos).m128_f32[0];

	//�n�_�ƕ��ʂ̋����i���ʂ̖@�������j
	float dist = d2 - plane.distance;

	//�n�_�ƕ��ʂ̋����i���C�����j
	float t = dist / -d1;

	//��_�����_�����ɂ���̂ŁA������Ȃ�
	if (t < 0) { return false; }

	//��������������
	if (distance) { *distance = t; }

	//��_���v�Z
	if (inter) { *inter = ray.pos + t * ray.dir; }

	return true;
}

bool Collision::CheckRay2Triangle(const Ray &ray, const Triangle triangle, float *distance, DirectX::XMVECTOR *inter)
{
	//�O�p�`������Ă��镽�ʂ��Z�o
	Plane plane;
	XMVECTOR interPlane;
	plane.normal = triangle.normal;
	plane.distance = XMVector3Dot(triangle.normal, triangle.p0).m128_f32[0];

	//���C�ƕ��ʂ��������Ă��Ȃ���΁A�������Ă��Ȃ�
	if (!CheckRay2Plane(ray, plane, distance, &interPlane)) { return false; }

	//���C�ƕ��ʂ��������Ă����̂ŁA�����ƌ�_���������܂ꂽ
	//���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
	const float epsilon = 1.0e-5f;//�ꂳ�z���p�̔����Ȓl

	XMVECTOR m;
	//��p0_p1�ɂ���
	XMVECTOR pt_p0 = triangle.p0 - interPlane;
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	m = XMVector3Cross(pt_p0, p0_p1);

	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) { return false; }



	//��p1_p2�ɂ���
	XMVECTOR pt_p1 = triangle.p1 - interPlane;
	XMVECTOR p1_p2 = triangle.p2 - triangle.p1;
	m = XMVector3Cross(pt_p1, p1_p2);

	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) { return false; }


	//��p0_p1�ɂ���
	XMVECTOR pt_p2 = triangle.p2 - interPlane;
	XMVECTOR p2_p0 = triangle.p0 - triangle.p2;
	m = XMVector3Cross(pt_p2, p2_p0);

	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) { return false; }


	//�����Ȃ̂ŁA�������Ă���
	if (inter)
	{
		*inter = interPlane;
	}
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, DirectX::XMVECTOR* inter)
{
	XMVECTOR m = ray.pos - sphere.center;
	float b = XMVector3Dot(m, ray.dir).m128_f32[0];
	float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;

	//ray�̎n�_��sphere�̊O���ɂ���(c > 0), ray��sphere�󗣂�Ă����������w���Ă���ꍇ(b > 0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}
	float discr = b * b - c;
	//���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f)
	{
		return false;
	}

	//���C�͋��ƌ������Ă���B
	//��������ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);
	//t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t < 0.0f) t = 0.0f;
	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.pos + t * ray.dir;
	}
	return true;
}

//bool Collision::RayToModelCollision(const Object3D& target, const Ray& ray, XMFLOAT3& impactPos, float& distance, XMFLOAT3& hitNormal) {
//	//�������Ă���|���S���̃f�[�^��ۑ�����悤�ϐ�	�Փ˒n�_�A�����A�Փ˖ʂ̖@��
//	vector<tuple<XMFLOAT3, float, XMFLOAT3>> buff{};
//
//	float epsilon = 1.0e-5f;
//	/*-----target����|���S���𔲂����-----*/
//	vector<Porygon> targetPorygon;		//�|���S���ۑ��p�R���e�i
//
//	//target�̃|���S�����ɍ��킹�ă��T�C�Y
//	targetPorygon.resize(target.indices.size() / 3.0f);
//
//	//�|���S���̒��g����
//	for (int i = 0; i < targetPorygon.size(); ++i) {
//		targetPorygon.at(i).p1 = target.vertices.at(target.indices.at(i * 3));
//		targetPorygon.at(i).p2 = target.vertices.at(target.indices.at((i * 3) + 1));
//		targetPorygon.at(i).p3 = target.vertices.at(target.indices.at((i * 3) + 2));
//		targetPorygon.at(i).isActive = true;
//	}
//
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
//
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
//
//	/*-----�|���S����3���_�Ƌ��E���̓����蔻����s���A���ȏ㋗�����������ꍇ�͏������΂�-----*/
//
//	/*-----�|���S�����Ƃɓ����蔻��-----*/
//	//���������̓|���S�����ƂɌv�Z����
//	for (int i = 0; i < targetPorygon.size(); ++i) {
//		/*-----���C�ƕ��ʂ̏Փ˓_���v�Z����-----*/
//
//		//�|���S��������������Ă����玟�̏�����
//		if (targetPorygon.at(i).isActive == false) continue;
//
//		//���C�̊J�n�n�_���畽�ʂɂ��낵�������̒��������߂�
//		XMFLOAT3 planeNorm = { -targetPorygon.at(i).p1.normal.x,-targetPorygon.at(i).p1.normal.y,-targetPorygon.at(i).p1.normal.z };
//		float rayToOriginLength = XMVector3Dot(ray.pos, XMLoadFloat3(&planeNorm)).m128_f32[0];
//		float planeToOriginLength = XMVector3Dot(XMLoadFloat3(&targetPorygon.at(i).p1.pos), XMLoadFloat3(&planeNorm)).m128_f32[0];
//		//���_���畽�ʂɂ��낵�������̒���
//		float perpendicularLine = rayToOriginLength - planeToOriginLength;
//
//		//�O�p�֐��𗘗p���Ď��_����Փ˓X�܂ł̋��������߂�
//		float dist = XMVector3Dot(XMLoadFloat3(&planeNorm), ray.dir).m128_f32[0];
//		float impDistance = perpendicularLine / -dist;
//
//		//distance��0�����̏ꍇ������Ă��Ȃ�
//		/*if (impDistance < 0) {
//			targetPorygon.at(i).isActive = false;
//			continue;
//		}*/
//
//		//�Փ˒n�_
//		XMFLOAT3 impactPoint = { ray.pos.m128_f32[0] + ray.dir.m128_f32[0] * impDistance,
//								ray.pos.m128_f32[1] + ray.dir.m128_f32[1] * impDistance,
//								ray.pos.m128_f32[2] + ray.dir.m128_f32[2] * impDistance };
//
//		/*-----�Փ˓_���|���S���̓����ɂ��邩�𒲂ׂ�-----*/
//		XMVECTOR m;
//
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
//
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
//
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
//
//		/*�����܂ŗ�����|���S���ɏՓ˂��Ă�I*/
//		tuple<XMFLOAT3, float, XMFLOAT3> buffer{};
//		get<0>(buffer) = impactPoint;
//		get<1>(buffer) = impDistance;
//		get<2>(buffer) = targetPorygon.at(i).p1.normal;
//		buff.push_back(buffer);
//	}
//
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
//
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