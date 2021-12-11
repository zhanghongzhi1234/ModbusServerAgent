#ifndef TEST_ACE_TIMER_H__
#define TEST_ACE_TIMER_H__

#include "ace/Timer_Queue_Adapters.h"
#include "ace/Timer_Heap.h"


namespace TA_Base_Test
{
	const long INVALID_TIMER_ID = -1;

	struct ScheduleParameter
	{
		std::string nameList;
	};

	class TestAceTimer : public ACE_Event_Handler
	{
	public:
		TestAceTimer();
		~TestAceTimer();

		// ACE_Event_Handler interface
		virtual int handle_timeout(const ACE_Time_Value& current_time, const void* act = 0);

	private:

		ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> m_thdScheduleTimer;
		long m_scheduleId;
		unsigned long m_interval;
	};
}
#endif
