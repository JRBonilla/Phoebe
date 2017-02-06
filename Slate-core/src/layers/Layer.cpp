#include "Layer.h"
#include <GLFW/glfw3.h>

namespace sl { namespace graphics {

	Layer::Layer(Renderer* renderer, Shader* shader, const math::mat4& projectionMatrix, bool visible)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix), m_Visible(visible) {
		m_Shader->Enable();
		m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->Disable();
		m_Camera = new OrthographicCamera(m_ProjectionMatrix);
	}

	Layer::~Layer() {
		delete m_Renderer;
		for (uint i = 0; i < m_Objects.size(); i++) {
			delete m_Objects[i];
		}
		m_Shader->Disable();
	}

	void Layer::Add(RenderObject* object) {
		m_Objects.push_back(object);
	}

	void Layer::Init() { }

	void Layer::Update() {
		m_Camera->Update();
	}
	
	void Layer::Render() {
		m_Shader->Enable();

		m_Renderer->PushMatrix(m_Camera->GetViewMatrix());
		m_Renderer->Begin();
		for (const RenderObject* object : m_Objects) {
			object->Render(m_Renderer);
		}
		m_Renderer->End();
		m_Renderer->PopMatrix();

		m_Renderer->Flush();
	}

}}
