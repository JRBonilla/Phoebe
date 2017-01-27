#pragma once

#include <vector>
#include "../graphics/layers/Layer.h"
#include "Window.h"
#include "../debug/DebugLayer.h"

namespace fl {

	using namespace math;

	class Application {
	private:
		Window*				m_Window;
		debug::DebugLayer*	m_DebugLayer;
		bool				m_Running, m_Suspended;
		std::string			m_Name;
		WindowProperties	m_Properties;
		std::vector<graphics::Layer*> m_LayerStack;
	public:
		Application(const std::string& name, const WindowProperties& properties);
		virtual ~Application();

		virtual void Init();

		virtual void PushLayer(graphics::Layer* layer);
		graphics::Layer* PopLayer();
		graphics::Layer* PopLayer(graphics::Layer* layer);

		virtual void Start();
		virtual void Suspend();
		virtual void Resume();
		virtual void Stop();

		inline Window*	GetWindow() const { return m_Window; }
		inline uint		GetWindowWidth() const { return m_Window->GetWidth(); }
		inline uint		GetWindowHeight() const { return m_Window->GetHeight(); }
		inline vec2		GetWindowSize() const { return vec2((float)m_Window->GetWidth(), (float)m_Window->GetHeight()); }
	private:
		virtual void Run();
		virtual void Update();
		virtual void Render();
	};

}
