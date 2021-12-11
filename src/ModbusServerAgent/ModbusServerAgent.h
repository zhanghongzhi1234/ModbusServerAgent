#ifndef MODBUS_SERVER_AGENT_H
#define MODBUS_SERVER_AGENT_H

#include "ModbusPointManager.h"
#include "../Threads/Thread.h"
#include <vector>

using namespace std;

namespace TA_Base_App
{
	class ModbusServerAgent : public TA_Base_Core::Thread
	{
	public:
		ModbusServerAgent(int argc, char* argv[]);
		~ModbusServerAgent();

		virtual void	run();
		virtual void	terminate();

		void startSynchronise(vector<string>& namelist);
		void stopSynchronise();
	private:
		void createModbusManager();
		bool initialiseUtilities(int argc, char* argv[]);
		bool getNameListFromFile(const std::string& fileName, vector<string>& output);

		ModbusPointManager* m_ModbusPointManager;
		vector<string> m_nameList;

		volatile bool			m_toTerminate;
	};
}

#endif