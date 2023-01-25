#pragma once
#include"TitleScene.h"
#include"GameScene.h"
#include"EndScene.h"

class SceneManager :public Singleton<SceneManager>
{
public:
	/*---- メンバ定数 ----*/
	DirectXBase DxBase;

	enum SceneNum {
		TITLE_SCENE,				//タイトル画面
		GAME_SCENE,				//ゲーム画面
		END_SCENE				//エンド画面
	};

	/*---- メンバ変数 ----*/
	
	int sceneNum;
	bool isDebug;

	/*---- メンバ関数 ----*/
	//コンストラクタ
	SceneManager();
	friend Singleton<SceneManager>;

	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

	//終了処理
	void Finalize();

	//セッタ
	void SetSceneNum(int num) { sceneNum = num; }

};