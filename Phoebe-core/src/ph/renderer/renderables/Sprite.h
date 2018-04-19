#pragma once

#include "Renderable2D.h"

namespace ph { namespace renderer {

	class Sprite : public Renderable2D {
	public:
		Sprite(float x, float y, float width, float height, uint color);
		Sprite(float x, float y, float width, float height, Texture2D* texture);
	};

}}

