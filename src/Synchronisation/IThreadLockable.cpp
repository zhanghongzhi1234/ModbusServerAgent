/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/WXL3_TIP/TA_BASE/transactive/core/synchronisation/src/IThreadLockable.cpp $
  * @author:  Robert Young
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2019/02/22 15:17:48 $
  * Last modified by:  $Author: lim.cy $
  *
  * Implements those functions that may not be supported by all ThreadLockable
  * implementations. In general they should just assert.
  *
  */

#include "../Utilities/TAAssert.h"
#include "IThreadLockable.h"

namespace TA_Base_Core
{

    void IThreadLockable::acquireRead()
    {
        TA_ASSERT(false, "Read locks not supported");
    }

    void IThreadLockable::releaseRead()
    {
        TA_ASSERT(false, "Read locks not supported");
    }

}