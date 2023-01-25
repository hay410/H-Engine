#pragma once
//#include"SpriteManager.h"
#include "Singleton.h"
#include "DirectXBase.h"
#include "Input.h"
#include "Camera.h"
#include "Object3D.h"
#include "Sprite.h"
#include "DescriptorHeapManager.h"
#include "LightManager.h"

class TitleScene :public Singleton<TitleScene>
{
public:
	/*---- メンバ定数 ----*/
	const int MAX_EASE_TIMER = 120;
	enum SceneNum {
		TITLE_SCENE,				//タイトル画面
		GAME_SCENE,				//ゲーム画面
		END_SCENE				//エンド画面
	};
	const int LIGHT_AMOUNT = 20;


	/*---- メンバ変数 ----*/
	Object3D stage;
	Object3D skydome;
	Object3D title;
	Vec3 titlePos;
	Object3D pressAny;
	Vec3 pressAnyPos;
	Object3D player;
	float level;
	int easeTimer;
	vector<Vec3> lightpos;
	bool isEaseStart;
	Vec3 eyePos;
	Vec3 targetPos;

	//test
	float a = 1.0f;

	/*---- メンバ関数 ----*/
	//コンストラクタ
	TitleScene();
	friend Singleton<TitleScene>;

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

};