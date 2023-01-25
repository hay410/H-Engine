#include "GameScene.h"
#include "EnemyManager.h"

GameScene::GameScene()
{
	skydome.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "skydome", L"Resources/Object/skydome/sky.png");
	skydome.ChangeScale(200, 200, 200);

	player.Init();

	kariStage.Generate({ 0,-50,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_LIGHT_ALPHA, "stage", L"Resources/Object/stage/color.png");
	//kariStage.Generate({ 0,-50,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_LIGHT_ALPHA, "stage", L"Resources/Object/stage/color.png");
	kariStage.ChangeScale(15, 15, 15);

	//for (int i = 0; i < LIGHT_AMOUNT; i++) {
	//	Vec3 pos = Vec3(0, 300, 0);
	//	if (i < LIGHT_AMOUNT / 2) {
	//		pos.x = -1000 + 400 * i;
	//		pos.z = -350;
	//	}
	//	else {
	//		pos.x = -1000 + 400 * (i - LIGHT_AMOUNT / 2) + 200.0f;
	//		pos.z = 350;
	//	}
	//	lightpos.push_back(pos);

	//	LightManager::GeneratePointlight(lightpos[i].ConvertXMFLOAT3(), { 1,1,1 }, { 0.001,0.001,0.001 });
	//}

	EnemyManager::Instance()->Generate(player);

	isEnd = false;
	enemyCount = 0;
}

void GameScene::Collition()
{
}

void GameScene::Init()
{
}

void GameScene::Update()
{
	Camera::Instance()->Update(player.GetPos());
	
	if (Input::Instance()->isKeyTrigger(DIK_RETURN)) {
		EnemyManager::Instance()->Generate(player);
	}

	Collition();

	for (int i = 0; i < EnemyManager::Instance()->GetEnemyValue(); i++) {
		if (!EnemyManager::Instance()->GetEnemy(i).GetIsAlive()) {
			enemyCount++;
		}
	}
	if (enemyCount == EnemyManager::Instance()->GetEnemyValue()) {
		isEnd = true;
	}
	enemyCount = 0;

	player.Update(EnemyManager::Instance()->GetAttackVec(), EnemyManager::Instance()->GetNearPos());
	EnemyManager::Instance()->Update(player);
	EnemyManager::Instance()->CD_PushBackPlayer(player);
}

void GameScene::Draw()
{
	kariStage.Draw();

	skydome.Draw();

	player.Draw();
	EnemyManager::Instance()->Draw();

}
