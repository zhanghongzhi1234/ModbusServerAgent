#ifndef GENERICLOGTYPE_H_INCLUDED
#define GENERICLOGTYPE_H_INCLUDED


#if defined( WIN32 )
#pragma warning( disable : 4786 )
#endif // defined( WIN32 )

#include <string>
#include <stdarg.h>
#include "ILogType.h"

  // Forward declaration

namespace TA_Base_Core
{
	class DebugUtil;
}


// Class Definition: GenericLogType

namespace TA_Base_Core
{
	class GenericLogType : public ILogType
	{
	public:

		/**
		  * GenericLogType
		  *
		  * Constructor
		  *
		  */
		GenericLogType() : ILogType(DebugUtil::GenericLog) {}

		/**
		  * ~GenericLogType
		  *
		  * Destructor
		  *
		  */
		virtual ~GenericLogType() {}

		/**
		  * getCompleteLogMessage
		  *
		  * Method inherited from ILogType. Constructs a string using a
		  * list of arguments retrieved from a variable argument list.
		  * Call constructMessage to append the date, time, level and
		  * thread ID to the message
		  *
		  * @return Log Message
		  *
		  * @param filename Name of file
		  * @param line		Line number in the file
		  * @param args		Pointer to a variable argument list
		  *
		  * @exception TA_Base_Core::DebugMsgConstructionException
		  *			   Thrown if there are problems retrieving arguments from
		  *			   the argument list
		  *
		  */
		virtual std::string getCompleteLogMessage(const std::string& filename, int line, va_list& args);

	private:

		GenericLogType(const GenericLogType& oldGenericLogType);

		const GenericLogType& operator=(const GenericLogType& rhs);
	};

}		// namespace TA_Base_Core

#endif // GENERICLOGTYPE_LOGTYPE_H_INCLUDED
