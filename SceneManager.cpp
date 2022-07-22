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
		//�^�C�g����ʂł̍X�V����
 		UpdateTitleScene();
		break;
	case GAME_SCENE:
		//�Q�[���v���C���ł̍X�V����
		UpdateGameScene();
		break;
	case END_SCENE:
		//�G���h��ʂł̍X�V����
		UpdateEndScene();
		break;
	}
}

void SceneManager::Draw()
{
	switch (sceneNum) {
	case TITLE_SCENE:
		//�^�C�g����ʂł̍X�V����
		DrawTitleScene();
		break;
	case GAME_SCENE:
		//�Q�[���v���C���ł̍X�V����
		DrawGameScene();
		break;
	case END_SCENE:
		//�G���h��ʂł̍X�V����
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
