#pragma once

#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl/client.h>
#include <vector>
#include "PipelineManager.h"
#include "HVec.h"

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

// �`��f�[�^�N���X�̊��N���X
class DrawDataBase {

public:

	/*-- �����o�֐� --*/

	// �X�P�[�����X�V (�w�肵���傫���ɂȂ�B)
	void ChangeScale(XMFLOAT3 amount);
	void ChangeScale(float x, float y, float z);
	// ��]�ʂ��X�V (�w�肵���ʕ���]�ʂ��������B)
	void ChangeRotation(XMFLOAT3 amount);
	void ChangeRotation(float x, float y, float z);
	// ��]�ʂ�������
	void InitRotation();
	// ��]�ʂ���
	void AssignmentRotationMat(XMMATRIX amount);
	// ���W���X�V (�w�肵���ʒu�Ɉړ��B)
	void ChangePosition(XMFLOAT3 amount);
	void ChangePosition(float x, float y, float z);
	// ��]�s��ɉ�]�s���������B
	void MulRotationMat(XMMATRIX rotationMat);
	// ���W���X�V (�w�肵���ʂ𑫂��B)
	void ChangePositionAdd(XMFLOAT3 amount);
	void ChangePositionAdd(float x, float y, float z);
	// �e��s������B
	void AssignmentWorldMatrix(const XMMATRIX& posMat, const XMMATRIX& scaleMat, const XMMATRIX& rotationMat);
	// ��ʂɔ�\��
	void DoNotDisplay();
	// ��ʂɕ\��
	void DisplayOnScreen();
	// isDisplay��Ԃ�
	bool GetIsDisplay();
	// �w�肳�ꂽ�C���f�b�N�X�̃e�N�X�`��ID��؂�ւ���B(�C���f�b�N�X���I�[�o�[�t���[���A���_�[�t���[���Ă�����ő吔or�擪���w�肷��B)
	void ChangeTextureID(int textureID, int index);
	// �e�N�X�`��ID��ǉ�����B
	void AddTextureID(int textureID);
	// �e�N�X�`��ID���N���A�B
	void ClearTextureID();

protected:

	/*-- �����o�ϐ� --*/

	// ��{�f�[�^
	bool isDisplay = true;	// �`�悷�邩�ǂ���
	vector<int> textureID;	// �e�N�X�`����ID�i���o�[
	int projectionID;		// �ǂ̓��e�����邩��ID
	int pipelineID;			// �g�p����p�C�v���C���̖��O

	// �e��s��
	XMMATRIX scaleMat;		// �X�P�[�����O�s��
	XMMATRIX rotationMat;	// ��]�s��(�W�ϒl)
	XMMATRIX positionMat;	// ���W�s��

	// �f�o�b�O�p�̍��W
	XMFLOAT3 pos;			// ���W




	/*-- �e��\���� --*/

public:

	// ���_�f�[�^�\����
	struct Vertex {
		XMFLOAT3 pos;			// xyz���W
		XMFLOAT3 normal;		// �@��
		XMFLOAT2 uv;			// uv���W
	};

	// �s��p�A�N�Z�b�^
	inline XMMATRIX GetScaleMat() { return scaleMat; }
	inline XMMATRIX GetRotationMat() { return rotationMat; }
	inline XMMATRIX GetPositionMat() { return positionMat; }

	// ���W�f�[�^���擾
	inline XMFLOAT3 GetPos() { return pos; }

	// �e�N�X�`��ID���擾
	inline int GetTextureID(int index) { return textureID[index]; }

protected:

	// �V�F�[�_�[�ɓn���s��̃f�[�^
	struct MatrixData {
		XMMATRIX world;			// ��]��������ړ��������肷��s��
		XMMATRIX viewproj;		// �r���[�ƃv���W�F�N�V���������s��
	};

	// �萔�o�b�t�@�\����b0
	struct ConstBufferDataB0 {
		MatrixData mat;			// �s��
		XMFLOAT4 color = { 1,1,1,1 };			// �F�f�[�^
		Vec3 eye;			// �J�������W
		float pad1;
	};


	/*-- �����o�֐� --*/

	// �萔�o�b�t�@�\����b0�̃}�b�v����
	void MapConstDataB0(ComPtr<ID3D12Resource> constBuffB0, const ConstBufferDataB0& constBufferDataB0);


public:

	// GSParticle�p�̒萔�o�b�t�@�\����b0
	struct GSConstBufferDataB0 {
		XMMATRIX mat;			// �s��
		XMFLOAT4 color;			// �F�f�[�^
	};


};