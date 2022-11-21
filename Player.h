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

class Player
{
private:
	//�����o�萔
	const float MAX_SPEED = 5.0f;
	const float SWAY_SPEED = 24.0f;
	const float WALK_SPEED = 2.0f;
	const int MAX_JAB_START_TIMER = 12;
	const int MAX_JAB_HIT_TIMER = 6;
	const int MAX_JAB_END_TIMER = 30;
	const int MAX_HOOK_START_TIMER = 8;
	const int MAX_HOOK_HIT_TIMER = 6;
	const int MAX_HOOK_END_TIMER = 30;
	const int MAX_UPPER_START_TIMER = 12;
	const int MAX_UPPER_HIT_TIMER = 6;
	const int MAX_UPPER_END_TIMER = 40;
	const float RADIUS = 40.0f;
	const float ATTACK_RADIUS = 20.0f;
	const float ATTACK_RANGE = 35.0f;

	//�����o�ϐ�
	//�v���C���[���f���̃f�[�^
	Object3D object;
	Object3D sphere;
	Vec3 position;				//���W
	float radius;				//���a
	float speed;				//���x
	Vec3 forwardVec;			//���ʃx�N�g��
	Vec3 previousForwardVec;	//�P�t���[���O�̐��ʃx�N�g��
	bool isAlive;
	bool isSway;
	bool isLockOn;
	bool isGuard;
	bool isHit;					//�U�����肪����Ƃ��̂ݏオ��t���O

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
	Vec3 attackPos;
	
	//�����o�֐�
	void Move();

	void Walk();

	void Sway();

	void Guard();

	void Attack();

	void Jab();

	void Hook();

	void Upper();

public:
	
	//�R���X�g���N�^
	Player();
	
	//������
	void Init();
	
	//�X�V
	void Update();
	
	//�`��
	void Draw();

	//�Q�b�^
	Vec3 GetPos() { return position; }
	void SetPos(const Vec3& pos) { position = pos; }
	float GetRadius() { return radius; }
	bool GetIsAlive() { return isAlive; }
	bool GetIsHit() { return isHit; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	Vec3 GetAttackPos() { return attackPos; }
	float GetAttackRadius() { return ATTACK_RADIUS; }
};