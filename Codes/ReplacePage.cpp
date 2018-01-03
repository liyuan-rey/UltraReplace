// ReplacePage.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "ReplacePage.h"

#include "URDlg.h"
#include "FileListPage.h"
#include "ResultPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplacePage dialog


CReplacePage::CReplacePage(CWnd* pParent /*=NULL*/)
	: TStackedPage(CReplacePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplacePage)
	//}}AFX_DATA_INIT
}

CReplacePage::~CReplacePage()
{
	if(m_pFlatSheet)
	{
		delete m_pFlatSheet;
		m_pFlatSheet = NULL;
	}
}


void CReplacePage::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplacePage)
	DDX_Control(pDX, IDC_REPLACE_TASKLIST, m_TaskListCtrl);
	DDX_Control(pDX, IDC_REPLACE_RUN, m_btnRun);
	DDX_Control(pDX, IDC_REPLACE_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_REPLACE_EXPORT, m_btnExport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplacePage, TStackedPage)
	//{{AFX_MSG_MAP(CReplacePage)
	ON_BN_CLICKED(IDC_REPLACE_RUN, OnReplaceRun)
	ON_BN_CLICKED(IDC_REPLACE_IMPORT, OnReplaceImport)
	ON_BN_CLICKED(IDC_REPLACE_EXPORT, OnReplaceExport)
	//}}AFX_MSG_MAP
	ON_MESSAGE(URLC_ITEMSELECTED, OnListItemSelected)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_REPLACE_TASKLIST, OnListItemCheckChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplacePage message handlers

BOOL CReplacePage::OnInitDialog() 
{
	ModifyStyleEx(0, WS_EX_CONTROLPARENT); // look in Knowledge Base Q149501
	TStackedPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// init force flat button
	m_btnExport.ForceFlatLook(TRUE);
	m_btnImport.ForceFlatLook(TRUE);
	m_btnRun.ForceFlatLook(TRUE);
	m_btnRun.EnableWindow(FALSE);

	// init property sheet
	m_pFlatSheet = new CFlatPropSheet("Detial Sheet");

	m_pFlatSheet->AddPage(&m_pageCommon);
	m_pFlatSheet->AddPage(&m_pageAdvSetting);

	m_pFlatSheet->Create(this, WS_CHILD | WS_VISIBLE, 0);

	// Move sheet
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pFlatSheet->SetWindowPos(NULL, rect.top - 6, rect.left - 6, 0, 0,
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );

	// init list ctrl
	m_TaskListCtrl.SubclassHeader(true);
	m_TaskListCtrl.GetWindowRect(&rect);
	m_TaskListCtrl.AddColumn(_T("任务列表"),
		rect.Width()-4, LVCFMT_LEFT);
	m_TaskListCtrl.SetExtendedStyle(
		m_TaskListCtrl.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
		| LVS_EX_ONECLICKACTIVATE | LVS_EX_FLATSB
		| LVS_EX_CHECKBOXES);
	m_TaskListCtrl.SetNormalCursor();
	CString strEmpty;
	strEmpty.LoadString(IDS_TASKLIST_EMPTY);
	m_TaskListCtrl.ShowEmptyText(strEmpty);

	SetBtnState();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReplacePage::OnReplaceRun() 
{
	// TODO: Add your control notification handler code here
	// 取文件列表
	CListCtrl* pListCtrl = &(((CFileListPage*)(((CURDlg*)AfxGetMainWnd())->GetPage(IDD_PAGE_FILELIST))->GetPage())->m_FileListCtrl);
	ASSERT(pListCtrl != NULL);
	
	CStringArray arrFileList;
	int nCount = pListCtrl->GetItemCount();
	// 确定至少有一个文件要操作
	if(nCount < 1)
	{
		MessageBox(_T("请选择所要操作的文件!"), _T("提示"));
		((CURDlg*)AfxGetMainWnd())->OnFileListClicked();
		return;
	}

	// 确定至少有一个要执行的任务
	LPSCHEDULER(pScheduler);
/*	if(pScheduler->m_arrSampleTask.GetSize() < 1)
	{
		MessageBox(_T("请先选择要操作的任务!"), _T("提示"));
		return;
	}
*/
	for(int i = 0; i < nCount; i++)
	{
		arrFileList.Add(pListCtrl->GetItemText(i, 0));
	}

	// 清除以前结果
	pListCtrl = &(((CResultPage*)(((CURDlg*)AfxGetMainWnd())->GetPage(IDD_PAGE_RESULT))->GetPage())->m_ResultListCtrl);
	ASSERT(pListCtrl != NULL);
	pListCtrl->DeleteAllItems();

	// 调用核心类
	pScheduler->SimpleReplace(arrFileList);

	// 切换到结果页
	((CURDlg*)AfxGetMainWnd())->OnResultClicked();

	return;
}

void CReplacePage::OnListItemCheckChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	
	if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)
		return;	// No change
	
	BOOL bPrevState = (BOOL)(((pNMListView->uOldState & LVIS_STATEIMAGEMASK)>>12)-1);   // Old check box state
	if (bPrevState < 0)	// On startup there's no previous state 
		bPrevState = 0; // so assign as false (unchecked)
	
	// New check box state
	BOOL bChecked=(BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
	if (bChecked < 0) // On non-checkbox notifications assume false
		bChecked = 0; 
	
	if (bPrevState == bChecked) // No change in check box
		return;
	
	// Now bChecked holds the new check box state
	CString strTaskName = m_TaskListCtrl.GetItemText(pNMListView->iItem, 0);
	LPSCHEDULER(pScheduler);
	pScheduler->SetTaskState(strTaskName, bChecked);

	// 设置按钮状态
	if(pScheduler->GetRunTaskCount() < 1)
		m_btnRun.EnableWindow(FALSE);
	else
		m_btnRun.EnableWindow();
}

LRESULT CReplacePage::OnListItemSelected(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	LVITEM* pItem = (LVITEM*)lParam;
	LPSCHEDULER(pScheduler);
	CSimpleTask task;
	task = pScheduler->GetTask(m_TaskListCtrl.GetItemText(pItem->iItem, 0));

	// 填写任务信息
	m_pageCommon.m_strSearch = task.m_strSearch;
	m_pageCommon.m_strReplace = task.m_strReplace;
	m_pageCommon.m_bIgnoreCase = task.m_bIsIgnoreCase;
	m_pageCommon.m_bWholeWord = task.m_bIsWholeWord;
	m_pageCommon.m_bSearchOnly = task.m_bIsSearchOnly;

	m_pageCommon.UpdateData(FALSE);
	return 0L;
}

void CReplacePage::OnReplaceImport() 
{
	// TODO: Add your control notification handler code here
	
}

void CReplacePage::OnReplaceExport() 
{
	// TODO: Add your control notification handler code here
	
}

void CReplacePage::SetBtnState()
{
	if(m_TaskListCtrl.GetItemCount() < 1)
		m_btnExport.EnableWindow(FALSE);
	else
		m_btnExport.EnableWindow();
}
