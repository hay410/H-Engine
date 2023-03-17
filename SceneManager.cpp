#include"SceneManager.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"EndScene.h"

SceneManager::SceneManager()
{
	sceneNum = TITLE_SCENE;
	isDebug = false;

	DxBase.Init();

	Camera::Instance()->Init();

	FbxModelLoader::Instance()->Init(DxBase.dev);
	FbxObject3d::SetDevice(DxBase.dev);
	FbxObject3d::CreateGraphicsPipeline();

	DescriptorHeapManager::Instance()->GenerateDescriptorHeap();
	PipelineManager::Instance()->Init();
	TitleScene::Instance()->Init();
	GameScene::Instance()->Init();
	EndScene::Instance()->Init();
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	Camera::Instance()->GenerateMatView();
	Camera::Instance()->SetSceneNum(sceneNum);

	switch (sceneNum) {
	case TITLE_SCENE:
		//�^�C�g����ʂł̍X�V����
		TitleScene::Instance()->Update();
		break;
	case GAME_SCENE:
		//�Q�[���v���C���ł̍X�V����
		GameScene::Instance()->Update();
		if (GameScene::Instance()->GetIsEnd()) {
			sceneNum = END_SCENE;
		}
		break;
	case END_SCENE:
		//�G���h��ʂł̍X�V����
		EndScene::Instance()->Update();
		//if (Input::Instance()->isKeyTrigger(DIK_SPACE)) {
		//	sceneNum = TITLE_SCENE;
		//}
		break;
	}
	if (isDebug) {
		//�G�X�P�[�v�������ꂽ�烋�[�v���甲����(�f�o�b�O�p)
		if (Input::Instance()->isKeyTrigger(DIK_ESCAPE))
		{
			exit(0);
		}

		if (Input::Instance()->isKeyTrigger(DIK_1)) {
			sceneNum = TITLE_SCENE;
		}
		if (Input::Instance()->isKeyTrigger(DIK_2)) {
			sceneNum = GAME_SCENE;
		}
		if (Input::Instance()->isKeyTrigger(DIK_3)) {
			sceneNum = END_SCENE;
		}
	}
}

void SceneManager::Draw()
{
	//�`��O����
	DxBase.BeforeDrawing();

	switch (sceneNum) {
	case TITLE_SCENE:
		//�^�C�g����ʂł̍X�V����
		TitleScene::Instance()->Draw();
		break;
	case GAME_SCENE:
		//�Q�[���v���C���ł̍X�V����
		GameScene::Instance()->Draw();
		break;
	case END_SCENE:
		//�G���h��ʂł̍X�V����
		EndScene::Instance()->Draw();
		break;
	}

	//�`��㏈��
	DxBase.AfterDrawing();
}

void SceneManager::Finalize()
{
	FbxModelLoader::Instance()->Fainalize();
}
