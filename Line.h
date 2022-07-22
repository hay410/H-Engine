#pragma once
#include "LineBase.h"
#include "Enum.h"

class Line : public LineBase {

public:

	/*-- �����o�֐� --*/

	// �f�[�^�������֐�
	void Generate(const XMFLOAT3& pos1 = XMFLOAT3(0, 0, 0), const XMFLOAT3& pos2 = XMFLOAT3(0, 0, 0), const XMFLOAT4& color = XMFLOAT4(1, 1, 1, 1), int projectionID = PROJECTIONID_OBJECT, int piplineID = PIPELINE_LINE_ALPHA);

	// �`��֐�
	void Draw();

	// ���_�X�V
	void ChangeVertexPos(const XMFLOAT3& pos1, const XMFLOAT3& pos2);

};