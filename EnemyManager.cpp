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
		Vec3 generatePos = HHelper::GetRandXMFLOAT3(-100, 100);
		generatePos.y = -50;
		if (i >= 0 && i < 3) {
			generatePos.x -= 300;
		}
		else if (i >= 3 && i < 6) {
			generatePos.x += 100;
		}
		else if (i >= 6 && i < MAX_VALUE) {
			generatePos.x += 700;
		}
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
			if (player.GetIsHit() && player.GetIs1Hit())
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
					enemy[i].SetIsKnockBack(true);
					enemy[i].SetkBackVel(player.GetValueKBackVel());
					player.SetIs1Hit(false);
					enemy[i].Damage(player.GetDamage());
				}
			}
			//�G�̍U���ƃv���C���[�̓����蔻��
			if(enemy[i].GetIsHit() && enemy[i].GetIs1Hit())
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
					player.SetkBackVel(enemy[i].GetValueKBackVel());
					attackVec = enemy[i].GetForwardVec();
					enemy[i].SetIs1Hit(false);
					player.Damage(enemy[i].GetDamage());
				}
			}
		}
	}

	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].Update(player.GetPos(), player.GetAttackVec());
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

		if (enemyToPlayerDistance < ComparingDistance) {
			ComparingDistance = enemyToPlayerDistance;
			playerNearPos = enemy[i].GetPos();
		}

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
