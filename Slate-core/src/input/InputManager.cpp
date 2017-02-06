#include "InputManager.h"

namespace sl {

	InputManager InputManager::s_Instance;

	InputManager& InputManager::GetInstance() {
		return s_Instance;
	}

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
	}

	void InputManager::SetMouseX(double x) {
		m_MouseX = x;
	}

	void InputManager::SetMouseY(double y) {
		m_MouseY = y;
	}

	void InputManager::SetKeyState(unsigned int key, bool state) {
		m_Keys[key] = state;
	}

	void InputManager::SetMouseButtonState(unsigned int button, bool state) {
		m_MouseButtons[button] = state;
	}

}
