#pragma once

#include <glad/glad.h>
#include "../Texture2D.h"
#include "ph/Types.h"
#include "ph/math/Vec4.h"
#include "ph/utils/Log.h"

namespace ph { namespace renderer {

	class Framebuffer {
	private:
		uint	    m_FramebufferID;
		uint	    m_RenderbufferID;
		uint	    m_Width;
		uint        m_Height;
		math::Vec4  m_ClearColor;
		Texture2D*  m_Texture;
	public:
		Framebuffer(uint width, uint height);
		~Framebuffer();

		void Bind() const;
		void Unbind() const;
		void Clear() const;

		inline const uint GetWidth() const { return m_Width; }
		inline const uint GetHeight() const { return m_Height; }

		inline Texture2D* GetTexture() const { return m_Texture; }
		inline void SetClearColor(const math::Vec4& color) { m_ClearColor = color; }
	private:
		void Init();
	};

}}