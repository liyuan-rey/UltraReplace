// ResultPage.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "ResultPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultPage dialog


CResultPage::CResultPage(CWnd* pParent /*=NULL*/)
	: TStackedPage(CResultPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CResultPage::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultPage)
	DDX_Control(pDX, IDC_RESULT_LISTCTRL, m_ResultListCtrl);
	DDX_Control(pDX, IDC_RESULT_SAVEAS, m_btnSaveAs);
	DDX_Control(pDX, IDC_RESULT_RECOVER, m_btnRecover);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultPage, TStackedPage)
	//{{AFX_MSG_MAP(CResultPage)
	//}}AFX_MSG_MAP
	ON_MESSAGE(URLC_ITEMSELECTED, OnListItemSelected)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultPage message handlers

BOOL CResultPage::OnInitDialog() 
{
	TStackedPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// init list control
	m_ResultListCtrl.SubclassHeader(true);
	CRect rect;
	m_ResultListCtrl.GetWindowRect(rect);
	m_ResultListCtrl.AddColumn(_T("结果列表"),
		rect.Width()-4, LVCFMT_LEFT);
	m_ResultListCtrl.SetExtendedStyle(
		m_ResultListCtrl.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
		| LVS_EX_ONECLICKACTIVATE | LVS_EX_FLATSB);
	m_ResultListCtrl.SetNormalCursor();
	CString strEmpty;
	strEmpty.LoadString(IDS_RESULTLIST_EMPTY);
	m_ResultListCtrl.ShowEmptyText(strEmpty);

	// init force flat look
	m_btnRecover.ForceFlatLook(TRUE);
	m_btnSaveAs.ForceFlatLook(TRUE);

	// create modeless result view dlg
	m_dlgResultView.Create(IDD_RESULT_VIEW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CResultPage::OnListItemSelected(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	// 分析文件名和匹配位置
	int nBeginPos = 0, nEndPos = 0;
	CString strItemText = m_ResultListCtrl.GetItemText(((LVITEM*)lParam)->iItem, 0);

	nBeginPos = 5;
	nEndPos = strItemText.Find(" 文件 ", nBeginPos);

	CString strTaskName = strItemText.Mid(nBeginPos, nEndPos - 5);

	nBeginPos = nEndPos;
	nEndPos = strItemText.Find(" 位置 ", nBeginPos + 5);
	
	CString strFileName = strItemText.Mid(nBeginPos + 6, nEndPos - nBeginPos - 6);

	nBeginPos = nEndPos + 6;
	nEndPos = strItemText.Find(" 匹配查找");

	DWORD dwTarPos = _ttoi((LPCTSTR)(strItemText.Mid(nBeginPos, nEndPos - nBeginPos)));

	// 读相关文件
	CFile file;
	if(!file.Open(strFileName, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary))
	{
		CString strMsg;
		strMsg.Format("无法打开文件:\n%s", strFileName);
		MessageBox(_T(strMsg), _T("错误"), MB_ICONWARNING | MB_OK);
		return 0L;
	}

	// 得到任务信息
	LPSCHEDULER(pScheduler);
	CSimpleTask task = pScheduler->GetTask(strTaskName);
	int nFixLength = task.m_strSearch.GetLength();
	if(!task.m_bIsSearchOnly)
		nFixLength = task.m_strReplace.GetLength();

	// 显示匹配字串和前后 100 个字符
	nFixLength += 200;
	if(dwTarPos < 101)
		file.SeekToBegin();
	else
		file.Seek(dwTarPos - 100, CFile::begin);

	CString strShow = "";
	TCHAR *pszRead = NULL;
	pszRead = new TCHAR[nFixLength + 1];
	long lRead = file.Read(pszRead, nFixLength);
	pszRead[lRead] = '\0';
	strShow = pszRead;
	m_dlgResultView.m_edtTextView.SetWindowText(strShow);
	delete pszRead;

	if(!m_dlgResultView.IsWindowVisible())
		m_dlgResultView.ShowWindow(SW_SHOWNORMAL);

	return 0L;
}
