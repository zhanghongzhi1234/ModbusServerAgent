#include "ModbusPointManager.h"
#include "../Utilities/RunParams.h"
#include "../ModbusComms/ModbusService.h"


namespace TA_Base_App
{
	ModbusPointManager::ModbusPointManager(std::string port, unsigned int startWord, unsigned int length, unsigned long peersocketTimeout)
		:
		m_port(port),
		m_startWord(startWord),
		m_length(length),
		m_peersocketTimeout(peersocketTimeout),
		m_bFirstUpdateAllFinished(false)
		//m_ThreadPoolManager(NULL)
	{
		try
		{
			if (RunParams::getInstance().isSet("Port"))
			{
				m_port = RunParams::getInstance().get("Port");
			}
			if (RunParams::getInstance().isSet("StartWord"))
			{
				m_startWord = atoi(RunParams::getInstance().get("StartWord").c_str());
			}
			/*if (RunParams::getInstance().isSet("Length"))
			{
				m_length = atoi(RunParams::getInstance().get("Length").c_str());			//length will decide by NameList.csv file datapoint size
			}*/
			if (RunParams::getInstance().isSet("PeersocketTimeout"))
			{
				m_peersocketTimeout = atol(RunParams::getInstance().get("PeersocketTimeout").c_str());
			}
		}
		catch (... )
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugError, "Wrong config file!");
		}

		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "ModbusPointManager init(port=%s, startWorld=%d, length=%d, socketTimeout=%d)", m_port.c_str(), m_startWord, m_length, m_peersocketTimeout);

		// set peersocketTimeout to 2s if parameter is not set between 1000 to 10000 ms
		if ((m_peersocketTimeout <= 100) || (m_peersocketTimeout >= 20000))
		{
			m_peersocketTimeout = 2000;
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Ignoring the input value. Setting PeerSocketTimeout to default [%u] ms for all listening ports.", m_peersocketTimeout);
		}
		else
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Setting PeerSocketTimeout to [%u] ms for all listening ports.", m_peersocketTimeout);
		}
		
		//m_ThreadPoolManager = new TA_Base_Core::LFThreadPoolManager();
	}

	ModbusPointManager::~ModbusPointManager()
	{
		m_pollingWorker->stopPollingJob();
		m_modbusService->terminateAndWait();
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "ModbusService stop");
		//delete m_ThreadPoolManager;

	}

	void ModbusPointManager::createPollingWorker()
	{
		m_pollingWorker = new DatapointPollingWorker(this);
	}

	void ModbusPointManager::createModbusService()
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "In ModbusPointManager::createModbusService...");
		m_modbusService = new TA_Base_Bus::ModbusService(m_port, m_startWord, m_length, m_peersocketTimeout);
		m_modbusService->start();
	}

	void ModbusPointManager::submitUpdateData(PointValueVector* updateData)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "In ModbusPointManager::submitUpdateData()");
		m_modbusService->setData(*updateData);
		{
			//TA_Base_Core::ThreadGuard guard( m_queueLock );
			//m_pointsUpdates.push(updateData);
		}
		//ProcessUpdateWorkItem* updateItem = new ProcessUpdateWorkItem(this, updateData);
		//m_ThreadPoolManager->queueWorkItem(updateItem);
		//m_queueSemaphore.post();
	}

	void ModbusPointManager::startSynchronise(vector<string>& namelist)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Start Modbus Service...");
		//m_modbusService->start();
		//LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Start Polling worker(%s)", namelist.c_str());
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Start Polling worker");
		m_pollingWorker->startPollingJob(namelist);
		//TA_Base_Core::Thread::sleep(2000);
	}

	void ModbusPointManager::stopSynchronise()
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Stop Polling Job");
		m_pollingWorker->stopPollingJob();
		//LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Terminating ModbusService", m_port);
		//m_modbusService->terminateAndWait();
	}

	void ModbusPointManager::processData(PointValueVector* updateData)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "In ModbusPointManager::processData()");
		if (m_modbusService == NULL)
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugWarn, "Modbus service is unavailable");
		}
		else
		{
			m_modbusService->setData(*updateData);
			LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "No of items in service buffers");
		}
	}

	//first time run need call this
	void ModbusPointManager::updateDataInitialized()
	{
		m_bFirstUpdateAllFinished = true;
		m_modbusService->setDataInitialized();
	}

	/*ProcessUpdateWorkItem::ProcessUpdateWorkItem(ModbusPointManager* manager, PointValueVector* updateData)
		:
		m_manager(manager),
		m_datapointUpdates(updateData)
	{
	}

	void ProcessUpdateWorkItem::executeWorkItem()
	{
		m_manager->processData(m_datapointUpdates);
		delete m_datapointUpdates;
	}*/

}
