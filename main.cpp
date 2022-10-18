#include"SceneManager.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	while (true) //ゲームループ
	{
		//更新
		SceneManager::Instance()->Update();
	
		//描画
		SceneManager::Instance()->Draw();
	}

	SceneManager::Instance()->Finalize();
	return 0;
}