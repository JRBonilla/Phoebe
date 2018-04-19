#pragma once

#include <cstring>
#include "ph/math/Vec2.h"

namespace ph {

#define MAX_KEYS			348
#define MAX_MOUSE_BUTTONS   7

	class InputManager {
	private:
		static InputManager s_Instance;

		static bool        m_Keys[MAX_KEYS];
		static bool        m_KeyState[MAX_KEYS];
		static bool        m_KeyTyped[MAX_KEYS];
			   	    
		static bool        m_MouseButtons[MAX_MOUSE_BUTTONS];
		static bool        m_MouseState[MAX_KEYS];
		static bool        m_MouseClicked[MAX_KEYS];
		static bool        m_MouseGrabbed;
				    
		static double      m_MouseX, m_MouseY;
		static double      m_ScrollX, m_ScrollY;
		static math::Vec2  m_MousePosition;
	private:
		InputManager() {
			ClearKeys();
			ClearMouseButtons();
			m_MouseGrabbed = false;
		}
		
		static void ClearKeys();
		static void ClearMouseButtons();
	public:
		static void Update();

		static void SetMouseX(double x);
		static void SetMouseY(double y);
		static void SetMousePosition(const math::Vec2& position);

		static void SetScrollX(double xoffset);
		static void SetScrollY(double yoffset);

		static void SetKeyState(unsigned int key, bool state);
		static void SetMouseButtonState(unsigned int button, bool state);
		static void SetMouseGrabbed(bool grabbed);
		
		static inline double GetMouseX() { return m_MouseX; }
		static inline double GetMouseY() { return m_MouseY; }
		static inline math::Vec2 GetMousePosition() { return m_MousePosition; }

		static inline double GetScrollX() { return m_ScrollX; }
		static inline double GetScrollY() { return m_ScrollY; }
		
		static inline bool IsMouseGrabbed() { return m_MouseGrabbed; }
		static inline bool IsKeyPressed(unsigned int key) { return m_Keys[key]; }
		static inline bool IsKeyTyped(unsigned int key) { return m_KeyTyped[key]; }

		static inline bool IsMouseButtonPressed(unsigned int button) { return m_MouseButtons[button]; }
		static inline bool IsMouseButtonClicked(unsigned int button) { return m_MouseClicked[button]; }
	};

}