#include "DebugInfoLayer.h"

namespace ph { namespace debug {

	bool lights = true;

	DebugInfoLayer::DebugInfoLayer()
		: Layer(new Renderer(), new Shader("debug", "res/shaders/default/default.vert", "res/shaders/default/text.frag"), Mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) { }

	DebugInfoLayer::~DebugInfoLayer() { }

	void DebugInfoLayer::Init() {
		m_FpsLabel = new Label("", -15.5f, 8.0f, FontManager::Get("default"), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		m_FramesPerSecond = 0;
		m_CurrentTime = 0.0f;
		m_LastTime = Timer::GetInstance()->Elapsed();
		Add(m_FpsLabel);

		m_DeltaTimeLabel = new Label("", -15.5f, 7.0f, FontManager::Get("default"), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		m_CurrentFrame = Timer::GetInstance()->Elapsed();
		m_LastFrame = m_CurrentFrame;
		Add(m_DeltaTimeLabel);
	}

	void DebugInfoLayer::Update() {
		m_CurrentTime = Timer::GetInstance()->Elapsed();

		m_CurrentFrame = m_CurrentTime;
		m_DeltaTime = m_CurrentFrame - m_LastFrame;
		m_LastFrame = m_CurrentFrame;

		m_FramesPerSecond++;
		if (m_CurrentTime - m_LastTime >= 1.0f) {
			m_FpsLabel->SetText(std::to_string(m_FramesPerSecond) + " FPS");
			m_FramesPerSecond = 0;
			m_LastTime += 1.0f;
		}
		m_DeltaTimeLabel->SetText(std::to_string(m_DeltaTime * 1000.0f) + " ms/frame");
	}

}}