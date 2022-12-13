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
	//敵同士の押し戻し処理
	for (int i = 0; i < enemy.size(); ++i) {
		//死亡してたら処理は行わない
		if (!enemy[i].GetIsAlive())continue;
		for (int j = 0; j < enemy.size(); j++) {
			//死亡していたら処理は行わない
			if (!enemy[j].GetIsAlive())continue;
			//同番の時は処理をスキップする
			if (i == j)continue;
			//敵と敵の2点間の距離を求める
			Vec3 directionVec = Vec3(enemy[i].GetPos() - enemy[j].GetPos());
			float enemyToEnemyDistance = directionVec.Length();

			//ある一定の距離離れていたら判定を行わない
			const float CertainDistance = 200.0f;
			if (enemyToEnemyDistance >= CertainDistance)continue;

			//当たり判定を取る
			float TotalRadius = enemy[i].GetRadius() + enemy[j].GetRadius();
			//当たっていた場合
			if (enemyToEnemyDistance < TotalRadius) {
				//距離から片方の半径を引いた値を求めておく
				float SubDistanceToRadius = enemyToEnemyDistance - enemy[i].GetRadius();
				//上で引かなかった方の半径から上で求めた値を引いて重なってる部分の距離を求める
				float OverlapDistance = enemy[j].GetRadius() - SubDistanceToRadius + 10.0f;
				//敵と敵の方向ベクトルも求める
				directionVec.Normalize();
				//色々求めた値を使って押し戻しっ処理を行う
				Vec3 position = enemy[i].GetPos();
				position += directionVec * OverlapDistance;
				enemy[i].SetPos(position);
			}
		}
	}

	if (player.GetIsAlive()) {
		for (int i = 0; i < enemy.size(); ++i) {
			if (!enemy[i].GetIsAlive())continue;
			//プレイヤーの攻撃と敵の当たり判定
			if (player.GetIsHit() && player.GetIs1Hit())
			{
				//敵と敵の2点間の距離を求める
				Vec3 directionVec = Vec3(player.GetAttackPos() - enemy[i].GetPos());
				float enemyToEnemyDistance = directionVec.Length();

				//ある一定の距離離れていたら判定を行わない
				const float CertainDistance = 200.0f;
				if (enemyToEnemyDistance >= CertainDistance)continue;

				//当たり判定を取る
				float TotalRadius = player.GetAttackRadius() + enemy[i].GetRadius();
				//当たっていた場合
				if (enemyToEnemyDistance < TotalRadius) {
					enemy[i].SetIsKnockBack(true);
					enemy[i].SetkBackVel(player.GetValueKBackVel());
					player.SetIs1Hit(false);
					enemy[i].Damage(player.GetDamage());
				}
			}
			//敵の攻撃とプレイヤーの当たり判定
			if(enemy[i].GetIsHit() && enemy[i].GetIs1Hit())
			{
				//敵と敵の2点間の距離を求める
				Vec3 directionVec = Vec3(player.GetPos() - enemy[i].GetAttackPos());
				float enemyToEnemyDistance = directionVec.Length();

				//ある一定の距離離れていたら判定を行わない
				const float CertainDistance = 200.0f;
				if (enemyToEnemyDistance >= CertainDistance)continue;

				//当たり判定を取る
				float TotalRadius = player.GetRadius() + enemy[i].GetAttackRadius();
				//当たっていた場合
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
	//敵とプレイヤーの押し戻し処理
	for (int i = 0; i < enemy.size(); ++i) {
		//死亡してたら処理は行わない
		if (!enemy[i].GetIsAlive())continue;
		//敵とプレイヤーの2点間の距離を求める
		Vec3 directionVec = Vec3(enemy[i].GetPos() -player.GetPos());
		float enemyToPlayerDistance = directionVec.Length();

		if (enemyToPlayerDistance < ComparingDistance) {
			ComparingDistance = enemyToPlayerDistance;
			playerNearPos = enemy[i].GetPos();
		}

		//ある一定の距離離れていたら判定を行わない
		const float CertainDistance = 200.0f;
		if (enemyToPlayerDistance >= CertainDistance)continue;

		//当たり判定を取る
		float TotalRadius = enemy[i].GetRadius() + player.GetRadius();
		//当たっていた場合
		if (enemyToPlayerDistance < TotalRadius) {
			//距離から片方の半径を引いた値を求めておく
			float SubDistanceToRadius = enemyToPlayerDistance - enemy[i].GetRadius();
			//上で引かなかった方の半径から上で求めた値を引いて重なってる部分の距離を求める
			float OverlapDistance = player.GetRadius() - SubDistanceToRadius;
			//敵と敵の方向ベクトルも求める
			directionVec.Normalize();
			//色々求めた値を使って押し戻しっ処理を行う
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
