#include "TestAceTimer.h"
#include "../Utilities/DebugUtil.h"

namespace TA_Base_Test
{
	TestAceTimer::TestAceTimer()
	{
		m_thdScheduleTimer.activate();

		ScheduleParameter* scheduleParameter = new ScheduleParameter();
		scheduleParameter->nameList = "datapoint.name";

		ACE_Time_Value atmScheduleTime(0, 0);			//start execute time by sceond
		ACE_Time_Value atmIntervalTime(m_interval, 0);			//interval time by second

		m_scheduleId = m_thdScheduleTimer.schedule(this, static_cast<void*>(scheduleParameter), atmScheduleTime, atmIntervalTime);

		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Ace Timer scheduled polling: %s, timer id: %d", scheduleParameter->nameList.c_str(), m_scheduleId);
	}


	TestAceTimer::~TestAceTimer()
	{
		m_thdScheduleTimer.deactivate();
		m_thdScheduleTimer.wait();
	}

	int TestAceTimer::handle_timeout(const ACE_Time_Value& current_time, const void *act)
	{
		const ScheduleParameter* scheduleParameter = static_cast<const ScheduleParameter*>(act);
		if (0 == scheduleParameter)
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "NULL pointer schedule to be executed");
			return 0;
		}

		std::string nameList = scheduleParameter->nameList;
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Execute schedule polling : %s", nameList.c_str());
	}
}