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

class EndScene :public Singleton<EndScene>
{
public:
	/*---- メンバ定数 ----*/


	/*---- メンバ変数 ----*/


	/*---- メンバ関数 ----*/
	//コンストラクタ
	EndScene();
	friend Singleton<EndScene>;

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();
};