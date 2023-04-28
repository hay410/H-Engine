#include "Melee.h"
#include "HEasing.h"

Object3D Melee::melee_;
Vec3 Melee::playerForwardVec_;
Vec3 Melee::playerPos_;

Melee::Melee()

{
	melee_ = {};
	insidenceFrame_ = 0;
	detectionFrame_ = 0;
	rigidityFrame_ = 0;
	startVec_ = Vec3();
	endVec_ = Vec3();
	melee_.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Katana", L"Resources/Object/Katana/color.png");
	float scale = 60;
	melee_.ChangeScale({ scale,scale,scale });
	startQ = {};
	endQ = {};
	updateQ = {};
}

void Melee::Load()
{
	//melee_.Generate({ 0,0,0 }, PROJECTIONID_OBJECT, PIPELINE_OBJECT_TOONSHADER_ALPHA, "Katana", L"Resources/Object/Katana/color.png");
}

void Melee::CommonUpdate(const Vec3& pPos, const Vec3& pFVec)
{
	playerPos_ = pPos;
	playerForwardVec_ = pFVec;
}

void Melee::Update(const AttackInfo& attackInfo)
{
	//îÒçUåÇéûÇÃèàóù
	if (!attackInfo.isAttack) {
		
	}
	//çUåÇéû
	else {


		if (insidenceFrame_ < attackInfo.insidenceFrame) {
			melee_.DoNotDisplay();
			detectionFrame_ = 0;
			rigidityFrame_ = 0;
			edgeVec_ = attackInfo.startVec;
			//Yê¨ï™
			Vec3 endVecElementXaxis = Vec3(attackInfo.endVec.x, 0, attackInfo.endVec.z);
			endVecElementXaxis.Normalize();
			float angleX = endVecElementXaxis.Dot(standerdVec);
			angleX = acos(angleX);

			//Xê¨ï™
			Vec3 endVecElementYaxis = Vec3(attackInfo.endVec.x, attackInfo.endVec.y, 0);
			endVecElementYaxis.Normalize();
			float angleY = endVecElementYaxis.Dot(standerdVec);
			angleY = acos(angleY);

			if (attackInfo.endVec.z < 0)angleX *= -1;
			if (attackInfo.endVec.y < 0)angleY *= -1;

			XMMATRIX buff = melee_.GetRotationMat();
			buff *= XMMatrixRotationZ(angleX);
			buff *= XMMatrixRotationY(angleY);

			endQ = XMQuaternionRotationMatrix(buff);
			endQ = XMQuaternionNormalize(endQ);

			Vec3 startVecElementXaxis = Vec3(attackInfo.startVec.x, 0, attackInfo.startVec.z);
			angleX = startVecElementXaxis.Dot(standerdVec);
			angleX = acos(angleX);

			Vec3 startVecElementYaxis = Vec3(attackInfo.endVec.x, attackInfo.startVec.y, 0);
			angleY = startVecElementYaxis.Dot(standerdVec);
			angleY = acos(angleY);


			if (attackInfo.startVec.x < 0)angleX *= -1;
			if (attackInfo.startVec.y < 0)angleY *= -1;

			buff = melee_.GetRotationMat();
			buff *= XMMatrixRotationZ(angleX);
			buff *= XMMatrixRotationY(angleY);

			startQ = XMQuaternionRotationMatrix(buff);
			startQ = XMQuaternionNormalize(startQ);

			updateQ = startQ;

			insidenceFrame_++;
		}
		else {
			if (detectionFrame_ < attackInfo.detectionFrame) {
				melee_.DisplayOnScreen();
				float rate = static_cast<float>(detectionFrame_) / static_cast<float>(attackInfo.detectionFrame);
				//rate = HEase::InSine(rate);
				updateQ = XMQuaternionSlerp(startQ, endQ, rate);

				detectionFrame_++;
			}
			else {
				if (rigidityFrame_ < attackInfo.rigidityFrame) {
					
					rigidityFrame_++;
				}
				else {
					melee_.DoNotDisplay();
					insidenceFrame_ = 0;
					detectionFrame_ = 0;
					rigidityFrame_ = 0;
				}
			}
		}

		melee_.AssignmentRotationMat(XMMatrixRotationQuaternion(updateQ));
		edgeVec_ = Vec3(updateQ);
		edgeVec_.Normalize();
		position_ = (edgeVec_ * 30) + playerPos_;
		position_ = (attackInfo.startVec * 30) + playerPos_;
		melee_.ChangePosition(position_.ConvertXMFLOAT3());
	}

}

void Melee::Draw(const XMMATRIX& parentMatRot, const AttackInfo& attackInfo)
{
	melee_.MulRotationMat(parentMatRot);
	if (melee_.GetIsDisplay()) {
		melee_.Draw();
	}
	melee_.InitRotation();
}
