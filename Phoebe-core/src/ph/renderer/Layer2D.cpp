#include "Layer2D.h"

namespace ph { namespace renderer {

	Layer2D::Layer2D(Shader* shader, const math::Mat4& projectionMatrix, bool visible)
		: m_Renderer(new Renderer2D()), m_Shader(shader), m_ProjectionMatrix(projectionMatrix), m_Visible(visible), m_Initialized(false) {
		m_Shader->Bind();
		m_Shader->SetUniform("sys_ProjectionMatrix", (byte*)&m_ProjectionMatrix);
		m_Shader->Unbind();
		m_Camera = new OrthographicCamera(m_ProjectionMatrix);
	}

	Layer2D::~Layer2D() {
		delete m_Renderer;
		for (uint i = 0; i < m_Renderables.size(); i++) {
			delete m_Renderables[i];
		}
		m_Renderables.clear();
		m_Shader->Unbind();
	}

	void Layer2D::Add(Renderable2D* renderable) {
		m_Renderables.push_back(renderable);
	}

	void Layer2D::Init() {
		m_Initialized = true;
	}

	void Layer2D::Update() {
		m_Camera->Update();
	}
	
	void Layer2D::Render() {
		m_Shader->Bind();

		m_Renderer->PushMatrix(m_Camera->GetViewMatrix());
		m_Renderer->Begin();
		for (const Renderable2D* renderable : m_Renderables) {
			renderable->Submit(m_Renderer);
		}
		m_Renderer->End();
		m_Renderer->PopMatrix();

		m_Renderer->Present();
	}

}}
