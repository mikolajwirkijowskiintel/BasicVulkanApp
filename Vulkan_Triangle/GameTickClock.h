#pragma once
#include <chrono>
class GameTickClock
{
public:
	GameTickClock();
	float tick();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTimepoint;
};

