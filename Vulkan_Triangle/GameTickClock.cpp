#include "GameTickClock.h"

GameTickClock::GameTickClock()
{
	previousTimepoint = std::chrono::high_resolution_clock::now();
}

float GameTickClock::tick()
{
	auto now = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
	auto then = std::chrono::time_point_cast<std::chrono::microseconds>(previousTimepoint).time_since_epoch().count();
	return float(now-then)/1000000;
}
