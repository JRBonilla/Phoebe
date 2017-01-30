#pragma once

#include "Camera.h"

namespace fl { namespace graphics {

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(const mat4& projectionMatrix);
		~OrthographicCamera();

		void Focus() override;
		void Update() override;
	};

}}