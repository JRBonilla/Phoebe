#pragma once

#include <iostream>

namespace ph { namespace math {

	struct Vec4 {
		float x, y, z, w;

		Vec4();
		Vec4(float scalar);
		Vec4(const float& x, const float& y, const float& z, const float& w);

		Vec4& Add(const Vec4& other);
		Vec4& Subtract(const Vec4& other);
		Vec4& Multiply(const Vec4& other);
		Vec4& Divide(const Vec4& other);

		friend Vec4 operator+(Vec4 left, const Vec4& right);
		friend Vec4 operator-(Vec4 left, const Vec4& right);
		friend Vec4 operator*(Vec4 left, const Vec4& right);
		friend Vec4 operator/(Vec4 left, const Vec4& right);

		Vec4& operator+=(const Vec4& other);
		Vec4& operator-=(const Vec4& other);
		Vec4& operator*=(const Vec4& other);
		Vec4& operator/=(const Vec4& other);

		bool operator==(const Vec4& other) const;
		bool operator!=(const Vec4& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
	};
	
}}
