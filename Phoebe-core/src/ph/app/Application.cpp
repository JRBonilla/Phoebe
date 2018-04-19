#include "Application.h"

namespace ph {

	using namespace debug;
	using namespace renderer;

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, const WindowProperties& properties)
		: m_Name(name), m_Properties(properties) {
		s_Instance = this;
	}

	Application::~Application() {
		for (uint i = 0; i < m_SceneStack.size(); i++) {
			delete m_SceneStack[i];
		}
		m_SceneStack.clear();
		for (uint i = 0; i < m_LayerStack.size(); i++) {
			delete m_LayerStack[i];
		}
		m_LayerStack.clear();
		delete m_PerformanceInfo;
		delete m_Window;
	}

	void Application::Init() {
		m_Window = new Window(m_Name.c_str(), m_Properties);
		DebugMenu::Init();
		m_PerformanceInfo = new PerformanceInfo();
		m_PerformanceInfo->Init();
	}

	void Application::PushScene(Scene* scene) {
		if (!scene->IsInitialized()) scene->Init();
		m_SceneStack.push_back(scene);
	}

	Scene* Application::PopScene() {
		Scene* scene = m_SceneStack.back();
		m_SceneStack.pop_back();
		return scene;
	}

	void Application::PushLayer(Layer2D* layer) {
		if (!layer->IsInitialized()) layer->Init();
		m_LayerStack.push_back(layer);
	}

	Layer2D* Application::PopLayer() {
		Layer2D* layer = m_LayerStack.back();
		m_LayerStack.pop_back();
		return layer;
	}

	void Application::Start() {
		Init();
		m_Running = true;
		m_Suspended = false;
		Run();
	}

	void Application::Suspend() {
		m_Suspended = true;
	}

	void Application::Resume() {
		m_Suspended = false;
	}

	void Application::Stop() {
		m_Running = false;
	}

	void Application::Update() {
		DebugMenu::Update();
		m_PerformanceInfo->Update();

		for (uint i = 0; i < m_SceneStack.size(); i++) {
			m_SceneStack[i]->Update();
		}

		for (uint i = 0; i < m_LayerStack.size(); i++) {
			m_LayerStack[i]->Update();
		}
	}

	void Application::Render() {
		for (uint i = 0; i < m_SceneStack.size(); i++) {
			if (m_SceneStack[i]->IsVisible()) {
				m_SceneStack[i]->Render();
			}
		}

		for (uint i = 0; i < m_LayerStack.size(); i++) {
			if (m_LayerStack[i]->IsVisible()) {
				m_LayerStack[i]->Render();
			}
		}

		if (m_PerformanceInfo->IsVisible()) {
			m_PerformanceInfo->Render();
		}

		if (DebugMenu::IsVisible()) {
			DebugMenu::Render();
		}
	}

	void Application::Run() {
		m_Timer = new Timer();
		float timer = 0.0f;
		float updateTimer = m_Timer->ElapsedMillis();
		float updateTick  = 1000.0f / 60.0f;
		uint frames  = 0;
		uint updates = 0;
		Timestep timestep(m_Timer->ElapsedMillis());
		Timer frametime;
		float now = m_Timer->ElapsedMillis();

		while (m_Running) {
			m_Window->Update();

			now = m_Timer->ElapsedMillis();
			if (now - updateTimer > updateTick) {
				timestep.Update(now);
				Update();
				updates++;
				updateTimer += updateTick;
			}
			{
				frametime.Reset();
				m_Window->ClearBuffer();
				Render();
				m_Window->SwapBuffers();
				frames++;
				m_FrameTime = frametime.ElapsedMillis();
			}
			if (m_Timer->Elapsed() - timer > 1.0f) {
				timer += 1.0f;
				m_FramesPerSecond  = frames;
				m_UpdatesPerSecond = updates;
				frames  = 0;
				updates = 0;
			}
			
			if (m_Window->Closed()) {
				m_Running = false;
			}
		}
	}

}