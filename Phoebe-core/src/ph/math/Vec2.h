#pragma once
#include <iostream>

namespace ph { namespace math {

	struct Vec2 {
		float x, y;

		Vec2();
		Vec2(float scalar);
		Vec2(const float& x, const float& y);

		Vec2& Add(const Vec2& other);
		Vec2& Subtract(const Vec2& other);
		Vec2& Multiply(const Vec2& other);
		Vec2& Divide(const Vec2& other);

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

		Vec2 Normalize() const;
		float Magnitude() const;
		float Distance(const Vec2& other) const;
		float Dot(const Vec2& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vec2& other);
	};

}}
