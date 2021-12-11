/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/WXL3_TIP/TA_BASE/transactive/core/synchronisation/src/ThreadGuard.cpp $
  * @author:  B Fountain
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2019/02/22 15:17:48 $
  * Last modified by:  $Author: lim.cy $
  * 
  * Implementation of the ThreadGuard class
  *
  */

#include "../Synchronisation/ThreadGuard.h"
#include "../Utilities/DebugUtil.h"

namespace TA_Base_Core
{
    //
    // Constructor
    //
    ThreadGuard::ThreadGuard( IThreadLockable& lockable, bool log )
		: m_lockable(lockable), m_log (log)
	{
		
		if (m_log)
		{
			LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugTrace,
				"ThreadGuard: Attempting lock acquire, address %lx", (unsigned long)&m_lockable);
		}

		m_lockable.acquire();
					
		if (m_log)
		{
			LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugTrace,
				"ThreadGuard: Acquired lock, address %lx", (unsigned long)&m_lockable);
		}
	}


    //
    // Destructor
    //
	ThreadGuard::~ThreadGuard()
	{
		if (m_log)
		{
			LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugTrace,
				"ThreadGuard: Releasing lock, address %lx", (unsigned long)&m_lockable);
		}

		m_lockable.release();
	}

} // namespace TA_Base_Core
