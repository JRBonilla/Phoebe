#pragma once

#include <glad/glad.h>
#include "../../common/Types.h"
#include "../Texture.h"

namespace ph { namespace graphics {

	class Framebuffer {
	private:
		uint	 m_FramebufferID;
		uint	 m_RenderbufferID;
		uint	 m_Width, m_Height;
		Texture* m_Texture;
	public:
		Framebuffer(uint width, uint height);
		~Framebuffer();

		void Bind() const;
		void Unbind() const;
		void Clear() const;

		inline const uint GetWidth() const { return m_Width; }
		inline const uint GetHeight() const { return m_Height; }

		inline Texture* GetTexture() const { return m_Texture; }
	private:
		void Init();
	};

}}