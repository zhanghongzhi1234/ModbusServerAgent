#include "BaseException.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace TA_Base_Core
{
	BaseException::BaseException()
		throw() : std::exception()
	{
	}

	BaseException::BaseException(const std::string& msg)
		throw() : std::exception(), m_msg(msg)
	{
	}

	const char* BaseException::what() const throw()
	{
		return m_msg.c_str();
	}

	BaseException::~BaseException() throw()
	{
	}
}
