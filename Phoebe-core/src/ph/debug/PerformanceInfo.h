#pragma once

#include <iomanip>
#include "ph/renderer/Layer2D.h"
#include "ph/renderer/fonts/FontManager.h"
#include "ph/renderer/renderables/Label.h"
#include "ph/utils/Timer.h"

namespace ph { namespace debug {

	class PerformanceInfo : public renderer::Layer2D {
	private:
		renderer::Label*  m_FPSLabel;
		renderer::Label*  m_UPSLabel;
		renderer::Label*  m_FrameTimeLabel;
	public:
		PerformanceInfo();
		~PerformanceInfo();

		void Init()   override;
		void Update() override;
	};

}}
