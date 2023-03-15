#pragma once
#include"struct.h"
#include <string>

namespace HHelper
{
	/*---- 便利変数 ----*/

	static const int COLOR_MAX = 255;														//色の最大値
	static const XMFLOAT3 COLOR_RED_VIVID = XMFLOAT3(COLOR_MAX, 0, 0);						//RGB振り切りの赤
	static const XMFLOAT3 COLOR_GREEN_VIVID = XMFLOAT3(0, COLOR_MAX, 0);					//RGB振り切りの緑
	static const XMFLOAT3 COLOR_BLUE_VIVID = XMFLOAT3(0, 0, COLOR_MAX);						//RGB振り切りの青
	static const XMFLOAT3 COLOR_CYAN_VIVID = XMFLOAT3(0, COLOR_MAX, COLOR_MAX);				//RGB振り切りのシアン
	static const XMFLOAT3 COLOR_MAGENTA_VIVID = XMFLOAT3(COLOR_MAX, 0, COLOR_MAX);			//RGB振り切りのマゼンタ
	static const XMFLOAT3 COLOR_YELLOW_VIVID = XMFLOAT3(COLOR_MAX, COLOR_MAX, 0);				//RGB振り切りのイエロー
	static const XMFLOAT3 COLOR_BLACK_VIVID = XMFLOAT3(0, 0, 0);							//RGB振り切りの黒
	static const XMFLOAT3 COLOR_WHITE_VIVID = XMFLOAT3(COLOR_MAX, COLOR_MAX, COLOR_MAX);	//RGB振り切りの白

	static const float H_PI_F = 3.14159265359;												//円周率 180度
	static const float H_PI_DIV_F = H_PI_F / 2.0f;											//円周率 90度
	static const float H_PI_3DIV_F = H_PI_F + H_PI_3DIV_F;									//円周率 270度
	static const float H_2PI_F = H_PI_F * 2.0f;												//円周率 360度

	/*---- 便利関数 ----*/

	//2D座標軸での二点間の距離を求める
	inline float Distance2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return sqrtf(powf(lhs.x - rhs.x, 2.0f) + powf(lhs.y - rhs.y, 2.0f));
	}
	//3D座標軸での二点間の距離を求める
	inline float Distance3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return sqrtf(powf(lhs.x - rhs.x, 2.0f) + powf(lhs.y - rhs.y, 2.0f) + powf(lhs.z - rhs.z, 2.0f));
	}

	//内積を求める
	inline float Dot2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	inline float Dot3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	//外積を求める
	inline float Cross2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}
	inline XMFLOAT3 Cross3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		//タイプミスしてる可能性あり
		return XMFLOAT3(lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x);
	}

	//ベクトルの長さを求める
	inline float Length2D(const XMFLOAT2& rhs) {
		return sqrtf(Dot2D(rhs, rhs));
	}
	inline float Length3D(const XMFLOAT3& rhs) {
		return sqrtf(Dot3D(rhs, rhs));
	}

	//ベクトルを正規化する
	inline XMFLOAT2 Normalize2D(const XMFLOAT2& rhs) {
		float len = Length2D(rhs);
		XMFLOAT2 buff = rhs;
		buff.x /= len;
		buff.y /= len;
		return buff;
	}
	inline XMFLOAT3 Normalize3D(const XMFLOAT3& rhs) {
		float len = Length3D(rhs);
		XMFLOAT3 buff = rhs;
		buff.x /= len;
		buff.y /= len;
		buff.z /= len;
		return buff;
	}

	//引数を足す
	inline XMFLOAT2 AddXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x + rhs.x, lhs.y + rhs.y);
	}
	inline XMFLOAT3 AddXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	//引数を引く
	inline XMFLOAT2 SubXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x - rhs.x, lhs.y - rhs.y);
	}
	inline XMFLOAT3 SubXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		XMFLOAT3 buff = XMFLOAT3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);

		//限りなく0に近かったら0にする
		if (fabs(buff.x) < 0.00001f) {
			buff.x = 0;
		}
		if (fabs(buff.y) < 0.00001f) {
			buff.y = 0;
		}
		if (fabs(buff.z) < 0.00001f) {
			buff.z = 0;
		}

		return buff;
	}

	//引数をかける
	inline XMFLOAT2 MulXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x * rhs.x, lhs.y * rhs.y);
	}
	inline XMFLOAT3 MulXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	//引数を割る
	inline XMFLOAT2 DivXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x / rhs.x, lhs.y / rhs.y);
	}
	inline XMFLOAT3 DivXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	//乱数取得
	inline int GetRand(const int& min, const int& max) {
		return (rand() % (max - min + 1)) + min;
	}
	inline XMFLOAT3 GetRandXMFLOAT3(const int& min, const int& max) {
		return XMFLOAT3(GetRand(min, max), GetRand(min, max), GetRand(min, max));
	}

	//clamp
	inline float clamp(float low, float v, float high) {
		if (v < low)return low + 0.01f;
		if (v > high)return high - 0.01f;
		return v;
	}

	//
	//wstring ConvertMultiByteStringToWideString(const string& mString)
	//{
	//	//ワイド文字列に変換した際の文字数を計算
	//	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//	//ワイド文字列
	//	std::wstring wString;
	//	wString.resize(filePathBufferSize);

	//	//ワイド文字列に変換
	//	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	//	return wString;
	//}
}