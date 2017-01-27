#pragma once

#include <imgui.h>
#include "../../ext/imgui/imgui_impl_glfw_gl3.h"
#include "../graphics/layers/Layer.h"
#include "../graphics/objects/Label.h"
#include "../graphics/fonts/FontManager.h"
#include "../utils/Timer.h"

namespace fl{ namespace debug {

	class DebugLayer : public graphics::Layer
	{
	private:
		graphics::Label* m_FPSLabel;
		int m_FramesPerSecond;
		float m_LastTime, m_CurrentTime;
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
