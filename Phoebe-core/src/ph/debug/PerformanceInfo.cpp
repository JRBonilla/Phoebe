#include "PerformanceInfo.h"
#include "ph/app/Application.h"

namespace ph { namespace debug {

	using namespace math;
	using namespace renderer;

	PerformanceInfo::PerformanceInfo()
		: Layer2D(ShaderManager::Get("Font"), Mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) {
	}

	PerformanceInfo::~PerformanceInfo() {
	}

	void PerformanceInfo::Init() {
		Layer2D::Init();

		m_FPSLabel = new Label("", 14.5f, 8.3f, FontManager::Get("Default"), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		this->Add(m_FPSLabel);

		m_UPSLabel = new Label("", 14.5f, 7.8f, FontManager::Get("Default"), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		this->Add(m_UPSLabel);

		m_FrameTimeLabel = new Label("", 13.0f, 7.3f, FontManager::Get("Default"), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		this->Add(m_FrameTimeLabel);
	}

	void PerformanceInfo::Update() {
		m_FPSLabel->SetText(std::to_string(Application::GetApplication().GetFPS()) + " FPS");
		m_UPSLabel->SetText(std::to_string(Application::GetApplication().GetUPS()) + " UPS");
		m_FrameTimeLabel->SetText(std::to_string(Application::GetApplication().GetFrameTime()).substr(0, 5) + " ms/frame");
	}

}}