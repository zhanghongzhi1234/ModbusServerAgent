#if !defined(ITHREADLOCKABLE_H__INCLUDED_)
#define ITHREADLOCKABLE_H__INCLUDED_


namespace TA_Base_Core
{
	class IThreadLockable
	{

	public:

		/**
		  * acquire
		  *
		  * Acquire the lock.
		  *
		  */
		virtual void acquire() = 0;


		/**
		  * acquireRead
		  *
		  * Acquire the read lock.
		  *
		  * This function will be overridden by those
		  * drived classes that support read locks
		  */
		virtual void acquireRead();


		/**
		  * release
		  *
		  * Release the lock.
		  *
		  * PreCondition: This IThreadLockable is currently acquired.
		  */
		virtual void release() = 0;


		/**
		  * release
		  *
		  * Release the lock.
		  *
		  * PreCondition: This IThreadLockable is currently acquired.
		  */
		virtual void releaseRead();


		/**
		  * Destructor
		  */
		virtual ~IThreadLockable() { };
	};
} // namespace TA_Base_App

#endif // !defined(ITHREADLOCKABLE_H__INCLUDED_)
