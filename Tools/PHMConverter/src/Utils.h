#pragma once

#include <cstdint>
#include <unordered_map>

typedef uint8_t  byte;
typedef uint32_t uint;

#define BIT(num) (1 << num)

struct Vec2 {
	float x, y;

	Vec2() {
		x = 0.0f;
		y = 0.0f;
	}

	Vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	bool operator==(const Vec2& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vec2& other) const {
		return !(*this == other);
	}

	uint GetHash() const {
		return (*(uint*)&x) ^ ((*(uint*)&y) << 14);
	}
};

struct Vec3 {
	float x, y, z;

	Vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	bool operator==(const Vec3& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vec3& other) const {
		return !(*this == other);
	}

	uint GetHash() const {
		return (*(uint*)&x) ^ ((*(uint*)&y) << 14) ^ ((*(uint*)&z) << 23);
	}
};

struct Vec4 {
	float x, y, z, w;

	Vec4() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	Vec4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	bool operator==(const Vec4& other) const {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool operator!=(const Vec4& other) const {
		return !(*this == other);
	}

	uint GetHash() const {
		return (*(uint*)&x) ^ ((*(uint*)&y) << 14) ^ ((*(uint*)&z) << 23) ^ ((*(uint*)&w) << 31);
	}
};

struct Vertex {
	Vec3 position;
	Vec3 normal;
	Vec2 uv;
	Vec3 tangent;
	Vec3 bitangent;

	bool operator==(const Vertex& other) const {
		return position == other.position && normal == other.normal && tangent == other.tangent && bitangent == other.bitangent;
	}
};

template<>
struct std::hash<Vertex> {
	const size_t operator()(const Vertex& key) const {
		return key.position.GetHash() ^ key.normal.GetHash() ^ key.uv.GetHash() ^ key.bitangent.GetHash() ^ key.tangent.GetHash();
	}
};

static std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters) {
	size_t start = 0;
	size_t end = string.find_first_of(delimiters);

	std::vector<std::string> result;

	while (end <= std::string::npos) {
		result.emplace_back(string.substr(start, end - start));

		if (end == std::string::npos) {
			break;
		}

		start = end + 1;
		end = string.find_first_of(delimiters, start);
	}

	return result;
}