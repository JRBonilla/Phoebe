#pragma once

#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "InputManager.h"
#include "ph/math/Math.h"
#include "ph/audio/SoundManager.h"
#include "ph/renderer/RenderSystem.h"
#include "ph/renderer/fonts/FontManager.h"
#include "ph/renderer/shaders/ShaderManager.h"

namespace ph {
	
	struct WindowProperties {
		uint width, height;
		bool fullscreen;
		bool vsync;
		bool resizable;
	};

	class Window {
	private:
		WindowProperties  m_Properties;
		GLFWwindow*		  m_Window;
		int				  m_WindowX, m_WindowY;
		int				  m_ViewPortWidth, m_ViewPortHeight;
		const char*		  m_Title;
		bool              m_MouseWasGrabbed;
	public:
		Window(const char* title, const WindowProperties& properties);
		Window(const char* title, uint width, uint height, bool fullscreen = false, bool vsync = true, bool resizable = false);
		~Window();

		void Update();
		void ClearBuffer() const;
		void SwapBuffers() const;
		void Maximize()    const;

		void SetVsync(bool vsync);
		inline bool GetVsync() const { return m_Properties.vsync; }

		bool Closed() const;

		inline int GetWidth()  const { return m_Properties.width; }
		inline int GetHeight() const { return m_Properties.height; }

		inline GLFWwindow* GetGLFWWindow() const { return m_Window; }
		inline const WindowProperties& GetProperties() const { return m_Properties; }
	private:
		bool Init();
		void CenterWindowOnScreen();
		void UpdateMouseGrab();

		// Callbacks
		static void MouseButtonCallback   (GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double x, double y);
		static void KeyCallback           (GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ResizeCallback        (GLFWwindow* window, int width, int height);
		static void ScrollCallback        (GLFWwindow* window, double xoffset, double yoffset);
	};

}
