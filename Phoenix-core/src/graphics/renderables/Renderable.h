#pragma once

#include "../../math/PhoenixMath.h"
#include "../Renderer.h"
#include "../Texture.h"

namespace ph { namespace graphics {

	struct VertexData {
		Vec3 vertex;
		Vec2 uv;
		float tid;
		unsigned int color;
	};

	class Renderable {
	protected:
		Vec3				m_Position;
		Vec2				m_Size;
		std::vector<Vec2>	m_UV;
		uint				m_Color;
		Texture*			m_Texture;
	protected:
		Renderable();
	public:
		Renderable(const Vec3& position, const Vec2& size, uint color);
		virtual ~Renderable();

		virtual void Render(Renderer* renderer) const;

		static const std::vector<Vec2>& GetDefaultUVs();

		inline const Vec3 GetPosition() const { return m_Position; }
		inline const Vec2 GetSize() const { return m_Size; }
		inline const std::vector<Vec2>& GetUVs() const { return m_UV; }
		inline unsigned int GetColor() const { return m_Color; }
		inline Texture* GetTexture() const { return m_Texture == nullptr ? 0 : m_Texture; }
	};

}}
