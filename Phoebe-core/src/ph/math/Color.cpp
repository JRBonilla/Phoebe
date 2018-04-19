#include "Color.h"

namespace ph { namespace math {

	Color::Color() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	}

	Color::Color(uint color) {
		r = ((color >> 24) & 0xFF) / 255.0f;
		g = ((color >> 16) & 0xFF) / 255.0f;
		b = ((color >>  8) & 0xFF) / 255.0f;
		a = ((color      ) & 0xFF) / 255.0f;
	}

	Color::Color(float scalar) {
		r = scalar;
		g = scalar;
		b = scalar;
		a = scalar;
	}

	Color::Color(const float& r, const float& g, const float& b, const float& a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color& Color::Add(const Color& other) {
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		return *this;
	}

	Color& Color::Subtract(const Color& other) {
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
		return *this;
	}

	Color& Color::Multiply(const Color& other) {
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
		return *this;
	}

	Color& Color::Divide(const Color& other) {
		r /= other.r;
		g /= other.g;
		b /= other.b;
		a /= other.a;
		return *this;
	}

	Color operator+(Color left, const Color& right) {
		return left.Add(right);
	}

	Color operator-(Color left, const Color& right) {
		return left.Subtract(right);
	}

	Color operator*(Color left, const Color& right) {
		return left.Multiply(right);
	}

	Color operator/(Color left, const Color& right) {
		return left.Divide(right);
	}

	Color& Color::operator+=(const Color& other) {
		return Add(other);
	}

	Color& Color::operator-=(const Color& other) {
		return Subtract(other);
	}

	Color& Color::operator*=(const Color& other) {
		return Multiply(other);
	}

	Color& Color::operator/=(const Color& other) {
		return Divide(other);
	}

	bool Color::operator==(const Color& other) const {
		return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
	}

	bool Color::operator!=(const Color& other) const {
		return !(*this == other);
	}

	uint Color::ToHex() {
		int r = (int)this->r * 255;
		int g = (int)this->g * 255;
		int b = (int)this->b * 255;
		int a = (int)this->a * 255;

		uint hexColor = a << 24 | b << 16 | g << 8 | r;
		return hexColor;
	}

	std::ostream& operator<<(std::ostream& stream, const Color& color) {
		stream << "color: (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
		return stream;
	}

}}