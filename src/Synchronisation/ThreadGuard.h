#ifndef THREADGUARD_H_INCLUDED
#define THREADGUARD_H_INCLUDED


#include "../Synchronisation/IThreadLockable.h"

#if !defined (TA_THREADGUARD)

#define TA_NAMED_THREADGUARD(threadlockable, guardName) \
	LOG(SourceInfo, \
		TA_Base_Core::DebugUtil::GenericLog, \
		TA_Base_Core::DebugUtil::DebugTrace, \
		"ThreadGuard: Attempting to acquire guard %s for lock %s", \
		#guardName , #threadlockable ); \
        TA_Base_Core::ThreadGuard guardName(threadlockable, true);

#define TA_THREADGUARD_NAME(prefix, suffix) prefix ## suffix

#define TA_THREADGUARD(threadlockable) TA_NAMED_THREADGUARD(threadlockable, TA_THREADGUARD_NAME(threadlockable, ThreadGuard))

#endif

namespace TA_Base_Core
{
	class ThreadGuard
	{
	public:

        /** 
          * Constructor
          *
          * Constructs ThreadGuard object, automatically acquiring the 
          * IThreadLockable object passed to it.
          *
          * @param &IThreadLockable - The IThreadLockable this ThreadGuard
          *                           is to acquire/release    
          */
		ThreadGuard( IThreadLockable& lockable, bool log = false );

		
        /** 
          * Destructor
          *
          * Automatically releases the IThreadLockable this ThreadGuard was
          * constructed with.
          *
          */
        virtual ~ThreadGuard();


        /** 
          * acquire
          *
          * Acquire the lock.
          *
          */
		inline void acquire()
    	{
        	m_lockable.acquire();
    	}

        /** 
          * release
          *
          * Release the lock.
          * 
          */
		inline void release()
    	{
        	m_lockable.release();
    	}

	private:

        //
        // Disable the default copy and assignment constructors as shouldn't used.
        //
        ThreadGuard( const ThreadGuard& );
        ThreadGuard& operator=( const ThreadGuard& );


		IThreadLockable& m_lockable;    // Reference to IThreadLockable this object 
		bool m_log;
	};
} // namespace TA_Base_Core

#endif // THREADGUARD_H_INCLUDED

