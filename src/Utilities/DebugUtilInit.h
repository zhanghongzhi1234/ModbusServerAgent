#ifndef DEBUGUTILINIT_H_INCLUDED
#define DEBUGUTILINIT_H_INCLUDED


#if defined( WIN32 )
#pragma warning( disable : 4786 )
#endif   // defined( WIN32 ) 

#include "DebugUtil.h"
#include "RunParams.h"

namespace TA_Base_Core
{
	// Uses the following RunParams to set the corresponding DebugUtil settings:
	// RPARAM_DEBUGFILE
	// RPARAM_DEBUGLEVEL
	// RPARAM_DEBUGFILEMAXSIZE
	// RPARAM_DEBUGMAXFILES
	// RPARAM_DEBUGPIDFILENAMES
	// RPARAM_DEBUGLEVELFILE
	// RPARAM_DEBUGLEVELOFF

	void gSetDebugUtilFromRunParams();

}

#endif // DEBUGUTILINIT_H_INCLUDED

