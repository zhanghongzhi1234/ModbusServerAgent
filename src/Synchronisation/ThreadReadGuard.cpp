/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/WXL3_TIP/TA_BASE/transactive/core/synchronisation/src/ThreadReadGuard.cpp $
  * @author:  Andrew Del Carlo
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2019/02/22 15:17:48 $
  * Last modified by:  $Author: lim.cy $
  *
  * Implementation of the ThreadReadGuard class
  *
  */

#include "ThreadReadGuard.h"
#include "../Utilities/DebugUtil.h"

namespace TA_Base_Core
{
	//
	// Constructor
	//
	ThreadReadGuard::ThreadReadGuard(IThreadLockable& lockable, bool log)
		: m_lockable(lockable), m_log(log)
	{
		if (m_log)
		{
			LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugTrace,
				"ThreadReadGuard: Attempting lock acquire, address %lx", (unsigned long)&m_lockable);
		}

		m_lockable.acquireRead();

		if (m_log)
		{
			LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugTrace,
				"ThreadReadGuard: Acquired lock, address %lx", (unsigned long)&m_lockable);
		}
	}

	//
	// Destructor
	//
	ThreadReadGuard::~ThreadReadGuard()
	{
		if (m_log)
		{
			LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugTrace,
				"ThreadReadGuard: Releasing lock, address %lx", (unsigned long)&m_lockable);
		}

		m_lockable.releaseRead();
	}

} // namespace TA_Base_Core
