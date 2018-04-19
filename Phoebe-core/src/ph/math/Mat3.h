#pragma once

#include "Vec3.h"

namespace ph { namespace math {
	
	struct Mat4;

	struct Mat3 {
		union {
			float elements[3 * 3];
			Vec3 column[3];
		};

		Mat3();
		Mat3(float diagonal);
		Mat3(float* elements);
		Mat3(const Vec3& col0, const Vec3& col1, const Vec3& col2);
		Mat3(const Mat4& mat4);

		Mat3& Multiply(const Mat3& other);
		friend Mat3 operator*(Mat3 left, const Mat3& right);
		Mat3& operator*=(const Mat3& other);

		friend std::ostream& operator<<(std::ostream& stream, const Mat3& matrix);
	};

}}