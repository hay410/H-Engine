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


	/*---- �����o�ϐ� ----*/


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