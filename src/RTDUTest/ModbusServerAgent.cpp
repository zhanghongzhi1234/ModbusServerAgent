#include "ModbusServerAgent.h"
#include "ace/Object_Manager.h"

namespace TA_Base_App
{
	ModbusServerAgent::ModbusServerAgent()
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "ModbusServerAgent started");
		ACE_Object_Manager::instance()->init();
		createModbusManager();
	}


	ModbusServerAgent::~ModbusServerAgent()
	{
		if (NULL != m_ModbusPointManager)
		{
			//ModbusPointManager has data structures and threads to clear out hence better to wait for neat clean up
			delete m_ModbusPointManager;
			m_ModbusPointManager = NULL;
		}
	}

	void ModbusServerAgent::createModbusManager()
	{
		//ModbusPointManager(std::string port, std::string startWord, std::string length, std::string peersocketTimeout)
		m_ModbusPointManager = new ModbusPointManager("502", 0, 1000, 2000);
		if (NULL == m_ModbusPointManager)
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "Failure to create ModbusPointManager object.");
			return;
		}
		else
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Created ModbusPointManager.");
		}
		m_ModbusPointManager->createPollingWorker();
	}

	void ModbusServerAgent::startSynchronise(std::string& namelist)
	{
		m_ModbusPointManager->startSynchronise(namelist);
	}

	void ModbusServerAgent::stopSynchronise()
	{
		m_ModbusPointManager->stopSynchronise();
	}
}
