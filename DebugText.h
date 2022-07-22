#pragma once
#include "Sprite.h"

#define MAX_CHAR 256				//1�t���[���ɕ`�悷��ő啶����
/*�ȉ��̓����o�ϐ��Ƃ��Ď������āA�t�H���g�e�N�X�`���ɂ���ĕς�����悤�ɂ��Ă���������*/
#define FONT_WIDTH 9				//�t�H���g�̕�
#define FONT_HEIGHT 18				//�t�H���g�̍���
#define FONT_LINE_COUNT_X 14		//�t�H���g�e�N�X�`���̈��̕�����
#define FONT_LINE_COUNT_Y 7			//�t�H���g�e�N�X�`���̈��̕�����

class DebugText {
private:
	Sprite chars[MAX_CHAR];			//������
public:
	//�R���X�g���N�^
	DebugText();
	//������
	void Init();
	//�����񐶐�
	void Print(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY);
	void PrintBack(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY);
	//�`��
	void Draw();
};

/*----- �O�̃R�[�h -----*/
//#pragma once
//#include "SpriteManager.h"
//
//#define MAX_CHAR 256
//
//class DebugText {
//private:
//	Sprite chars[MAX_CHAR];			//������
//
//	const float FONT_WIDTH = 9;				//�t�H���g�̕�
//	const float FONT_HEIGHT = 18;			//�t�H���g�̍���
//	const int FONT_LINE_COUNT_X = 14;		//�t�H���g�e�N�X�`���̈��̕�����
//	const int FONT_LINE_COUNT_Y = 7;		//�t�H���g�e�N�X�`���̈��̕�����
//
//public:
//	//�R���X�g���N�^
//	DebugText();
//	//������
//	void Init();
//	//�����񐶐�
//	void Print(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY);
//	void PrintBack(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY);
//	//�`��
//	void Draw();
//};