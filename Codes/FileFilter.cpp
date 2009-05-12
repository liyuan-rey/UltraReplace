// FileFilter.cpp : implementation file
//

#include "stdafx.h"
#include "ur.h"
#include "FileFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileFilter dialog


CFileFilter::CFileFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CFileFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileFilter)
	m_strFilter = _T("");
	//}}AFX_DATA_INIT
}


void CFileFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileFilter)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_FILEFILTER_EDIT, m_strFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileFilter, CDialog)
	//{{AFX_MSG_MAP(CFileFilter)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileFilter message handlers

BOOL CFileFilter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnCancel.ForceFlatLook(TRUE);
	m_btnOK.ForceFlatLook(TRUE);
	
	CWnd* pEdit = GetDlgItem(IDC_FILEFILTER_EDIT);
	ASSERT(pEdit != NULL);
	GotoDlgCtrl(pEdit);

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileFilter::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_strFilter.GetLength() > MAX_PATH - 1)
	{
		MessageBox(_T("过滤字串长度不能超过 255 个字符!"), _T("提示"), MB_ICONINFORMATION | MB_OK);
		return;
	}
	
	LPSCHEDULER(pScheduler);

	if (!pScheduler->SetMaskString(m_strFilter))
		return;
	
	CDialog::OnOK();
}
