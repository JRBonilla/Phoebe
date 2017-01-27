#pragma once

#include <chrono>

namespace fl {
	
	class Timer
	{
	public:
		static Timer* GetInstance();
	private:
		static Timer* s_Instance;
		typedef std::chrono::high_resolution_clock HighResClock;
		typedef std::chrono::duration<float, std::milli> milliseconds;
		std::chrono::time_point<HighResClock> m_Start;
	public:
		void reset();
		float elapsed() const;
	private:
		Timer();
	};

}