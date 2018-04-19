#include "Vec3.h"

namespace ph { namespace math {

	Vec3::Vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vec3::Vec3(float scalar) {
		x = scalar;
		y = scalar;
		z = scalar;
	}

	Vec3::Vec3(const float& x, const float& y, const float& z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3 Vec3::Up() {
		return Vec3(0.0f, 1.0f, 0.0f);
	}

	Vec3 Vec3::Down() {
		return Vec3(0.0f, -1.0f, 0.0f);
	}

	Vec3 Vec3::Left() {
		return Vec3(-1.0f, 0.0f, 0.0f);
	}

	Vec3 Vec3::Right() {
		return Vec3(1.0f, 1.0f, 0.0f);
	}

	Vec3 Vec3::Zero() {
		return Vec3(0.0f, 0.0f, 0.0f);
	}

	Vec3 Vec3::XAxis() {
		return Vec3(1.0f, 0.0f, 0.0f);
	}

	Vec3 Vec3::YAxis() {
		return Vec3(0.0f, 1.0f, 0.0f);
	}

	Vec3 Vec3::ZAxis() {
		return Vec3(0.0f, 0.0f, 1.0f);
	}

	Vec3& Vec3::Add(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& Vec3::Subtract(const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3& Vec3::Multiply(const Vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vec3& Vec3::Divide(const Vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vec3 operator+(Vec3 left, const Vec3& right) {
		return left.Add(right);
	}

	Vec3 operator-(Vec3 left, const Vec3& right) {
		return left.Subtract(right);
	}

	Vec3 operator*(Vec3 left, const Vec3& right) {
		return left.Multiply(right);
	}

	Vec3 operator/(Vec3 left, const Vec3& right) {
		return left.Divide(right);
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
		return Add(other);
	}

	Vec3& Vec3::operator-=(const Vec3& other) {
		return Subtract(other);
	}

	Vec3& Vec3::operator*=(const Vec3& other) {
		return Multiply(other);
	}

	Vec3& Vec3::operator/=(const Vec3& other) {
		return Divide(other);
	}

	bool Vec3::operator==(const Vec3& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool Vec3::operator!=(const Vec3& other) const {
		return !(*this == other);
	}

	Vec3 operator-(const Vec3& vector) {
		return Vec3(-vector.x, -vector.y, -vector.z);
	}

	float Vec3::Magnitude() const {
		return sqrt(x*x + y*y + z*z);
	}

	float Vec3::Distance(const Vec3& other) const {
		float a = x - other.x;
		float b = y - other.y;
		float c = z - other.z;
		return sqrt(a*a + b*b + c*c);
	}

	Vec3 Vec3::Cross(const Vec3& other) const {
		return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.z);
	}

	float Vec3::Dot(const Vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	Vec3 Vec3::Normalize() const {
		float length = Magnitude();
		return Vec3(x / length, y / length, z / length);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector) {
		stream << "Vec3: (" << vector.x << ", " << vector.y << " ," << vector.z << ")";
		return stream;
	}

}}