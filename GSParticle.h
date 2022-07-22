#pragma once
#include "GSParticleBase.h"
#include <vector>

class GSParticle : public GSParticleBase {

private:

	// ���ʂ̐�������
	void CommonGenerate(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int pipelineID, int instanceCount = 1);

public:

	// ��������
	void GenerateForTexture(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, LPCWSTR fileName, int instanceCount = 1);
	void GenerateForColor(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, XMFLOAT4 color, int instanceCount = 1);
	void GenerateSpecifyTextureID(XMFLOAT3 centerPos, XMFLOAT2 size, int projectionID, int piplineID, int textureID, int instanceCount = 1);

	// �`�揈��
	void Draw();
	void DrawInstance(vector<GSConstBufferDataB0> instanceData);

	// �F��ς��鏈��
	inline void ChangeColor(const XMFLOAT4& color) {

		constBufferDataB0.color = color;

	}
	// �F���擾���鏈��
	inline XMFLOAT4 GetColor() { return constBufferDataB0.color; }

};