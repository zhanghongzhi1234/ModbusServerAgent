#ifndef MODBUS_POINT_MANAGER_H
#define MODBUS_POINT_MANAGER_H

#include "../Synchronisation/ReEntrantThreadLockable.h"
#include "../synchronisation/Semaphore.h"
#include "../Threads/LFThreadPoolManager.h"

//#include "core/data_access_interface/src/ModbusServerPointAccessFactory.h"
//#include "core/data_access_interface/src/IModbusServerPoint.h"
//#include "core/data_access_interface/entity_access/src/ModbusServerAgentEntityData.h"
#include "../ModbusComms/ModbusService.h"
//#include "core/data_access_interface/src/IModbusServerAnaloguePoint.h"

#include "DatapointPollingWorker.h"
#include <queue>

using namespace TA_Base_Bus;
namespace TA_Base_App
{
	class ModbusPointData
	{
	public:
		unsigned long	m_pKey; //entitykey
		PointAddress*	m_address;
		unsigned long	m_size;		//must be one of (1, 16, 32). other values will be invalid.
		unsigned int	m_port;
	};

	class ModbusPointManager
	{
	public:
		ModbusPointManager(std::string port, unsigned int startWord, unsigned int length, unsigned long peersocketTimeout);
		virtual ~ModbusPointManager();
		void startSynchronise(std::string& namelist);
		void stopSynchronise();

		void createPollingWorker();
		void submitUpdateData(PointValueVector* updateData);
		void processData(PointValueVector* updateData);
		void updateDataInitialized();

	private:

		TA_Base_Bus::ModbusService*	m_modbusService;
		std::string m_port;
		unsigned int m_startWord;
		unsigned int m_length;
		unsigned long m_peersocketTimeout;

		DatapointPollingWorker*	m_pollingWorker;

		TA_Base_Core::ReEntrantThreadLockable		m_checkFirstUpdateLock;
		bool 	m_bFirstUpdateAllFinished;
		TA_Base_Core::LFThreadPoolManager*			m_ThreadPoolManager;

	};

	class ProcessUpdateWorkItem : public TA_Base_Core::IThreadPoolExecuteItem
	{
	public:
		ProcessUpdateWorkItem(ModbusPointManager* manager, PointValueVector* updateData);
		void executeWorkItem();
	private:
		ModbusPointManager*				m_manager;
		PointValueVector*			m_datapointUpdates;
	};
}
#endif
