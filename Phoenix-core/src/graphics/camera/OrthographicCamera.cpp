#include "OrthographicCamera.h"

namespace ph { namespace graphics {

	OrthographicCamera::OrthographicCamera(const Mat4& projectionMatrix)
		: Camera(projectionMatrix) { }

	OrthographicCamera::~OrthographicCamera() { }
	
	void OrthographicCamera::Focus() { }

	void OrthographicCamera::Update()
	{
		Mat4 rotation = Mat4::Rotate(0.0f, m_Rotation);
		Mat4 translation = Mat4::Translate(m_Position);
		m_ViewMatrix = rotation * translation;
	}

}}