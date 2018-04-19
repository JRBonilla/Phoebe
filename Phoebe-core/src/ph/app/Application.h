#pragma once

#include "Settings.h"
#include "Window.h"
#include "ph/debug/DebugMenu.h"
#include "ph/debug/PerformanceInfo.h"
#include "ph/renderer/Scene.h"
#include "ph/utils/Timer.h"
#include "ph/utils/Timestep.h"

namespace ph {

	typedef std::vector<renderer::Scene*>   SceneStack;
	typedef std::vector<renderer::Layer2D*> LayerStack;

	class Application {
	private:
		static Application*      s_Instance;
	private:
		Window*                  m_Window;
		WindowProperties         m_Properties;
		Settings                 m_Settings;
		debug::PerformanceInfo*  m_PerformanceInfo;
		bool                     m_Running;
		bool                     m_Suspended;
		Timer*                   m_Timer;
		uint                     m_FramesPerSecond;
		uint                     m_UpdatesPerSecond;
		float                    m_FrameTime;
		std::string              m_Name;
		SceneStack               m_SceneStack;
		LayerStack               m_LayerStack;
	public:
		Application(const std::string& name, const WindowProperties& properties);
		virtual ~Application();

		virtual void Init();

		void PushScene(renderer::Scene* scene);
		renderer::Scene* PopScene();

		void PushLayer(renderer::Layer2D* layer);
		renderer::Layer2D* PopLayer();

		void Start();
		void Suspend();
		void Resume();
		void Stop();

		inline float GetFrameTime() const { return m_FrameTime; }
		inline uint  GetFPS()       const { return m_FramesPerSecond; }
		inline uint  GetUPS()       const { return m_UpdatesPerSecond; }

		inline Window* GetWindow() const { return m_Window; }
		inline uint GetWindowWidth()  const { return m_Window->GetWidth(); }
		inline uint GetWindowHeight() const { return m_Window->GetHeight(); }
		inline const math::Vec2& GetWindowSize() const { return math::Vec2((float)m_Window->GetWidth(), (float)m_Window->GetHeight()); }
	private:
		void Run();
		void Update();
		void Render();
	public:
		inline static Application& GetApplication() { return *s_Instance; }
	};

}