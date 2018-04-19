#pragma once

#include "ph/math/Vec3.h"
#include "ph/math/Vec4.h"

namespace ph { namespace renderer {

#define POINT_LIGHT_SIZE          (sizeof(Vec3) + sizeof(Vec4) + sizeof(float))
#define SPOT_LIGHT_SIZE           ((sizeof(Vec3) * 2) + sizeof(Vec4) + (sizeof(float) * 3))
#define DIRECTIONAL_LIGHT_SIZE    (sizeof(Vec3) + sizeof(Vec4))

	enum DirectionalLightIndices {
		DirectionalLightIndex_Direction = 0,
		DirectionalLightIndex_Color     = 1,
		DirectionalLightIndex_Size
	};

	enum PointLightIndices {
		PointLightIndex_Position  = 0,
		PointLightIndex_Color     = 1,
		PointLightIndex_Intensity = 2,
		PointLightIndex_Size
	};

	enum SpotLightIndices {
		SpotLightIndex_Position    = 0,
		SpotLightIndex_Direction   = 1,
		SpotLightIndex_Color       = 2,
		SpotLightIndex_CutOff      = 3,
		SpotLightIndex_OuterCutOff = 4,
		SpotLightIndex_Intensity   = 5,
		SpotLightIndex_Size
	};

	class Light {
	public:
		enum class Type {
			NONE, DIRECTIONAL_LIGHT, POINT_LIGHT, SPOT_LIGHT
		};
	protected:
		bool        m_Active;
		Type        m_Type;
		math::Vec4  m_Color;
		float       m_Intensity;
	public:
		Light(const math::Vec4& color, float intensity, const Light::Type& type = Light::Type::NONE);
		virtual ~Light() {}

		inline bool IsActive() const { return m_Active; }
		inline void SetActive(bool active) { m_Active = active; }

		inline const Light::Type& GetType()  const { return m_Type; }

		inline const math::Vec4& GetColor() const { return m_Color; }
		inline void SetColor(const math::Vec4& color) { m_Color = color; }

		inline const float GetIntensity() const { return m_Intensity; }
		inline void SetIntensity(float intensity) { m_Intensity = intensity; }
	};

	class DirectionalLight : public Light {
	private:
		math::Vec3 m_Direction;
	public:
		DirectionalLight(const math::Vec3& direction, const math::Vec4& color);

		inline const math::Vec3& GetDirection() const { return m_Direction; }
		inline void SetDirection(const math::Vec3& direction) { m_Direction = direction; }
	};

	class PointLight : public Light {
	private:
		math::Vec3 m_Position;
	public:
		PointLight(const math::Vec3& position, const math::Vec4& color, float intensity);

		inline const math::Vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const math::Vec3& position) { m_Position = position; }
	};

	class SpotLight : public Light {
	private:
		math::Vec3 m_Position;
		math::Vec3 m_Direction;

		float m_CutOff;
		float m_OuterCutOff;
	public:
		SpotLight(const math::Vec3& position, const math::Vec3& direction, const math::Vec4& color,
			float cutOff, float outerCutOff, float intensity);

		inline const math::Vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const math::Vec3& position) { m_Position = position; }

		inline const math::Vec3& GetDirection() const { return m_Direction; }
		inline void SetDirection(const math::Vec3& direction) { m_Direction = direction; }

		inline const float& GetCutOff()      const { return m_CutOff; }
		inline const float& GetOuterCutOff() const { return m_OuterCutOff; }
	};

}}