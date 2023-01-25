#include "TitleScene.h"
#include "HHelper.h"
#include "SceneManager.h"
#include "HEasing.h"

TitleScene::TitleScene()
{
	skydome.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_NOLIGHT_ALPHA, "skydome", L"Resources/Object/skydome/sky.png");
	float skyDomeScale = 200.0f;
	skydome.ChangeScale(skyDomeScale, skyDomeScale, skyDomeScale);

	stage.Generate({ 0,-50,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "stage", L"Resources/Object/stage/color.png");
	float stageScale = 15.0f;
	stage.ChangeScale(stageScale, stageScale, stageScale);

	titlePos = Vec3(-400, 200, 0);
	title.Generate(titlePos.ConvertXMFLOAT3(), PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Title", L"Resources/Object/Title/color.png");
	level = 0.0f;
	float titleScale = 220.0f;
	title.ChangeScale(titleScale, titleScale, titleScale);

	pressAnyPos = Vec3(-500, -15, 0);
	pressAny.Generate(pressAnyPos.ConvertXMFLOAT3(), PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "PressAny", L"Resources/Object/PressAny/color.png");
	float pressAnyScale = 90.0f;
	pressAny.ChangeScale(pressAnyScale, pressAnyScale, pressAnyScale);

	player.Generate({ -900,-20,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Body", L"Resources/Object/Body/Body.png");
	float playerScale = 1.5f;
	player.ChangeScale({ playerScale,playerScale,playerScale });

	for (int i = 0; i < LIGHT_AMOUNT; i++) {
		Vec3 pos = Vec3(0, 300, 0);
		if (i < LIGHT_AMOUNT / 2) {
			pos.x = -1000 + 400 * i;
			pos.z = -350;
		}
		else {
			pos.x = -1000 + 400 * (i - LIGHT_AMOUNT / 2) + 200.0f;
			pos.z = 350;
		}
		lightpos.push_back(pos);

		LightManager::GeneratePointlight(lightpos[i].ConvertXMFLOAT3(), { 1.0,1.0,1.0 }, { 0.001,0.001,0.001});
	}

	eyePos = Vec3(-900, 50, 0);
	targetPos = Vec3(0, 100, 0);

	easeTimer = 0;
	isEaseStart = false;
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	Camera::Instance()->Update(Vec3());
	
	for (int i = 0; i < 255; i++) {
		if (Input::Instance()->isKeyTrigger(i)) {
			//SceneManager::Instance()->SetSceneNum(GAME_SCENE);
			isEaseStart = true;
		}
	}

	//遷移中
	if (isEaseStart)
	{
		easeTimer++;
		float easeRate = static_cast<float>(easeTimer) / static_cast<float>(MAX_EASE_TIMER);

		easeRate = HEase::InQuint(easeRate);

		//ゲームシーン開始時の視点座標
		Vec3 horaiEyePos = Vec3(-1092, 37, 0);

		//差分を求める
		Vec3 subEyePos = eyePos - horaiEyePos;
		//easeRateをかける
		subEyePos *= easeRate;

		eyePos -= subEyePos;
		Camera::Instance()->SetEyePos(eyePos);

		//ゲームシーン開始時の注視点座標
		Vec3 horaiTargetPos = Vec3(-708, -77, 0);
		//差分を求める
		Vec3 subTargetPos = targetPos - horaiTargetPos;
		//easeRateをかける
		subTargetPos *= easeRate;

		targetPos -= subTargetPos;
		Camera::Instance()->SetTargetPos(targetPos);


		//ゲームシーン開始時のタイトルモデル座標
		Vec3 honraiTitlePos = titlePos;
		honraiTitlePos.y += 200;
		//差分を求める
		Vec3 subTitlePos = titlePos - honraiTitlePos;
		//easeRateをかける
		subTitlePos *= easeRate;

		titlePos -= subTitlePos;

		//ゲームシーン開始時のUIモデル座標
		Vec3 honraiPressAnyPos = pressAnyPos;
		honraiPressAnyPos.y += 200;
		//差分を求める
		Vec3 subPressAnyPos = pressAnyPos - honraiPressAnyPos;
		//easeRateをかける
		subPressAnyPos *= easeRate;

		pressAnyPos -= subPressAnyPos;


		if (easeTimer >= MAX_EASE_TIMER) {
			SceneManager::Instance()->SetSceneNum(GAME_SCENE);
			easeTimer = 0;
			isEaseStart = false;
		}
	}
	
	titlePos.y += sin(level * (HHelper::H_PI_F / 180.0f)) * 2 / 8.0f;

	level += 2.0f;
	title.ChangePosition(titlePos.ConvertXMFLOAT3());
	pressAny.ChangePosition(pressAnyPos.ConvertXMFLOAT3());
	pressAny.ChangeColor({ 1, 1, 1, a });
	if (Input::Instance()->isKey(DIK_C)) {
		a -= 0.01f;
	}
}

void TitleScene::Draw()
{
	stage.Draw();
	title.Draw();
	skydome.Draw();
	pressAny.Draw();
	player.Draw();
}
