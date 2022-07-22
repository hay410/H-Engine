#include "DebugText.h"
#include "Enum.h"

DebugText::DebugText()
{
	for (int i = 0; i < MAX_CHAR; ++i) {
		chars[i].DoNotDisplay();
	}
}

void DebugText::Init()
{
	for (int i = 0; i < MAX_CHAR; ++i) {
		chars[i].DisplayOnScreen();
	}
}

void DebugText::Print(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY)
{
	//���͂��ꂽ��������for������
	for (int i = 0; i < text.size(); ++i) {

		//i�Ԗڂ̕���������o��
		const unsigned char& charactor = text[i];

		//ASCII�R�[�h�̏�2�i���΂����ԍ����v�Z
		UINT fontIndex = charactor - 32;
		if (charactor >= 0x7F) {
			fontIndex = 0;
		}

		//�t�H���g�e�N�X�`���̎w��̕����̂�����C���f�b�N�X�����߂�
		UINT fontIndexY = fontIndex / FONT_LINE_COUNT_X;
		UINT fontIndexX = fontIndex % FONT_LINE_COUNT_X;

		//�e�����v�Z
		XMFLOAT3 centerPos = { x + (FONT_WIDTH + FONT_WIDTH / 3.0f * 2.0f) * scaleX * i, y, 0 };
		XMFLOAT2 size = { FONT_WIDTH * scaleX, FONT_HEIGHT * scaleY };

		//����
		Sprite buff;
		buff.GenerateForTexture(centerPos, size, PROJECTIONID_UI, PIPELINE_SPRITE_ALPHA, fontFile);

		//�󂢂Ă���v�f��T���đ��
		for (int j = 0; j < MAX_CHAR; ++j) {

			if (chars[j].GetIsDisplay() == true) continue;

			chars[j] = buff;
			break;
		}
	}
}

void DebugText::PrintBack(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY)
{
	//���͂��ꂽ��������for������
	for (int i = 0; i < text.size(); ++i) {

		//i�Ԗڂ̕���������o��
		const unsigned char& charactor = text[i];

		//ASCII�R�[�h�̏�2�i���΂����ԍ����v�Z
		UINT fontIndex = charactor - 32;
		if (charactor >= 0x7F) {
			fontIndex = 0;
		}

		//�t�H���g�e�N�X�`���̎w��̕����̂�����C���f�b�N�X�����߂�
		UINT fontIndexY = fontIndex / FONT_LINE_COUNT_X;
		UINT fontIndexX = fontIndex % FONT_LINE_COUNT_X;

		//�e�����v�Z
		XMFLOAT3 centerPos = { x + (FONT_WIDTH + FONT_WIDTH / 3.0f * 2.0f) * scaleX * i - (text.size() * ((FONT_WIDTH + FONT_WIDTH / 3.0f * 2.0f) * scaleX)), y, 0 };
		XMFLOAT2 size = { FONT_WIDTH * scaleX, FONT_HEIGHT * scaleY };

		//����
		Sprite buff;
		buff.GenerateForTexture(centerPos, size, PROJECTIONID_UI, PIPELINE_SPRITE_ALPHA, fontFile);

		//�󂢂Ă���v�f��T���đ��
		for (int j = 0; j < MAX_CHAR; ++j) {

			if (chars[j].GetIsDisplay() == true) continue;

			chars[j] = buff;
			break;
		}
	}
}

void DebugText::Draw()
{
	//��������Ă��镶����for������
	for (int i = 0; i < MAX_CHAR; ++i) {

		if (chars[i].GetIsDisplay() == false) continue;

		//�`��
		chars[i].Draw();

	}
}


//#include"DebugText.h"
//
//DebugText::DebugText()
//{
//	for (int i = 0; i < MAX_CHAR; ++i)
//	{
//		chars[i].isDisplay = false;
//	}
//}
//
//void DebugText::Init()
//{
//	for (int i = 0; i < MAX_CHAR; ++i)
//	{
//		chars[i].isDisplay = false;
//	}
//}
//
//void DebugText::Print(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY)
//{
//	//���͂��ꂽ��������for������
//	for (int i = 0; i < text.size(); ++i) {
//
//		//i�Ԗڂ̕���������o��
//		const unsigned char& charactor = text[i];
//
//		//ASCII�R�[�h�̏�2�i���΂����ԍ����v�Z
//		UINT fontIndex = charactor - 32;
//		if (charactor >= 0x7F) {
//			fontIndex = 0;
//		}
//
//		//�t�H���g�e�N�X�`���̎w��̕����̂�����C���f�b�N�X�����߂�
//		UINT fontIndexY = fontIndex / FONT_LINE_COUNT_X;
//		UINT fontIndexX = fontIndex % FONT_LINE_COUNT_X;
//
//		//�e�����v�Z
//		XMFLOAT3 centerPos = { x + (FONT_WIDTH + FONT_WIDTH / 3.0f * 2.0f) * scaleX * i, y, 0 };
//		XMFLOAT2 size = { FONT_WIDTH * scaleX, FONT_HEIGHT * scaleY };
//
//		//����
//		Sprite buff = SpriteManager::Instance()->InitSprite(centerPos, size, PROJECTIONID_UI, fontFile);
//
//		//�󂢂Ă���v�f��T���đ��
//		for (int j = 0; j < MAX_CHAR; ++j) {
//
//			if (chars[j].isDisplay == true) continue;
//
//			chars[j] = buff;
//			break;
//		}
//	}
//}
//
//void DebugText::PrintBack(LPCWSTR fontFile, string text, float x, float y, float scaleX, float scaleY)
//{
//	//���͂��ꂽ��������for������
//	for (int i = 0; i < text.size(); ++i) {
//
//		//i�Ԗڂ̕���������o��
//		const unsigned char& charactor = text[i];
//
//		//ASCII�R�[�h�̏�2�i���΂����ԍ����v�Z
//		UINT fontIndex = charactor - 32;
//		if (charactor >= 0x7F) {
//			fontIndex = 0;
//		}
//
//		//�t�H���g�e�N�X�`���̎w��̕����̂�����C���f�b�N�X�����߂�
//		UINT fontIndexY = fontIndex / FONT_LINE_COUNT_X;
//		UINT fontIndexX = fontIndex % FONT_LINE_COUNT_X;
//
//		//�e�����v�Z
//		XMFLOAT3 centerPos = { x + (FONT_WIDTH + FONT_WIDTH / 3.0f * 2.0f) * scaleX * i - (text.size() * ((FONT_WIDTH + FONT_WIDTH / 3.0f * 2.0f) * scaleX)), y, 0 };
//		XMFLOAT2 size = { FONT_WIDTH * scaleX, FONT_HEIGHT * scaleY };
//
//		//����
//		Sprite buff = SpriteManager::Instance()->InitSprite(centerPos, size, PROJECTIONID_UI, fontFile);
//
//		//�󂢂Ă���v�f��T���đ��
//		for (int j = 0; j < MAX_CHAR; ++j) {
//
//			if (chars[j].isDisplay == true) continue;
//
//			chars[j] = buff;
//			break;
//		}
//	}
//}
//
//void DebugText::Draw()
//{
//	for (int i = 0; i < MAX_CHAR; ++i) {
//
//		if (chars[i].isDisplay == false) continue;
//
//		//�`��
//		SpriteManager::Instance()->Draw(chars[i]);
//	}
//}
