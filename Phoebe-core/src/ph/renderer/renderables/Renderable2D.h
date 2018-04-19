#pragma once

#include "../Renderer2D.h"
#include "../Texture2D.h"
#include "ph/math/Math.h"

namespace ph { namespace renderer {

	struct VertexData {
		math::Vec3   vertex;
		math::Vec2   uv;
		float        tid;
		unsigned int color;
	};

	class Renderable2D {
	protected:
		math::Vec3               m_Position;
		math::Vec2               m_Size;
		std::vector<math::Vec2>  m_UVs;
		uint                     m_Color;
		Texture2D*               m_Texture;
		math::Rectangle          m_Bounds;
		bool                     m_Visible;
	protected:
		Renderable2D();
	public:
		Renderable2D(const math::Vec3& position, const math::Vec2& size, uint color);
		virtual ~Renderable2D();

		virtual void Submit(Renderer2D* renderer) const;

		inline const math::Vec3 GetPosition() const { return m_Position; }
		inline const math::Vec2 GetSize() const { return m_Size; }
		inline const uint GetColor() const { return m_Color; }

		inline const math::Rectangle& GetBounds() const { return m_Bounds; }

		inline Texture2D* GetTexture() const { return m_Texture; }
		inline const std::vector<math::Vec2>& GetUVs() const { return m_UVs; }
		
		inline void SetVisibility(bool visible) { m_Visible = visible; }
		inline bool IsVisible() const { return m_Visible; }

		inline void SetPosition(const math::Vec3& position) { m_Position = position; }
		inline void SetSize(const math::Vec2& size) { m_Size = size; }
		inline void SetColor(uint color) { m_Color = color; }
		inline void SetTexture(Texture2D* texture) { m_Texture = texture; }
	public:
		static const std::vector<math::Vec2>& GetDefaultUVs();
	};

}}
