#include "Framebuffer.h"

namespace ph { namespace renderer {

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
		m_Texture = new Texture2D(m_Width, m_Height, false, parameters);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);

		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->GetID(), 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Framebuffer::Unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Clear() const {
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}}