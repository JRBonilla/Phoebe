#include "Rectangle.h"

namespace fl { namespace math {

	Rectangle::Rectangle() : position(vec2()), size(vec2()) { }

	Rectangle::Rectangle(const vec2& position, const vec2& size) : position(position), size(size) { }

	Rectangle::Rectangle(float x, float y, float width, float height) : position(vec2(x, y)), size(vec2(width, height)) { }

	bool Rectangle::intersects(const Rectangle& other) const {
		return (maximum() > other.position && position < other.maximum()) || (position > other.maximum() && maximum() < other.position);
	}

	bool Rectangle::contains(const vec2& point) const {
		return (point > minimum()) && (point < maximum());
	}

	bool Rectangle::operator==(const Rectangle& other) const {
		return (position == other.position) && (size == other.size);
	}
	
	bool Rectangle::operator!=(const Rectangle& other) const {
		return !(*this == other);
	}

	bool Rectangle::operator<(const Rectangle& other) const {
		return size < other.size;
	}

	bool Rectangle::operator>(const Rectangle& other) const {
		return size > other.size;
	}

	std::ostream& operator<<(std::ostream& stream, const Rectangle& rectangle) {
		stream << "Rectangle: position(" << rectangle.position.x << ", " << rectangle.position.y << "), size(" << rectangle.size.x << ", " << rectangle.size.y << ")";
		return stream;
	}
}}