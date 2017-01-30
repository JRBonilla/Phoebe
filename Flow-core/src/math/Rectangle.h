#pragma once

#include "vec2.h"

namespace fl { namespace math {

	struct Rectangle {
		union {
			vec2 position;
			struct {
				float x;
				float y;
			};
		};
		union {
			vec2 size;
			struct {
				float width;
				float height;
			};
		};

		Rectangle();
		Rectangle(const vec2& position, const vec2& size);
		Rectangle(float x, float y, float width, float height);

		bool intersects(const Rectangle& other) const;
		bool contains(const vec2& point) const;

		inline vec2 minimum() const { return position; }
		inline vec2 maximum() const { return position + size; }
		inline vec2 center() const { return (minimum() + maximum()) * 0.5f; }

		bool operator==(const Rectangle& other) const;
		bool operator!=(const Rectangle& other) const;

		bool operator<(const Rectangle& other) const;
		bool operator>(const Rectangle& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Rectangle& rectangle);
	};

}}
