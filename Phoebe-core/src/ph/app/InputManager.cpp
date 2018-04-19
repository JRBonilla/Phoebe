#include "InputManager.h"
#include "ph/app/Application.h"

namespace ph {

	InputManager  InputManager::s_Instance;
	bool          InputManager::m_Keys[MAX_KEYS];
	bool          InputManager::m_KeyState[MAX_KEYS];
	bool          InputManager::m_KeyTyped[MAX_KEYS];
				  
	bool          InputManager::m_MouseButtons[MAX_MOUSE_BUTTONS];
	bool          InputManager::m_MouseState[MAX_KEYS];
	bool          InputManager::m_MouseClicked[MAX_KEYS];
	bool          InputManager::m_MouseGrabbed;
				  
	double        InputManager::m_MouseX;
	double        InputManager::m_MouseY;
	double        InputManager::m_ScrollX;
	double        InputManager::m_ScrollY;
	math::Vec2    InputManager::m_MousePosition;

	void InputManager::ClearKeys() {
		memset(m_Keys, false, MAX_KEYS);
		memset(m_KeyState, false, MAX_KEYS);
		memset(m_KeyTyped, false, MAX_KEYS);
	}

	void InputManager::ClearMouseButtons() {
		memset(m_MouseButtons, false, MAX_MOUSE_BUTTONS);
		memset(m_MouseState, false, MAX_MOUSE_BUTTONS);
		memset(m_MouseClicked, false, MAX_MOUSE_BUTTONS);
	}

	void InputManager::Update() {
		for (int i = 0; i < MAX_KEYS; i++) {
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];
		}

		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];
		}

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_MOUSE_BUTTONS);
		m_MousePosition = math::Vec2((float)m_MouseX, (float)m_MouseY);
	}

	void InputManager::SetMouseX(double x) {
		m_MouseX = x;
	}

	void InputManager::SetMouseY(double y) {
		m_MouseY = y;
	}

	void InputManager::SetMousePosition(const math::Vec2& position) {
		glfwSetCursorPos(Application::GetApplication().GetWindow()->GetGLFWWindow(), position.x, position.y);
		SetMouseX(position.x);
		SetMouseY(position.y);
	}

	void InputManager::SetScrollX(double xoffset) {
		m_ScrollX = xoffset;
	}

	void InputManager::SetScrollY(double yoffset) {
		m_ScrollY = yoffset;
	}

	void InputManager::SetMouseGrabbed(bool grabbed) {
		m_MouseGrabbed = grabbed;
	}

	void InputManager::SetKeyState(unsigned int key, bool state) {
		m_Keys[key] = state;
	}

	void InputManager::SetMouseButtonState(unsigned int button, bool state) {
		m_MouseButtons[button] = state;
	}

}
