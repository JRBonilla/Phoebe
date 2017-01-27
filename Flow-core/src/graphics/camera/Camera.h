#pragma once

#include "../../math/Math.h"

namespace fl { namespace graphics {

	using namespace math;

	class Camera
	{
	protected:
		mat4 m_ProjectionMatrix, m_ViewMatrix;
		vec3 m_Position, m_Rotation, m_FocalPoint;
	public:
		Camera(const mat4& projectionMatrix);

		virtual void Focus() {  }
		virtual void Update() {  }

		inline const vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const vec3& position) { m_Position = position; }

		inline const vec3& GetRotation() const { return m_Rotation; }
		inline void SetRotation(const vec3& rotation) { m_Rotation = rotation; }

		inline const mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline void SetProjectionMatrix(const mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

		inline void Translate(const vec3& translation) { m_Position += translation; }
		inline void Rotate(const vec3& rotation) { m_Rotation += rotation; }

		inline void Translate(float x, float y, float z) { m_Position += vec3(x, y, z); }
		inline void Rotate(float x, float y, float z) { m_Rotation += vec3(x, y, z); }

		inline const vec3& GetFocalPoint() const { return m_FocalPoint; }
		inline const mat4& GetViewMatrix() const { return m_ViewMatrix; }
	};

}}