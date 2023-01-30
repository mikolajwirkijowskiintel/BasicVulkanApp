#include <iostream>
#include "ScopeTimer.h"

ScopeTimer::ScopeTimer(std::string name):name(name)
{
	m_StartTimepoint = std::chrono::high_resolution_clock::now();
}

ScopeTimer::~ScopeTimer()
{
	auto endTimePoint = std::chrono::high_resolution_clock::now();
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
	auto duration = end - start;
	std::cout << name <<" " << duration << "us" << std::endl;
}

TickTimer::TickTimer(std::string name) :name(name)
{
	previousTimepoint = std::chrono::high_resolution_clock::now();
}

TickTimer::~TickTimer()
{

}

void TickTimer::tick()
{
	auto now = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
	auto then = std::chrono::time_point_cast<std::chrono::microseconds>(previousTimepoint).time_since_epoch().count();
	std::cout << name << " " << now - then << "us" << std::endl;
	previousTimepoint = std::chrono::high_resolution_clock::now();
	
}
