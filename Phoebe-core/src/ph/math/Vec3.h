#pragma once

#include <iostream>

namespace ph { namespace math {

	struct Vec3 {
		float x, y, z;

		Vec3();
		Vec3(float scalar);
		Vec3(const float& x, const float& y, const float& z);

		static Vec3 Up();
		static Vec3 Down();
		static Vec3 Left();
		static Vec3 Right();
		static Vec3 Zero();

		static Vec3 XAxis();
		static Vec3 YAxis();
		static Vec3 ZAxis();

		Vec3& Add(const Vec3& other);
		Vec3& Subtract(const Vec3& other);
		Vec3& Multiply(const Vec3& other);
		Vec3& Divide(const Vec3& other);

		friend Vec3 operator+(Vec3 left, const Vec3& right);
		friend Vec3 operator-(Vec3 left, const Vec3& right);
		friend Vec3 operator*(Vec3 left, const Vec3& right);
		friend Vec3 operator/(Vec3 left, const Vec3& right);

		friend Vec3 operator+(Vec3 left, float value);
		friend Vec3 operator-(Vec3 left, float value);
		friend Vec3 operator*(Vec3 left, float value);
		friend Vec3 operator/(Vec3 left, float value);

		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(const Vec3& other);
		Vec3& operator/=(const Vec3& other);

		bool operator==(const Vec3& other) const;
		bool operator!=(const Vec3& other) const;

		friend Vec3 operator-(const Vec3& vector);

		float Magnitude() const;
		Vec3 Normalize() const;
		float Distance(const Vec3& other) const;

		Vec3 Cross(const Vec3& other) const;
		float Dot(const Vec3& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vec3& other);
	};
	
}}