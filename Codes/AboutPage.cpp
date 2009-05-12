// AboutPage.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "AboutPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutPage dialog


CAboutPage::CAboutPage(CWnd* pParent /*=NULL*/)
	: TStackedPage(CAboutPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutPage::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutPage)
	DDX_Control(pDX, IDC_ABOUT_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_ABOUT_REGISTER, m_btnRegister);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutPage, TStackedPage)
	//{{AFX_MSG_MAP(CAboutPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutPage message handlers

void CAboutPage::OnSetActive()
{
//	AfxMessageBox("�������ע�����!");
}

void CAboutPage::OnKillActive()
{
//	AfxMessageBox("��ʧȥ�״̬!");
}

void CAboutPage::OnCreatePage()
{
//	AfxMessageBox("�Ѵ���!");
}

void CAboutPage::OnDestroyPage()
{
//	AfxMessageBox("������!");
}

BOOL CAboutPage::OnInitDialog() 
{
	TStackedPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// init force flat button
	m_btnRegister.ForceFlatLook(TRUE);
	m_btnUpdate.ForceFlatLook(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
