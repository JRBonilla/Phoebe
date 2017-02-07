#include "OrthographicCamera.h"

namespace ph { namespace graphics {

	OrthographicCamera::OrthographicCamera(const mat4& projectionMatrix)
		: Camera(projectionMatrix) { }

	OrthographicCamera::~OrthographicCamera() { }
	
	void OrthographicCamera::Focus() { }

	void OrthographicCamera::Update()
	{
		mat4 rotation = mat4::rotate(0.0f, m_Rotation);
		mat4 translation = mat4::translate(m_Position);
		m_ViewMatrix = rotation * translation;
	}

}}