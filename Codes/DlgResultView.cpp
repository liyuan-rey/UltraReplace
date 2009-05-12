// DlgResultView.cpp : implementation file
//

#include "stdafx.h"
#include "ur.h"
#include "DlgResultView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgResultView dialog


CDlgResultView::CDlgResultView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgResultView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgResultView)
	//}}AFX_DATA_INIT
}


void CDlgResultView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgResultView)
	DDX_Control(pDX, ID_HIDE, m_btnOK);
	DDX_Control(pDX, IDC_TEXTVIEW, m_edtTextView);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgResultView, CDialog)
	//{{AFX_MSG_MAP(CDlgResultView)
	ON_BN_CLICKED(ID_HIDE, OnHide)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgResultView message handlers

BOOL CDlgResultView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnOK.ForceFlatLook(TRUE);
	m_edtTextView.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgResultView::OnHide() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}
