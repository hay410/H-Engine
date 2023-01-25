#pragma once
#include"TitleScene.h"
#include"GameScene.h"
#include"EndScene.h"

class SceneManager :public Singleton<SceneManager>
{
public:
	/*---- �����o�萔 ----*/
	DirectXBase DxBase;

	enum SceneNum {
		TITLE_SCENE,				//�^�C�g�����
		GAME_SCENE,				//�Q�[�����
		END_SCENE				//�G���h���
	};

	/*---- �����o�ϐ� ----*/
	
	int sceneNum;
	bool isDebug;

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

	//�I������
	void Finalize();

	//�Z�b�^
	void SetSceneNum(int num) { sceneNum = num; }

};