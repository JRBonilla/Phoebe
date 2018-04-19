#pragma once

#include "Camera.h"

namespace ph { namespace renderer {

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(const math::Mat4& projectionMatrix);
		~OrthographicCamera();

		void Focus()  override;
		void Update() override;
	};

}}