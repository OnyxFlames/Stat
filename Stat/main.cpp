#include <iostream>

#include "SystemStats.hpp"

using namespace onyx;
using namespace onyx::System;

int main()
{
	SystemStats sys;
	std::cout << "Memory:\n"
		"\tRAM:\t" << to_MB(sys.getUsedMemory()) << "MB/" << to_MB(sys.getTotalMemory()) << "MB (" << sys.getMemoryLoad() << "%)\n"
		"\tPage:\t" << to_MB(sys.getPageMemory()) << "MB\n"
		"\nProcessor:\n\t"
		"Arch: " << sys.getProcessorArch() << "\n\n";
	TimeStat ts = sys.getSystemTime();
	std::cout << "It is " << ts.dayOfWeekStr << ", " << ts.monthStr << " " << ts.dayStr << " of the year " << ts.year << "\n";
	
	std::cout << "Plugged in: " << std::boolalpha << sys.isPluggedIn() << std::boolalpha << "\nBattery State: " << sys.getBatteryState() << "\nBattery: " << sys.getBatteryLife() << "%\n";

	std::cout << "Current battery life: \n" << to_day(sys.getBatteryLifeTime()) << " days\n" <<
		to_hour(sys.getBatteryLifeTime()) << " hours\n" <<
		to_min(sys.getBatteryLifeTime()) << " minutes\n" <<
		sys.getBatteryLifeTime() << " seconds\n";

	std::cout << "Full battery life: \n" << to_day(sys.getFullBatteryLifeTime()) << " days\n" <<
		to_hour(sys.getFullBatteryLifeTime()) << " hours\n" <<
		to_min(sys.getFullBatteryLifeTime()) << " minutes\n" <<
		sys.getFullBatteryLifeTime() << " seconds\n";
	getchar();
	return 0;
}