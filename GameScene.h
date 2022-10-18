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
	/*---- �����o�萔 ----*/


	/*---- �����o�ϐ� ----*/

	Player player;
	Object3D skydome;
	Object3D kariStage;
	XMFLOAT3 lightpos;

	/*---- �����o�֐� ----*/
	//�R���X�g���N�^
	GameScene();
	friend Singleton<GameScene>;

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();
};