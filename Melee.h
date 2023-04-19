#pragma once
#include "Object3D.h"

struct AttackInfo {
	bool isAttack;
	int insidenceFrame;		//�����t���[��
	int detectionFrame;		//����t���[��
	int rigidityFrame;		//�d���t���[��
	int damageAmount;		//�_���[�W��
	float knockBackPower;	//�m�b�N�o�b�N��
	float stepDistance;		//�X�e�b�v����
	Vec3 startVec;			//�J�n�x�N�g��
	Vec3 endVec;			//�I���x�N�g��
	AttackInfo() {
		isAttack = false;
		insidenceFrame = 0;
		detectionFrame = 0;
		rigidityFrame = 0;
		damageAmount = 0;
		knockBackPower = 0.0f;
		stepDistance = 0.0f;
		startVec = Vec3();
		endVec = Vec3();
	}
};

class Melee
{
private:
	const Vec3 standerdVec = Vec3(1, 0, 0);

	//�ÓI�����o�ϐ�
	static Object3D melee_;
	static Vec3 playerForwardVec_;
	static Vec3 playerPos_;

	//�����o�ϐ�
	Vec3 position_;
	bool isMelee_;
	string name_;
	int insidenceFrame_;
	int detectionFrame_;
	int rigidityFrame_;
	Vec3 startVec_;
	Vec3 endVec_;
	Vec3 edgeVec_ = Vec3(0, 1.0, 0);
	Vec3 directionVec_ = Vec3(1.0, 0, 0);
	XMVECTOR startQ, endQ, updateQ;

public:
	

	Melee();
	static void Load();
	static void CommonUpdate(const Vec3& pPos, const Vec3& pFVec);
	void Update(const AttackInfo& attackInfo);
	void Draw(const XMMATRIX& parentMatRot, const AttackInfo& attackInfo);
};