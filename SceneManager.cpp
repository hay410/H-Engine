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
		//タイトル画面での更新処理
		TitleScene::Instance()->Update();
		break;
	case GAME_SCENE:
		//ゲームプレイ中での更新処理
		GameScene::Instance()->Update();
		if (GameScene::Instance()->GetIsEnd()) {
			sceneNum = END_SCENE;
		}
		break;
	case END_SCENE:
		//エンド画面での更新処理
		EndScene::Instance()->Update();
		//if (Input::Instance()->isKeyTrigger(DIK_SPACE)) {
		//	sceneNum = TITLE_SCENE;
		//}
		break;
	}
	if (isDebug) {
		//エスケープが押されたらループから抜ける(デバッグ用)
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
	//描画前処理
	DxBase.BeforeDrawing();

	switch (sceneNum) {
	case TITLE_SCENE:
		//タイトル画面での更新処理
		TitleScene::Instance()->Draw();
		break;
	case GAME_SCENE:
		//ゲームプレイ中での更新処理
		GameScene::Instance()->Draw();
		break;
	case END_SCENE:
		//エンド画面での更新処理
		EndScene::Instance()->Draw();
		break;
	}

	//描画後処理
	DxBase.AfterDrawing();
}

void SceneManager::Finalize()
{
	FbxModelLoader::Instance()->Fainalize();
}
