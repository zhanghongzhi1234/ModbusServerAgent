#include "../Utilities/DebugUtil.h"
#include "CommonFunction.h"
#include "DatapointPollingWorker.h"
#include "ModbusPointManager.h"
#include "RTDBDefine.h"
#include "RTDBInterface.h"

namespace TA_Base_App
{
	DatapointPollingWorker::DatapointPollingWorker(ModbusPointManager* pointMgr)
		:
		m_scheduleId(INVALID_TIMER_ID),
		m_interval(2),
		m_pointManager(pointMgr)
	{
		m_thdScheduleTimer.activate();
	}


	DatapointPollingWorker::~DatapointPollingWorker()
	{
		m_thdScheduleTimer.deactivate();
		m_thdScheduleTimer.wait();
	}

	void DatapointPollingWorker::startPollingJob(std::string & nameList)
	{
		ScheduleParameter* scheduleParameter = new ScheduleParameter();
		scheduleParameter->nameList = nameList;

		ACE_Time_Value atmScheduleTime(0, 0);			//start execute time by sceond
		ACE_Time_Value atmIntervalTime(m_interval, 0);			//interval time by second

		m_scheduleId = m_thdScheduleTimer.schedule(this, static_cast<void*>(scheduleParameter), atmScheduleTime, atmIntervalTime);

		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Ace Timer scheduled polling: %s, timer id: %d", nameList.c_str(), m_scheduleId);
	}

	void DatapointPollingWorker::stopPollingJob()
	{
		m_thdScheduleTimer.cancel(m_scheduleId);
		m_scheduleId = INVALID_TIMER_ID;
	}

	int DatapointPollingWorker::handle_timeout(const ACE_Time_Value& current_time, const void *act)
	{
		const ScheduleParameter* scheduleParameter = static_cast<const ScheduleParameter*>(act);
		if (0 == scheduleParameter)
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "NULL pointer schedule to be executed");
			return 0;
		}

		std::string nameList = scheduleParameter->nameList;
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Execute schedule polling : %s", nameList.c_str());

		const char delim = '\n';
		std::vector<std::string> svec;
		CommonFunction::tokenize(nameList, delim, svec);

		try
		{
			int nCount = svec.size();
			char** tagNames = CommonFunction::vector2StringArray(svec);
			TagData* pTagData = new TagData[nCount];
			int nResult = GetRTDataByBatch(tagNames, pTagData, nCount);			//call batch datapoint api
			if (nResult < 0)
			{
				LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Failed to poll RTDU datapoint, result=%d", nResult);
				ReleaseConnect();
			}
			else
			{
				PointValueVector valueVec;
				for (int i = 0; i < nCount; i++)
				{
					TA_Base_Bus::PointValueStruct value;
					PointAddress address(i, 0);
					value.m_address = address;
					value.m_size = 16;
					value.m_value = pTagData[i].value;
					value.m_Dblvalue = pTagData[i].value;
					valueVec.push_back(value);
				}

				m_pointManager->submitUpdateData(&valueVec);

				m_pointManager->updateDataInitialized();
			}
			delete[] tagNames;
			delete pTagData;
		}
		catch (...)
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "Failed to execute polling");
			return 0;
		}

		return 0;
	}
}