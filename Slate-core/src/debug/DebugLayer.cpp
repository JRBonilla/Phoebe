#include "DebugLayer.h"

namespace sl { namespace debug {

	bool lights = true;

	DebugLayer::DebugLayer(GLFWwindow* window)
		: Layer(new Renderer(), new Shader("debug", "res/shaders/default/default.vert", "res/shaders/default/text.frag"), mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) { 
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::SetupImGuiStyle(true, 1.0f);
	}

	DebugLayer::~DebugLayer() {
		ImGui_ImplGlfwGL3_Shutdown();
	}

	void DebugLayer::Init() {
		m_FPSLabel = new Label("", -15.5f, 8.0f, FontManager::Get("default"), 0xffffff);
		m_FramesPerSecond = 0;
		m_CurrentTime = 0.0f;
		m_LastTime = Timer::GetInstance()->Elapsed();
		Add(m_FPSLabel);

		m_UPSLabel = new Label("", -15.5f, 7.0f, FontManager::Get("default"), 0xffffff);
		m_CurrentFrame = Timer::GetInstance()->Elapsed();
		m_LastFrame = m_CurrentFrame;
		Add(m_UPSLabel);
	}

	void DebugLayer::RenderDebugInterface() const {
		ImGui_ImplGlfwGL3_NewFrame(); {
		}
		ImGui::Render();
	}

	void DebugLayer::Update() {
		m_CurrentTime = Timer::GetInstance()->Elapsed();

		m_CurrentFrame = m_CurrentTime;
		m_DeltaTime = m_CurrentFrame - m_LastFrame;
		m_LastFrame = m_CurrentFrame;

		m_FramesPerSecond++;
		if (m_CurrentTime - m_LastTime >= 1.0f) {
			m_FPSLabel->SetText(std::to_string(m_FramesPerSecond) + " FPS");
			m_FramesPerSecond = 0;
			m_LastTime += 1.0f;
		}
		m_UPSLabel->SetText(std::to_string(m_DeltaTime) + " ms/frame");
	}

	void DebugLayer::Render() {
		Layer::Render();
		RenderDebugInterface();
	}

}}