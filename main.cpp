#include"SceneManager.h"
#include"FbxModelLoader.h"
#include"FbxObject3D.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//DirectX初期化
	DirectXBase DxBase;
	unique_ptr<FbxObject3d>object1;

	DxBase.Init();
	Camera::Instance()->Init();
	FbxModelLoader::Instance()->Init(DxBase.dev);

	FbxObject3d::SetDevice(DxBase.dev);
	FbxObject3d::CreateGraphicsPipeline();

	FbxModel* model;
	//モデル名を指定してファイル読み込み
	model = FbxModelLoader::Instance()->LoadModelFromFile("boneTest");

	//3dオブジェクトの生成とモデルのセット
	object1 = make_unique<FbxObject3d>();
	object1->Init();
	object1->SetModel(model);

	object1->PlayAnimation();

	DescriptorHeapManager::Instance()->GenerateDescriptorHeap();

	PipelineManager::Instance()->Init();

	Object3D sample;
	sample.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "Resources/Knight/", "Knight.obj", L"Resources/Knight/color.png", false);
	Object3D skydome;
	skydome.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "Resources/skydome/", "skydome.obj", L"Resources/skydome/sea.png", false);

	LightManager::GeneratePointlight({ 10,10,10 }, { 1,1,1 }, { 1,1,1 });

	while (true) //ゲームループ
	{
		SceneManager::Instance()->Update();

		object1->Update();

		if (Input::Instance()->isKeyTrigger(DIK_1)) {
			sample.SetPiplineID(PIPELINE_OBJECT_NOLIGHT_ALPHA);
		}

		if (Input::Instance()->isKeyTrigger(DIK_2)) {
			sample.SetPiplineID(PIPELINE_OBJECT_LIGHT_ALPHA);
		}

		if (Input::Instance()->isKeyTrigger(DIK_3)) {
			sample.SetPiplineID(PIPELINE_OBJECT_TOONSHADER_ALPHA);
		}

		//描画前処理
		DxBase.BeforeDrawing();

		//SceneManager::Instance()->Draw();

		object1->Draw();
		
		sample.Draw();
		skydome.Draw();
		//描画後処理
		DxBase.AfterDrawing();
	}

	FbxModelLoader::Instance()->Fainalize();

	return 0;
}