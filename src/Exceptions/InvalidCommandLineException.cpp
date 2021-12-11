#include "InvalidCommandLineException.h"

namespace TA_Base_Core
{

	InvalidCommandLineException::InvalidCommandLineException() throw()
	{}

	InvalidCommandLineException::InvalidCommandLineException(const std::string& msg)
		throw() : BaseException(msg)
	{}

	InvalidCommandLineException::~InvalidCommandLineException() throw()
	{}
}
