#if !defined(INVALIDCOMMANDLINEEXCEPTION)
#define INVALIDCOMMANDLINEEXCEPTION

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseException.h"
#include <string>

namespace TA_Base_Core
{
	class InvalidCommandLineException : public TA_Base_Core::BaseException
	{
	public:
		InvalidCommandLineException() throw();
		InvalidCommandLineException(const std::string& msg) throw();
		virtual ~InvalidCommandLineException() throw();
	};
}

#endif // !defined(INVALIDCOMMANDLINEEXCEPTION)
