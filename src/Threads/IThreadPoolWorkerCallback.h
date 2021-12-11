#ifndef THREADPOOLWORKER_CALLBACK_H
#define THREADPOOLWORKER_CALLBACK_H


namespace TA_Base_Core
{

	class IThreadPoolWorkerCallback
	{

	public:

		virtual ~IThreadPoolWorkerCallback() {};

		/**
		*
		* workerFree
		*
		* This is called by a worker when it becomes free
		*
		*/
		virtual void workerFree() = 0;
	};

}

#endif
