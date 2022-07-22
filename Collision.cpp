#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere &sphere, const Plane &plane, DirectX::XMVECTOR *inter)
{
	//座標系の原点から球の中心座標への距離
	XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
	//平面の原点距離を減産することで、平面と球の中心との距離が出る
	float dist = distV.m128_f32[0] - plane.distance;
	//距離の絶対値が半径より大きければ当たっていない
	if (fabsf(dist) > sphere.radius) return false;

	//疑似交点を計算
	if (inter)
	{
		//平面上の最近接点を、疑似交点とする
		*inter = -dist * plane.normal + sphere.center;
	}
	return true;
}

void Collision::ClosestPtPoint2Triangle(const DirectX::XMVECTOR &point, const Triangle &triangle, DirectX::XMVECTOR *closest)
{
	//pointがp0の外側の頂点領域にあるかどうかチェック
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	XMVECTOR p0_p2 = triangle.p2 - triangle.p0;
	XMVECTOR p0_pt = point - triangle.p0;

	XMVECTOR d1 = XMVector3Dot(p0_p1, p0_pt);
	XMVECTOR d2 = XMVector3Dot(p0_p2, p0_pt);

	if (d1.m128_f32[0] <= 0.0f &&
		d2.m128_f32[0] <= 0.0f)
	{
		//p0が最近傍
		*closest = triangle.p0;
		return;
	}

	//pointがp1の外側の頂点領域の　中にあるかどうかチェック
	XMVECTOR p1_pt = point - triangle.p1;

	XMVECTOR d3 = XMVector3Dot(p0_p1, p1_pt);
	XMVECTOR d4 = XMVector3Dot(p0_p2, p1_pt);

	if (d3.m128_f32[0] >= 0.0f &&
		d4.m128_f32[0] <= d3.m128_f32[0])
	{
		//p1が最近傍
		*closest = triangle.p1;
		return;
	}

	//pointがp0_p1の変領域の中にあるかどうかチェックし、あればpointのp0_p1上に対する射影を返す
	float vc = d1.m128_f32[0] * d4.m128_f32[0] -
		d3.m128_f32[0] * d2.m128_f32[0];
	if (vc <= 0.0f &&
		d1.m128_f32[0] >= 0.0f &&
		d3.m128_f32[0] <= 0.0f)
	{
		float v = d1.m128_f32[0] / (d1.m128_f32[0] - d3.m128_f32[0]);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	//pointがp2の外側の頂点領域の中にあるかどうかチェック
	XMVECTOR p2_pt = point - triangle.p2;

	XMVECTOR d5 = XMVector3Dot(p0_p1, p2_pt);
	XMVECTOR d6 = XMVector3Dot(p0_p2, p2_pt);
	if (d6.m128_f32[0] >= 0.0f &&
		d5.m128_f32[0] <= d6.m128_f32[0])
	{
		*closest = triangle.p2;
		return;
	}

	//pointがp0_p2の変領域の中にあるかどうかチェックし、あればpointのp0_p2上に対する射影を返す
	float vb = d5.m128_f32[0] * d2.m128_f32[0] -
		d1.m128_f32[0] * d6.m128_f32[0];

	if (vb <= 0.0f &&
		d2.m128_f32[0] >= 0.0f &&
		d6.m128_f32[0] <= 0.0f)
	{
		float w = d2.m128_f32[0] / (d2.m128_f32[0] - d6.m128_f32[0]);

		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	//pointがp1_p2の辺領域の中にあるかどうかチェックし、あればpointのp1_p2上に対する射影を返す
	float va = d3.m128_f32[0] * d6.m128_f32[0] -
		d5.m128_f32[0] * d4.m128_f32[0];

	if (va <= 0.0f &&
		(d4.m128_f32[0] - d3.m128_f32[0]) >= 0.0f &&
		(d5.m128_f32[0] - d6.m128_f32[0]) >= 0.0f)
	{
		float w = (d4.m128_f32[0] - d3.m128_f32[0]) /
			((d4.m128_f32[0] - d3.m128_f32[0]) +
				(d5.m128_f32[0] - d6.m128_f32[0]));

		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere &sphere, const Triangle &triangle, DirectX::XMVECTOR *inter)
{
	XMVECTOR p;
	//球の中心に対する差近接店である三角形上にある点pを見つける
	ClosestPtPoint2Triangle(sphere.center, triangle, &p);

	//点pと球の中心の差分ベクトル
	XMVECTOR v = p - sphere.center;
	//距離の二乗を求める
	//（同じベクトル同士の内積は三平方の定理のルーツの内部の式と一致する）
	v = XMVector3Dot(v, v);
	//球と三角形の距離が半径以下なら当たっていない
	if (v.m128_f32[0] > sphere.radius * sphere.radius) return false;
	//疑似交点を計算
	if (inter)
	{
		//三角形上の最近接店pを疑似交点とする
		*inter = p;
	}
	return true;
}

bool Collision::CheckRay2Plane(const Ray &ray, const Plane &plane, float *distance, DirectX::XMVECTOR *inter)
{
	const float epsilon = 1.0e-5f;	//誤差吸収用の微小な値

	//面法線と例の方向ベクトルの内積
	float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];

	//裏面には当たらない
	if (d1 > -epsilon) { return false; }

	//始点と原点の距離（平面の法線方向）
	//面法線トレイの視点座標（位置ベクトル）の内積
	float d2 = XMVector3Dot(plane.normal, ray.pos).m128_f32[0];

	//始点と平面の距離（平面の法線方向）
	float dist = d2 - plane.distance;

	//始点と平面の距離（レイ方向）
	float t = dist / -d1;

	//交点が視点より後ろにあるので、当たらない
	if (t < 0) { return false; }

	//距離を書き込む
	if (distance) { *distance = t; }

	//交点を計算
	if (inter) { *inter = ray.pos + t * ray.dir; }

	return true;
}

bool Collision::CheckRay2Triangle(const Ray &ray, const Triangle triangle, float *distance, DirectX::XMVECTOR *inter)
{
	//三角形が乗っている平面を算出
	Plane plane;
	XMVECTOR interPlane;
	plane.normal = triangle.normal;
	plane.distance = XMVector3Dot(triangle.normal, triangle.p0).m128_f32[0];

	//レイと平面が当たっていなければ、当たっていない
	if (!CheckRay2Plane(ray, plane, distance, &interPlane)) { return false; }

	//レイと平面が当たっていたので、距離と交点が書き込まれた
	//レイと平面の交点が三角形の内側にあるか判定
	const float epsilon = 1.0e-5f;//語さ吸収用の微小な値

	XMVECTOR m;
	//辺p0_p1について
	XMVECTOR pt_p0 = triangle.p0 - interPlane;
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	m = XMVector3Cross(pt_p0, p0_p1);

	//辺の外側であれば当たっていないので判定を打ち切る
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) { return false; }



	//辺p1_p2について
	XMVECTOR pt_p1 = triangle.p1 - interPlane;
	XMVECTOR p1_p2 = triangle.p2 - triangle.p1;
	m = XMVector3Cross(pt_p1, p1_p2);

	//辺の外側であれば当たっていないので判定を打ち切る
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) { return false; }


	//辺p0_p1について
	XMVECTOR pt_p2 = triangle.p2 - interPlane;
	XMVECTOR p2_p0 = triangle.p0 - triangle.p2;
	m = XMVector3Cross(pt_p2, p2_p0);

	//辺の外側であれば当たっていないので判定を打ち切る
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) { return false; }


	//内側なので、当たっている
	if (inter)
	{
		*inter = interPlane;
	}
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, DirectX::XMVECTOR* inter)
{
	XMVECTOR m = ray.pos - sphere.center;
	float b = XMVector3Dot(m, ray.dir).m128_f32[0];
	float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;

	//rayの始点がsphereの外側にあり(c > 0), rayがsphere空離れていく方向を指している場合(b > 0)、当たらない
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}
	float discr = b * b - c;
	//負の判別式はレイが球を外れていることに一致
	if (discr < 0.0f)
	{
		return false;
	}

	//レイは球と交差している。
	//交差する最小の値tを計算
	float t = -b - sqrtf(discr);
	//tが負である場合、レイは球の内側から開始しているのでtをゼロにクランプ
	if (t < 0.0f) t = 0.0f;
	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.pos + t * ray.dir;
	}
	return true;
}

//bool Collision::RayToModelCollision(const Object3D& target, const Ray& ray, XMFLOAT3& impactPos, float& distance, XMFLOAT3& hitNormal) {
//	//あたっているポリゴンのデータを保存するよう変数	衝突地点、距離、衝突面の法線
//	vector<tuple<XMFLOAT3, float, XMFLOAT3>> buff{};
//
//	float epsilon = 1.0e-5f;
//	/*-----targetからポリゴンを抜き取る-----*/
//	vector<Porygon> targetPorygon;		//ポリゴン保存用コンテナ
//
//	//targetのポリゴン数に合わせてリサイズ
//	targetPorygon.resize(target.indices.size() / 3.0f);
//
//	//ポリゴンの中身を代入
//	for (int i = 0; i < targetPorygon.size(); ++i) {
//		targetPorygon.at(i).p1 = target.vertices.at(target.indices.at(i * 3));
//		targetPorygon.at(i).p2 = target.vertices.at(target.indices.at((i * 3) + 1));
//		targetPorygon.at(i).p3 = target.vertices.at(target.indices.at((i * 3) + 2));
//		targetPorygon.at(i).isActive = true;
//	}
//
//	/*-----保存したポリゴンの頂点座標にワールド変換行列をかける-----*/
//	//ワールド行列
//	XMMATRIX matWorld = XMMatrixIdentity();
//	matWorld *= target.matScale;
//	matWorld *= target.matRot;
//	matWorld *= target.matTrans;
//	for (int i = 0; i < targetPorygon.size(); ++i) {
//		//頂点を変換
//		XMStoreFloat3(&targetPorygon.at(i).p1.pos, XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p1.pos), matWorld));
//		XMStoreFloat3(&targetPorygon.at(i).p2.pos, XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p2.pos), matWorld));
//		XMStoreFloat3(&targetPorygon.at(i).p3.pos, XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p3.pos), matWorld));
//		//法線を回転行列分だけ変換
//		XMStoreFloat3(&targetPorygon.at(i).p1.normal, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p1.normal), target.matRot)));
//		XMStoreFloat3(&targetPorygon.at(i).p2.normal, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p2.normal), target.matRot)));
//		XMStoreFloat3(&targetPorygon.at(i).p3.normal, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&targetPorygon.at(i).p3.normal), target.matRot)));
//	}
//
//	/*-----レイの方向と法線が同じ方向なら除外-----*/
//	for (int i = 0; i < targetPorygon.size(); ++i) {
//		//まずは1つ目の頂点をチェック
//		float kari = XMVector3Dot(XMLoadFloat3(&targetPorygon.at(i).p1.normal), ray.dir).m128_f32[0];
//		if (XMVector3Dot(XMLoadFloat3(&targetPorygon.at(i).p1.normal), ray.dir).m128_f32[0] > -0.0001f) {
//			//ここまで来たら完全に反対側を向いているので、削除フラグを建てる
//			targetPorygon.at(i).isActive = false;
//			continue;
//		}
//	}
//
//	/*-----ポリゴンの3頂点と境界球の当たり判定を行い、一定以上距離があった場合は処理を飛ばす-----*/
//
//	/*-----ポリゴンごとに当たり判定-----*/
//	//此処から先はポリゴンごとに計算する
//	for (int i = 0; i < targetPorygon.size(); ++i) {
//		/*-----レイと平面の衝突点を計算する-----*/
//
//		//ポリゴンが無効化されていたら次の処理へ
//		if (targetPorygon.at(i).isActive == false) continue;
//
//		//レイの開始地点から平面におろした垂線の長さを求める
//		XMFLOAT3 planeNorm = { -targetPorygon.at(i).p1.normal.x,-targetPorygon.at(i).p1.normal.y,-targetPorygon.at(i).p1.normal.z };
//		float rayToOriginLength = XMVector3Dot(ray.pos, XMLoadFloat3(&planeNorm)).m128_f32[0];
//		float planeToOriginLength = XMVector3Dot(XMLoadFloat3(&targetPorygon.at(i).p1.pos), XMLoadFloat3(&planeNorm)).m128_f32[0];
//		//視点から平面におろした垂線の長さ
//		float perpendicularLine = rayToOriginLength - planeToOriginLength;
//
//		//三角関数を利用して視点から衝突店までの距離を求める
//		float dist = XMVector3Dot(XMLoadFloat3(&planeNorm), ray.dir).m128_f32[0];
//		float impDistance = perpendicularLine / -dist;
//
//		//distanceが0未満の場合交わっていない
//		/*if (impDistance < 0) {
//			targetPorygon.at(i).isActive = false;
//			continue;
//		}*/
//
//		//衝突地点
//		XMFLOAT3 impactPoint = { ray.pos.m128_f32[0] + ray.dir.m128_f32[0] * impDistance,
//								ray.pos.m128_f32[1] + ray.dir.m128_f32[1] * impDistance,
//								ray.pos.m128_f32[2] + ray.dir.m128_f32[2] * impDistance };
//
//		/*-----衝突点がポリゴンの内側にあるかを調べる-----*/
//		XMVECTOR m;
//
//		/*辺1本目*/
//		XMVECTOR impactToP1 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p1.pos.x - impactPoint.x, targetPorygon.at(i).p1.pos.y - impactPoint.y, targetPorygon.at(i).p1.pos.z - impactPoint.z));
//		XMVECTOR P2ToP1 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p2.pos.x - targetPorygon.at(i).p1.pos.x, targetPorygon.at(i).p2.pos.y - targetPorygon.at(i).p1.pos.y, targetPorygon.at(i).p2.pos.z - targetPorygon.at(i).p1.pos.z));
//		m = XMVector3Cross(impactToP1, P2ToP1);
//		//正規化
//		m = XMVector3Normalize(m);
//		//法線と一致しているか調べる
//		float result = XMVector3Dot(m, XMLoadFloat3(&targetPorygon.at(i).p1.normal)).m128_f32[0];
//		if (result <= 0) {
//			//結果が0以外だったら衝突地点がポリゴンの内側ではないので、衝突していない
//			targetPorygon.at(i).isActive = false;
//			continue;
//		}
//
//		/*辺2本目*/
//		XMVECTOR impactToP2 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p2.pos.x - impactPoint.x, targetPorygon.at(i).p2.pos.y - impactPoint.y, targetPorygon.at(i).p2.pos.z - impactPoint.z));
//		XMVECTOR P3ToP2 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p3.pos.x - targetPorygon.at(i).p2.pos.x, targetPorygon.at(i).p3.pos.y - targetPorygon.at(i).p2.pos.y, targetPorygon.at(i).p3.pos.z - targetPorygon.at(i).p2.pos.z));
//		m = XMVector3Cross(impactToP2, P3ToP2);
//		//正規化
//		m = XMVector3Normalize(m);
//		//法線と一致しているか調べる
//		result = XMVector3Dot(m, XMLoadFloat3(&targetPorygon.at(i).p1.normal)).m128_f32[0];
//		if (result <= 0) {
//			//結果が0以外だったら衝突地点がポリゴンの内側ではないので、衝突していない
//			targetPorygon.at(i).isActive = false;
//			continue;
//		}
//
//		/*辺3本目*/
//		XMVECTOR impactToP3 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p3.pos.x - impactPoint.x, targetPorygon.at(i).p3.pos.y - impactPoint.y, targetPorygon.at(i).p3.pos.z - impactPoint.z));
//		XMVECTOR P1ToP3 = XMLoadFloat3(&XMFLOAT3(targetPorygon.at(i).p1.pos.x - targetPorygon.at(i).p3.pos.x, targetPorygon.at(i).p1.pos.y - targetPorygon.at(i).p3.pos.y, targetPorygon.at(i).p1.pos.z - targetPorygon.at(i).p3.pos.z));
//		m = XMVector3Cross(impactToP3, P1ToP3);
//		//正規化
//		m = XMVector3Normalize(m);
//		//法線と一致しているか調べる
//		result = XMVector3Dot(m, XMLoadFloat3(&targetPorygon.at(i).p1.normal)).m128_f32[0];
//		if (result <= 0) {
//			//結果が0以外だったら衝突地点がポリゴンの内側ではないので、衝突していない
//			targetPorygon.at(i).isActive = false;
//			continue;
//		}
//
//		/*ここまで来たらポリゴンに衝突してる！*/
//		tuple<XMFLOAT3, float, XMFLOAT3> buffer{};
//		get<0>(buffer) = impactPoint;
//		get<1>(buffer) = impDistance;
//		get<2>(buffer) = targetPorygon.at(i).p1.normal;
//		buff.push_back(buffer);
//	}
//
//	//buffの値が1以上だったら距離が最小の要素を検索
//	if (buff.size() >= 1) {
//		//距離が最小の要素を検索
//		int min = 0;
//		float minDistance = 100000;
//		for (int i = 0; i < buff.size(); ++i) {
//			if (fabs(get<1>(buff.at(i))) < fabs(minDistance)) {
//				minDistance = get<1>(buff.at(i));
//				min = i;
//			}
//		}
//
//		//検索した最小値を代入してreturn
//		impactPos = get<0>(buff.at(min));
//		distance = get<1>(buff.at(min));
//		hitNormal = get<2>(buff.at(min));
//		return true;
//	}
//	else {
//		impactPos = { 0,0,0 };
//		distance = 0;
//		hitNormal = { 0,0,0 };
//		return false;
//	}
//}