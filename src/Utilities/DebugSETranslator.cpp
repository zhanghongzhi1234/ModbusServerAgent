#include "DebugSETranslator.h"
#include "DebugUtil.h"       // Need definition of CONTEXT for Solaris builds

#include "TAAssert.h"
#include "RunParams.h"

namespace TA_Base_Core
{
#ifdef WIN32
	// TODO LPP: This might interfere with int 3 breakpoints (so it might not be
	// possible to stop using the debugger - although this won't be much different
	// to the present situation with catch(...) handlers).
	void translator_func(unsigned int exceptionCode, EXCEPTION_POINTERS* exceptionInfo)
	{
		switch (exceptionCode)
		{
		case EXCEPTION_ACCESS_VIOLATION:
			throw WinAccessViolationException(exceptionCode, exceptionInfo);
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			throw WinFloatDivideByZeroException(exceptionCode, exceptionInfo);
			break;
		case EXCEPTION_BREAKPOINT:
			throw WinBreakpointException(exceptionCode, exceptionInfo);
			break;
		default:
			throw WinStructuredException(exceptionCode, exceptionInfo);
			break;
		};
	}

	void gInitStructuredExceptionHandler()
	{
		// TODO LPP: Should we use a thread local variable to ensure we only call
		// _set_se_translator() once per thread?  Does _set_se_translator() already do this?

		static bool shouldSetSeTranslator = RunParams::getInstance().isSet(RPARAM_DEBUGLOGSTACKTRACE);
		if (shouldSetSeTranslator)
		{
			LOG0(SourceInfo, DebugUtil::DebugDebug, "gInitStructuredExceptionHandler(): calling _set_se_translator()");
			_set_se_translator(translator_func);
		}
		else
		{
			LOG0(SourceInfo, DebugUtil::DebugDebug, "gInitStructuredExceptionHandler(): NOT calling _set_se_translator()");
		}
	}

	CONTEXT* gContextFromExceptionInfo(EXCEPTION_POINTERS* exceptionInfo)
	{
		return exceptionInfo->ContextRecord;
	}

#else
	void gInitStructuredExceptionHandler()
	{
		LOG0(SourceInfo, DebugUtil::DebugDebug, "gInitStructuredExceptionHandler(): NOT IMPLEMENTED()");
	}

	CONTEXT* gContextFromExceptionInfo(EXCEPTION_POINTERS* exceptionInfo)
	{
		LOG0(SourceInfo, DebugUtil::DebugDebug, "gContextFromExceptionInfo(): NOT IMPLEMENTED()");
		return NULL;
	}

#endif


};  // namespace TA_Base_Core


