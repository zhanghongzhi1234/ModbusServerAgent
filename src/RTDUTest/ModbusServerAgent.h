#ifndef MODBUS_SERVER_AGENT_H
#define MODBUS_SERVER_AGENT_H

#include "ModbusPointManager.h"

namespace TA_Base_App
{
	class ModbusServerAgent
	{
	public:
		ModbusServerAgent();
		~ModbusServerAgent();

		void startSynchronise(std::string& namelist);
		void stopSynchronise();
	private:
		void createModbusManager();

		ModbusPointManager* m_ModbusPointManager;
	};
}

#endif