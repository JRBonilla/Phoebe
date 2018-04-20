#pragma once

#include <vector>
#include "DebugMenuItem.h"
#include "ph/Types.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace ph { namespace debug {

	class DebugMenu {
	private:
		static DebugMenu* s_Instance;
	private:
		static MenuItemList      m_MenuItems;
		static ImGuiWindowFlags  m_WindowFlags;
		static bool              m_Visible;
		static bool              m_Focus;
		static float             m_WindowWidth;
		static float             m_WindowHeight;
	public:
		static void Init();

		static void Add(FloatSlider* slider);
		static void Add(const std::string& label, float* var, float min, float max);

		static void Add(IntSlider*   slider);
		static void Add(const std::string& label, int* var, int min, int max);

		static void Add(FloatDrag* drag);
		static void Add(IntDrag*  drag);

		static void Add(Checkbox* checkbox);
		static void Add(const std::string& label, bool* var);

		static void Update();
		static void Render();

		static inline bool HasFocus() { return m_Focus; }

		static inline bool IsVisible() { return m_Visible; }
		static inline void SetVisibility(bool visible) { m_Visible = visible; }
	private:
		DebugMenu();
		~DebugMenu();

		static void DrawSlider(FloatSlider* slider);
		static void DrawSlider(IntSlider* slider);

		static void DrawDrag(FloatDrag* drag);
		static void DrawDrag(IntDrag* drag);

		static void DrawCheckbox(Checkbox* checkbox);
	};

}}