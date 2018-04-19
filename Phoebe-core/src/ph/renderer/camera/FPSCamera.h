#pragma once

#include "Camera.h"

namespace ph { namespace renderer {

	class FPSCamera : public Camera {
	private:
		float  m_VerticalSensitivity;
		float  m_HorizontalSensitivity;
		float  m_Speed;
		float  m_SprintSpeed;
		float  m_Pitch;
		float  m_Yaw;
		bool   m_MouseWasGrabbed;
	public:
		FPSCamera(const math::Mat4& projectionMatrix);
		~FPSCamera();

		void Focus()  override;
		void Update() override;

		math::Vec3 GetForwardDirection() const override;
		math::Vec3 GetUpDirection()      const override;
		math::Vec3 GetRightDirection()   const override;
	private:
		math::Quat GetOrientation() const;
		math::Vec3 GetForwardDirection(const math::Quat& orientation) const;
		math::Vec3 GetUpDirection(const math::Quat& orientation)      const;
		math::Vec3 GetRightDirection(const math::Quat& orientation)   const;
	};

}}