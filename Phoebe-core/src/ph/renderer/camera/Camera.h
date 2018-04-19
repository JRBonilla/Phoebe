#pragma once

#include "ph/math/Math.h"

namespace ph { namespace renderer {

	class Camera {
	protected:
		math::Mat4 m_ProjectionMatrix, m_ViewMatrix;
		math::Vec3 m_Position, m_Rotation, m_FocalPoint;
	public:
		Camera(const math::Mat4& projectionMatrix);

		virtual void Focus()  {  }
		virtual void Update() {  }

		virtual math::Vec3 GetForwardDirection() const { return math::Vec3(0.0f); }
		virtual math::Vec3 GetUpDirection()      const { return math::Vec3(0.0f); }
		virtual math::Vec3 GetRightDirection()   const { return math::Vec3(0.0f); }

		inline const math::Vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const math::Vec3& position) { m_Position = position; }

		inline const math::Vec3& GetRotation() const { return m_Rotation; }
		inline void SetRotation(const math::Vec3& rotation) { m_Rotation = rotation; }

		inline const math::Mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline void SetProjectionMatrix(const math::Mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

		inline void Translate(const math::Vec3& translation) { m_Position += translation; }
		inline void Rotate(const math::Vec3& rotation)       { m_Rotation += rotation; }

		inline void Translate(float x, float y, float z) { m_Position += math::Vec3(x, y, z); }
		inline void Rotate(float x, float y, float z)    { m_Rotation += math::Vec3(x, y, z); }

		inline const math::Vec3& GetFocalPoint() const { return m_FocalPoint; }

		inline const math::Mat4& GetViewMatrix() const { return m_ViewMatrix; }
	};

}}