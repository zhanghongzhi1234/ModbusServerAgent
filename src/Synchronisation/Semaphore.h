#ifndef SEMAPHORE_H_INCLUDED
#define SEMAPHORE_H_INCLUDED


class omni_semaphore;

namespace TA_Base_Core
{
	class Semaphore
	{
	public:
		/**
		  * Semaphore
		  *
		  * Construct a new semaphore object
		  *
		  * @param initial	the initial count. Set to zero if you want the semaphore to
		  *						block on the first call to wait
		  */
		Semaphore(unsigned int initial = 1);

		/**
		  * ~Semaphore
		  *
		  * semaphore desctructor
		  */
		virtual ~Semaphore();

		/**
		  * wait
		  *
		  * wait (and block) for the semaphore to be signalled, or continue if already signalled
		  *
		  * ie: If semaphore value is > 0 then decrement it and carry on. If it's
		  * already 0 then block.
		  */
		void wait(void);

		/**
		  * trywait
		  *
		  * test to see if the semaphore will block on wait. This allows your thread to do something
		  * else while it waits for a signal.
		  *
		  * ie: if semaphore value is > 0 then decrement it and return true.
		  * If it's already 0 then return false.
		  *
		  * @return bool	false if the semaphore will block
		  */
		bool tryWait(void);

		/**
		  * post
		  *
		  * if any threads are blocked in wait(), wake one of them up. Otherwise
		  * increment the value of the semaphore.
		  *
		  * @param void
		  */
		void post(void);

	private:

		//
		// Disable the default copy and assignment constructors as shouldn't used.
		//
		Semaphore(const Semaphore&);
		Semaphore& operator=(const Semaphore&);


		/**
		* The underlying semaphore implementation
		*/
		omni_semaphore* m_semaphore;
	};
}

#endif // SEMAPHORE_H_INCLUDED

