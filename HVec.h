#pragma once
#include <cmath>
#include <DirectXMath.h>

// Vector�N���X
class Vec3 {

public:

	/*===== �����o�ϐ� =====*/

	float x;
	float y;
	float z;

public:

	/*===== �����o�֐� =====*/

	// �R���X�g���N�^
	Vec3() :x(0), y(0), z(0) {};
	Vec3(const float& X, const float& Y, const float& Z) : x(X), y(Y), z(Z) {};
	Vec3(const float& X) :x(X), y(X), z(X) {};
	Vec3(const DirectX::XMFLOAT3& Rhs) :x(Rhs.x), y(Rhs.y), z(Rhs.z) {};
	Vec3(const DirectX::XMVECTOR& Rhs) :x(Rhs.m128_f32[0]), y(Rhs.m128_f32[1]), z(Rhs.m128_f32[2]) {};

	// ����
	inline const float& Dot(const Vec3& Rhs) {
		return x * Rhs.x + y * Rhs.y + z * Rhs.z;
	}
	// �O��
	inline const Vec3& Cross(const Vec3& Rhs) {
		return Vec3(y * Rhs.z - z * Rhs.y,
			z * Rhs.x - x * Rhs.z,
			x * Rhs.y - y * Rhs.x);
	}
	// ����
	inline const float& Length() {
		return sqrtf(Dot(*this));
	}
	// ���K��
	inline void Normalize() {
		float length = this->Length();
		x /= length;
		y /= length;
		z /= length;
	}
	// ���K�������l���擾
	inline Vec3 GetNormal() {
		float length = this->Length();
		Vec3 buff = *this;
		buff.x /= length;
		buff.y /= length;
		buff.z /= length;
		return buff;
	}
	// DirectX::XMFLOAT3�֕ϊ�
	inline DirectX::XMFLOAT3 ConvertXMFLOAT3() {
		return DirectX::XMFLOAT3(x, y, z);
	}
	// DirectX::XMVECTOR�֕ϊ�
	inline DirectX::XMVECTOR ConvertXMVECTOR() {
		return { x,y,z };
	}


#pragma region �I�y���[�^�[���Z�q
	Vec3 operator-() const {
		return Vec3(-x, -y, -z);
	}
	Vec3 operator+(const Vec3& Rhs) const {
		return Vec3(x + Rhs.x, y + Rhs.y, z + Rhs.z);
	};
	Vec3 operator-(const Vec3& Rhs)const {
		return Vec3(x - Rhs.x, y - Rhs.y, z - Rhs.z);
	};
	Vec3 operator*(const Vec3& Rhs)const {
		return Vec3(x * Rhs.x, y * Rhs.y, z * Rhs.z);
	};
	Vec3 operator*(const float& Rhs)const {
		return Vec3(x * Rhs, y * Rhs, z * Rhs);
	};
	Vec3 operator/(const Vec3& Rhs)const {
		return Vec3(x / Rhs.x, y / Rhs.y, z / Rhs.z);
	};
	Vec3 operator/(const float& Rhs)const {
		return Vec3(x / Rhs, y / Rhs, z / Rhs);
	};
	Vec3 operator%(const Vec3& Rhs) const {
		return Vec3(fmodf(x, Rhs.x), fmodf(y, Rhs.y), fmodf(z, Rhs.z));
	};
	void operator=(const Vec3& Rhs) {
		x = Rhs.x;
		y = Rhs.y;
		z = Rhs.z;
	};
	bool operator==(const Vec3& Rhs)const {
		return (x == Rhs.x && y == Rhs.y && z == Rhs.z);
	};
	bool operator!=(const Vec3& Rhs)const {
		return !(*this == Rhs);
	};
	void operator+=(const Vec3& Rhs) {
		x += Rhs.x;
		y += Rhs.y;
		z += Rhs.z;
	};
	void operator-=(const Vec3& Rhs) {
		x -= Rhs.x;
		y -= Rhs.y;
		z -= Rhs.z;
	};
	void operator*=(const Vec3& Rhs) {
		x *= Rhs.x;
		y *= Rhs.y;
		z *= Rhs.z;
	};
	void operator/=(const Vec3& Rhs) {
		x /= Rhs.x;
		y /= Rhs.y;
		z /= Rhs.z;
	};
	void operator%=(const Vec3& Rhs) {
		x = fmodf(x, Rhs.x);
		y = fmodf(y, Rhs.y);
		z = fmodf(z, Rhs.z);
	};

	void operator+=(const float& Rhs) {
		x += Rhs;
		y += Rhs;
		z += Rhs;
	};
	void operator-=(const float& Rhs) {
		x -= Rhs;
		y -= Rhs;
		y -= Rhs;
	};
	void operator*=(const float& Rhs) {
		x *= Rhs;
		y *= Rhs;
		y *= Rhs;
	};
	void operator/=(const float& Rhs) {
		x /= Rhs;
		y /= Rhs;
		y /= Rhs;
	};
	void operator%=(const float& Rhs) {
		x = fmodf(x, Rhs);
		y = fmodf(y, Rhs);
		z = fmodf(z, Rhs);
	};

	/*----- DirectXMath�֌W�̃I�y���[�^�[���Z�q -----*/

	Vec3 operator+(const DirectX::XMFLOAT3& Rhs) const {
		return Vec3(x + Rhs.x, y + Rhs.y, z + Rhs.z);
	};
	Vec3 operator-(const DirectX::XMFLOAT3& Rhs)const {
		return Vec3(x - Rhs.x, y - Rhs.y, z - Rhs.z);
	};
	Vec3 operator*(const DirectX::XMFLOAT3& Rhs)const {
		return Vec3(x * Rhs.x, y * Rhs.y, z * Rhs.z);
	};
	Vec3 operator/(const DirectX::XMFLOAT3& Rhs)const {
		return Vec3(x / Rhs.x, y / Rhs.y, z / Rhs.z);
	};
	Vec3 operator%(const DirectX::XMFLOAT3& Rhs) const {
		return Vec3(fmodf(x, Rhs.x), fmodf(y, Rhs.y), fmodf(z, Rhs.z));
	};
	void operator=(const DirectX::XMFLOAT3& Rhs) {
		x = Rhs.x;
		y = Rhs.y;
		z = Rhs.z;
	};
	bool operator==(const DirectX::XMFLOAT3& Rhs)const {
		return (x == Rhs.x && y == Rhs.y && z == Rhs.z);
	};
	bool operator!=(const DirectX::XMFLOAT3& Rhs)const {
		return !(*this == Rhs);
	};
	void operator+=(const DirectX::XMFLOAT3& Rhs) {
		x += Rhs.x;
		y += Rhs.y;
		z += Rhs.z;
	};
	void operator-=(const DirectX::XMFLOAT3& Rhs) {
		x -= Rhs.x;
		y -= Rhs.y;
		z -= Rhs.z;
	};
	void operator*=(const DirectX::XMFLOAT3& Rhs) {
		x *= Rhs.x;
		y *= Rhs.y;
		z *= Rhs.z;
	};
	void operator/=(const DirectX::XMFLOAT3& Rhs) {
		x /= Rhs.x;
		y /= Rhs.y;
		z /= Rhs.z;
	};
	void operator%=(const DirectX::XMFLOAT3& Rhs) {
		x = fmodf(x, Rhs.x);
		y = fmodf(y, Rhs.y);
		z = fmodf(z, Rhs.z);
	};

	Vec3 operator+(const DirectX::XMVECTOR& Rhs) const {
		return Vec3(x + Rhs.m128_f32[0], y + Rhs.m128_f32[1], z + Rhs.m128_f32[2]);
	};
	Vec3 operator-(const DirectX::XMVECTOR& Rhs)const {
		return Vec3(x - Rhs.m128_f32[0], y - Rhs.m128_f32[1], z - Rhs.m128_f32[2]);
	};
	Vec3 operator*(const DirectX::XMVECTOR& Rhs)const {
		return Vec3(x * Rhs.m128_f32[0], y * Rhs.m128_f32[1], z * Rhs.m128_f32[2]);
	};
	Vec3 operator/(const DirectX::XMVECTOR& Rhs)const {
		return Vec3(x / Rhs.m128_f32[0], y / Rhs.m128_f32[1], z / Rhs.m128_f32[2]);
	};
	Vec3 operator%(const DirectX::XMVECTOR& Rhs) const {
		return Vec3(fmodf(x, Rhs.m128_f32[0]), fmodf(y, Rhs.m128_f32[1]), fmodf(z, Rhs.m128_f32[2]));
	};
	void operator=(const DirectX::XMVECTOR& Rhs) {
		x = Rhs.m128_f32[0];
		y = Rhs.m128_f32[1];
		z = Rhs.m128_f32[2];
	};
	bool operator==(const DirectX::XMVECTOR& Rhs)const {
		return (x == Rhs.m128_f32[0] && y == Rhs.m128_f32[1] && z == Rhs.m128_f32[2]);
	};
	bool operator!=(const DirectX::XMVECTOR& Rhs)const {
		return !(*this == Rhs);
	};
	void operator+=(const DirectX::XMVECTOR& Rhs) {
		x += Rhs.m128_f32[0];
		y += Rhs.m128_f32[1];
		z += Rhs.m128_f32[2];
	};
	void operator-=(const DirectX::XMVECTOR& Rhs) {
		x -= Rhs.m128_f32[0];
		y -= Rhs.m128_f32[1];
		z -= Rhs.m128_f32[2];
	};
	void operator*=(const DirectX::XMVECTOR& Rhs) {
		x *= Rhs.m128_f32[0];
		y *= Rhs.m128_f32[1];
		z *= Rhs.m128_f32[2];
	};
	void operator/=(const DirectX::XMVECTOR& Rhs) {
		x /= Rhs.m128_f32[0];
		y /= Rhs.m128_f32[1];
		z /= Rhs.m128_f32[2];
	};
	void operator%=(const DirectX::XMVECTOR& Rhs) {
		x = fmodf(x, Rhs.m128_f32[0]);
		y = fmodf(y, Rhs.m128_f32[1]);
		z = fmodf(z, Rhs.m128_f32[2]);
	};

#pragma endregion

};