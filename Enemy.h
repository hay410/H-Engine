#pragma once
#include "Singleton.h"
#include "DirectXBase.h"
#include "Input.h"
#include "Camera.h"
#include "Object3D.h"
#include "Sprite.h"
#include "DescriptorHeapManager.h"
#include "LightManager.h"
#include "Collision.h"

class Enemy
{
private:
	//�����o�萔
	const float MAX_SPEED = 1.0f;
	const float SWAY_SPEED = 24.0f;
	const float WALK_SPEED = 0.6f;
	const int MAX_JAB_START_TIMER = 12;
	const int MAX_JAB_HIT_TIMER = 6;
	const int MAX_JAB_END_TIMER = 30;
	const int MAX_HOOK_START_TIMER = 8;
	const int MAX_HOOK_HIT_TIMER = 6;
	const int MAX_HOOK_END_TIMER = 30;
	const int MAX_UPPER_START_TIMER = 12;
	const int MAX_UPPER_HIT_TIMER = 6;
	const int MAX_UPPER_END_TIMER = 40;
	const float ADD_ANGLE = 0.02f;			//�p�x�ɑ�����
	const float WALK_DISTANCE = 100.0f;
	const float RUN_DISTANCE = 200.0f;
	const float RADIUS = 20.0f;

	//�����o�ϐ�
	//�v���C���[���f���̃f�[�^
	Object3D object;

	Vec3 position;				//���W
	float radius;
	float speed;				//���x
	Vec3 forwardVec;			//���ʃx�N�g��
	Vec3 previousForwardVec;	//�P�t���[���O�̐��ʃx�N�g��
	float angle;
	bool isSway;
	bool isLockOn;
	bool isGuard;
	bool isHit;					//�U�����肪����Ƃ��̂ݏオ��t���O
	bool isAlive;
	bool availableAttack;

	//��p���`
	bool isJab;
	int jabStartTmier;
	int jabHitTimer;
	int jabEndTimer;

	//���p���`
	bool isHook;
	int hookStartTmier;
	int hookHitTimer;
	int hookEndTimer;

	//�����p���`
	bool isUpper;
	int upperStartTmier;
	int upperHitTimer;
	int upperEndTimer;

	//�����蔻��p
	Sphere bodySphere;
	Sphere attackSphere;

	//�����o�֐�
	void Move(const Vec3& playerPos);

	void Walk();

	void Sway();

	void Guard();

	void Attack();

	void Jab();

	void Hook();

	void Upper();

public:

	//�R���X�g���N�^
	Enemy();

	//������
	void Init();

	//����
	void Generate(const Vec3& position, const Vec3& playerPos);

	//�X�V
	void Update(const Vec3& playerPos);

	//�`��
	void Draw();

	//���S����
	void Dead();

	//�Q�b�^
	Vec3 GetPos() { return position; }
	bool GetIsAlive() { return isAlive; }
	float GetRadius() { return radius; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	float GetSpeed() { return speed; }

	//�Z�b�^
	void SetPos(const Vec3& pos) { position = pos; }
	void SetSpeed(float speed) { this->speed = speed; }
};