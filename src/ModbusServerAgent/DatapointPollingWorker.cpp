#include "CommonFunction.h"
#include "DatapointPollingWorker.h"
#include "ModbusPointManager.h"
#include "RTDBDefine.h"
//#include "RTDBInterface.h"
#include "../Utilities/DebugUtil.h"
#include "../Utilities/RunParams.h"

#define  MAX_POINT_COUNT 10000

namespace TA_Base_App
{
	DatapointPollingWorker::DatapointPollingWorker(ModbusPointManager* pointMgr)
		:
		m_scheduleId(INVALID_TIMER_ID),
		m_interval(500),
		m_dllPath("E:\\CPlusPlus\\QT\\RTDUTest\\RTDUTest\\dll\\"),
		m_iniPath("E:\\CPlusPlus\\QT\\RTDUTest\\RTDUTest\\dll\\"),
		m_pointManager(pointMgr)
	{
		if (RunParams::getInstance().isSet("RtduPollingInterval"))
			m_interval = std::stoi(RunParams::getInstance().get("RtduPollingInterval").c_str());

		if (RunParams::getInstance().isSet("RtduDllPath"))
			m_dllPath = RunParams::getInstance().get("RtduDllPath");

		if (RunParams::getInstance().isSet("RtduIniPath"))
			m_iniPath = RunParams::getInstance().get("RtduIniPath");
		
		if (RunParams::getInstance().isSet("StartWord"))
		{
			m_startWord = atoi(RunParams::getInstance().get("StartWord").c_str());
		}

		m_veStore = new VeStore();

		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Init RTDU Connect..., dllPath: %s, iniPath: %s", m_dllPath.c_str(), m_iniPath.c_str());
		m_veStore->initConnect(m_dllPath, m_iniPath);
		//initRTDU();

		m_thdScheduleTimer.activate();
	}


	DatapointPollingWorker::~DatapointPollingWorker()
	{
		m_thdScheduleTimer.deactivate();
		m_thdScheduleTimer.wait();
	}

	/*void DatapointPollingWorker::initRTDU()
	{
		char* strParameters[4] = { (char*)m_dllPath.data(), (char*)m_iniPath.data(), (char*)"", (char*)"" };
		int nResult = InitConnect(strParameters, 1);
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Init RTDU Connect, dllPath: %s, iniPath: %s", m_dllPath.c_str(), m_iniPath.c_str());
	}*/

	void DatapointPollingWorker::startPollingJob(const vector<string>& nameList)
	{
		ScheduleParameter* scheduleParameter = new ScheduleParameter();
		scheduleParameter->nameList = nameList;

		ACE_Time_Value atmScheduleTime = ACE_OS::gettimeofday() + ACE_Time_Value(2, 0);			//start execute time by sceond
		ACE_Time_Value atmIntervalTime(0, m_interval * 1000);			//interval time by second

		m_scheduleId = m_thdScheduleTimer.schedule(this, static_cast<void*>(scheduleParameter), atmScheduleTime, atmIntervalTime);

		//LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Ace Timer scheduled polling: %s, timer id: %d, interval: %d ms", nameList.c_str(), m_scheduleId, m_interval);
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Ace Timer scheduled polling, timer id: %d, interval: %d ms", m_scheduleId, m_interval);
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

		//std::string nameList = scheduleParameter->nameList;
		//LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Execute schedule polling : %s", nameList.c_str());

		/*const char delim = ';';
		std::vector<std::string> svec;
		CommonFunction::tokenize(nameList, delim, svec);*/

		try
		{
			int nCount = scheduleParameter->nameList.size();
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Start to poll RTDU datapoint, count=%d", nCount);
			/*char** tagNames = CommonFunction::vector2StringArray(scheduleParameter->nameList);
			TagData* pTagData = new TagData[nCount];*/

			TagData *pTagData;
			char *tagNames[MAX_POINT_COUNT];
			int i = 0;
			for (i = 0; i < nCount; i++)
			{
				tagNames[i] = (char*)malloc(48 * sizeof(char));
				memset(tagNames[i], 0, 48);
				CString strTagName = scheduleParameter->nameList[i].c_str();
				strcpy(tagNames[i], (LPSTR)(LPCTSTR)strTagName);
			}
			pTagData = (TagData*)malloc(nCount * sizeof(TagData));
			int nResult = m_veStore->getRTDataByBatch(tagNames, pTagData, nCount);			//call batch datapoint api
			//int nResult = 0;				//for localtest
			if (nResult != 0)
			{
				LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Failed to poll RTDU datapoint, result=%d", nResult);
				//ReleaseConnect();
			}
			else
			{
				PointValueVector valueVec;
				for (int i = 0; i < nCount; i++)
				{
					TA_Base_Bus::PointValueStruct value;
					PointAddress address(m_startWord + i, 0);
					value.m_address = address;
					value.m_size = 16;
					value.m_value = pTagData[i].value;
					value.m_Dblvalue = pTagData[i].value;			//m_Dblvalue is not used in Modbus server library
					value.m_value = 20;		//for localtest
					value.m_Dblvalue = 51.12;	//for localtest
					valueVec.push_back(value);
				}
				m_pointManager->submitUpdateData(&valueVec);
				m_pointManager->updateDataInitialized();
				LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Update modbus server data successfully");
			}
			//delete[] tagNames;
			//delete pTagData;
			free(pTagData);
			for (i = 0; i < nCount; i++)
			{
				free(tagNames[i]);
			}
		}
		catch (...)
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "Failed to execute polling");
			return 0;
		}

		return 0;
	}
}