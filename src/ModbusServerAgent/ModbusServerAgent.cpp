#include "Commonfunction.h"
#include "ModbusServerAgent.h"
#include "ace/Object_Manager.h"
#include "../Utilities/DebugSETranslator.h"
#include "../Utilities/DebugUtilInit.h"
#include "../Utilities/RunParams.h"
#include "../Exceptions/InvalidCommandLineException.h"

using TA_Base_Core::DebugUtil;
using TA_Base_Core::RunParams;

namespace TA_Base_App
{
	ModbusServerAgent::ModbusServerAgent(int argc, char* argv[]) 
		: m_toTerminate(false)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "ModbusServerAgent started");

		RunParams::getInstance().set(RPARAM_ENTITYNAME, "ModbusServerAgent");

		initialiseUtilities(argc, argv);
		
		 getNameListFromFile("TagName.csv", m_nameList);
		/*m_nameList = "";
		if (RunParams::getInstance().isSet("NameList"))
		{
			m_nameList = RunParams::getInstance().get("NameList");
		}*/

		ACE_Object_Manager::instance()->init();
		createModbusManager();
		//Thread::sleep(2000);
		//startSynchronise(m_nameList);
	}

	bool ModbusServerAgent::getNameListFromFile(const std::string& fileName, vector<string>& output)
	{
		vector<string> vecStr;
		if (CommonFunction::readFileToVectorString(fileName, vecStr))
		{
			vector<string>::iterator it = vecStr.begin();
			for (; it != vecStr.end(); it++)
			{
				if (*it != "")
				{
					vector<string> vecLine = CommonFunction::stringToVector(*it, ",");
					string tagName = vecLine[0];
					output.push_back(tagName);
				}
			}
		}
		else
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "read namelist file fail: %s", fileName);
			return false;
		}
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

	void ModbusServerAgent::terminate()
	{
		m_toTerminate = true;
		stopSynchronise();
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "ModbusServerAgent::terminate()");
	}


	void ModbusServerAgent::run()
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "ModbusServerAgent in run()");
		std::string nameList = "Datapoint_Name1";
		startSynchronise(m_nameList);
		while (!m_toTerminate)
		{
			//processRequest();
		}
		m_toTerminate = true;
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "ModbusServerAgent finished run()");
	}

	void ModbusServerAgent::createModbusManager()
	{
		m_ModbusPointManager = new ModbusPointManager("502", 0, m_nameList.size(), 2000);
		if (NULL == m_ModbusPointManager)
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "Failure to create ModbusPointManager object.");
			return;
		}
		else
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Created ModbusPointManager.");
		}
		m_ModbusPointManager->createModbusService();
		m_ModbusPointManager->createPollingWorker();
	}

	void ModbusServerAgent::startSynchronise(vector<string>& namelist)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "StartSynchronise");
		m_ModbusPointManager->startSynchronise(namelist);
	}

	void ModbusServerAgent::stopSynchronise()
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "StopSynchronise");
		m_ModbusPointManager->stopSynchronise();
	}

	bool ModbusServerAgent::initialiseUtilities(int argc, char* argv[])
	{
		try
		{
			if (false == RunParams::getInstance().parseCmdLine(argc, argv))
			{
				if (RunParams::getInstance().isSet(RPARAM_VERSION))
				{
					// Versioning info printed to stdout. Not an exceptional condition,
					// but there's no need to continue.
					return false;
				}

				TA_THROW(TA_Base_Core::InvalidCommandLineException("Command line arguments are in invalid format"));
			}

			parseLocalConfigurationFile();
			gSetDebugUtilFromRunParams();
			gInitStructuredExceptionHandler();   // Only initialises the calling thread
		}
		catch (const TA_Base_Core::InvalidCommandLineException&)
		{
			throw; // Ensuring we only throw the exceptions listed in the documentation
		}
		catch (...)
		{
			TA_THROW(TA_Base_Core::BaseException("One or more utilities failed to initialise"));
		}

		return true;
	}

}
