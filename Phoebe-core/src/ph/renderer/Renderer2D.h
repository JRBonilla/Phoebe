#pragma once

#include <vector>
#include "Texture2D.h"
#include "fonts/Font.h"
#include "objects/IndexBuffer.h"
#include "objects/VertexArray.h"
#include "shaders/Shader.h"
#include "ph/math/Math.h"

namespace ph { namespace renderer {

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES   32 - 1

	class Renderable2D;
	struct VertexData;

	class Renderer2D {
	private:
		const math::Mat4*        m_TransformationBack;
		std::vector<math::Mat4>  m_TransformationStack;
		int                      m_IndexCount;
		IndexBuffer*             m_IndexBuffer;
		VertexData*              m_Buffer;
		VertexArray*             m_VertexArray;
		VertexBuffer*            m_VertexBuffer;
		std::vector<Texture2D*>  m_Textures;
	public:
		Renderer2D();
		~Renderer2D();

		void PushMatrix(const math::Mat4& matrix, bool override = false);
		void PopMatrix();

		void Begin();
		void Submit(const Renderable2D* renderable);
		void Present();
		void End();
		
		void DrawString(const char* text, const math::Vec3& position, const Font& font, const uint& color = 0xffffffff);
		void DrawString(const std::string& text, const math::Vec3& position, const Font& font, const uint& color = 0xffffffff);

		void DrawLine(float x0, float y0, float x1, float y1, uint color, float thickness = 0.1f);
		void DrawLine(const math::Vec2& start, const math::Vec2& end, uint color, float thickness = 0.1f);
		
		void DrawRectangle(float x, float y, float width, float height, uint color = 0xffffffff);
		void DrawRectangle(const math::Vec2& position, const math::Vec2& size, uint color = 0xffffffff);
		void DrawRectangle(const math::Rectangle& rectangle, uint color = 0xffffffff);

		void FillRectangle(float x, float y, float width, float height, uint color = 0xffffffff);
		void FillRectangle(const math::Vec2& position, const math::Vec2& size, uint color = 0xffffffff);
		void FillRectangle(const math::Rectangle& rectangle, uint color = 0xffffffff);
	private:
		void Init();
		float SubmitTexture(Texture2D* texture);
	};

}}
