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
	/*---- �����o�萔 ----*/


	/*---- �����o�ϐ� ----*/

	Player player;
	//Enemy enemy;
	Object3D skydome;
	Object3D kariStage;
	XMFLOAT3 lightpos;

	/*---- �����o�֐� ----*/
	//�R���X�g���N�^
	GameScene();
	friend Singleton<GameScene>;

	//�����蔻��
	void Collition();

public:

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();
};