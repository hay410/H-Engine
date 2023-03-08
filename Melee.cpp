#include "Melee.h"
#include "HEasing.h"

Object3D Melee::melee_;
Vec3 Melee::playerForwardVec_;
Vec3 Melee::playerPos_;

Melee::Melee()
{
	melee_ = {};
	isMelee_ = false;
	name_ = "";
	startTimer_ = 0;
	hitTimer_ = 0;
	endTimer_ = 0;
	startVec_ = Vec3();
	endVec_ = Vec3();
}

void Melee::Load()
{
	melee_.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Katana", L"Resources/Object/Katana/color.png");
}

void Melee::CommonUpdate(const Vec3& pPos, const Vec3& pFVec)
{
	playerPos_ = pPos;
	playerForwardVec_ = pFVec;
}

void Melee::Update(bool isAttack, const AttackInfo& attackInfo)
{
	//îÒçUåÇéûÇÃèàóù
	if (!isAttack) {
		
	}
	else {

	}
}

void Melee::Draw()
{
	melee_.Draw();
}
