#include "Time.h"

namespace cg
{
	Time::clock_rep Time::GetElapsedNanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_startTime).count();
	}

	Time::clock_rep Time::GetElapsedMicroseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - m_startTime).count();
	}

	Time::clock_rep Time::GetElapsedMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_startTime).count();
	}

	float Time::GetElapsedSeconds()
	{
		return (clock::now() - m_startTime).count() / static_cast<float>(clock_duration::period::den);
	}
}

