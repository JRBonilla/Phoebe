#include "Rectangle.h"

namespace ph { namespace math {

	Rectangle::Rectangle() : position(Vec2()), size(Vec2()) { }

	Rectangle::Rectangle(const Vec2& position, const Vec2& size) : position(position), size(size) { }

	Rectangle::Rectangle(float x, float y, float width, float height) : position(Vec2(x, y)), size(Vec2(width, height)) { }

	bool Rectangle::intersects(const Rectangle& other) const {
		return (maximum() > other.position && position < other.maximum()) || (position > other.maximum() && maximum() < other.position);
	}

	bool Rectangle::contains(const Vec2& point) const {
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
		stream << "Rectangle: position(" << rectangle.position << "), size(" << rectangle.size << ")";
		return stream;
	}
}}