#if !defined DEBUGMSGCONSTRUCTIONEXCEPTION_H
#define DEBUGMSGCONSTRUCTIONEXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseException.h"

namespace TA_Base_Core
{
	class DebugMsgConstructionException : public BaseException
	{
	public:
		DebugMsgConstructionException(const std::string& desc) throw()
			: BaseException(desc.c_str()) {}

		virtual ~DebugMsgConstructionException() throw() {}

	private:
		DebugMsgConstructionException() throw();
	};
};

#endif // DEBUGMSGCONSTRUCTIONEXCEPTION_HH


