#pragma once

#include "Singleton.h"
//#include "Helper.h"

#include <chrono>
#include <string>
#include <vector>

#define TIMEPOINT std::chrono::time_point<std::chrono::high_resolution_clock>
#define GET_SYSTEMS_PERFORMANCES() PerformanceVisualiser::GetInstance()->GetPerformances();
#define GET_SYSTEM_PERFORMANCE(_systemName) PerformanceVisualiser::GetInstance()->GetPerformance(_systemName);
#define TRACK_PERFORMANCE(_systemName) PerformanceVisualiser::GetInstance()->StartSystemTracking(_systemName);
#define END_TRACK(_systemName) PerformanceVisualiser::GetInstance()->StopSystemTracking(_systemName);

class PerformanceVisualiser : public Singleton<PerformanceVisualiser>
{
public:
	PerformanceVisualiser() = default;
	~PerformanceVisualiser() = default;

	PerformanceVisualiser(const PerformanceVisualiser&) = delete;
	const PerformanceVisualiser& operator=(const PerformanceVisualiser&) = delete;

	void StartSystemTracking(std::string _systemName);
	double StopSystemTracking(std::string _systemName);
	double GetPerformance(std::string _systemName);
	std::string GetPerformances();

private:
	std::vector<std::pair<std::string, std::pair<double, std::pair<TIMEPOINT, TIMEPOINT>>>> mSystemPerformance;
};
