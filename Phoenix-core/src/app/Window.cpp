#include "Window.h"

namespace ph {

	using namespace audio;
	using namespace graphics;

	Window::Window(const char* title, const WindowProperties& properties)
		: m_Title(title), m_Properties(properties) {
		if (!Init()) {
			glfwTerminate();
		}

		ShaderManager::Init();
		FontManager::Init();
		SoundManager::Init();
	}

	Window::Window(const char* title, uint width, uint height, bool fullscreen, bool vsync, bool resizable)
		: m_Title(title), m_Properties({ width, height, fullscreen, vsync, resizable }) {
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
			PHOENIX_LOG("Failed to initialize GLFW!");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, m_Properties.resizable ? GL_TRUE : GL_FALSE);

		int iconWidth = 32, iconHeight = 32, iconBits = 0;
		unsigned char* pixels = Image::Load("res/icon.png", &iconWidth, &iconHeight, &iconBits, false);
		GLFWimage icon = { iconWidth, iconHeight, pixels };
		
		m_Window = glfwCreateWindow(m_Properties.width, m_Properties.height, m_Title, m_Properties.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
		if (m_Window == nullptr) {
			PHOENIX_LOG("Failed to initialize GLFW window!");
			return false;
		}
		glfwSetWindowIcon(m_Window, 1, &icon);
		CenterWindowOnScreen();
		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(m_Properties.vsync);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, CursorPositionCallback);
		glfwSetWindowSizeCallback(m_Window, ResizeCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			PHOENIX_LOG("Failed to initialize OpenGL!");
			return false;
		}

		PrintOpenGLVersion();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glfwGetFramebufferSize(m_Window, &m_ViewPortWidth, &m_ViewPortHeight);
		glViewport(0, 0, m_ViewPortWidth, m_ViewPortHeight);

		return true;
	}

	void Window::PrintOpenGLVersion() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 13);
		std::cout << glGetString(GL_RENDERER) << ", OpenGL " << glGetString(GL_VERSION) << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
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
		InputManager::GetInstance().SetMouseButtonState(button, action != GLFW_RELEASE);
	}

	void Window::CursorPositionCallback(GLFWwindow* window, double x, double y) {
		InputManager::GetInstance().SetMouseX(x);
		InputManager::GetInstance().SetMouseY(y);
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		InputManager::GetInstance().SetKeyState(key, action != GLFW_RELEASE);
	}

	void Window::ResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::Update() {
		glfwPollEvents();
		InputManager::GetInstance().Update();
		SoundManager::Update();
	}

	void Window::ClearBuffer() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SwapBuffers() const {
		glfwSwapBuffers(m_Window);
	}

	bool Window::Closed() const {
		return glfwWindowShouldClose(m_Window) || InputManager::GetInstance().IsKeyTyped(GLFW_KEY_ESCAPE);
	}

}
