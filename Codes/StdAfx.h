// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F09B8410_A073_4D11_A835_98439E331D5F__INCLUDED_)
#define AFX_STDAFX_H__F09B8410_A073_4D11_A835_98439E331D5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Adding for CJLibrary 6.08
#include <CJLibrary.h>

// Adding for stack dialog
#include "StackDialog.h"

// point to Scheduler
#define LPSCHEDULER(lpScheduler) \
	CScheduler* lpScheduler = ((CURApp*)AfxGetApp())->m_pScheduler

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F09B8410_A073_4D11_A835_98439E331D5F__INCLUDED_)
