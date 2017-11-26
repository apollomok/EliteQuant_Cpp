/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

namespace IBOfficial
{
#ifndef DLLEXP
#define DLLEXP __declspec( dllexport )
#endif

#ifdef _MSC_VER

#define assert ASSERT
	//#define snprintf _snprintf		// Since, snprintf() is now officially supported. We should never #define it.
}

//#include <afxwin.h>

#endif

