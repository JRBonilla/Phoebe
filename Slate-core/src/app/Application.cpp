#include "Application.h"

namespace sl {

	using namespace graphics;

	Application::Application(const std::string& name, const WindowProperties& properties)
		: m_Name(name), m_Properties(properties), m_Running(false), m_Suspended(false) {
		m_Window = new Window(m_Name.c_str(), m_Properties);
		m_DebugLayer = new debug::DebugLayer(m_Window->GetGLFWWindow());
	}

	Application::~Application() {
		delete m_Window;
		delete m_DebugLayer;
		for (uint i = 0; i < m_LayerStack.size(); i++) {
			m_LayerStack.erase(m_LayerStack.begin() + i);
			delete m_LayerStack[i];
		}
	}

	void Application::Init() {
		m_DebugLayer->Init();
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.push_back(layer);
		layer->Init();
	}

	Layer* Application::PopLayer() {
		Layer* layer = m_LayerStack.back();
		m_LayerStack.pop_back();
		return layer;
	}

	Layer* Application::PopLayer(Layer* layer) {
		for (uint i = 0; i < m_LayerStack.size(); i++) {
			if (m_LayerStack[i] == layer) {
				m_LayerStack.erase(m_LayerStack.begin() + i);
				break;
			}
		}
		return layer;
	}

	void Application::Update() {
		m_Window->Update();
		m_DebugLayer->Update();

		for (uint i = 0; i < m_LayerStack.size(); i++) {
			m_LayerStack[i]->Update();
		}
	}


	void Application::Render() {
		m_Window->ClearBuffer();
		for (uint i = 0; i < m_LayerStack.size(); i++) {
			if (m_LayerStack[i]->IsVisible()) {
				m_LayerStack[i]->Render();
			}
		}

		if (m_DebugLayer->IsVisible()) {
			m_DebugLayer->Render();
		}
	}

	void Application::Run() { }

	void Application::Start() {
		m_Running = true;
		Run();
	}

	void Application::Resume() { }

	void Application::Stop() { }

	void Application::Suspend() { }

}