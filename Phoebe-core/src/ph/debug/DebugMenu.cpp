#include "DebugMenu.h"
#include "ph/app/Application.h"

namespace ph { namespace debug {

	DebugMenu*         DebugMenu::s_Instance = new DebugMenu();
	MenuItemList       DebugMenu::m_MenuItems;
	ImGuiWindowFlags   DebugMenu::m_WindowFlags  = 0.0f;
	float              DebugMenu::m_WindowWidth  = 500.0f;
	float              DebugMenu::m_WindowHeight = 800.0f;
	bool               DebugMenu::m_Visible = false;
	bool               DebugMenu::m_Focus   = false;

	DebugMenu::DebugMenu() {
	}

	DebugMenu::~DebugMenu() {
		for (uint i = 0; i < m_MenuItems.size(); i++) {
			delete m_MenuItems[i];
		}
		m_MenuItems.clear();

		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void DebugMenu::Init() {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();(void)io;

		m_WindowFlags |= ImGuiWindowFlags_NoCollapse;
		m_WindowFlags |= ImGuiWindowFlags_NoResize;
		m_WindowFlags |= ImGuiWindowFlags_NoMove;
		m_WindowFlags |= ImGuiWindowFlags_NoSavedSettings;
		m_WindowFlags |= ImGuiWindowFlags_NoNavInputs;

		GLFWwindow* window = Application::GetApplication().GetWindow()->GetGLFWWindow();
		ImGui_ImplGlfwGL3_Init(window, false);
		
		ImGui::StyleColorsDark();
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImColor(0.06f, 0.06f, 0.06f, 0.85f);
		ImGui::GetStyle().WindowBorderSize = 0.0f;
		ImGui::GetStyle().WindowRounding = 0.0f;
	}

	void DebugMenu::Add(FloatSlider* slider) {
		m_MenuItems.push_back(slider);
	}

	void DebugMenu::Add(const std::string& label, float* var, float min, float max) {
		m_MenuItems.push_back(new FloatSlider(label, var, min, max));
	}

	void DebugMenu::Add(IntSlider* slider) {
		m_MenuItems.push_back(slider);
	}

	void DebugMenu::Add(const std::string& label, int* var, int min, int max) {
		m_MenuItems.push_back(new IntSlider(label, var, min, max));
	}

	void DebugMenu::Add(FloatDrag* drag) {
		m_MenuItems.push_back(drag);
	}

	void DebugMenu::Add(IntDrag* drag) {
		m_MenuItems.push_back(drag);
	}

	void DebugMenu::Add(Checkbox* checkbox) {
		m_MenuItems.push_back(checkbox);
	}

	void DebugMenu::Add(const std::string& label, bool* var) {
		m_MenuItems.push_back(new Checkbox(label, var));
	}

	void DebugMenu::Update() {
		// Change visibility if CTRL+D is typed
		if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && InputManager::IsKeyTyped(GLFW_KEY_D)) {
			SetVisibility(!IsVisible());
		}

		// Set focus based on whether or not imgui is requesting mouse input
		if (ImGui::GetIO().WantCaptureMouse) {
			m_Focus = true;
		}
		else {
			m_Focus = false;
		}
	}

	void DebugMenu::Render() {
		if (!m_MenuItems.empty()) {
			ImGui_ImplGlfwGL3_NewFrame();
			ImGui::SetNextWindowSize(ImVec2(m_WindowWidth, m_WindowHeight));

			ImGui::Begin("Debug menu", NULL, m_WindowFlags);
			{
				ImGui::Text("Options");

				for (uint i = 0; i < m_MenuItems.size(); i++) {
					MenuItem* item = m_MenuItems[i];
					if (item->m_Type == MenuItem::Type::FLOAT_SLIDER) {
						FloatSlider* slider = (FloatSlider*)item;
						ImGui::SliderFloat(slider->m_Label.c_str(), slider->m_Var, slider->m_Min, slider->m_Max);
					}
					else if (item->m_Type == MenuItem::Type::INT_SLIDER) {
						IntSlider* slider = (IntSlider*)item;
						ImGui::SliderInt(slider->m_Label.c_str(), slider->m_Var, slider->m_Min, slider->m_Max);
					}
					else if (item->m_Type == MenuItem::Type::FLOAT_DRAG) {
						FloatDrag* drag = (FloatDrag*)item;
						ImGui::DragFloat(drag->m_Label.c_str(), drag->m_Var, drag->m_Speed, drag->m_Min, drag->m_Max);
					}
					else if (item->m_Type == MenuItem::Type::INT_DRAG) {
						IntDrag* drag = (IntDrag*)item;
						ImGui::DragInt(drag->m_Label.c_str(), drag->m_Var, drag->m_Speed, drag->m_Min, drag->m_Max);
					}
					else if (item->m_Type == MenuItem::Type::CHECKBOX) {
						Checkbox* checkbox = (Checkbox*)item;
						ImGui::Checkbox(checkbox->m_Label.c_str(), checkbox->m_Var);
					}
				}
			}
			ImGui::End();

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		}
	}

}}