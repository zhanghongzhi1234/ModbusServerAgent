/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/WXL3_TIP/TA_BASE/transactive/core/synchronisation/src/ReEntrantThreadLockable.cpp $
  * @author:  Robert Young
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2019/02/22 15:17:48 $
  * Last modified by:  $Author: lim.cy $
  *
  * Implementation of the IThreadLockable interface that allows the same thread to acquire the
  * lock multiple times (i.e. consecutively). A count of consecutive acquisitions by the same
  * thread is maintained, with the lock only being released when the equivalent number of calls
  * to release() are made.
  *
  * This lock should not be acquired directly, but managed using a temporary object (i.e.
  * ThreadGuard) which ensures the lock is acquired during construction, and subsequently
  * released during destruction.
  *
  * Note, this class wrappers the omni_mutex class, which in turn wrappers the OS-specific
  * threading API.
  *
  * NOTE: Condition is made a friend class so it can access backupReEntrantAcquisitionState() and
  * restoreReEntrantAcquisitionState(). This is necessary to allow Condition to backup and
  * restore the state before and after calling wait() or timedWait() on it's omni_condition.
  * Such backup and restore is needed as the linked omni_mutex (wrappered by this class) is intrinisically
  * released and reacquired at these times by the omni_condition. By allowing Condition to wrapper
  * the omni_condition's linked omni_mutex with this class, it can offer re-entrant access of the
  * mutex to it's clients.
  */

#include "ReEntrantThreadLockable.h"
#include "ThreadLockableHolderVerifier.h"
#include "../Utilities/TAAssert.h"

#include <omnithread.h>

namespace TA_Base_Core
{
	//
	// Default Constructor
	//
	ReEntrantThreadLockable::ReEntrantThreadLockable()
		: m_numTimesThreadAcquiredLock(0),
		m_lock(new omni_mutex),
		m_threadLockableHolderVerifier(new ThreadIdWrapper),
		m_previousNumTimesThreadAcquiredLock(0),
		m_previousThreadLockableHolderVerifier(new ThreadIdWrapper)
	{
	}


	//
	// Constructor from existing omni_mutex.
	//
	ReEntrantThreadLockable::ReEntrantThreadLockable(omni_mutex* mutex)
		: m_numTimesThreadAcquiredLock(0),
		m_lock(mutex),
		m_threadLockableHolderVerifier(new ThreadIdWrapper),
		m_previousNumTimesThreadAcquiredLock(0),
		m_previousThreadLockableHolderVerifier(new ThreadIdWrapper)
	{
	}


	//
	// Destructor
	//
	ReEntrantThreadLockable::~ReEntrantThreadLockable()
	{
		delete m_lock;
		delete m_threadLockableHolderVerifier;
		delete m_previousThreadLockableHolderVerifier;
	}


	//
	// acquire
	//
	void ReEntrantThreadLockable::acquire()
	{
		// (ReEntrant) If the thread has currently acquired this lock already, increment the count and 
		// return without passing call onto the mutex.
		if ((0 < m_numTimesThreadAcquiredLock) && (m_threadLockableHolderVerifier->isCurrentThreadId()))
		{
			m_numTimesThreadAcquiredLock++;
			return;
		}

		m_lock->acquire();

		// Thread has acquired lock so set as current lock holder and set count to 1.
		m_threadLockableHolderVerifier->setCurrentThreadId();
		m_numTimesThreadAcquiredLock = 1;
	}


	//
	// release
	//
	void ReEntrantThreadLockable::release()
	{
        TA_ASSERT( ( 0 != m_numTimesThreadAcquiredLock ), "Call made to release while lock not currently acquired." );

		// Decrement the count.
		m_numTimesThreadAcquiredLock--;

		// If the count is now back to 0, release the mutex.
		if (0 == m_numTimesThreadAcquiredLock)
		{
			m_lock->release();
		}
	}


	////////////////////////////////////////////////////////////////////////////////
	//// Private methods to allow friend class Condition to offer its           ////
	//// linked mutex to client code wrappered in re-entrant access. These      ////
	//// methods allow Condition to backup and restore the re-entrant           ////
	//// lock acquisition state. Condition needs to backup just before calling  ////
	//// wait or timedWait on its wrappered omni_condition, and restore just    ////
	//// after the wait completes. This is because the associated mutex is      ////
	//// intrinisically released just before entering wait and intrinisically   ////
	//// re-acquired directly afterwards. The period inbetween allows           ////
	//// competing thread to acquire and release the lock and hence modify the  ////
	//// re-entrant acquisition state.                                          ////
	////////////////////////////////////////////////////////////////////////////////


	//
	// backupReEntrantAcquisitionState
	//
	void ReEntrantThreadLockable::backupReEntrantAcquisitionState()
	{
		*m_previousThreadLockableHolderVerifier = *m_threadLockableHolderVerifier;
		m_previousNumTimesThreadAcquiredLock = m_numTimesThreadAcquiredLock;
	}


	//
	// restoreReEntrantAcquisitionState
	//
	void ReEntrantThreadLockable::restoreReEntrantAcquisitionState()
	{
		// !! The order is important here - should always set identity of lockholder
		// before indicating it is indeed acquired by setting count !!
		*m_threadLockableHolderVerifier = *m_previousThreadLockableHolderVerifier;
		m_numTimesThreadAcquiredLock = m_previousNumTimesThreadAcquiredLock;
	}
}
