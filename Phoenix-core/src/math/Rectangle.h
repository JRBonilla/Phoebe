#pragma once

#include "Vec2.h"

namespace ph { namespace math {

	struct Rectangle {
		union {
			Vec2 position;
			struct {
				float x;
				float y;
			};
		};

		union {
			Vec2 size;
			struct {
				float width;
				float height;
			};
		};

		Rectangle();
		Rectangle(const Vec2& position, const Vec2& size);
		Rectangle(float x, float y, float width, float height);

		bool intersects(const Rectangle& other) const;
		bool contains(const Vec2& point) const;

		inline Vec2 minimum() const { return position; }
		inline Vec2 maximum() const { return position + size; }
		inline Vec2 center() const { return (minimum() + maximum()) * 0.5f; }

		bool operator==(const Rectangle& other) const;
		bool operator!=(const Rectangle& other) const;

		bool operator<(const Rectangle& other) const;
		bool operator>(const Rectangle& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Rectangle& rectangle);
	};

}}
