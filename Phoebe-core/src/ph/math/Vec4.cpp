#include "Vec4.h"

namespace ph { namespace math {

	Vec4::Vec4() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	Vec4::Vec4(float scalar) {
		x = scalar;
		y = scalar;
		z = scalar;
		w = scalar;
	}

	Vec4::Vec4(const float& x, const float& y, const float& z, const float& w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vec4& Vec4::Add(const Vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vec4& Vec4::Subtract(const Vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vec4& Vec4::Multiply(const Vec4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vec4& Vec4::Divide(const Vec4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	Vec4 operator+(Vec4 left, const Vec4& right) {
		return left.Add(right);
	}

	Vec4 operator-(Vec4 left, const Vec4& right) {
		return left.Subtract(right);
	}

	Vec4 operator*(Vec4 left, const Vec4& right) {
		return left.Multiply(right);
	}

	Vec4 operator/(Vec4 left, const Vec4& right) {
		return left.Divide(right);
	}


	Vec4& Vec4::operator+=(const Vec4& other) {
		return Add(other);
	}

	Vec4& Vec4::operator-=(const Vec4& other) {
		return Subtract(other);
	}

	Vec4& Vec4::operator*=(const Vec4& other) {
		return Multiply(other);
	}

	Vec4& Vec4::operator/=(const Vec4& other) {
		return Divide(other);
	}

	bool Vec4::operator==(const Vec4& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}

	bool Vec4::operator!=(const Vec4& other) const {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec4& vector) {
		stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}
	
}}