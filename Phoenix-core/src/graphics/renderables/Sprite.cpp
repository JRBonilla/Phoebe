#include "Sprite.h"

namespace ph { namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, uint color)
		: Renderable(math::Vec3(x, y, 0), math::Vec2(width, height), color) { }
	
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable(math::Vec3(x, y, 0), math::Vec2(width, height), 0xffffffff) {
		m_Texture = texture;
	}

}}