#pragma once

#include <imgui.h>
#include "../../ext/imgui/imgui_impl_glfw_gl3.h"
#include "../../ext/imgui/imgui_utils.h"
#include "../../ext/imgui/imgui_dock.h"
#include "../layers/Layer.h"
#include "../graphics/objects/Label.h"
#include "../graphics/fonts/FontManager.h"
#include "../graphics/shaders/ShaderManager.h" 
#include "../utils/Timer.h"

namespace sl { namespace debug {

	using namespace graphics;

	class DebugLayer : public Layer {
	private:
		Label* m_FPSLabel;
		Label* m_UPSLabel;
		int m_FramesPerSecond;
		float m_LastTime, m_CurrentTime;
		float m_CurrentFrame, m_LastFrame, m_DeltaTime;
	public:
		DebugLayer(GLFWwindow* window);
		~DebugLayer();

		void Init() override;
		void Update() override;
		void Render() override;
	private:
		void RenderDebugInterface() const;
	};

}}
