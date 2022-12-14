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
	const float MAX_SPEED = 1.0f;				//�ʏ�̈ړ����x
	const float SWAY_SPEED = 18.0f;				//�X�E�F�C���̑��x
	const float WALK_SPEED = 0.6f;				//�����̑��x
	const float ADD_ANGLE = 0.02f;				//�p�x�ɑ�����
	const float WALK_DISTANCE = 50.0f;			//��������U���Ɉڍs���鋗��
	const float RUN_DISTANCE = 200.0f;			//���肩������Ɉڍs���鋗��
	const float SENSE_DISTANCE = 500.0f;		//�v���C���[�����m���鋗��
	const float RADIUS = 20.0f;					//���a
	const int	MAX_STATE_TIMER = 60;			//��Ԃ�ύX����^�C�}�[
	const int	MAX_GUARD_TIMER = 300;			//�K�[�h��Ԃ̃^�C�}�[
	const float ATTACK_RADIUS = 20.0f;			//�U���̔��a
	const float ATTACK_RANGE = 35.0f;			//�U���̋���
	const float	MAX_HP = 70.0f;				//�ő�HP
	const float	REDUCTION_RATE = 90.0f;			//�K�[�h���_���[�W���y�����銄��(%)

	//��p���`
	const int	MAX_JAB_START_TIMER = 12;		//�����t���[��
	const int	MAX_JAB_HIT_TIMER = 6;			//����t���[��
	const int	MAX_JAB_END_TIMER = 30;			//�㌄�t���[��
	const int	JAB_DAMAGE = 15;				//�_���[�W��
	const float JAB_KNOCKBACK_POWER = 3.0f;		//�m�b�N�o�b�N�̋���
	const float JAB_STEP_RANGE = 3.0f;			//�X�e�b�v�̋���

	//���p���`
	const int	MAX_HOOK_START_TIMER = 8;		//�����t���[��
	const int	MAX_HOOK_HIT_TIMER = 6;			//����t���[��
	const int	MAX_HOOK_END_TIMER = 30;		//�㌄�t���[��
	const int	HOOK_DAMAGE = 20;				//�_���[�W��
	const float HOOK_KNOCKBACK_POWER = 5.0f;	//�m�b�N�o�b�N�̋���
	const float HOOK_STEP_RANGE = 6.0f;			//�X�e�b�v�̋���

	//�����p���`
	const int	MAX_UPPER_START_TIMER = 12;		//�����t���[��
	const int	MAX_UPPER_HIT_TIMER = 6;		//����t���[��
	const int	MAX_UPPER_END_TIMER = 40;		//�㌄�t���[��
	const int	UPPER_DAMAGE = 35;				//�_���[�W��
	const float UPPER_KNOCKBACK_POWER = 18.0f;	//�m�b�N�o�b�N�̋���
	const float UPPER_STEP_RANGE = 9.0f;			//�X�e�b�v�̋���

	enum class STATE {
		WAIT,
		ATTACK,
		SWAY,
		GUARD,
		MOVE,
	};

	//�����o�ϐ�
	//�v���C���[���f���̃f�[�^
	Object3D object;			//���f��
	Object3D sphere;			//��
	Vec3 position;				//���W
	float radius;				//���a
	float speed;				//���x
	Vec3 forwardVec;			//���ʃx�N�g��
	Vec3 previousForwardVec;	//�P�t���[���O�̐��ʃx�N�g��
	float angle;				//����
	bool isSway;				//�X�E�F�C����
	bool isGuard;				//�K�[�h����
	int guardTimer;				//�K�[�h�p�̃^�C�}�[
	bool isHit;					//�U�����肪����Ƃ��̂ݏオ��t���O
	bool isAttack;
	bool isAlive;				//�����t���O
	bool availableAttack;		//�U���\
	int random;					//����
	STATE state;				//���
	int stateTimer;				//�s���Ԋu
	float HP;						//HP
	int damage;					//�v���C���[�ɗ^����_���[�W��
	bool is1Hit;

	//�m�b�N�o�b�N�p
	bool isKnockBack;
	float kBackVel;				//�����̃m�b�N�o�b�N�Ɏg�������x
	float valueKBackVel;		//�G���m�b�N�o�b�N�����邽�߂ɓG�ɓn�������x

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
	void Move(const Vec3& playerPos);

	void StateControl();

	void Sway();

	void Guard();

	void Attack();

	void Jab();

	void Hook();

	void Upper();

	void KnockBack(const Vec3& attackVec);


public:

	//�R���X�g���N�^
	Enemy();

	//������
	void Init();

	//����
	void Generate(const Vec3& position, const Vec3& playerPos);

	//�X�V
	void Update(const Vec3& playerPos, const Vec3& attackVec);

	//�`��
	void Draw();

	//�_���[�W(HP�̃Z�b�^�̂悤�Ȃ���)
	void Damage(float damage);

	//���S����
	void Dead();

	//�Q�b�^
	Vec3 GetPos() { return position; }
	bool GetIsAlive() { return isAlive; }
	float GetRadius() { return radius; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	float GetSpeed() { return speed; }
	Vec3 GetForwardVec() { return forwardVec; }
	Vec3 GetAttackPos() { return attackPos; }
	float GetAttackRadius() { return ATTACK_RADIUS; }
	bool GetIsHit() { return isHit; }
	int GetDamage() { return damage; }
	float GetValueKBackVel() { return valueKBackVel; }
	bool GetIs1Hit() { return is1Hit; }

	//�Z�b�^
	void SetPos(const Vec3& value) { position = value; }
	void SetSpeed(float value) { this->speed = value; }
	void SetIsKnockBack(bool value) { isKnockBack = value; }
	void SetIs1Hit(bool value) { is1Hit = value; }
	void SetkBackVel(float value) { kBackVel = value; }
};