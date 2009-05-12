// UR.h : main header file for the UR application
//

#if !defined(AFX_UR_H__04359015_3B66_4804_9DCC_7C050E665983__INCLUDED_)
#define AFX_UR_H__04359015_3B66_4804_9DCC_7C050E665983__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define URR_FILTERSTRING _TEXT("*.txt|*.htm")

#include "resource.h"		// main symbols
#include "Scheduler.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CURApp:
// See UR.cpp for the implementation of this class
//

class CURApp : public CWinApp
{
public:
	CScheduler* m_pScheduler;
	CURApp();
	~CURApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CURApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CURApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// 操作变量值的类型
#define URMD_COMMONTEXT		0
#define URMD_WILDCARDSTAR		1
#define URMD_WILDCARDQUERY	2
#define URMD_VARIABLE		4

// 通配符的值的类型
#define URWC_NUMBER			1
#define URWC_LOWERCASE		2
#define URWC_UPPERCASE		4
#define URWC_ALLLETTER		6
#define URWC_CUSTOM			0

// 操作模式类型
#define UROT_COMMON			0
#define UROT_ADVANCE		1

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UR_H__04359015_3B66_4804_9DCC_7C050E665983__INCLUDED_)
