#pragma once

#include <GLFW\glfw3.h>
#include "Camera.h"
#include "ph/app/InputManager.h"

namespace ph { namespace renderer {

	class EditorCamera : public Camera {
	private:
		bool        m_Panning;
		bool        m_Rotating;

		math::Vec2  m_InitialMousePosition;
		math::Vec3  m_InitialFocalPoint;
		math::Vec3  m_InitialRotation;

		int         m_ZoomAmount;
		int         m_LastScrollY;

		float       m_Distance;
		float       m_PanSpeed;
		float       m_RotationSpeed;
		float       m_ZoomSpeed;
		float       m_Pitch;
		float       m_Yaw;
	public:
		EditorCamera(const math::Mat4& projectionMatrix);

		void Focus()  override;
		void Update() override;

		inline float GetDistance() const { return m_Distance; }
		inline void  SetDistance(float distance) { m_Distance = distance; }

		math::Vec3 GetForwardDirection() const override;
		math::Vec3 GetUpDirection()      const override;
		math::Vec3 GetRightDirection()   const override;
		
		math::Vec3 CalculatePosition() const;
		math::Quat GetOrientation()    const;
	private:
		void MousePan(const math::Vec2& delta);
		void MouseRotate(const math::Vec2& delta);
		void MouseZoom(float delta);
	};

}}