#include"SceneManager.h"

SceneManager::SceneManager()
{
	sceneNum = TITLE_SCENE;
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	Camera::Instance()->GenerateMatView();
	//Camera::Instance()->Update();
	switch (sceneNum) {
	case TITLE_SCENE:
		//タイトル画面での更新処理
 		UpdateTitleScene();
		break;
	case GAME_SCENE:
		//ゲームプレイ中での更新処理
		UpdateGameScene();
		break;
	case END_SCENE:
		//エンド画面での更新処理
		UpdateEndScene();
		break;
	}
}

void SceneManager::Draw()
{
	switch (sceneNum) {
	case TITLE_SCENE:
		//タイトル画面での更新処理
		DrawTitleScene();
		break;
	case GAME_SCENE:
		//ゲームプレイ中での更新処理
		DrawGameScene();
		break;
	case END_SCENE:
		//エンド画面での更新処理
		DrawEndScene();
		break;
	}
}

void SceneManager::UpdateTitleScene()
{
}

void SceneManager::DrawTitleScene()
{
}

void SceneManager::UpdateGameScene()
{
}

void SceneManager::DrawGameScene()
{
}

void SceneManager::UpdateEndScene()
{
}

void SceneManager::DrawEndScene()
{
}
