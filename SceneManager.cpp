#include"SceneManager.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"EndScene.h"

SceneManager::SceneManager()
{
	sceneNum = GAME_SCENE;
	isDebug = true;

	DxBase.Init();

	Camera::Instance()->Init();

	FbxModelLoader::Instance()->Init(DxBase.dev);
	FbxObject3d::SetDevice(DxBase.dev);
	FbxObject3d::CreateGraphicsPipeline();

	DescriptorHeapManager::Instance()->GenerateDescriptorHeap();
	PipelineManager::Instance()->Init();
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
		TitleScene::Instance()->Update();
		break;
	case GAME_SCENE:
		//�Q�[���v���C���ł̍X�V����
		GameScene::Instance()->Update();
		break;
	case END_SCENE:
		//�G���h��ʂł̍X�V����
		EndScene::Instance()->Update();
		break;
	}
	//�G�X�P�[�v�������ꂽ�烋�[�v���甲����(�f�o�b�O�p)
	if (Input::Instance()->isKeyTrigger(DIK_ESCAPE) && isDebug)
	{
		exit(0);
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
