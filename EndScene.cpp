#include "EndScene.h"

EndScene::EndScene()
{
	box.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "Box", L"Resources/Yanfei.jpg");
	box.ChangeScale(50, 50, 50);
	pera.GenerateForTexture({ window_width/2,window_height/2,0 }, { 512,512 }, PROJECTIONID_UI, PIPELINE_SPRITE_ALPHA, L"Resources/Yanfei.jpg");
	alpha1 = 1.0f;
}

void EndScene::Init()
{
}

void EndScene::Update()
{
	Camera::Instance()->Update(Vec3(0, 0, 0));
	box.ChangeRotation({ 0,0.01,0 });
	//pera.ChangeRotation({ 0,0.01,0 })
	
	if (alpha1 >= 0.0f) {
		if (Input::Instance()->isKey(DIK_DOWN)) {
			alpha1 -= 0.01f;
		}
	}
	if (alpha1 <= 1.0f) {
		if (Input::Instance()->isKey(DIK_UP)) {
			alpha1 += 0.01f;
		}
	}
	pera.SetColor({ 1, 1, 1, alpha1 });
}

void EndScene::Draw()
{
	//box.Draw();
	//pera.Draw();
}
