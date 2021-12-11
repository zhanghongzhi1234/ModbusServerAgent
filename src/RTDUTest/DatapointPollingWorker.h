#ifndef DATAPOINTPOLLINGWORKER__INCLUDED_
#define DATAPOINTPOLLINGWORKER__INCLUDED_

#include <map>

#include "ace/Timer_Queue_Adapters.h"
#include "ace/Timer_Heap.h"
#include "../ModbusComms/ModbusService.h"


using namespace TA_Base_Bus;
namespace TA_Base_App
{
	class ModbusPointManager;

	const long INVALID_TIMER_ID = -1;

	struct ScheduleParameter
	{
		std::string nameList;
	};

	class DatapointPollingWorker : public ACE_Event_Handler
	{
	public:
		DatapointPollingWorker(ModbusPointManager* pointMgr);
		virtual ~DatapointPollingWorker();

		// ACE_Event_Handler interface
		virtual int handle_timeout(const ACE_Time_Value& current_time, const void* act = 0);

		void startPollingJob(std::string & nameList);
		void stopPollingJob();

	private:

		ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> m_thdScheduleTimer;
		long m_scheduleId;
		unsigned long m_interval;

		ModbusPointManager* m_pointManager;
	};
}

#endif // ifndef (DATAPOINTPOLLINGWORKER__INCLUDED_)