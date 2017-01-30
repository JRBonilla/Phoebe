#pragma once

#include <chrono>

namespace fl {
	
	class Timer {
	public:
		static Timer* GetInstance();
	private:
		static Timer* s_Instance;
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds;
		std::chrono::time_point<HighResolutionClock> m_Start;
	public:
		void Reset();
		float Elapsed() const;
	private:
		Timer();
	};

}