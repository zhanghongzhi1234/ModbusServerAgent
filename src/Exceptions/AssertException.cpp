#include "AssertException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace TA_Base_Core
{
	AssertException::AssertException()
		throw()
	{

	}

	AssertException::AssertException(const std::string& msg)
		throw() : BaseException(msg)
	{

	}

	AssertException::~AssertException() throw()
	{

	}
}
