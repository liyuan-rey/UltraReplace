// ReplaceCommon.cpp : implementation file
//

#include "stdafx.h"
#include "ur.h"
#include "ReplaceCommon.h"

#include "URDlg.h"
#include "ReplacePage.h"
#include "DlgInput.h"
#include "SimpleTask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplaceCommon property page

IMPLEMENT_DYNCREATE(CReplaceCommon, CPropertyPage)

CReplaceCommon::CReplaceCommon() : CPropertyPage(CReplaceCommon::IDD)
{
	//{{AFX_DATA_INIT(CReplaceCommon)
	m_bAdvanced = FALSE;
	m_bWholeWord = FALSE;
	m_bIgnoreCase = FALSE;
	m_bSearchOnly = FALSE;
	m_strSearch = _T("");
	m_strReplace = _T("");
	//}}AFX_DATA_INIT
}

CReplaceCommon::~CReplaceCommon()
{
}

void CReplaceCommon::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceCommon)
	DDX_Control(pDX, IDC_REPLACE_COMMON_SAVENEWTASK, m_btnSaveNewTask);
	DDX_Control(pDX, IDC_REPLACE_COMMON_MODIFYTASK, m_btnModifyTask);
	DDX_Control(pDX, IDC_REPLACE_COMMON_CLEAR, m_btnClear);
	DDX_Check(pDX, IDC_REPLACE_COMMON_ADVMODE, m_bAdvanced);
	DDX_Check(pDX, IDC_REPLACE_COMMON_FULLWORD, m_bWholeWord);
	DDX_Check(pDX, IDC_REPLACE_COMMON_IGNORECASE, m_bIgnoreCase);
	DDX_Check(pDX, IDC_REPLACE_COMMON_SEARCHONLY, m_bSearchOnly);
	DDX_Text(pDX, IDC_REPLACE_COMMON_SEARCHTEXT, m_strSearch);
	DDX_Text(pDX, IDC_REPLACE_COMMON_REPLACETEXT, m_strReplace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceCommon, CPropertyPage)
	//{{AFX_MSG_MAP(CReplaceCommon)
	ON_BN_CLICKED(IDC_REPLACE_COMMON_CLEAR, OnReplaceCommonClear)
	ON_BN_CLICKED(IDC_REPLACE_COMMON_MODIFYTASK, OnReplaceCommonModifytask)
	ON_BN_CLICKED(IDC_REPLACE_COMMON_SAVENEWTASK, OnReplaceCommonSavenewtask)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplaceCommon message handlers

BOOL CReplaceCommon::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// init force flat button
	m_btnClear.ForceFlatLook(TRUE);
	m_btnModifyTask.ForceFlatLook(TRUE);
	m_btnSaveNewTask.ForceFlatLook(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReplaceCommon::OnReplaceCommonClear() 
{
	// TODO: Add your control notification handler code here
	m_strSearch = _T("");
	m_strReplace = _T("");

	UpdateData(FALSE);
}

void CReplaceCommon::OnReplaceCommonModifytask() 
{
	// TODO: Add your control notification handler code here
	// 校验数据合法性
	if(!VerifyData())
		return;

	CListCtrl* pListCtrl = &(((CReplacePage*)(((CURDlg*)AfxGetMainWnd())->GetPage(IDD_PAGE_REPLACE))->GetPage())->m_TaskListCtrl);
	// 检查列表选项
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请先选定一项任务!"), _T("提示"));
		return;
	}

	// 构造任务数据
	CSimpleTask task;
	int nItem = pListCtrl->GetNextSelectedItem(pos);
	task.m_strTaskName = pListCtrl->GetItemText(nItem, 0);
	
	UpdateData();
	
	task.m_bIsIgnoreCase = m_bIgnoreCase;
	task.m_bIsSearchOnly = m_bSearchOnly;
	task.m_bIsWholeWord = m_bWholeWord;
	task.m_strReplace = m_strReplace;
	task.m_strSearch = m_strSearch;
	
	// 添加到核心类
	LPSCHEDULER(pScheduler);
	pScheduler->ModifyTask(task);		
}

void CReplaceCommon::OnReplaceCommonSavenewtask() 
{
	// TODO: Add your control notification handler code here
	// 校验数据合法性
	if(!VerifyData())
		return;

	// 取任务名称
	CDlgInput dlgInput;
	if(IDCANCEL == dlgInput.DoModal())
		return;

	// 构造任务数据
	CSimpleTask task;
	task.m_strTaskName = dlgInput.m_strInput;

	UpdateData();

	task.m_bIsIgnoreCase = m_bIgnoreCase;
	task.m_bIsSearchOnly = m_bSearchOnly;
	task.m_bIsWholeWord = m_bWholeWord;
	task.m_strReplace = m_strReplace;
	task.m_strSearch = m_strSearch;

	task.m_bRun = FALSE;

	// 添加到核心类
	CListCtrl* pListCtrl = &(((CReplacePage*)(((CURDlg*)AfxGetMainWnd())->GetPage(IDD_PAGE_REPLACE))->GetPage())->m_TaskListCtrl);
	ASSERT(pListCtrl !=NULL);

	LPSCHEDULER(pScheduler);
	if(pScheduler->AddSimpleTask(task))
	{
		// 添加到任务列表视
		int nPos = pListCtrl->GetItemCount();
		pListCtrl->InsertItem(nPos, _T(task.m_strTaskName));

		// 设置按钮状态
		CReplacePage* pReplacePage = (CReplacePage*)(((CURDlg*)AfxGetMainWnd())->GetPage(IDD_PAGE_REPLACE))->GetPage();
		ASSERT(pReplacePage != NULL);
		pReplacePage->SetBtnState();
	}
}

BOOL CReplaceCommon::VerifyData()
{
	UpdateData();
	if(m_strSearch.IsEmpty())
	{
		MessageBox(_T("请输入查找文本!"), _T("提示"), MB_ICONINFORMATION | MB_OK);
		return FALSE;
	}

	if(!m_bSearchOnly && m_strReplace.IsEmpty())
	{
		if(IDNO == MessageBox(_T("替换文本为空, 所有查找到的文本都会被删除.\n要继续么?"), _T("提示"), MB_ICONQUESTION | MB_YESNO))
			return FALSE;
	}

	return TRUE;
}
