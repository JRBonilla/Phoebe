#pragma once

#include <iostream>
#include "ph/Types.h"

namespace ph { namespace math {

	struct Color {
		float r, g, b, a;

		Color();
		Color(uint color);
		Color(float scalar);
		Color(const float& r, const float& g, const float& b, const float& a);

		Color& Add(const Color& other);
		Color& Subtract(const Color& other);
		Color& Multiply(const Color& other);
		Color& Divide(const Color& other);

		friend Color operator+(Color left, const Color& right);
		friend Color operator-(Color left, const Color& right);
		friend Color operator*(Color left, const Color& right);
		friend Color operator/(Color left, const Color& right);

		Color& operator+=(const Color& other);
		Color& operator-=(const Color& other);
		Color& operator*=(const Color& other);
		Color& operator/=(const Color& other);

		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;

		uint ToHex();

		friend std::ostream& operator<<(std::ostream& stream, const Color& color);
	};

}}