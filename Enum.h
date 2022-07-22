#pragma once

//3D�}�`�f�[�^ID
enum ShapeDataID {
	SHAPEDATA_CONE,
	SHAPEDETA_CLYINDER,
	SHAPEDATA_SPHERE
};

//�ǂ�ȓ��e�����邩��ID
enum projectionID {
	PROJECTIONID_UI,						//���s���e
	PROJECTIONID_OBJECT,					//�������e
	PROJECTIONID_BILLBOARD					//�r���{�[�h
};

//�ǂ�ȃu�����h�����邩��ID
enum blendID {
	BLENDMODE_ADD,							//���Z����
	BLENDMODE_ALPHA							//�A���t�@�u�����h
};

//�p�C�v���C��ID	PIPLINE _ (�^��) _ (����) _ (����)
enum PipelineID {
	/*���C���p*/
	PIPELINE_LINE_ALPHA,								//���C���p												�A���t�@�u�����h		�萔1�A�e�N�X�`��1��
	/*�X�v���C�g�p*/
	PIPELINE_SPRITE_ADD,								//�X�v���C�g�p												���Z����				�萔1�A�e�N�X�`��1��
	PIPELINE_SPRITE_ALPHA,							//�X�v���C�g�p												�A���t�@�u�����h		�萔1�A�e�N�X�`��1��
	/*�I�u�W�F�N�g�p*/
	PIPELINE_OBJECT_SIMPLE_COLOR_ALPHA,
	PIPELINE_OBJECT_LIGHT_ALPHA,						//3D�I�u�W�F�N�g�p			���C�e�B���O						�A���t�@�u�����h		�萔3�A�e�N�X�`��1��
	PIPELINE_OBJECT_NOLIGHT_ALPHA,					//3D�I�u�W�F�N�g�p			���C�e�B���O����					�A���t�@�u�����h		�萔3�A�e�N�X�`��1��
	PIPELINE_OBJECT_NOLIGHT_ALPHA_F,					//3D�I�u�W�F�N�g�p			���C�e�B���O���� �O�ʃJ�����O			�A���t�@�u�����h		�萔3�A�e�N�X�`��1��
	PIPELINE_OBJECT_OUTLINE_ALPHA,					//3D�I�u�W�F�N�g�p			�A�E�g���C���p						�A���t�@�u�����h		�萔3�A�e�N�X�`��1��
	PIPELINE_OBJECT_TOONSHADER_ALPHA,				//3D�I�u�W�F�N�g�p			�g�D�[���V�F�[�_�[					�A���t�@�u�����h		�萔3�A�e�N�X�`��1��
	/*GS�p�[�e�B�N���p*/
	PIPELINE_GSPARTICLE_NOLIGHT_ALPHA,				//GS�p�[�e�B�N���p			�_���痧�̂𐶐�					�A���t�@�u�����h		�萔1�A�e�N�X�`��1��
	/*�}���`�p�X�����_�����O�p*/
	PIPELINE_MULTIPATH_NORMAL_ADD,					//�}���`�p�X�����_�����O�p									���Z����				�萔2�A�e�N�X�`��1��
	PIPELINE_MULTIPATH_NORMAL_ALPHA,					//�}���`�p�X�����_�����O�p									�A���t�@�u�����h		�萔2�A�e�N�X�`��1��
	PIPELINE_MULTIPATH_MONOCHROME_ADD,				//�}���`�p�X�����_�����O�p	���m�N����						���Z����				�萔2�A�e�N�X�`��1��
	PIPELINE_MULTIPATH_MONOCHROME_ALPHA,				//�}���`�p�X�����_�����O�p	���m�N����						�A���t�@�u�����h		�萔2�A�e�N�X�`��1��
	PIPELINE_MULTIPATH_GAUSSIAN_X_ALPHA,				//�}���`�p�X�����_�����O�p	�K�E�X�ڂ�����������				�A���t�@�u�����h		�萔2�A�e�N�X�`��1��
	PIPELINE_MULTIPATH_GAUSSIAN_Y_ALPHA,				//�}���`�p�X�����_�����O�p	�K�E�X�ڂ�����������				�A���t�@�u�����h		�萔2�A�e�N�X�`��1��
};