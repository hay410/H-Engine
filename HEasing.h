#pragma once
#include<cmath>
#include"HHelper.h"

//イージング関係
namespace HEase {

	/*----- イージング関数 -----*/

	//tは0~1の範囲

	inline float InSine(float t) {

		return 1.0f - cosf((t * HHelper::H_PI_F) / 2.0f);

	}
	inline float InCubic(float t) {

		return t * t * t;

	}

	inline float InOutSine(float t) {
		return -(cosf(HHelper::H_PI_F * t) - 1.0f) / 2.0f;
	}

	inline float OutSine(float t) {

		return sinf((t * HHelper::H_PI_F) / 2.0f);

	}

	inline float OutCubic(float t) {
		return 1.0f - powf(1 - t, 3.0f);
	}

	inline float OutQuar(float t) {
		return 1.0f - powf(1 - t, 4.0f);
	}

	inline float InOutQuint(float t) {
		return t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f - powf(-2.0f * t + 2.0f, 5.0f) / 2.0f;
	}

	inline float InQuint(float t) {
		return t * t * t * t * t;
	}

	inline float OutQuint(float t) {
		return 1.0f - powf(1.0f - t, 5);
	}

	inline float InBack(float t) {
		float c1 = 1.70158f;
		float c3 = c1 + 1.0f;

		return c3 * t * t * t - c1 * t * t;
	}

	inline float OutBack(float t) {
		float c1 = 1.70158f;
		float c3 = c1 + 1.0f;

		return 1.0f + c3 * std::powf(t - 1.0f, 3.0f) + c1 * std::powf(t - 1.0f, 2.0f);
	}

	inline float InOutExpo(float t) {
		return t == 0
			? 0
			: t == 1
			? 1
			: t < 0.5 ? powf(2, 20 * t - 10) / 2
			: (2 - powf(2, -20 * t + 10)) / 2;
	}


}