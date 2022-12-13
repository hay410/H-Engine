#include "GameScene.h"
#include "EnemyManager.h"

GameScene::GameScene()
{
	skydome.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "skydome", L"Resources/Object/skydome/sky.png");
	skydome.ChangeScale(200, 200, 200);

	player.Init();

	kariStage.Generate({ 0,-50,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "stage", L"Resources/Object/stage/color.png");
	kariStage.ChangeScale(15, 15, 15);

	lightpos = { 50,50,50 };

	LightManager::GeneratePointlight(lightpos, { 1,1,1 }, { 0.0001,0.0001,0.0001 });

	EnemyManager::Instance()->Generate(player);
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
