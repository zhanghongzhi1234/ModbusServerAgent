#ifndef LFThreadPoolWorker_H
#define LFThreadPoolWorker_H

#include "../Synchronisation/ReEntrantThreadLockable.h"
#include "../Synchronisation/Semaphore.h"
#include "Thread.h"

#include "IThreadPoolBase.h"

namespace TA_Base_Core
{
	class IThreadPoolWorkerCallback;
};

namespace TA_Base_Core
{
	class LFThreadPoolWorker : public Thread, public IListItem
	{
	public:

		LFThreadPoolWorker(ILFThreadPoolManager& callback);
		virtual ~LFThreadPoolWorker();

		virtual void run();
		virtual void terminate();


		void changeToLeader();

	private:

		LFThreadPoolWorker();

		void doLeaderWorker();

		volatile bool m_threadRunning;
		ReEntrantThreadLockable m_lock;
		Semaphore m_semaphore;
		ILFThreadPoolManager& m_callback;
	};
};

#endif
