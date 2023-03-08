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
#include "Melee.h"

class Player
{
private:
	//�����o�萔
	const float MAX_SPEED = 4.0f;				//�ʏ�̃X�s�[�h
	const float SWAY_SPEED = 24.0f;				//�X�E�F�C�̃X�s�[�h
	const float WALK_SPEED = 2.5f;				//�����̃X�s�[�h
	const float RADIUS = 40.0f;					//���a
	const float ATTACK_RADIUS = 20.0f;			//�U���̔��a
	const float ATTACK_RANGE = 35.0f;			//�U���̋���
	const int	MAX_HP = 300;					//�ő�HP
	const int	MAX_STUN_TIMER = 60;			//�X�^���̎���
	const float LOCKON_RANGE = 500.0f;			//���b�N�I���̋���

	const int	MAX_JAB_START_TIMER = 12;		//�����t���[��
	const int	MAX_JAB_HIT_TIMER = 6;			//����t���[��
	const int	MAX_JAB_END_TIMER = 30;			//�㌄�t���[��
	const int	JAB_DAMAGE = 20;				//�_���[�W��
	const float JAB_KNOCKBACK_POWER = 4.0f;		//�m�b�N�o�b�N�̋���
	const float JAB_STEP_RANGE = 3.0f;			//�X�e�b�v�̋���

	const int	MAX_HOOK_START_TIMER = 8;		//�����t���[��
	const int	MAX_HOOK_HIT_TIMER = 6;			//����t���[��
	const int	MAX_HOOK_END_TIMER = 30;		//�㌄�t���[��
	const int	HOOK_DAMAGE = 30;				//�_���[�W��
	const float HOOK_KNOCKBACK_POWER = 6.0f;	//�m�b�N�o�b�N�̋���
	const float HOOK_STEP_RANGE = 6.0f;			//�X�e�b�v�̋���

	const int	MAX_UPPER_START_TIMER = 12;		//�����t���[��
	const int	MAX_UPPER_HIT_TIMER = 6;			//����t���[��
	const int	MAX_UPPER_END_TIMER = 40;		//�㌄�t���[��
	const int	UPPER_DAMAGE = 50;				//�_���[�W��
	const float UPPER_KNOCKBACK_POWER = 24.0f;	//�m�b�N�o�b�N�̋���
	const float UPPER_STEP_RANGE = 9.0f;		//�X�e�b�v�̋���


	//�����o�ϐ�
	//�v���C���[���f���̃f�[�^
	Object3D object;			//���f��
	Object3D sphere;			//��
	Vec3 position;				//���W
	float radius;				//���a
	float speed;				//���x
	Vec3 forwardVec;			//���ʃx�N�g��
	Vec3 previousForwardVec;	//�P�t���[���O�̐��ʃx�N�g��
	bool isAlive;				//�����t���O
	bool isSway;				//�X�E�F�C�t���O
	bool isLockOn;				//���b�N�I���t���O
	Vec3 enemyNearPos;			//��ԋ߂��G�̍��W
	bool isGuard;				//�K�[�h�t���O
	bool isHit;					//�U�����肪����Ƃ��̂ݏオ��t���O
	int HP;						//�q�b�g�|�C���g
	int damage;					//�G�ɗ^����_���[�W
	bool is1Hit;				//�����蔻��g���K�[�t���O
	float stepSpeed;			//�U�����̃X�e�b�v�̑��x

	vector<AttackInfo> attackInfo;

	//�m�b�N�o�b�N�p
	bool isKnockBack;
	float kBackVel;			//�����̃m�b�N�o�b�N�Ɏg�������x
	float valueKBackVel;	//�G���m�b�N�o�b�N�����邽�߂ɓG�ɓn�������x
	int stunTimer;			//�X�^���̃^�C�}�[

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
	Vec3 attackVec;
	
	//�����o�֐�
	//�ړ�
	void Move();

	//����
	void Walk();

	//�X�E�F�C
	void Sway();

	//�K�[�h
	void Guard();
	
	//�U��
	void Attack();
	
	//��p���`
	void Jab();

	//���p���`
	void Hook();

	//�����p���`
	void Upper();

	//�m�b�N�o�b�N
	void KnockBack(const Vec3& attackVec);

	//csv����U������ǂݍ���
	void LoadAttackInfoFromCSV();

public:
	
	//�R���X�g���N�^
	Player();
	
	//������
	void Init();
	
	//�X�V
	void Update(const Vec3& attackVec, const Vec3& enemyNearPos);
	
	//�`��
	void Draw();

	//�_���[�W(HP�̃Z�b�^�̂悤�Ȃ���)
	void Damage(int damage);

	//���S����
	void Dead();

	//�Q�b�^
	Vec3 GetPos() { return position; }
	float GetRadius() { return radius; }
	bool GetIsAlive() { return isAlive; }
	bool GetIsHit() { return isHit; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	Vec3 GetAttackPos() { return attackPos; }
	float GetDamage() { return damage; }
	float GetAttackRadius() { return ATTACK_RADIUS; }
	bool GetIs1Hit() { return is1Hit; }
	Vec3 GetAttackVec() { return attackVec; }
	float GetValueKBackVel() { return valueKBackVel; }

	//�Z�b�^
	void SetPos(const Vec3& value) { position = value; }
	void SetIsKnockBack(bool value) { isKnockBack = value; }
	void SetIs1Hit(bool value) { is1Hit = value; }
	void SetkBackVel(float value) { kBackVel = value; }
};