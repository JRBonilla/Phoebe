#include "Vec2.h"

namespace ph { namespace math {

	Vec2::Vec2() {
		x = 0.0f;
		y = 0.0f;
	}

	Vec2::Vec2(const float& x, const float& y) {
		this->x = x;
		this->y = y;
	}

	Vec2& Vec2::add(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& Vec2::subtract(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2& Vec2::multiply(const Vec2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2& Vec2::divide(const Vec2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Vec2 operator+(Vec2 left, const Vec2& right) {
		return left.add(right);
	}

	Vec2 operator-(Vec2 left, const Vec2& right) {
		return left.subtract(right);
	}

	Vec2 operator*(Vec2 left, const Vec2& right) {
		return left.multiply(right);
	}

	Vec2 operator/(Vec2 left, const Vec2& right) {
		return left.divide(right);
	}

	Vec2 operator+(Vec2 left, float value) {
		return Vec2(left.x + value, left.y + value);
	}

	Vec2 operator-(Vec2 left, float value) {
		return Vec2(left.x - value, left.y - value);
	}

	Vec2 operator*(Vec2 left, float value) {
		return Vec2(left.x * value, left.y * value);
	}

	Vec2 operator/(Vec2 left, float value) {
		return Vec2(left.x / value, left.y / value);
	}

	Vec2& Vec2::operator+=(const Vec2& other) {
		return add(other);
	}

	Vec2& Vec2::operator-=(const Vec2& other) {
		return subtract(other);
	}

	Vec2& Vec2::operator*=(const Vec2& other) {
		return multiply(other);
	}

	Vec2& Vec2::operator/=(const Vec2& other) {
		return divide(other);
	}

	bool Vec2::operator==(const Vec2& other) const {
		return (x == other.x) && (y == other.y);
	}

	bool Vec2::operator!=(const Vec2& other) const {
		return !(*this == other);
	}

	bool Vec2::operator<(const Vec2& other) const {
		return (x < other.x) && (y < other.y);
	}

	bool Vec2::operator<=(const Vec2& other) const {
		return (x <= other.x) && (y <= other.y);
	}

	bool Vec2::operator>(const Vec2& other) const {
		return (x > other.x) && (y > other.y);
	}

	bool Vec2::operator>=(const Vec2& other) const {
		return (x >= other.x) && (y >= other.y);
	}

	float Vec2::magnitude() const {
		return sqrt(x*x + y*y);
	}

	float Vec2::distance(const Vec2& other) const {
		float a = x - other.x;
		float b = y - other.y;
		return sqrt(a*a + b*b);
	}

	float Vec2::dot(const Vec2& other) const {
		return x * other.x + y * other.y;
	}

	Vec2 Vec2::normalize() const {
		float length = magnitude();
		return Vec2(x / length, y / length);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2& vector) {
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

}}