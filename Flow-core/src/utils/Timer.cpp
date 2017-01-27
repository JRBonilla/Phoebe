#include "Timer.h"

namespace fl {

	Timer* Timer::s_Instance = new Timer();

	Timer* Timer::GetInstance()
	{
		return s_Instance;
	}

	Timer::Timer()
	{
		reset();
	}


	void Timer::reset()
	{
		m_Start = HighResClock::now();
	}

	float Timer::elapsed() const
	{
		return std::chrono::duration_cast<milliseconds>(HighResClock::now() - m_Start).count() / 1000.0f;
	}

}