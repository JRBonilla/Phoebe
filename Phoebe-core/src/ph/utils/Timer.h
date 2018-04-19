#pragma once

#include <chrono>

namespace ph {
	
	typedef std::chrono::duration<float, std::milli> milliseconds;
	typedef std::chrono::high_resolution_clock       HighResolutionClock;
	
	class Timer {
	private:
		std::chrono::time_point<HighResolutionClock> m_Start;
	public:
		Timer();

		void Reset();
		
		float Elapsed()       const;
		float ElapsedMillis() const;
	};

}