#pragma warning( disable: 4305 )
#pragma once

#include "Functions.h"
#include "Vec3.h"
#include "Vec4.h"
#include "ph/Types.h"

namespace ph { namespace math {

	struct Quat {
		float x, y, z, w;

		Quat();
		Quat(const Quat& other);
		Quat(float x, float y, float z, float w);
		Quat(const Vec3& xyz, float w);
		Quat(const Vec4& vec);
		Quat(float scalar);

		Quat& operator=(const Quat& other);

		Quat& SetXYZ(const Vec3& vec);
		const Vec3 GetXYZ() const;

		Quat& SetElement(int32 index, float value);
		float GetElement(int32 index) const;
		Vec3 GetAxis() const;
		Vec3 ToEulerAngles() const;

		const Quat operator+(const Quat& other) const;
		const Quat operator-(const Quat& other) const;
		const Quat operator*(const Quat& other) const;
		const Quat operator*(float scalar) const;
		const Quat operator/(float scalar) const;
		float operator[](int32 index) const;

		Quat& operator+=(const Quat& other) {
			*this = *this + other;
			return *this;
		}

		Quat& operator-=(const Quat& other) {
			*this = *this - other;
			return *this;
		}

		Quat& operator*=(const Quat& other) {
			*this = *this * other;
			return *this;
		}

		Quat& operator*=(float scalar) {
			*this = *this * scalar;
			return *this;
		}

		Quat& operator/=(float scalar) {
			*this = *this / scalar;
			return *this;
		}

		const Quat operator-() const;
		bool operator==(const Quat& other) const;
		bool operator!=(const Quat& other) const;

		static Quat Identity();
		static Quat FromEulerAngles(const Vec3& angles);

		static Vec3 Rotate(const Quat& quat, const Vec3& vec);

		static const Quat Rotation(const Vec3& unitVec0, const Vec3& unitVec1);
		static const Quat Rotation(float radians, const Vec3& unitVec);

		static const Quat RotationX(float radians) {
			float angle = radians * 0.5f;
			return Quat(sin(angle), 0.0f, 0.0f, cos(angle));
		}

		static const Quat RotationY(float radians) {
			float angle = radians * 0.5f;
			return Quat(0.0f, sin(angle), 0.0f, cos(angle));
		}

		static const Quat RotationZ(float radians) {
			float angle = radians * 0.5f;
			return Quat(0.0f, 0.0f, sin(angle), cos(angle));
		}

		float Dot(const Quat& other) const;
		Quat Conjugate() const;
	};

}}