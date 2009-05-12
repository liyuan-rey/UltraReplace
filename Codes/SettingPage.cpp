// SettingPage.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "SettingPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingPage dialog


CSettingPage::CSettingPage(CWnd* pParent /*=NULL*/)
	: TStackedPage(CSettingPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingPage)
	m_bIsDelBak = FALSE;
	m_bIsNotify = TRUE;
	m_bIsSaveTask = FALSE;
	m_nShowNum = 100;
	m_bIncludeSubFld = TRUE;
	m_bSetTopMost = FALSE;
	//}}AFX_DATA_INIT
}


void CSettingPage::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingPage)
	DDX_Control(pDX, IDC_SETTING_SETUP, m_btnSetup);
	DDX_Control(pDX, IDC_SETTING_APPLY, m_btnApply);
	DDX_Control(pDX, IDC_SETTING_CLEAN, m_btnClean);
	DDX_Check(pDX, IDC_SETTING_DELBAK, m_bIsDelBak);
	DDX_Check(pDX, IDC_SETTING_NOTIFY, m_bIsNotify);
	DDX_Check(pDX, IDC_SETTING_SAVETASK, m_bIsSaveTask);
	DDX_Text(pDX, IDC_SETTING_SHOWNUM, m_nShowNum);
	DDV_MinMaxInt(pDX, m_nShowNum, 0, 4096);
	DDX_Check(pDX, IDC_SETTING_SUBFOLDER, m_bIncludeSubFld);
	DDX_Check(pDX, IDC_SETTING_TOPWND, m_bSetTopMost);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingPage, TStackedPage)
	//{{AFX_MSG_MAP(CSettingPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingPage message handlers

BOOL CSettingPage::OnInitDialog() 
{
	TStackedPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// init force flat button
	m_btnClean.ForceFlatLook(TRUE);
	m_btnApply.ForceFlatLook(TRUE);
	m_btnSetup.ForceFlatLook(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
