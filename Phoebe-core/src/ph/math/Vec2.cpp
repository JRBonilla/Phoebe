#include "Vec2.h"

namespace ph { namespace math {

	Vec2::Vec2() {
		x = 0.0f;
		y = 0.0f;
	}

	Vec2::Vec2(float scalar) {
		x = scalar;
		y = scalar;
	}

	Vec2::Vec2(const float& x, const float& y) {
		this->x = x;
		this->y = y;
	}

	Vec2& Vec2::Add(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& Vec2::Subtract(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2& Vec2::Multiply(const Vec2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2& Vec2::Divide(const Vec2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Vec2 operator+(Vec2 left, const Vec2& right) {
		return left.Add(right);
	}

	Vec2 operator-(Vec2 left, const Vec2& right) {
		return left.Subtract(right);
	}

	Vec2 operator*(Vec2 left, const Vec2& right) {
		return left.Multiply(right);
	}

	Vec2 operator/(Vec2 left, const Vec2& right) {
		return left.Divide(right);
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
		return Add(other);
	}

	Vec2& Vec2::operator-=(const Vec2& other) {
		return Subtract(other);
	}

	Vec2& Vec2::operator*=(const Vec2& other) {
		return Multiply(other);
	}

	Vec2& Vec2::operator/=(const Vec2& other) {
		return Divide(other);
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

	float Vec2::Magnitude() const {
		return sqrt(x*x + y*y);
	}

	float Vec2::Distance(const Vec2& other) const {
		float a = x - other.x;
		float b = y - other.y;
		return sqrt(a*a + b*b);
	}

	float Vec2::Dot(const Vec2& other) const {
		return x * other.x + y * other.y;
	}

	Vec2 Vec2::Normalize() const {
		float length = Magnitude();
		return Vec2(x / length, y / length);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2& vector) {
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

}}