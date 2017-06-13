#pragma once

#include <vector>
#include <glad/glad.h>
#include "Texture.h"
#include "fonts/Font.h"
#include "../math/Math.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexArray.h"
#include "shaders/Shader.h"

namespace ph { namespace graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32 - 1

	// Forward declarations to avoid recursive inclusions
	class Renderable;
	struct VertexData;

	using namespace math;

	class Renderer
	{
	private:
		GLsizei					m_IndexCount;
		const Mat4*				m_TransformationBack;
		std::vector<Mat4>		m_TransformationStack;
		IndexBuffer*			m_IndexBuffer;
		VertexData*				m_Buffer;
		VertexArray*			m_VertexArray;
		VertexBuffer*			m_VertexBuffer;
		std::vector<Texture*>	m_Textures;
	public:
		Renderer();
		~Renderer();

		void PushMatrix(const Mat4& matrix, bool override = false);
		void PopMatrix();

		void Begin();
		void Flush();
		void End();

		float GetTextureSlot(Texture* texture);

		void PushRenderable(const Renderable* renderable);

		void DrawString(const char* text, const Vec3& position, const Font& font, const uint& color = 0xffffffff);
		void DrawString(const std::string& text, const Vec3& position, const Font& font, const uint& color = 0xffffffff);

		void DrawLine(float x0, float y0, float x1, float y1, uint color, float thickness = 0.1f);
		void DrawLine(const Vec2& start, const Vec2& end, uint color, float thickness = 0.1f);
		
		void DrawRectangle(float x, float y, float width, float height, uint color = 0xffffffff);
		void DrawRectangle(const Vec2& position, const Vec2& size, uint color = 0xffffffff);
		void DrawRectangle(const Rectangle& rectangle, uint color = 0xffffffff);

		void FillRectangle(float x, float y, float width, float height, uint color = 0xffffffff);
		void FillRectangle(const Vec2& position, const Vec2& size, uint color = 0xffffffff);
		void FillRectangle(const Rectangle& rectangle, uint color = 0xffffffff);
	private:
		void Init();
	};

}}
