#if !defined(AFX_ASSERTEXCEPTION_H__599117C1_47C9_11D7_B150_0080C8E32E69__INCLUDED_)
#define AFX_ASSERTEXCEPTION_H__599117C1_47C9_11D7_B150_0080C8E32E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseException.h"
#include <string>

namespace TA_Base_Core
{
	class AssertException : public BaseException
	{
	public:
		AssertException() throw();
		AssertException(const std::string& msg) throw();
		virtual ~AssertException() throw();

	};
}

#endif // !defined(AFX_ASSERTEXCEPTION_H__599117C1_47C9_11D7_B150_0080C8E32E69__INCLUDED_)

