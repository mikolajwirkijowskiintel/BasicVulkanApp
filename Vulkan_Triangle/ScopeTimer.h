#pragma once
#include <chrono>
#include <string>

class ScopeTimer
{
public:
	ScopeTimer(std::string name);
	~ScopeTimer();
private:
	const std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;

};

class TickTimer
{
public:
	TickTimer(std::string name);
	~TickTimer();
	void tick();
private:
	const std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTimepoint;

};