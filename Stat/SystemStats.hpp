#pragma once

#include <iostream>
#include <string>


#ifdef _WIN32
#include <Windows.h>
typedef unsigned char uc;
typedef unsigned short us;
typedef unsigned long ul;
typedef unsigned long long ull;
#elif
#error "This program currently only supports Windows platforms"
#endif


namespace onyx
{
	namespace System
	{

		ull to_KB(ull val);
		ull to_MB(ull val);
		ull to_GB(ull val);

		ull to_min(ull val);
		ull to_hour(ull val);
		ull to_day(ull val);

		// Probably move this elsewhere
		struct TimeStat
		{
			us year;
			us month;
			std::string monthStr;
			us dayOfWeek;
			std::string dayOfWeekStr;
			us day;
			std::string dayStr;
			us hour;
			us minute;
			us second;
			us millisecond;
		};
		/*
			Wrapper class to grab current system stats.
			Currently only supports Windows.
		*/
		class SystemStats
		{
		private:
			// Found here: https://msdn.microsoft.com/en-us/library/windows/desktop/aa366770(v=vs.85).aspx
			MEMORYSTATUSEX memInfo;
			SYSTEM_INFO sysInfo;
			SYSTEMTIME sysTime;
			SYSTEM_POWER_STATUS sysPower;

			// Call this function before getting any info regarding system power/battery
			void updatePowerStatus()
			{
				GetSystemPowerStatus(&sysPower);
			}
		public:
			SystemStats();
			~SystemStats();

			void update();

			ul getMemoryLoad();
			ull getAvailMemory();
			ull getUsedMemory();
			ull getTotalMemory();
			ull getPageMemory();

			std::string getProcessorArch();
			std::string getProcessorRev();

			System::TimeStat getSystemTime();

			bool isPluggedIn();
			std::string getBatteryState();
			ul getBatteryLife();
			bool isPowerSaverOn();
			// Returns in 'seconds'
			ul getBatteryLifeTime();
			ul getFullBatteryLifeTime();
		};

	}
}