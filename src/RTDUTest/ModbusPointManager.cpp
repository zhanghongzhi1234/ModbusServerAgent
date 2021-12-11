#include "ModbusPointManager.h"
//#include "../Exceptions/DataException.h"
#include "../Utilities/RunParams.h"

//#include "core/data_access_interface/src/ModbusServerPointAccessFactory.h"
#include "../ModbusComms/ModbusService.h"

//using TA_Base_Core::DebugUtil;

namespace TA_Base_App
{
	ModbusPointManager::ModbusPointManager(std::string port, unsigned int startWord, unsigned int length, unsigned long peersocketTimeout)
		:
		m_port(port),
		m_startWord(startWord),
		m_length(length),
		m_peersocketTimeout(peersocketTimeout),
		m_bFirstUpdateAllFinished(false),
		m_ThreadPoolManager(NULL)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "ModbusPointManager init(port=%s, startWorld=%s, length=%s, socketTimeout=%s)", m_port, m_startWord, m_length, m_peersocketTimeout);
		// set peersocketTimeout to 2s if parameter is not set between 1000 to 10000 ms
		//m_peersocketTimeout = atol(peersocketTimeout.c_str());

		if ((m_peersocketTimeout <= 100) || (m_peersocketTimeout >= 20000))
		{
			m_peersocketTimeout = 2000;
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Ignoring the input value. Setting PeerSocketTimeout to default [%u] ms for all listening ports.", m_peersocketTimeout);
		}
		else
		{
			LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Setting PeerSocketTimeout to [%u] ms for all listening ports.", m_peersocketTimeout);
		}
		
		m_ThreadPoolManager = new TA_Base_Core::LFThreadPoolManager();
	}

	ModbusPointManager::~ModbusPointManager()
	{
		m_pollingWorker->stopPollingJob();
		m_modbusService->terminateAndWait();
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "ModbusService stop");
		delete m_ThreadPoolManager;

	}

	void ModbusPointManager::createPollingWorker()
	{
		m_pollingWorker = new DatapointPollingWorker(this);
	}


	void ModbusPointManager::submitUpdateData(PointValueVector* updateData)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "In ModbusPointManager::submitUpdateData()");
		{
			//TA_Base_Core::ThreadGuard guard( m_queueLock );
			//m_pointsUpdates.push(updateData);
		}
		ProcessUpdateWorkItem* updateItem = new ProcessUpdateWorkItem(this, updateData);
		m_ThreadPoolManager->queueWorkItem(updateItem);
		//m_queueSemaphore.post();
	}

	void ModbusPointManager::startSynchronise(std::string& namelist)
	{
		m_modbusService = new TA_Base_Bus::ModbusService(m_port, m_startWord, m_length, m_peersocketTimeout);
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "In ModbusPointManager::startModbusService");

		m_pollingWorker->startPollingJob(namelist);
		TA_Base_Core::Thread::sleep(22000);

		m_modbusService->start();
	}

	void ModbusPointManager::stopSynchronise()
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "In ModbusPointManager::stopSynchronise()");
		LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Terminating ModbusService", m_port);
		m_modbusService->terminateAndWait();
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

	ProcessUpdateWorkItem::ProcessUpdateWorkItem(ModbusPointManager* manager, PointValueVector* updateData)
		:
		m_manager(manager),
		m_datapointUpdates(updateData)
	{
	}

	void ProcessUpdateWorkItem::executeWorkItem()
	{
		m_manager->processData(m_datapointUpdates);
		delete m_datapointUpdates;
	}
}
