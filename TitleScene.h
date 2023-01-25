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
	/*---- �����o�萔 ----*/
	const int MAX_EASE_TIMER = 120;
	enum SceneNum {
		TITLE_SCENE,				//�^�C�g�����
		GAME_SCENE,				//�Q�[�����
		END_SCENE				//�G���h���
	};
	const int LIGHT_AMOUNT = 20;


	/*---- �����o�ϐ� ----*/
	Object3D stage;
	Object3D skydome;
	Object3D title;
	Vec3 titlePos;
	Object3D pressAny;
	Vec3 pressAnyPos;
	Object3D player;
	float level;
	int easeTimer;
	vector<Vec3> lightpos;
	bool isEaseStart;
	Vec3 eyePos;
	Vec3 targetPos;

	//test
	float a = 1.0f;

	/*---- �����o�֐� ----*/
	//�R���X�g���N�^
	TitleScene();
	friend Singleton<TitleScene>;

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

};