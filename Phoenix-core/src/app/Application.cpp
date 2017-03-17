#include "Application.h"

namespace ph {
	Application::Application(const std::string& title, uint width, uint height)
		: m_Title(title), m_Width(width), m_Height(height) {
		m_Window = new Window(m_Title.c_str(), m_Width, m_Height);
	}

	Application::~Application() { }

	void Application::Start() {	}

	void Application::Stop() { }

	void Application::Pause() {	}

	void Application::Resume() { }
}