#ifndef HAHSLFThreadPoolManager_H
#define HAHSLFThreadPoolManager_H

#include <vector>

#include "../Synchronisation/ReEntrantThreadLockable.h"
#include "../Synchronisation/Semaphore.h"
#include "Thread.h"

#include "IThreadPoolBase.h"
#include "./LFThreadPoolWorker.h"

namespace TA_Base_Core
{
	class ThreadedWorker;
};

namespace TA_Base_Core
{
	class LFThreadPoolManager : public ILFThreadPoolManager
	{
	public:

		LFThreadPoolManager(unsigned long numThreads = 30, bool autoStart = true);

		virtual ~LFThreadPoolManager();

		//
		// Operations specific to LFThreadPoolManager
		//

		/**
		*
		* queueWorkItem
		*
		* Queue the specified IThreadPoolExecuteItem for processing by a thread in the thread pool
		* and return immediately
		*
		* @param	IThreadPoolExecuteItem	The work item to be processed by a thread
		*
		*/
		void queueWorkItem(IThreadPoolExecuteItem* workItem);
		void queueWorkItemList(std::vector<IThreadPoolExecuteItem*>& WorkItemList);


		/**
		*
		* removeWorkItem
		*
		* Remove the specified IThreadPoolExecuteItem so that it is no longer processed by a thread
		* in the thread pool.  This will block until the specified IThreadPoolExecuteItem is successfully
		* removed from the ThreadPool.
		*
		* @param	IThreadPoolExecuteItem	The work item to be processed by a thread
		*
		*/
		void removeWorkItem(IThreadPoolExecuteItem* workItem);

		virtual void start();
		/**
		  * getNumberOfThreads
		  *
		  * @return the current thread pool size
		  */
		unsigned long getNumberOfThreads();

		/* IThreadPoolWorkerCallback implementation
		 * called by worker threads */

		 /**
		 *
		 * workerFree
		 *
		 * This is called by a worker when it becomes free
		 *
		 */
		virtual void workerFree(IListItem* worker);


		/**
		*
		* The following methods provides statistics
		*/
		long getQueueSize(void);

	protected:

		IThreadPoolExecuteItem* leaderExecuteItem();

		void setNewLeader();

		void cleanUp();

	private:

		LFThreadPoolManager(const LFThreadPoolManager & theInstance);
		LFThreadPoolManager & operator= (const LFThreadPoolManager & rhs);

	protected:

		Semaphore								m_semaphore;
		ReEntrantThreadLockable					m_workItemListLock;
		ReEntrantThreadLockable					m_workerListLock;
		volatile bool							m_threadRunning;

		std::vector < LFThreadPoolWorker * >		m_threadWorkerList;

		volatile unsigned long                  m_currentSize;
		volatile bool							m_isLeaderSet;


		DuLinkList								m_itemList;
		SgLinkList								m_workerList;
	};
};

#endif
