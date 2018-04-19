#include "Quat.h"

namespace ph { namespace math {

	Quat::Quat()
		: x(0), y(0), z(0), w(1) {
	}

	Quat::Quat(const Quat& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	Quat::Quat(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) {
	}

	Quat::Quat(const Vec4& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}

	Quat::Quat(float scalar) {
		x = scalar;
		y = scalar;
		z = scalar;
		w = scalar;
	}

	Quat::Quat(const Vec3& xyz, float w) {
		this->SetXYZ(xyz);
		this->w = w;
	}

	Quat Quat::Identity() {
		return Quat(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Quat Quat::FromEulerAngles(const Vec3& angles) {
		Quat pitch(Vec3(1.0f, 0.0f, 0.0f), angles.x);
		Quat yaw(Vec3(0.0f, 1.0f, 0.0f), angles.y);
		Quat roll(Vec3(0.0f, 0.0f, 1.0f), angles.z);
		return pitch * yaw * roll;
	}

	Quat& Quat::operator=(const Quat& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	Quat& Quat::SetXYZ(const Vec3& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	const Vec3 Quat::GetXYZ() const {
		return Vec3(x, y, z);
	}

	Quat& Quat::SetElement(int32 index, float value) {
		*(&x + index) = value;
		return *this;
	}

	float Quat::GetElement(int32 index) const {
		return *(&x + index);
	}

	float Quat::operator[](int32 index) const {
		return *(&x + index);
	}

	Vec3 Quat::GetAxis() const {
		float x = 1.0f - w * w;
		if (x < 0.0000001f) { // Divide by zero safety check
			return Vec3::XAxis();
		}

		float x2 = x * x;
		return GetXYZ() / x2;
	}

	Vec3 Quat::ToEulerAngles() const {
		return Vec3(atan2(2 * x * w - 2 * y * z, 1 - 2 * x * x - 2 * z * z),
					atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z),
					 asin(2 * x * y + 2 * z * w));
	}

	const Quat Quat::operator+(const Quat& other) const {
		return Quat(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	const Quat Quat::operator-(const Quat& other) const {
		return Quat(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	const Quat Quat::operator*(float scalar) const {
		return Quat(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	const Quat Quat::operator/(float scalar) const {
		return Quat(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	const Quat Quat::operator-() const {
		return Quat(-x, -y, -z, -w);
	}

	bool Quat::operator==(const Quat & other) const {
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}

	bool Quat::operator!=(const Quat & other) const {
		return !(*this == other);
	}

	float Norm(const Quat& other) {
		float result;
		result = (other.x * other.x);
		result = (result + (other.y * other.y));
		result = (result + (other.z * other.z));
		result = (result + (other.w * other.w));
		return result;
	}

	float Length(const Quat& other) {
		return sqrt(Norm(other));
	}

	const Quat Normalize(const Quat& other) {
		float lenSqr, lenInv;
		lenSqr = Norm(other);
		lenInv = rsqrt(lenSqr);
		return other * lenInv;
	}

	const Quat NormalizeEst(const Quat& other) {
		float lenSqr, lenInv;
		lenSqr = Norm(other);
		lenInv = rsqrt(lenSqr);
		return other * lenInv;
	}

	const Quat Quat::Rotation(const Vec3& unitVec0, const Vec3& unitVec1) {
		float cosHalfAngleX2, recipCosHalfAngleX2;
		cosHalfAngleX2 = sqrt((2.0f * (1.0f + unitVec0.Dot(unitVec1))));
		recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
		return Quat((unitVec0.Cross(unitVec1) * recipCosHalfAngleX2), (cosHalfAngleX2 * 0.5f));
	}

	const Quat Quat::Rotation(float radians, const Vec3 & unitVec) {
		float angle = radians * 0.5f;
		return Quat((unitVec * sin(angle)), cos(angle));
	}

	const Quat Quat::operator*(const Quat& other) const {
		return Normalize(Quat(
			(((w * other.x) + (x * other.w)) + (y * other.z)) - (z * other.y),
			(((w * other.y) + (y * other.w)) + (z * other.x)) - (x * other.z),
			(((w * other.z) + (z * other.w)) + (x * other.y)) - (y * other.x),
			(((w * other.w) - (x * other.x)) - (y * other.y)) - (z * other.z)
		));
	}

	Vec3 Quat::Rotate(const Quat& quat, const Vec3& vec) {
		float tmpX, tmpY, tmpZ, tmpW;
		tmpX = (((quat.w * vec.x) + (quat.y * vec.z)) - (quat.z * vec.y));
		tmpY = (((quat.w * vec.y) + (quat.z * vec.x)) - (quat.x * vec.z));
		tmpZ = (((quat.w * vec.z) + (quat.x * vec.y)) - (quat.y * vec.x));
		tmpW = (((quat.x * vec.x) + (quat.y * vec.y)) + (quat.z * vec.z));
		return Vec3(
			((((tmpW * quat.x) + (tmpX * quat.w)) - (tmpY * quat.z)) + (tmpZ * quat.y)),
			((((tmpW * quat.y) + (tmpY * quat.w)) - (tmpZ * quat.x)) + (tmpX * quat.z)),
			((((tmpW * quat.z) + (tmpZ * quat.w)) - (tmpX * quat.y)) + (tmpY * quat.x))
		);
	}

	Quat Quat::Conjugate() const {
		return Quat(-x, -y, -z, w);
	}

	const Quat Select(const Quat& quat0, const Quat& quat1, bool select1) {
		return Quat(select1 ? quat1.x : quat0.x, select1 ? quat1.y : quat0.y, select1 ? quat1.z : quat0.z, select1 ? quat1.w : quat0.w);
	}

	float Quat::Dot(const Quat& other) const {
		float result = (x * other.x);
		result = (result + (y * other.y));
		result = (result + (z * other.z));
		result = (result + (w * other.w));
		return result;
	}

}}