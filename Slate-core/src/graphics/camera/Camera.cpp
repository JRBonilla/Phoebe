#include "Camera.h"

namespace sl { namespace graphics {

	Camera::Camera(const mat4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix) {
		m_ViewMatrix = mat4::identity();
		m_Position = vec3();
		m_Rotation = vec3();
	}

}}