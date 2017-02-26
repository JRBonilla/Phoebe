#pragma once

#include <iomanip>
#include "../layers/Layer.h"
#include "../graphics/renderables/Label.h"
#include "../graphics/renderables/Sprite.h"
#include "../graphics/fonts/FontManager.h"
#include "../graphics/shaders/ShaderManager.h" 
#include "../utilities/Timer.h"

namespace ph { namespace debug {

	using namespace graphics;

	class DebugInfoLayer : public Layer {
	private:
		Label*	m_FpsLabel;
		Label*	m_DeltaTimeLabel;
		int		m_FramesPerSecond;
		float	m_LastTime, m_CurrentTime;
		float	m_CurrentFrame, m_LastFrame, m_DeltaTime;
	public:
		DebugInfoLayer();
		~DebugInfoLayer();

		void Init() override;
		void Update() override;
	};

}}
