#include "Camera.h"

namespace ph { namespace graphics {

	Camera::Camera(const Mat4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix) {
		m_ViewMatrix = Mat4::Identity();
		m_Position = Vec3();
		m_Rotation = Vec3();
	}

}}