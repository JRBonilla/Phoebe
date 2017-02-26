#pragma once

#include "Renderable.h"

namespace ph { namespace graphics {

	class Sprite : public Renderable {
	public:
		Sprite(float x, float y, float width, float height, uint color);
		Sprite(float x, float y, float width, float height, Texture* texture);
	};

}}

