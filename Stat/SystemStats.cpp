#include "SystemStats.hpp"

using namespace onyx;
using namespace onyx::System;

ull System::to_KB(ull val)
{
	return val / 1000;
}
ull System::to_MB(ull val)
{
	return val / 1000 / 1000;
}
ull System::to_GB(ull val)
{
	return val / 1000 / 1000 / 1000;
}
ull System::to_min(ull val)
{
	return val / 60;
}
ull System::to_hour(ull val)
{
	return val / 60 / 60;
}
ull System::to_day(ull val)
{
	return val / 60 / 60 / 24;
}
SystemStats::SystemStats()
{
	// Memory
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);

	//CPU
	GetSystemInfo(&sysInfo);

	//Time
	GetLocalTime(&sysTime);

	//Battery
	GetSystemPowerStatus(&sysPower);
}
SystemStats::~SystemStats()
{
}
void SystemStats::update()
{
	GlobalMemoryStatusEx(&memInfo);

	//CPU
	GetSystemInfo(&sysInfo);

	//Time
	GetLocalTime(&sysTime);

	//Battery
	GetSystemPowerStatus(&sysPower);
}

ul SystemStats::getMemoryLoad()
{
	ul memLoad = memInfo.dwMemoryLoad;
	return memLoad;
}
ull SystemStats::getAvailMemory()
{
	ull availMem = memInfo.ullAvailPhys;
	return availMem;
}
ull SystemStats::getUsedMemory()
{
	ull memUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	return memUsed;
}
ull SystemStats::getTotalMemory()
{
	ull memTotal = memInfo.ullTotalPhys;
	return memTotal;
}
ull SystemStats::getPageMemory()
{
	ull pagedMemory = memInfo.ullTotalPageFile - memInfo.ullTotalPhys;
	return pagedMemory;
}

std::string SystemStats::getProcessorArch()
{
	/*
		Note: If the program is compiled as 32bit on a 64bit system it still will return x86
	*/
	switch (sysInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64:
		return "x64";
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		return "ARM";
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		return "IA-64";
		break;
	case PROCESSOR_ARCHITECTURE_INTEL:
		return "x86";
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		return "Unknown";
		break;
	default:
		return "An error has occured when requesting processor information.\n";
		break;
	}
}
std::string SystemStats::getProcessorRev()
{
	// Might not do. Differentiating between processors types might not be possible.
	return "?";
}

System::TimeStat SystemStats::getSystemTime()
{
	// Due to the nature of time, we will update it the moment the function is called.
	GetLocalTime(&sysTime);
	System::TimeStat ret;
	ret.year = sysTime.wYear;
	ret.month = sysTime.wMonth;
	switch (ret.month)
	{
	case 0: ret.monthStr = "January"; break;
	case 1: ret.monthStr = "February"; break;
	case 2: ret.monthStr = "March"; break;
	case 3: ret.monthStr = "April"; break;
	case 4: ret.monthStr = "May"; break;
	case 5: ret.monthStr = "June"; break;
	case 6: ret.monthStr = "July"; break;
	case 7: ret.monthStr = "August"; break;
	case 8: ret.monthStr = "September"; break;
	case 9: ret.monthStr = "October"; break;
	case 10: ret.monthStr = "November"; break;
	case 11: ret.monthStr = "December"; break;
	default: ret.monthStr = "Unknown"; break;
	}
	ret.dayOfWeek = sysTime.wDayOfWeek;
	switch (ret.dayOfWeek)
	{
	case 0: ret.dayOfWeekStr = "Sunday"; break;
	case 1: ret.dayOfWeekStr = "Monday"; break;
	case 2: ret.dayOfWeekStr = "Tuesday"; break;
	case 3: ret.dayOfWeekStr = "Wednesday"; break;
	case 4: ret.dayOfWeekStr = "Thursday"; break;
	case 5: ret.dayOfWeekStr = "Friday"; break;
	case 6: ret.dayOfWeekStr = "Saturday"; break;
	default: ret.dayOfWeekStr = "Unknown"; break;
	}
	ret.day = sysTime.wDay;
	ret.dayStr = std::to_string(ret.day);
	switch (ret.dayStr[0])
	{
	case '1': ret.dayStr = std::to_string(ret.day) + "st"; break;
	case '2': ret.dayStr = std::to_string(ret.day) + "nd"; break;
	case '3': ret.dayStr = std::to_string(ret.day) + "rd"; break;
	default: ret.dayStr = std::to_string(ret.day) + "th"; break;
	}
	ret.hour = sysTime.wHour;
	ret.minute = sysTime.wMinute;
	ret.second = sysTime.wSecond;
	ret.millisecond = sysTime.wMilliseconds;
	return ret;
}

bool SystemStats::isPluggedIn()
{
	updatePowerStatus();
	return sysPower.ACLineStatus;
}
std::string SystemStats::getBatteryState()
{
	updatePowerStatus();
	switch (sysPower.BatteryFlag)
	{
	case 0: return "Okay"; break;
	case 1: return "High"; break;
	case 2: return "Low"; break;
	case 4: return "Critical"; break;
	case 8: return "Charging"; break;
	case 128: return "No battery"; break;
	default: return "An error has occured getting system batter information"; break;
	}
}
ul SystemStats::getBatteryLife()
{
	updatePowerStatus();
	uc batteryLife = sysPower.BatteryLifePercent;
	if (batteryLife == 255)
		batteryLife = 100;
	return batteryLife;
}
bool SystemStats::isPowerSaverOn()
{
	return false;
}
ul SystemStats::getBatteryLifeTime()
{
	updatePowerStatus();
	ul batteryLife = sysPower.BatteryLifeTime;
	if (batteryLife == 0UL - 1)
		batteryLife = 0U;
	return batteryLife;
}
ul SystemStats::getFullBatteryLifeTime()
{
	updatePowerStatus();
	ul fullBatteryLife = sysPower.BatteryFullLifeTime;
	if (fullBatteryLife == 0UL - 1)
		fullBatteryLife = 0U;
	return fullBatteryLife;
}