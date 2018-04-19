#include "Mat3.h"
#include "Mat4.h"

namespace ph { namespace math {

	Mat3::Mat3() {
		memset(elements, 0, 3 * 3 * sizeof(float));
	}

	Mat3::Mat3(float diagonal) {
		memset(elements, 0, 3 * 3 * sizeof(float));

		elements[0 + 0 * 3] = diagonal;
		elements[1 + 1 * 3] = diagonal;
		elements[2 + 2 * 3] = diagonal;
	}

	Mat3::Mat3(float* elements) {
		memcpy(this->elements, elements, 3 * 3 * sizeof(float));
	}

	Mat3::Mat3(const Vec3& col0, const Vec3& col1, const Vec3& col2) {
		column[0] = col0;
		column[1] = col1;
		column[2] = col2;
	}

	Mat3::Mat3(const Mat4& mat4) {
		column[0] = Vec3(mat4.column[0].x, mat4.column[0].y, mat4.column[0].z);
		column[1] = Vec3(mat4.column[1].x, mat4.column[1].y, mat4.column[1].z);
		column[2] = Vec3(mat4.column[2].x, mat4.column[2].y, mat4.column[2].z);
	}

	Mat3& Mat3::Multiply(const Mat3& other) {
		float data[9];
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 3; e++) {
					sum += elements[x + e * 3] * other.elements[e + y * 3];
				}
				data[x + y * 3] = sum;
			}
		}

		memcpy(elements, data, 9 * 3);
		return *this;
	}

	Mat3 operator*(Mat3 left, const Mat3& right) {
		return left.Multiply(right);
	}

	Mat3& Mat3::operator*=(const Mat3& other) {
		return Multiply(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Mat3& matrix) {
		stream << "mat3: (" << matrix.column[0].x << ", " << matrix.column[1].x << ", " << matrix.column[2].x << "), ";
		stream << "(" << matrix.column[0].y << ", " << matrix.column[1].y << ", " << matrix.column[2].y << "), ";
		stream << "(" << matrix.column[0].z << ", " << matrix.column[1].z << ", " << matrix.column[2].z << ")";
		return stream;
	}

}}