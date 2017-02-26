#include "Framebuffer.h"

namespace ph { namespace graphics {

	Framebuffer::Framebuffer(uint width, uint height)
		: m_Width(width), m_Height(height) {
		Init();
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &m_FramebufferID);
	}

	void Framebuffer::Init() {
		glGenFramebuffers(1, &m_FramebufferID);
		glGenRenderbuffers(1, &m_RenderbufferID);

		TextureParameters parameters = { TextureFormat::RGBA, TextureFilter::LINEAR, TextureWrap::CLAMP_TO_BORDER };
		m_Texture = new Texture(m_Width, m_Height, false, parameters);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);
	}

	void Framebuffer::Bind() const {
	}

	void Framebuffer::Unbind() const {
	}

	void Framebuffer::Clear() const {
	}

}}