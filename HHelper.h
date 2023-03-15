#pragma once
#include"struct.h"
#include <string>

namespace HHelper
{
	/*---- �֗��ϐ� ----*/

	static const int COLOR_MAX = 255;														//�F�̍ő�l
	static const XMFLOAT3 COLOR_RED_VIVID = XMFLOAT3(COLOR_MAX, 0, 0);						//RGB�U��؂�̐�
	static const XMFLOAT3 COLOR_GREEN_VIVID = XMFLOAT3(0, COLOR_MAX, 0);					//RGB�U��؂�̗�
	static const XMFLOAT3 COLOR_BLUE_VIVID = XMFLOAT3(0, 0, COLOR_MAX);						//RGB�U��؂�̐�
	static const XMFLOAT3 COLOR_CYAN_VIVID = XMFLOAT3(0, COLOR_MAX, COLOR_MAX);				//RGB�U��؂�̃V�A��
	static const XMFLOAT3 COLOR_MAGENTA_VIVID = XMFLOAT3(COLOR_MAX, 0, COLOR_MAX);			//RGB�U��؂�̃}�[���^
	static const XMFLOAT3 COLOR_YELLOW_VIVID = XMFLOAT3(COLOR_MAX, COLOR_MAX, 0);				//RGB�U��؂�̃C�G���[
	static const XMFLOAT3 COLOR_BLACK_VIVID = XMFLOAT3(0, 0, 0);							//RGB�U��؂�̍�
	static const XMFLOAT3 COLOR_WHITE_VIVID = XMFLOAT3(COLOR_MAX, COLOR_MAX, COLOR_MAX);	//RGB�U��؂�̔�

	static const float H_PI_F = 3.14159265359;												//�~���� 180�x
	static const float H_PI_DIV_F = H_PI_F / 2.0f;											//�~���� 90�x
	static const float H_PI_3DIV_F = H_PI_F + H_PI_3DIV_F;									//�~���� 270�x
	static const float H_2PI_F = H_PI_F * 2.0f;												//�~���� 360�x

	/*---- �֗��֐� ----*/

	//2D���W���ł̓�_�Ԃ̋��������߂�
	inline float Distance2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return sqrtf(powf(lhs.x - rhs.x, 2.0f) + powf(lhs.y - rhs.y, 2.0f));
	}
	//3D���W���ł̓�_�Ԃ̋��������߂�
	inline float Distance3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return sqrtf(powf(lhs.x - rhs.x, 2.0f) + powf(lhs.y - rhs.y, 2.0f) + powf(lhs.z - rhs.z, 2.0f));
	}

	//���ς����߂�
	inline float Dot2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	inline float Dot3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	//�O�ς����߂�
	inline float Cross2D(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}
	inline XMFLOAT3 Cross3D(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		//�^�C�v�~�X���Ă�\������
		return XMFLOAT3(lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x);
	}

	//�x�N�g���̒��������߂�
	inline float Length2D(const XMFLOAT2& rhs) {
		return sqrtf(Dot2D(rhs, rhs));
	}
	inline float Length3D(const XMFLOAT3& rhs) {
		return sqrtf(Dot3D(rhs, rhs));
	}

	//�x�N�g���𐳋K������
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

	//�����𑫂�
	inline XMFLOAT2 AddXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x + rhs.x, lhs.y + rhs.y);
	}
	inline XMFLOAT3 AddXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	//����������
	inline XMFLOAT2 SubXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x - rhs.x, lhs.y - rhs.y);
	}
	inline XMFLOAT3 SubXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		XMFLOAT3 buff = XMFLOAT3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);

		//����Ȃ�0�ɋ߂�������0�ɂ���
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

	//������������
	inline XMFLOAT2 MulXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x * rhs.x, lhs.y * rhs.y);
	}
	inline XMFLOAT3 MulXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	//����������
	inline XMFLOAT2 DivXMFLOAT2(const XMFLOAT2& lhs, const XMFLOAT2& rhs) {
		return XMFLOAT2(lhs.x / rhs.x, lhs.y / rhs.y);
	}
	inline XMFLOAT3 DivXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return XMFLOAT3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	//�����擾
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
	//	//���C�h������ɕϊ������ۂ̕��������v�Z
	//	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//	//���C�h������
	//	std::wstring wString;
	//	wString.resize(filePathBufferSize);

	//	//���C�h������ɕϊ�
	//	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	//	return wString;
	//}
}