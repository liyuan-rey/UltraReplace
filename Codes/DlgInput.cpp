// DlgInput.cpp : implementation file
//

#include "stdafx.h"
#include "ur.h"
#include "DlgInput.h"

#include "URDlg.h"
#include "ReplacePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInput dialog


CDlgInput::CDlgInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInput)
	m_strInput = _T("");
	m_strPrompt = _T("");
	//}}AFX_DATA_INIT
}


void CDlgInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInput)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_INPUT, m_strInput);
	DDX_Text(pDX, IDC_PROMPT, m_strPrompt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInput, CDialog)
	//{{AFX_MSG_MAP(CDlgInput)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInput message handlers


void CDlgInput::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CReplacePage* pReplacePage = (CReplacePage*)(((CURDlg*)AfxGetMainWnd())->GetPage(IDD_PAGE_REPLACE))->GetPage();

	int nCount = pReplacePage->m_TaskListCtrl.GetItemCount();
	BOOL bExist = FALSE;
	for(int i = 0; i < nCount; i++)
	{
		if(m_strInput.Compare(pReplacePage->m_TaskListCtrl.GetItemText(i, 0)) == 0)
		{
			bExist = TRUE;
			break;
		}
	}

	if(bExist)
	{
		MessageBox(_T("新建任务已存在!"), _T("提示"), MB_ICONINFORMATION | MB_OK);
		return;
	}

	CDialog::OnOK();
}

BOOL CDlgInput::OnInitDialog() 
{
	m_strPrompt = _T("请输入任务名称:");
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnOK.ForceFlatLook(TRUE);
	m_btnCancel.ForceFlatLook(TRUE);

	CWnd* pEdit = GetDlgItem(IDC_INPUT);
	ASSERT(pEdit != NULL);
	GotoDlgCtrl(pEdit);
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

