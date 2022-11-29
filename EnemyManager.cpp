#include "EnemyManager.h"
#include "HHelper.h"
#include "Player.h"

EnemyManager::EnemyManager()
{
	enemy.resize(MAX_VALUE);
}

void EnemyManager::Generate(Player& player)
{
	for (int i = 0; i < enemy.size(); ++i) {
		Vec3 generatePos = HHelper::GetRandXMFLOAT3(-300, 300);
		generatePos.y = -50;
		enemy[i].Generate(generatePos, player.GetPos());
	}
}

void EnemyManager::Update(Player& player)
{
	//�G���m�̉����߂�����
	for (int i = 0; i < enemy.size(); ++i) {
		//���S���Ă��珈���͍s��Ȃ�
		if (!enemy[i].GetIsAlive())continue;
		for (int j = 0; j < enemy.size(); j++) {
			//���S���Ă����珈���͍s��Ȃ�
			if (!enemy[j].GetIsAlive())continue;
			//���Ԃ̎��͏������X�L�b�v����
			if (i == j)continue;
			//�G�ƓG��2�_�Ԃ̋��������߂�
			Vec3 directionVec = Vec3(enemy[i].GetPos() - enemy[j].GetPos());
			float enemyToEnemyDistance = directionVec.Length();

			//������̋�������Ă����画����s��Ȃ�
			const float CertainDistance = 200.0f;
			if (enemyToEnemyDistance >= CertainDistance)continue;

			//�����蔻������
			float TotalRadius = enemy[i].GetRadius() + enemy[j].GetRadius();
			//�������Ă����ꍇ
			if (enemyToEnemyDistance < TotalRadius) {
				//��������Е��̔��a���������l�����߂Ă���
				float SubDistanceToRadius = enemyToEnemyDistance - enemy[i].GetRadius();
				//��ň����Ȃ��������̔��a�����ŋ��߂��l�������ďd�Ȃ��Ă镔���̋��������߂�
				float OverlapDistance = enemy[j].GetRadius() - SubDistanceToRadius + 10.0f;
				//�G�ƓG�̕����x�N�g�������߂�
				directionVec.Normalize();
				//�F�X���߂��l���g���ĉ����߂����������s��
				Vec3 position = enemy[i].GetPos();
				position += directionVec * OverlapDistance;
				enemy[i].SetPos(position);
			}
		}
	}

	if (player.GetIsAlive()) {
		for (int i = 0; i < enemy.size(); ++i) {
			if (!enemy[i].GetIsAlive())continue;
			//�v���C���[�̍U���ƓG�̓����蔻��
			if (player.GetIsHit())
			{
				//�G�ƓG��2�_�Ԃ̋��������߂�
				Vec3 directionVec = Vec3(player.GetAttackPos() - enemy[i].GetPos());
				float enemyToEnemyDistance = directionVec.Length();

				//������̋�������Ă����画����s��Ȃ�
				const float CertainDistance = 200.0f;
				if (enemyToEnemyDistance >= CertainDistance)continue;

				//�����蔻������
				float TotalRadius = player.GetAttackRadius() + enemy[i].GetRadius();
				//�������Ă����ꍇ
				if (enemyToEnemyDistance < TotalRadius) {
					enemy[i].Dead();
				}
			}
			//�G�̍U���ƃv���C���[�̓����蔻��
			if(enemy[i].GetIsHit())
			{
				//�G�ƓG��2�_�Ԃ̋��������߂�
				Vec3 directionVec = Vec3(player.GetPos() - enemy[i].GetAttackPos());
				float enemyToEnemyDistance = directionVec.Length();

				//������̋�������Ă����画����s��Ȃ�
				const float CertainDistance = 200.0f;
				if (enemyToEnemyDistance >= CertainDistance)continue;

				//�����蔻������
				float TotalRadius = player.GetRadius() + enemy[i].GetAttackRadius();
				//�������Ă����ꍇ
				if (enemyToEnemyDistance < TotalRadius) {
					player.SetIsKnockBack(true);
					attackVec = enemy[i].GetForwardVec();
				}
			}
		}
	}

	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].Update(player.GetPos());
	}
}

void EnemyManager::CD_PushBackPlayer(Player& player)
{
	//�G�ƃv���C���[�̉����߂�����
	for (int i = 0; i < enemy.size(); ++i) {
		//���S���Ă��珈���͍s��Ȃ�
		if (!enemy[i].GetIsAlive())continue;
		//�G�ƃv���C���[��2�_�Ԃ̋��������߂�
		Vec3 directionVec = Vec3(enemy[i].GetPos() -player.GetPos());
		float enemyToPlayerDistance = directionVec.Length();

		//������̋�������Ă����画����s��Ȃ�
		const float CertainDistance = 200.0f;
		if (enemyToPlayerDistance >= CertainDistance)continue;

		//�����蔻������
		float TotalRadius = enemy[i].GetRadius() + player.GetRadius();
		//�������Ă����ꍇ
		if (enemyToPlayerDistance < TotalRadius) {
			//��������Е��̔��a���������l�����߂Ă���
			float SubDistanceToRadius = enemyToPlayerDistance - enemy[i].GetRadius();
			//��ň����Ȃ��������̔��a�����ŋ��߂��l�������ďd�Ȃ��Ă镔���̋��������߂�
			float OverlapDistance = player.GetRadius() - SubDistanceToRadius;
			//�G�ƓG�̕����x�N�g�������߂�
			directionVec.Normalize();
			//�F�X���߂��l���g���ĉ����߂����������s��
			Vec3 position = enemy[i].GetPos();
			position += directionVec *OverlapDistance;
			//enemy[i].SetSpeed(0.0f);
			enemy[i].SetPos(position);
		} 
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < enemy.size(); ++i) {
		if (!enemy[i].GetIsAlive())continue;
		enemy[i].Draw();
	}
}
