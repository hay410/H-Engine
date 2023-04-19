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


	enum ATTACK_INFO
	{
		INSIDENCE_FRAME,
		DETECTION_FRAME,
		RIGIDITY_FRAME,
		DAMAGE_AMOUNT,
		KNOCKBACK_POWER,
		STEP_DISTANCE,
		STARTVEC_X,
		STARTVEC_Y,
		STARTVEC_Z,
		ENDVEC_X,
		ENDVEC_Y,
		ENDVEC_Z,
	};

	//�����o�ϐ�
	//�v���C���[���f���̃f�[�^
	Object3D object_;			//���f��
	Object3D sphere;			//��
	Vec3 position_;				//���W
	float radius_;				//���a
	float speed_;				//���x
	Vec3 forwardVec_;			//���ʃx�N�g��
	Vec3 previousForwardVec_;	//�P�t���[���O�̐��ʃx�N�g��
	bool isAlive_;				//�����t���O
	bool isSway_;				//�X�E�F�C�t���O
	bool isLockOn_;				//���b�N�I���t���O
	Vec3 enemyNearPos_;			//��ԋ߂��G�̍��W
	bool isGuard_;				//�K�[�h�t���O
	bool isHit_;					//�U�����肪����Ƃ��̂ݏオ��t���O
	int HP_;						//�q�b�g�|�C���g
	int damage_;					//�G�ɗ^����_���[�W
	bool is1Hit_;				//�����蔻��g���K�[�t���O
	float stepSpeed_;			//�U�����̃X�e�b�v�̑��x

	vector<AttackInfo> attackInfo;	//csv�t�@�C������ǂݎ���������i�[���Ă����R���e�i
	AttackInfo sendAttackInfo;		//�ߐڍU���N���X�ɑ��邽�߂̂��

	//�m�b�N�o�b�N�p
	bool isKnockBack_;
	float kBackVel_;			//�����̃m�b�N�o�b�N�Ɏg�������x
	float valueKBackVel_;	//�G���m�b�N�o�b�N�����邽�߂ɓG�ɓn�������x
	int stunTimer_;			//�X�^���̃^�C�}�[

	//�U���p
	int insidenceFrame_;//�����t���[��
	int detectionFrame_;//����t���[��
	int rigidityFrame_;//�d���t���[��
	Melee melee_;

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
	Vec3 GetPos() { return position_; }
	float GetRadius() { return radius_; }
	bool GetIsAlive() { return isAlive_; }
	bool GetIsHit() { return isHit_; }
	Sphere GetBodySphere() { return bodySphere; }
	Sphere GetAttackSphere() { return attackSphere; }
	Vec3 GetAttackPos() { return attackPos; }
	float GetDamage() { return damage_; }
	float GetAttackRadius() { return ATTACK_RADIUS; }
	bool GetIs1Hit() { return is1Hit_; }
	Vec3 GetAttackVec() { return attackVec; }
	float GetValueKBackVel() { return valueKBackVel_; }

	//�Z�b�^
	void SetPos(const Vec3& value) { position_ = value; }
	void SetIsKnockBack(bool value) { isKnockBack_ = value; }
	void SetIs1Hit(bool value) { is1Hit_ = value; }
	void SetkBackVel(float value) { kBackVel_ = value; }
};