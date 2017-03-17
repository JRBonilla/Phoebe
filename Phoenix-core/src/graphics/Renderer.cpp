#include "Renderer.h"
#include "renderables/Renderable.h"

namespace ph { namespace graphics {

	Renderer::Renderer() {
		Init();
	}

	Renderer::~Renderer() {
		delete m_IndexBuffer;
		delete m_VertexBuffer;
		delete m_VertexArray;
		m_TransformationStack.clear();
		m_Textures.clear();
	}

	void Renderer::Init() {
		m_TransformationStack.push_back(Mat4::Identity());
		m_TransformationBack = &m_TransformationStack.back();

		m_VertexArray = new VertexArray();
		m_VertexBuffer = new VertexBuffer(BufferUsage::DYNAMIC);

		m_VertexArray->Bind();
		m_VertexBuffer->Bind();
		m_VertexBuffer->SetData(RENDERER_BUFFER_SIZE, nullptr);

		BufferLayout layout;
		
		layout.Push(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)0);
		layout.Push(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, uv)));
		layout.Push(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, tid)));
		layout.Push(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, color)));
		
		m_VertexBuffer->SetLayout(layout);
		m_VertexBuffer->Unbind();

		GLushort indices[RENDERER_INDICES_SIZE];
		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IndexBuffer = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
		m_Buffer = nullptr;
		m_IndexCount = 0;
		m_VertexArray->Unbind();
	}

	void Renderer::PushMatrix(const Mat4& matrix, bool override) {
		if (override) {
			m_TransformationStack.push_back(matrix);
		}
		else {
			m_TransformationStack.push_back(matrix * m_TransformationStack.back());
		}
		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer::PopMatrix() {
		if (m_TransformationStack.size() > 1) {
			m_TransformationStack.pop_back();
		}
		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer::Begin() {
		m_VertexBuffer->Bind();
		m_Buffer = (VertexData*)m_VertexBuffer->GetPointer();
	}

	float Renderer::GetTextureSlot(Texture* texture) {
		float result = 0.0f;
		bool found = false;
		for (uint i = 0; i < m_Textures.size(); i++) {
			if (m_Textures[i] == texture) {
				result = (float)i + 1;
				found = true;
				break;
			}
		}
		if (!found) {
			if (m_Textures.size() >= RENDERER_MAX_TEXTURES) {
				End();
				Flush();
				Begin();
			}
			m_Textures.push_back(texture);
			result = (float)m_Textures.size();
		}

		return result;
	}


	// Pushes a renderable to the renderer's buffer
	void Renderer::PushRenderable(const Renderable* renderable) {
		// Renderable's vertex data
		const Vec2& size			= renderable->GetSize();
		const std::vector<Vec2>& uv = renderable->GetUVs();
		const Vec3& position		= renderable->GetPosition();
		const unsigned int color	= renderable->GetColor();
		Texture* texture			= renderable->GetTexture();

		// Find an available texture slot for the renderable's texture
		float textureSlot = 0.0f;
		if (texture != nullptr) {
			textureSlot = GetTextureSlot(texture);
		}

		// Push renderable data to the buffer
		m_Buffer->vertex = *m_TransformationBack * position;
		m_Buffer->uv = uv[0];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(position.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[1];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[2];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(position.x + size.x, position.y, position.z);
		m_Buffer->uv = uv[3];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Renderer::DrawString(const char* text, const Vec3& position, const Font& font, const uint& color) {
		float x					= position.x;
		float y					= position.y;
		float textureSlot		= GetTextureSlot(font.GetTexture());
		const Vec2& scale		= font.GetScale();
		FTTextureAtlas* atlas	= font.GetTextureAtlas();

		for (const char* p = text; *p; p++) {
			float x0 = x  + atlas->characters[*p].left   / scale.x;
			float y0 = y  + atlas->characters[*p].top    / scale.y;
			float x1 = x0 + atlas->characters[*p].width  / scale.x;
			float y1 = y0 - atlas->characters[*p].height / scale.y;

			float u0 = atlas->characters[*p].offset_x;
			float v0 = atlas->characters[*p].offset_y;
			float u1 = u0 + atlas->characters[*p].width / atlas->width;
			float v1 = v0 + atlas->characters[*p].height / atlas->height;

			// Push the font data to the buffer
			m_Buffer->vertex = *m_TransformationBack * Vec3(x0, y0, 0.0f);
			m_Buffer->uv = Vec2(u0, v0);							 
			m_Buffer->tid = textureSlot;							 
			m_Buffer->color = color;								 
			m_Buffer++;												 
																	 
			m_Buffer->vertex = *m_TransformationBack * Vec3(x0, y1, 0.0f);
			m_Buffer->uv = Vec2(u0, v1);							 
			m_Buffer->tid = textureSlot;							 
			m_Buffer->color = color;								 
			m_Buffer++;												 
																	 
			m_Buffer->vertex = *m_TransformationBack * Vec3(x1, y1, 0.0f);
			m_Buffer->uv = Vec2(u1, v1);							 
			m_Buffer->tid = textureSlot;							 
			m_Buffer->color = color;								 
			m_Buffer++;												 
																	 
			m_Buffer->vertex = *m_TransformationBack * Vec3(x1, y0, 0.0f);
			m_Buffer->uv = Vec2(u1, v0);
			m_Buffer->tid = textureSlot;
			m_Buffer->color = color;
			m_Buffer++;

			// Increment the number of indices
			m_IndexCount += 6;

			x += atlas->characters[*p].advance_x / scale.x;
			y += atlas->characters[*p].advance_y / scale.y;
		}
	}

	void Renderer::DrawString(const std::string& text, const Vec3& position, const Font& font, const uint& color) {
		DrawString(text.c_str(), position, font, color);
	}

	void Renderer::DrawLine(float x0, float y0, float x1, float y1, uint color, float thickness) {
		const std::vector<Vec2>& uv = Renderable::GetDefaultUVs();
		float textureSlot = 0.0f;

		Vec2 normal = Vec2(y1 - y0, -(x1 - x0)).normalize() * thickness;

		m_Buffer->vertex = *m_TransformationBack * Vec3(x0 + normal.x, y0 + normal.y, 0.0f);
		m_Buffer->uv = uv[0];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(x1 + normal.x, y1 + normal.y, 0.0f);
		m_Buffer->uv = uv[1];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(x1 - normal.x, y1 - normal.y, 0.0f);
		m_Buffer->uv = uv[2];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(x0 - normal.x, y0 - normal.y, 0);
		m_Buffer->uv = uv[3];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Renderer::DrawLine(const Vec2& start, const Vec2& end, uint color, float thickness) {
		DrawLine(start.x, start.y, end.x, end.y, color, thickness);
	}
	
	void Renderer::DrawRectangle(float x, float y, float width, float height, uint color) {
		DrawLine(x, y, x + width, y, color);
		DrawLine(x + width, y, x + width, y + height, color);
		DrawLine(x + width, y + height, x, y + height, color);
		DrawLine(x, y + height, x, y, color);
	}

	void Renderer::DrawRectangle(const Vec2& position, const Vec2& size, uint color) {
		DrawRectangle(position.x, position.y, size.x, size.y, color);
	}

	void Renderer::DrawRectangle(const Rectangle& rectangle, uint color) {
		DrawRectangle(rectangle.minimum(), rectangle.size, color);
	}

	void Renderer::FillRectangle(float x, float y, float width, float height, uint color) {
		float textureSlot = 0.0f;
		Vec3 position(x, y, 0.0f);
		Vec2 size(width, height);
		const std::vector<Vec2>& uv = Renderable::GetDefaultUVs();

		m_Buffer->vertex = *m_TransformationBack * position;
		m_Buffer->uv = uv[0];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(position.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[1];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[2];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * Vec3(position.x + size.x, position.y, position.z);
		m_Buffer->uv = uv[3];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Renderer::FillRectangle(const Vec2& position, const Vec2& size, uint color) {
		FillRectangle(position.x, position.y, size.x, size.y, color);
	}

	void Renderer::FillRectangle(const Rectangle& rectangle, uint color) {
		FillRectangle(rectangle.minimum(), rectangle.size, color);
	}
	
	void Renderer::Flush() {
		for (uint i = 0; i < m_Textures.size(); i++) {
			m_Textures[i]->Bind(i);
		}
		m_VertexArray->Bind();
		m_IndexBuffer->Bind();

		m_VertexArray->Draw(m_IndexCount);
		
		m_IndexBuffer->Unbind();
		m_VertexArray->Unbind();
		for (uint i = 0; i < m_Textures.size(); i++) {
			m_Textures[i]->Bind(0);
		}

		m_IndexCount = 0;
		m_Textures.clear();
	}

	void Renderer::End() {
		m_VertexBuffer->ReleasePointer();
		m_Buffer = nullptr;
		m_VertexBuffer->Unbind();
	}
	
}}