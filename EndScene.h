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

class EndScene :public Singleton<EndScene>
{
public:
	/*---- �����o�萔 ----*/
	Object3D box;
	Sprite pera;
	float alpha1;

	/*---- �����o�ϐ� ----*/


	/*---- �����o�֐� ----*/
	//�R���X�g���N�^
	EndScene();
	friend Singleton<EndScene>;

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();
};