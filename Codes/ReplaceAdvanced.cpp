// ReplaceAdvanced.cpp : implementation file
//

#include "stdafx.h"
#include "ur.h"
#include "ReplaceAdvanced.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplaceAdvanced property page

IMPLEMENT_DYNCREATE(CReplaceAdvanced, CPropertyPage)

CReplaceAdvanced::CReplaceAdvanced() : CPropertyPage(CReplaceAdvanced::IDD)
{
	//{{AFX_DATA_INIT(CReplaceAdvanced)
	m_IsAInclude = -1;
	m_IsQInclude = -1;
	//}}AFX_DATA_INIT
}

CReplaceAdvanced::~CReplaceAdvanced()
{
}

void CReplaceAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceAdvanced)
	DDX_Radio(pDX, IDC_REPLACE_ADVANCED_AINCLUDE, m_IsAInclude);
	DDX_Radio(pDX, IDC_REPLACE_ADVANCED_QINCLUDE, m_IsQInclude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceAdvanced, CPropertyPage)
	//{{AFX_MSG_MAP(CReplaceAdvanced)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplaceAdvanced message handlers
