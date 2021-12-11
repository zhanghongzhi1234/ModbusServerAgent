#if !defined DEBUGEMPTYARGSEXCEPTION_H
#define DEBUGEMPTYARGSEXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseException.h"

namespace TA_Base_Core
{
	class DebugEmptyArgsException : public BaseException
	{
	public:
		DebugEmptyArgsException(const std::string& desc) throw()
			: BaseException(desc.c_str()) {}

		virtual ~DebugEmptyArgsException() throw() {}

	private:
		DebugEmptyArgsException() throw();
	};
}

#endif // DEBUGEMPTYARGSEXCEPTION_H

