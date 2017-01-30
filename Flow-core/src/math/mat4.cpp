#include "mat4.h"

namespace fl { namespace math {

	mat4::mat4() {
		memset(elements, 0, 4 * 4 * sizeof(float));
	}

	mat4::mat4(float diagonal) {
		memset(elements, 0, 4 * 4 * sizeof(float));

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4::mat4(float* elements) {
		memcpy(this->elements, elements, 4 * 4 * sizeof(float));
	}

	mat4::mat4(const vec4& col0, const vec4& col1, const vec4& col2, const vec4& col3) {
		column[0] = col0;
		column[1] = col1;
		column[2] = col2;
		column[3] = col3;
	}


	mat4 mat4::identity() {
		return mat4(1.0f);
	}

	mat4& mat4::multiply(const mat4& other) {
		float data[16];
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}

		memcpy(elements, data, 16 * 4);
		return *this;
	}

	mat4 operator*(mat4 left, const mat4& right) {
		return left.multiply(right);
	}

	mat4& mat4::operator*=(const mat4& other) {
		return multiply(other);
	}

	vec3 mat4::multiply(const vec3& other) const {
		return vec3 (
			(column[0].x * other.x) + (column[1].x * other.y) + (column[2].x * other.z) + (column[3].x * 1),
			(column[0].y * other.x) + (column[1].y * other.y) + (column[2].y * other.z) + (column[3].y * 1),
			(column[0].z * other.x) + (column[1].z * other.y) + (column[2].z * other.z) + (column[3].z * 1)
		);
	}

	vec3 operator*(const mat4& left, const vec3& right) {
		return left.multiply(right);
	}

	vec4 mat4::multiply(const vec4& other) const {
		return vec4 (
			(column[0].x * other.x) + (column[1].x * other.y) + (column[2].x * other.z) + (column[3].x * other.w),
			(column[0].y * other.x) + (column[1].y * other.y) + (column[2].y * other.z) + (column[3].y * other.w),
			(column[0].z * other.x) + (column[1].z * other.y) + (column[2].z * other.z) + (column[3].z * other.w),
			(column[0].w * other.x) + (column[1].w * other.y) + (column[2].w * other.z) + (column[3].w * other.w)
		);
	}

	vec4 operator*(const mat4& left, const vec4& right) {
		return left.multiply(right);
	}


	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) {
		mat4 result;

		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2 * far * near) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}

	mat4 mat4::lookAt(const vec3& camera, const vec3& object, const vec3& up) {
		mat4 result = identity();
		vec3 f = (object - camera).normalize();
		vec3 s = f.cross(up.normalize());
		vec3 u = s.cross(f);

		result.elements[0 + 0 * 4] = s.x;
		result.elements[1 + 0 * 4] = s.y;
		result.elements[2 + 0 * 4] = s.z;

		result.elements[0 + 1 * 4] = u.x;
		result.elements[1 + 1 * 4] = u.y;
		result.elements[2 + 1 * 4] = u.z;
		
		result.elements[0 + 2 * 4] = -f.x;
		result.elements[1 + 2 * 4] = -f.y;
		result.elements[2 + 2 * 4] = -f.z;

		return result * translate(vec3(-camera.x, -camera.y, -camera.z));
	}


	mat4 mat4::translate(const vec3& translation) {
		mat4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

	struct mat4 mat4::scale(const vec3& scale) {
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}


	mat4 mat4::rotate(float angle, const vec3& axis) {
		mat4 result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * x * omc + c;
		result.elements[0 + 1 * 4] = x * y * omc + z * s;
		result.elements[0 + 2 * 4] = x * z * omc - y * s;

		result.elements[1 + 0 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * y * omc + c;
		result.elements[1 + 2 * 4] = y * z * omc + x * s;

		result.elements[2 + 0 * 4] = x * z * omc + y * s;
		result.elements[2 + 1 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * z * omc + c;

		return result;
	}

}}