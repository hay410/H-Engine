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


	/*---- メンバ変数 ----*/


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