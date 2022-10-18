#pragma once
#include "Singleton.h"
#include "DirectXBase.h"
#include "Input.h"
#include "Camera.h"
#include "Object3D.h"
#include "Sprite.h"
#include "DescriptorHeapManager.h"
#include "LightManager.h"

class Player
{
private:
	//�����o�萔
	const float MAX_SPEED = 6.0f;
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

	//�����o�ϐ�
	//�v���C���[���f���̃f�[�^
	Object3D object;
	
	Vec3 position;				//���W
	float speed;				//���x
	Vec3 forwardVec;			//���ʃx�N�g��
	Vec3 previousForwardVec;	//�P�t���[���O�̐��ʃx�N�g��
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
};