#pragma once
#include "SpriteBase.h"

class Sprite : public SpriteBase {

private:

	// ���ʂ̐�������
	void CommonGenerate(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID);

public:

	// ��������
	void GenerateForTexture(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, LPCWSTR fileName);
	void GenerateForColor(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, XMFLOAT4 color);
	void GenerateSpecifyTextureID(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, int textureID);

	// �`�揈��
	void Draw();

	// �F��ς��鏈��
	inline void SetColor(const XMFLOAT4& color) { constBufferDataB0.color = color; }

};