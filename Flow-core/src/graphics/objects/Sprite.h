#pragma once

#include "RenderObject.h"

namespace fl { namespace graphics {

	class Sprite : public RenderObject
	{
	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);
	};

}}

