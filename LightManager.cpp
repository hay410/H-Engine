#include "LightManager.h"

PointLightData LightManager::pointlights[POINTLIGHT_NUM]{};			//点光源
DirLightData LightManager::dirlights[DIRLIGHT_NUM]{};				//面光源
SpotLightData LightManager::spotlights[SPOTLIGHT_NUM]{};			//スポットライト
CircleShadowData LightManager::circleShadows[CIRCLESHADOW_NUM]{};	//丸影光源

void LightManager::GeneratePointlight(XMFLOAT3 pos, XMFLOAT3 color, XMFLOAT3 atten)
{
	for (int i = 0; i < POINTLIGHT_NUM; ++i) {
		if (pointlights[i].active == 1)continue;
		pointlights[i].active = 1;
		pointlights[i].lightpos = pos;
		pointlights[i].lightcolor = color;
		pointlights[i].lightatten = atten;
		break;
	}
}

void LightManager::GenerateDirlight(XMFLOAT3 vec, XMFLOAT3 color)
{
	for (int i = 0; i < DIRLIGHT_NUM; ++i) {
		if (dirlights[i].active == 1)continue;
		dirlights[i].active = 1;
		dirlights[i].lightvec = vec;
		dirlights[i].lightcolor = color;
		break;
	}
}

void LightManager::GenerateSpotlight(XMFLOAT3 vec, XMFLOAT3 pos, XMFLOAT3 color, XMFLOAT3 atten, XMFLOAT2 lightfactoranglecos)
{
	for (int i = 0; i < SPOTLIGHT_NUM; ++i) {
		if (spotlights[i].active == 1)continue;
		spotlights[i].active = 1;
		spotlights[i].lightv = XMVector3Normalize(XMLoadFloat3(&vec));
		spotlights[i].lightpos = pos;
		spotlights[i].lightcolor = color;
		spotlights[i].lightfactoranglecos = XMFLOAT2(cosf(XMConvertToRadians(lightfactoranglecos.x)), cosf(XMConvertToRadians(lightfactoranglecos.y)));
		break;
	}
}

int LightManager::GenerateCircleShadow(XMFLOAT3 dir, XMFLOAT3 centerPos, float distanceCasterLight, XMFLOAT3 atten, XMFLOAT2 facterAngleCos, unsigned int active)
{
	for (int i = 0; i < CIRCLESHADOW_NUM; ++i) {
		if (circleShadows[i].active == 1)continue;
		circleShadows[i].dir = XMVector3Normalize(XMLoadFloat3(&dir));
		circleShadows[i].centerpos = centerPos;
		circleShadows[i].distanceCasterLight = distanceCasterLight;
		circleShadows[i].atten = atten;
		circleShadows[i].facterAngleCos = XMFLOAT2(cosf(XMConvertToRadians(facterAngleCos.x)), cosf(XMConvertToRadians(facterAngleCos.y)));
		circleShadows[i].active = 1;
		return i;
	}
}
