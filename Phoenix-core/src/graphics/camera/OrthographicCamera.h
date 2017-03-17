#pragma once

#include "Camera.h"

namespace ph { namespace graphics {

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(const Mat4& projectionMatrix);
		~OrthographicCamera();

		void Focus() override;
		void Update() override;
	};

}}