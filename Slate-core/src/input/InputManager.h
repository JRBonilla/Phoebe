#pragma once

#include <cstring>
#include <GLFW/glfw3.h>

namespace sl {

#define MAX_KEYS			GLFW_KEY_LAST
#define MAX_MOUSE_BUTTONS   GLFW_MOUSE_BUTTON_LAST

	class InputManager {
	private:
		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];

		bool m_MouseButtons[MAX_MOUSE_BUTTONS];
		bool m_MouseState[MAX_KEYS];
		bool m_MouseClicked[MAX_KEYS];
		double m_MouseX, m_MouseY;
	private:
		static InputManager s_Instance;

		InputManager() {
			ClearKeys();
			ClearMouseButtons();
		}
		
		void ClearKeys();
		void ClearMouseButtons();
	public:
		static InputManager& GetInstance();

		void Update();

		void SetMouseX(double x);
		void SetMouseY(double y);

		void SetKeyState(unsigned int key, bool state);
		void SetMouseButtonState(unsigned int button, bool state);
		
		inline double GetMouseX() const { return m_MouseX; }
		inline double GetMouseY() const { return m_MouseY; }

		inline bool IsKeyPressed(unsigned int key) const { return m_Keys[key]; }
		inline bool IsKeyTyped(unsigned int key) const { return m_KeyTyped[key]; }

		inline bool IsMouseButtonPressed(unsigned int button) const { return m_MouseButtons[button]; }
		inline bool IsMouseButtonClicked(unsigned int button) const { return m_MouseClicked[button]; }
	};

}