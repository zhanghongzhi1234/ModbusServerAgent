#include "LFThreadPoolWorker.h"
#include "../Utilities/DebugUtil.h"
#include "../Synchronisation/ThreadGuard.h"

#include "IThreadPoolWorkerCallback.h"

namespace TA_Base_Core
{

	LFThreadPoolWorker::LFThreadPoolWorker(ILFThreadPoolManager& callback)
		:
		m_threadRunning(true),
		m_callback(callback),
		m_semaphore(0)	//zn++
	{

	}


	LFThreadPoolWorker::~LFThreadPoolWorker()
	{
		//
		// stop the background task if the flag indicates that the thread has been
		// started
		//

		if (THREAD_STATE_RUNNING == getCurrentState())
		{
			terminateAndWait();
		}

	}


	void LFThreadPoolWorker::terminate()
	{
		// set the flag to indicate the thread is not supposed to be running anymore
		m_threadRunning = false;

		// notify the running thread to break the thread loop
		m_semaphore.post();
	}


	void LFThreadPoolWorker::run()
	{
		// tell the callback it can give some work
		m_callback.workerFree(this);

		// wait here until m_semaphore.post() is called
		m_semaphore.wait();

		while (true == m_threadRunning)
		{
			// process the queued work item now
			doLeaderWorker();

			// wait here until m_semaphore.post() is called
			m_semaphore.wait();
		}
	}


	void LFThreadPoolWorker::changeToLeader()
	{
		m_semaphore.post();
	}


	void LFThreadPoolWorker::doLeaderWorker()
	{
		IThreadPoolExecuteItem* item = m_callback.leaderExecuteItem();
		if (item)
		{
			try
			{
				item->executeWorkItem();
			}
			catch (const BaseException & te)
			{
				LOG_EXCEPTION_CATCH(SourceInfo, "BaseException", te.what());
			}
			catch (const std::exception & e)
			{
				LOG_EXCEPTION_CATCH(SourceInfo, "std::exception", e.what());
			}
			catch (...)
			{
				LOG_EXCEPTION_CATCH(SourceInfo, "Unknown Exception", "Caught unknown exception in LFThreadPoolManager::run");
			}

			// we need delete item, because no one knows when item finished.
			// oringal the workitem of ThreadPoolManager is using shared_ptr, no need care releasing,
			// but the workitem in these is using raw pointer.
			delete item;
			item = NULL;
		}
		m_callback.workerFree(this);
	}
}
