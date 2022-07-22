#pragma once
#include "struct.h"
#include "Singleton.h"

class LightManager : public Singleton<LightManager> {
public:
	/*-----����-----*/
	static PointLightData pointlights[POINTLIGHT_NUM];			//�_����
	static DirLightData dirlights[DIRLIGHT_NUM];				//�ʌ���
	static SpotLightData spotlights[SPOTLIGHT_NUM];				//�X�|�b�g���C�g
	/*-----�e-----*/
	static CircleShadowData circleShadows[CIRCLESHADOW_NUM];	//�ۉe����

	friend Singleton<LightManager>;
	LightManager() {};

	/*-----����-----*/
	static void GeneratePointlight(XMFLOAT3 lightpos, XMFLOAT3 lightcolor, XMFLOAT3 lightatten);
	static void GenerateDirlight(XMFLOAT3 lightvec, XMFLOAT3 lightcolor);
	static void GenerateSpotlight(XMFLOAT3 lightv, XMFLOAT3 lightpos, XMFLOAT3 lightcolor, XMFLOAT3 lightatten, XMFLOAT2 lightfactoranglecos);
	/*-----�e-----*/
	static int GenerateCircleShadow(XMFLOAT3 dir, XMFLOAT3 centerPos, float distanceCasterLight, XMFLOAT3 atten, XMFLOAT2 facterAngleCos, unsigned int active);
};