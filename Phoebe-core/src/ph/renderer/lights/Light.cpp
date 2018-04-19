#include "Light.h"

namespace ph { namespace renderer {

	Light::Light(const math::Vec4& color, float intensity, const Light::Type& type)
		: m_Color(color), m_Intensity(intensity), m_Type(type), m_Active(true) {
	}

	DirectionalLight::DirectionalLight(const math::Vec3& direction, const math::Vec4& color)
		: m_Direction(direction), Light(color, 1.0f, Light::Type::DIRECTIONAL_LIGHT) {
	}

	PointLight::PointLight(const math::Vec3& position, const math::Vec4& color, float intensity)
		: m_Position(position), Light(color, intensity, Light::Type::POINT_LIGHT) {
	}

	SpotLight::SpotLight(const math::Vec3& position, const math::Vec3& direction, const math::Vec4& color,
		float cutOff, float outerCutOff, float intensity)
		: m_Position(position), m_Direction(direction), m_CutOff(cutOff), m_OuterCutOff(outerCutOff),
		Light(color, intensity, Light::Type::SPOT_LIGHT) {
	}

}}