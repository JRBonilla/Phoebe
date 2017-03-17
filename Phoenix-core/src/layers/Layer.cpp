#include "Layer.h"
#include <GLFW/glfw3.h>

namespace ph { namespace graphics {

	Layer::Layer(Renderer* renderer, Shader* shader, const math::Mat4& projectionMatrix, bool visible)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix), m_Visible(visible) {
		m_Shader->Enable();
		m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->Disable();
		m_Camera = new OrthographicCamera(m_ProjectionMatrix);
	}

	Layer::~Layer() {
		delete m_Renderer;
		for (uint i = 0; i < m_Renderables.size(); i++) {
			delete m_Renderables[i];
		}
		m_Shader->Disable();
	}

	void Layer::Add(Renderable* renderable) {
		m_Renderables.push_back(renderable);
	}

	void Layer::Init() { }

	void Layer::Update() {
		m_Camera->Update();
	}
	
	void Layer::Render() {
		m_Shader->Enable();

		m_Renderer->PushMatrix(m_Camera->GetViewMatrix());
		m_Renderer->Begin();
		for (const Renderable* renderable : m_Renderables) {
			renderable->Render(m_Renderer);
		}
		m_Renderer->End();
		m_Renderer->PopMatrix();

		m_Renderer->Flush();
	}

}}
