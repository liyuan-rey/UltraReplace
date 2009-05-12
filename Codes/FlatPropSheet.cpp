// FlatPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "ur.h"
#include "FlatPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatPropSheet

IMPLEMENT_DYNAMIC(CFlatPropSheet, CPropertySheet)

CFlatPropSheet::CFlatPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CFlatPropSheet::CFlatPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CFlatPropSheet::~CFlatPropSheet()
{
}


BEGIN_MESSAGE_MAP(CFlatPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CFlatPropSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatPropSheet message handlers

BOOL CFlatPropSheet::OnInitDialog() 
{
	ModifyStyleEx(0, WS_EX_CONTROLPARENT); // look in Knowledge Base Q149501
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTabCtrl *pTab = GetTabControl();
	//Subclass default CTabCtrl to CLBTabCtrl
	m_flatTabCtrl.SubclassWindow(pTab->m_hWnd);
	
	return bResult;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
