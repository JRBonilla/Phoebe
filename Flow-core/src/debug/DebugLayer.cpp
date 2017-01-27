#include "DebugLayer.h"

namespace fl{ namespace debug {

	DebugLayer::DebugLayer(GLFWwindow* window)
		: Layer(new graphics::Renderer(), new graphics::Shader("res/shaders/default/default.vert", "res/shaders/default/text.frag"), math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) { 
		ImGui_ImplGlfwGL3_Init(window, false);
	}

	DebugLayer::~DebugLayer() {
		ImGui_ImplGlfwGL3_Shutdown();
	}

	void DebugLayer::Init() {
		m_FPSLabel = new graphics::Label("", -15.5, 8, graphics::FontManager::Get("Default"), 0xffffffff);
		m_FramesPerSecond = 0;
		m_CurrentTime = 0;
		m_LastTime = Timer::GetInstance()->elapsed();
		Add(m_FPSLabel);
	}

	void DebugLayer::RenderDebugInterface() const {
		ImGui_ImplGlfwGL3_NewFrame(); {
			ImGui::ShowTestWindow();
		}
		ImGui::Render();
	}

	void DebugLayer::Update() {
		m_CurrentTime = Timer::GetInstance()->elapsed();
		m_FramesPerSecond++;
		if (m_CurrentTime - m_LastTime >= 1.0f) {
			m_FPSLabel->SetText(std::to_string(m_FramesPerSecond) + " FPS");
			m_FramesPerSecond = 0;
			m_LastTime += 1.0f;
		}
	}

	void DebugLayer::Render() {
		RenderDebugInterface();
		Layer::Render();
	}

}}