#pragma once
#include <chrono>

namespace cg
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() : 
			m_startTime{ clock::now() }
		{}

		void Reset() { m_startTime = clock::now(); }

		clock_rep GetElapsedNanoseconds();
		clock_rep GetElapsedMicroseconds();
		clock_rep GetElapsedMilliseconds();
		float GetElapsedSeconds();

	private:
		clock::time_point m_startTime;
	};
}