#pragma once

#include "../../math/PhoenixMath.h"
#include "../Renderer.h"
#include "../Texture.h"

namespace ph { namespace graphics {

	struct VertexData {
		vec3 vertex;
		vec2 uv;
		float tid;
		unsigned int color;
	};

	class Renderable {
	protected:
		vec3				m_Position;
		vec2				m_Size;
		std::vector<vec2>	m_UV;
		uint				m_Color;
		Texture*			m_Texture;
	protected:
		Renderable();
	public:
		Renderable(const vec3& position, const vec2& size, uint color);
		virtual ~Renderable();

		virtual void Render(Renderer* renderer) const;

		static const std::vector<vec2>& GetDefaultUVs();

		inline const vec3 GetPosition() const { return m_Position; }
		inline const vec2 GetSize() const { return m_Size; }
		inline const std::vector<vec2>& GetUVs() const { return m_UV; }
		inline unsigned int GetColor() const { return m_Color; }
		inline Texture* GetTexture() const { return m_Texture == nullptr ? 0 : m_Texture; }
	};

}}
