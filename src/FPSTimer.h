#pragma once

#define WINDOWS_TIMER 2

#if WINDOWS_TIMER == 0
#include <Windows.h>
#elif WINDOWS_TIMER == 1
#include <SFML/Graphics.hpp>
#else
#include <chrono>
#endif

#if WINDOWS_TIMER == 0
class FPSTimer
{
private:
	LARGE_INTEGER _start;
	double _frequency;

public:
	FPSTimer()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		_frequency = 1.0 / frequency.QuadPart;
		QueryPerformanceCounter(&_start);
	}

	void reset()
	{
		QueryPerformanceCounter(&_start);
	}

	float elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - _start.QuadPart;
		return (float)(cycles * _frequency);
	}
};
#elif WINDOWS_TIMER == 1
class FPSTimer
{
private:
	sf::Clock clock;
public:
	FPSTimer()
	{
		reset();
	}

	void reset()
	{
		clock.restart();
	}

	float elapsed()
	{
		return clock.getElapsedTime().asSeconds();
	}
}
#else
class FPSTimer
{
private:
	typedef std::chrono::high_resolution_clock HighResolutionClock;
	typedef std::chrono::duration<float, std::milli> milliseconds_type;
	std::chrono::time_point<HighResolutionClock> _start;
public:
	FPSTimer()
	{
		reset();
	}

	void reset()
	{
		_start = HighResolutionClock::now();
	}

	float elapsed()
	{
		return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - _start).count() / 1000.0f;
	}

};
#endif