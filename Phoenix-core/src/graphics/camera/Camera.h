#pragma once

#include "../../math/Math.h"

namespace ph { namespace graphics {

	using namespace math;

	class Camera {
	protected:
		Mat4 m_ProjectionMatrix, m_ViewMatrix;
		Vec3 m_Position, m_Rotation, m_FocalPoint;
	public:
		Camera(const Mat4& projectionMatrix);

		virtual void Focus() {  }
		virtual void Update() {  }

		inline const Vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const Vec3& position) { m_Position = position; }

		inline const Vec3& GetRotation() const { return m_Rotation; }
		inline void SetRotation(const Vec3& rotation) { m_Rotation = rotation; }

		inline const Mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline void SetProjectionMatrix(const Mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

		inline void Translate(const Vec3& translation) { m_Position += translation; }
		inline void Rotate(const Vec3& rotation) { m_Rotation += rotation; }

		inline void Translate(float x, float y, float z) { m_Position += Vec3(x, y, z); }
		inline void Rotate(float x, float y, float z) { m_Rotation += Vec3(x, y, z); }

		inline const Vec3& GetFocalPoint() const { return m_FocalPoint; }
		inline const Mat4& GetViewMatrix() const { return m_ViewMatrix; }
	};

}}