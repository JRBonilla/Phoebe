#pragma once

#include "Vec3.h"
#include "Vec4.h"

namespace ph { namespace math {

	struct Quat;
	struct Mat3;

	struct Mat4 {
		union {
			float elements[4 * 4];
			Vec4 column[4];
		};

		Mat4();
		Mat4(float diagonal);
		Mat4(float* elements);
		Mat4(const Vec4& col0, const Vec4& col1, const Vec4& col2, const Vec4& col3);
		Mat4(const Mat3& mat3);

		Mat4& Multiply(const Mat4& other);
		friend Mat4 operator*(Mat4 left, const Mat4& right);
		Mat4& operator*=(const Mat4& other);

		Vec3 Multiply(const Vec3& other) const;
		friend Vec3 operator*(const Mat4& left, const Vec3& right);

		Vec4 Multiply(const Vec4& other) const;
		friend Vec4 operator*(const Mat4& left, const Vec4& right);

		Mat4& Invert();

		static Mat4 Identity();

		static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static Mat4 Perspective(float fov, float aspectRatio, float near, float far);
		static Mat4 LookAt(const Vec3& camera, const Vec3& object, const Vec3& up);

		static Mat4 Translate(const Vec3& translation);
		static Mat4 Scale(const Vec3& scale);
		static Mat4 Rotate(float angle, const Vec3& axis);
		static Mat4 Rotate(const Quat& quaternion);
		static Mat4 Invert(const Mat4& matrix);

		friend std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);
	};

}}
