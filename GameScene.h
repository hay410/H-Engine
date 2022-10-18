#pragma once
//#include"SpriteManager.h"
#include"FbxModelLoader.h"
#include"FbxObject3D.h"
#include"MultiPath.h"
#include "GaussianSprite.h"
#include"Player.h"

class GameScene :public Singleton<GameScene>
{
public:
	/*---- メンバ定数 ----*/


	/*---- メンバ変数 ----*/

	Player player;
	Object3D skydome;
	Object3D kariStage;
	XMFLOAT3 lightpos;

	/*---- メンバ関数 ----*/
	//コンストラクタ
	GameScene();
	friend Singleton<GameScene>;

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();
};