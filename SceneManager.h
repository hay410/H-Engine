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

class SceneManager :public Singleton<SceneManager>
{
public:
	/*---- �����o�萔 ----*/


	enum SceneNum {
		TITLE_SCENE,				//�^�C�g�����
		GAME_SCENE,				//�Q�[�����
		END_SCENE				//�G���h���
	};

	/*---- �����o�ϐ� ----*/
	
	int sceneNum;

	/*---- �����o�֐� ----*/
	//�R���X�g���N�^
	SceneManager();
	friend Singleton<SceneManager>;

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();


	//titleScene�ł̍X�V
	void UpdateTitleScene();

	//titleScene�ł̕`��
	void DrawTitleScene();

	//gameScene�ł̍X�V
	void UpdateGameScene();

	//gameScene�ł̕`��
	void DrawGameScene();

	//endScene�ł̍X�V
	void UpdateEndScene();

	//endScene�ł̕`��
	void DrawEndScene();


};