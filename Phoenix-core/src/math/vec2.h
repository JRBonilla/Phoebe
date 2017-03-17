#pragma once
#include <iostream>

namespace ph { namespace math {

	struct Vec2 {
		float x, y;

		Vec2();
		Vec2(const float& x, const float& y);

		Vec2& add(const Vec2& other);
		Vec2& subtract(const Vec2& other);
		Vec2& multiply(const Vec2& other);
		Vec2& divide(const Vec2& other);

		friend Vec2 operator+(Vec2 left, const Vec2& right);
		friend Vec2 operator-(Vec2 left, const Vec2& right);
		friend Vec2 operator*(Vec2 left, const Vec2& right);
		friend Vec2 operator/(Vec2 left, const Vec2& right);

		friend Vec2 operator+(Vec2 left, float value);
		friend Vec2 operator-(Vec2 left, float value);
		friend Vec2 operator*(Vec2 left, float value);
		friend Vec2 operator/(Vec2 left, float value);

		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);
		Vec2& operator*=(const Vec2& other);
		Vec2& operator/=(const Vec2& other);

		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;

		bool operator<(const Vec2& other) const;
		bool operator>(const Vec2& other) const;
		bool operator>=(const Vec2& other) const;
		bool operator<=(const Vec2& other) const;

		float magnitude() const;
		Vec2 normalize() const;
		float distance(const Vec2& other) const;
		float dot(const Vec2& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vec2& other);
	};

}}
