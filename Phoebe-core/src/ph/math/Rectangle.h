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

		bool Intersects(const Rectangle& other) const;
		bool Contains(const Vec2& point) const;

		inline Vec2 Minimum() const { return position; }
		inline Vec2 Maximum() const { return position + size; }
		inline Vec2 Center() const { return (Minimum() + Maximum()) * 0.5f; }

		bool operator==(const Rectangle& other) const;
		bool operator!=(const Rectangle& other) const;

		bool operator<(const Rectangle& other) const;
		bool operator>(const Rectangle& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Rectangle& rectangle);
	};

}}
