
#if defined(_MSC_VER)
#pragma warning(disable:4503)
#endif // _MSC_VER

#include "ModbusServerAgent.h"
#include "ace/OS.h"
#include "../Utilities/DebugUtil.h"
#include "../Utilities/RunParams.h"
#include "../Exceptions/GenericAgentException.h"

using TA_Base_Core::DebugUtil;
using TA_Base_Core::RunParams;
using TA_Base_Core::GenericAgentException;

int main(int argc, char* argv[])
{
	try
	{
		TA_Base_App::ModbusServerAgent agent(argc, argv);
		agent.run();
		//delete agent;
	}
	catch (const GenericAgentException& gae)
	{
		LOG(SourceInfo, DebugUtil::ExceptionCatch,
			"GenericAgentException", gae.what());
	}

	return 0;
}
