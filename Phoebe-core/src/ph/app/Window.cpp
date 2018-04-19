#include "Window.h"

namespace ph {

	using namespace audio;
	using namespace renderer;

	Window::Window(const char* title, const WindowProperties& properties)
		: m_Title(title), m_Properties(properties), m_MouseWasGrabbed(false) {
		if (!Init()) {
			glfwTerminate();
		}

		ShaderManager::Init();
		FontManager::Init();
		SoundManager::Init();
	}

	Window::Window(const char* title, uint width, uint height, bool fullscreen, bool vsync, bool resizable)
		: m_Title(title), m_Properties({ width, height, fullscreen, vsync, resizable }), m_MouseWasGrabbed(false) {
		if (!Init()) {
			glfwTerminate();
		}

		ShaderManager::Init();
		FontManager::Init();
		SoundManager::Init();
	}


	Window::~Window() {
		SoundManager::Clean();
		FontManager::Clean();
		ShaderManager::Clean();
		glfwTerminate();
	}

	bool Window::Init() {
		if (!glfwInit()) {
			PH_FATAL("Failed to initialize GLFW!");
			return false;
		}

		// Set GLFW window hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, m_Properties.resizable ? true : false);
		glfwWindowHint(GLFW_SAMPLES, 4);

		// Load the window icon
		uint iconWidth = 32, iconHeight = 32;
		uint iconBits = 0;
		byte* pixels = Image::Load("res/icon.png", &iconWidth, &iconHeight, &iconBits, true);
		GLFWimage icon = { (int)iconWidth, (int)iconHeight, pixels };

		m_Window = glfwCreateWindow(m_Properties.width, m_Properties.height, m_Title,
			m_Properties.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
		if (m_Window == nullptr) {
			PH_FATAL("Failed to initialize GLFW window!");
			return false;
		}
		glfwSetWindowIcon(m_Window, 1, &icon);
		CenterWindowOnScreen();
		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(m_Properties.vsync);
		
		// Set GLFW callbacks
		glfwSetKeyCallback        (m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback  (m_Window, CursorPositionCallback);
		glfwSetWindowSizeCallback (m_Window, ResizeCallback);
		glfwSetScrollCallback     (m_Window, ScrollCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			PH_FATAL("Failed to initialize OpenGL!");
			return false;
		}

		RenderSystem::Init();
		glfwGetFramebufferSize(m_Window, &m_ViewPortWidth, &m_ViewPortHeight);
		RenderSystem::SetViewport(0, 0, m_ViewPortWidth, m_ViewPortHeight);

		delete[] pixels;
		return true;
	}

	void Window::CenterWindowOnScreen()	{
		// Gets information about the monitor
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		// Sets the m_Window position to the CenterOnScreen
		m_WindowX = (mode->width / 2) - (m_Properties.width / 2);
		m_WindowY = (mode->height / 2) - (m_Properties.height / 2);
		glfwSetWindowPos(m_Window, m_WindowX, m_WindowY);
	}

	void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		InputManager::SetMouseButtonState(button, action != GLFW_RELEASE);
	}

	void Window::CursorPositionCallback(GLFWwindow* window, double x, double y) {
		InputManager::SetMouseX(x);
		InputManager::SetMouseY(y);
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		InputManager::SetKeyState(key, action != GLFW_RELEASE);
	}

	void Window::ResizeCallback(GLFWwindow* window, int width, int height) {
		RenderSystem::SetViewport(0, 0, width, height);
	}

	void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		InputManager::SetScrollX(xoffset);
		InputManager::SetScrollY(yoffset);
	}

	void Window::Update() {
		glfwPollEvents();
		InputManager::Update();
		UpdateMouseGrab();
		SoundManager::Update();
	}

	void Window::UpdateMouseGrab() {
		if (m_MouseWasGrabbed != InputManager::IsMouseGrabbed()) {
			if (InputManager::IsMouseGrabbed()) {
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			else {
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			m_MouseWasGrabbed = InputManager::IsMouseGrabbed();
		}
	}

	void Window::ClearBuffer() const {
		RenderSystem::Clear(COLOR_BUFFER | DEPTH_BUFFER);
	}

	void Window::SwapBuffers() const {
		glfwSwapBuffers(m_Window);
	}

	void Window::Maximize() const {
		glfwMaximizeWindow(m_Window);
	}

	void Window::SetVsync(bool vsync) {
		m_Properties.vsync = vsync;
		glfwSwapInterval(m_Properties.vsync);
	}

	bool Window::Closed() const {
		return glfwWindowShouldClose(m_Window) || (!m_MouseWasGrabbed && InputManager::IsKeyTyped(GLFW_KEY_ESCAPE));
	}

}
