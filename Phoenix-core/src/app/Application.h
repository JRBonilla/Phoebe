#pragma once

#include <string>
#include "Window.h"

namespace ph {

	class Application {
	private:
		Window* m_Window;
		std::string m_Title;
		uint m_Width, m_Height;
	public:
		Application(const std::string& title, uint width, uint height);
		~Application();

		void Start();
		void Stop();
		void Pause();
		void Resume();
	};

}