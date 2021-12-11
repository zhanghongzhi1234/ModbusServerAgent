#include "FunctionEntry.h"
#include "DebugUtil.h"

using TA_Base_Core::DebugUtil;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace TA_Base_Core
{

	FunctionEntry::FunctionEntry(const char* functName, char* file, int line)
		: m_line(-1), m_file(file), m_functName(functName)
	{
		DebugUtil::getInstance().log(file, line, DebugUtil::FunctionEntry, m_functName.c_str());
	}


	FunctionEntry::~FunctionEntry()
	{
		DebugUtil::getInstance().log(m_file, m_line, DebugUtil::FunctionExit, m_functName.c_str());
	}

} // namespace TA_Base_Core
