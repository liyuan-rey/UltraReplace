// ReplaceAdvSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ur.h"
#include "ReplaceAdvSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplaceAdvSetting property page

IMPLEMENT_DYNCREATE(CReplaceAdvSetting, CPropertyPage)

CReplaceAdvSetting::CReplaceAdvSetting() : CPropertyPage(CReplaceAdvSetting::IDD)
{
	//{{AFX_DATA_INIT(CReplaceAdvSetting)
	m_bIsQueryInclude = -1;
	m_bIsAllInclude = -1;
	//}}AFX_DATA_INIT
}

CReplaceAdvSetting::~CReplaceAdvSetting()
{
}

void CReplaceAdvSetting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceAdvSetting)
	DDX_Control(pDX, IDC_REPLACE_ADVANCED_VARLIST, m_VarListCtrl);
	DDX_Radio(pDX, IDC_REPLACE_ADVANCED_QINCLUDE, m_bIsQueryInclude);
	DDX_Radio(pDX, IDC_REPLACE_ADVANCED_AINCLUDE, m_bIsAllInclude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceAdvSetting, CPropertyPage)
	//{{AFX_MSG_MAP(CReplaceAdvSetting)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplaceAdvSetting message handlers
