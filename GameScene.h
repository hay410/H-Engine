#pragma once
//#include"SpriteManager.h"
#include"FbxModelLoader.h"
#include"FbxObject3D.h"
#include"MultiPath.h"
#include "GaussianSprite.h"
#include"Player.h"
#include"Enemy.h"

class GameScene :public Singleton<GameScene>
{
private:
	/*---- メンバ定数 ----*/
	const int LIGHT_AMOUNT = 20;

	/*---- メンバ変数 ----*/

	Player player;
	//Enemy enemy;
	Object3D skydome;
	Object3D kariStage;
	vector<Vec3> lightpos;
	bool isEnd;
	int enemyCount;

	/*---- メンバ関数 ----*/
	//コンストラクタ
	GameScene();
	friend Singleton<GameScene>;

	//当たり判定
	void Collition();

public:

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

	//ゲッタ
	bool GetIsEnd() { return isEnd; }
};