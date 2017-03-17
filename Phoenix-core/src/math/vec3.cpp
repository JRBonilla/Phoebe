#include "Vec3.h"

namespace ph { namespace math {

	Vec3::Vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vec3::Vec3(const float& x, const float& y, const float& z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3& Vec3::add(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& Vec3::subtract(const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3& Vec3::multiply(const Vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vec3& Vec3::divide(const Vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vec3 operator+(Vec3 left, const Vec3& right) {
		return left.add(right);
	}

	Vec3 operator-(Vec3 left, const Vec3& right) {
		return left.subtract(right);
	}

	Vec3 operator*(Vec3 left, const Vec3& right) {
		return left.multiply(right);
	}

	Vec3 operator/(Vec3 left, const Vec3& right) {
		return left.divide(right);
	}

	Vec3 operator+(Vec3 left, float value) {
		return Vec3(left.x + value, left.y + value, left.z + value);
	}

	Vec3 operator-(Vec3 left, float value) {
		return Vec3(left.x - value, left.y - value, left.z - value);
	}

	Vec3 operator*(Vec3 left, float value) {
		return Vec3(left.x * value, left.y * value, left.z * value);
	}

	Vec3 operator/(Vec3 left, float value) {
		return Vec3(left.x / value, left.y / value, left.z / value);
	}

	Vec3& Vec3::operator+=(const Vec3& other) {
		return add(other);
	}

	Vec3& Vec3::operator-=(const Vec3& other) {
		return subtract(other);
	}

	Vec3& Vec3::operator*=(const Vec3& other) {
		return multiply(other);
	}

	Vec3& Vec3::operator/=(const Vec3& other) {
		return divide(other);
	}

	bool Vec3::operator==(const Vec3& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool Vec3::operator!=(const Vec3& other) const {
		return !(*this == other);
	}

	float Vec3::magnitude() const {
		return sqrt(x*x + y*y + z*z);
	}

	float Vec3::distance(const Vec3& other) const {
		float a = x - other.x;
		float b = y - other.y;
		float c = z - other.z;
		return sqrt(a*a + b*b + c*c);
	}

	Vec3 Vec3::cross(const Vec3& other) const {
		return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.z);
	}

	float Vec3::dot(const Vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	Vec3 Vec3::normalize() const {
		float length = magnitude();
		return Vec3(x / length, y / length, z / length);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector) {
		stream << "vec3: (" << vector.x << ", " << vector.y << " ," << vector.z << ")";
		return stream;
	}

}}