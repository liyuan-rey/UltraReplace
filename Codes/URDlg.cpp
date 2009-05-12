// URDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "URDlg.h"

// include every page head
#include "FileListPage.h"
#include "ReplacePage.h"
#include "ResultPage.h"
#include "SettingPage.h"
#include "AboutPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CURDlg dialog

CURDlg::CURDlg(CWnd* pParent /*=NULL*/)
	: TStackedDialog(IDC_PLACE_PAGE, CURDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CURDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CURDlg::DoDataExchange(CDataExchange* pDX)
{
	TStackedDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CURDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDHELP, m_btnHelp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CURDlg, TStackedDialog)
	//{{AFX_MSG_MAP(CURDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDS_BTN_FILELIST, OnFileListClicked)
	ON_COMMAND(IDS_BTN_REPLACE, OnReplaceClicked)
	ON_COMMAND(IDS_BTN_RESULT, OnResultClicked)
	ON_COMMAND(IDS_BTN_SETTING, OnSettingClicked)
	ON_COMMAND(IDS_BTN_ABOUT, OnAboutClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CURDlg message handlers

BOOL CURDlg::OnInitDialog()
{
	TStackedDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// init .net bar
	InitNetBar();

	// init stack page
	InitStackPage();
	OnFileListClicked();

	// init force flat button
	m_btnHelp.ForceFlatLook(TRUE);
	m_btnOK.ForceFlatLook(TRUE);
//	m_btnOK.SetInCursor(AfxGetApp()->LoadCursor(IDC_HANDCUR));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CURDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		BringWindowToTop();
		OnAboutClicked();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CURDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CURDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

TStackedPage* CURDlg::CreatePage(UINT nId)
{
	switch (nId)
	{
	case IDD_PAGE_FILELIST:
		return new CFileListPage; 
	case IDD_PAGE_REPLACE:
		return new CReplacePage;
	case IDD_PAGE_RESULT:
		return new CResultPage;
	case IDD_PAGE_SETTING:
		return new CSettingPage;
	case IDD_PAGE_ABOUT:
		return new CAboutPage;
	}

	return NULL;    // this will assert
}

void CURDlg::OnPageChanged(UINT nId, BOOL bActivated)
{
	return;
}

BOOL CURDlg::InitNetBar()
{
	CRect rcWnd;
	rcWnd.SetRect(0, 0, 80, 53);
	CWnd* pWndNetBar = GetDlgItem(IDC_PLACE_BAR);
	ASSERT(pWndNetBar != NULL);
	m_ImageList.Create(IDB_BARBMP, 32, 1, RGB(255, 0, 255));

	m_btnFileList.Create(_T("ÎÄ¼þÁÐ±í"), WS_CHILD | WS_VISIBLE, rcWnd,
		pWndNetBar, IDS_BTN_FILELIST, &m_ImageList,0);  
	m_btnFileList.m_bEnabled = TRUE;

	rcWnd.OffsetRect(0, 53);

	m_btnReplace.Create(_T("²éÕÒÌæ»»"), WS_CHILD | WS_VISIBLE, rcWnd,
		pWndNetBar, IDS_BTN_REPLACE, &m_ImageList,1);  
	m_btnReplace.m_bEnabled = TRUE;

	rcWnd.OffsetRect(0, 53);

	m_btnResult.Create(_T("½á¹ûÒ»ÀÀ"), WS_CHILD | WS_VISIBLE, rcWnd,
		pWndNetBar, IDS_BTN_RESULT, &m_ImageList,2);  
	m_btnResult.m_bEnabled = TRUE;

	rcWnd.OffsetRect(0, 53);

	m_btnSetting.Create(_T("¿ØÖÆÌ¨"), WS_CHILD | WS_VISIBLE, rcWnd,
		pWndNetBar, IDS_BTN_SETTING, &m_ImageList,3);  
	m_btnSetting.m_bEnabled = TRUE;

	rcWnd.OffsetRect(0, 53);

	m_btnAbout.Create(_T("¹ØÓÚ..."), WS_CHILD | WS_VISIBLE, rcWnd,
		pWndNetBar, IDS_BTN_ABOUT, &m_ImageList,4);  
	m_btnAbout.m_bEnabled = TRUE;

	return TRUE;
}

void CURDlg::SetActiveButton(CDotNetBtn *btn)
{
	m_btnFileList.SetState(FALSE);
	m_btnReplace.SetState(FALSE);
	m_btnResult.SetState(FALSE);
	m_btnSetting.SetState(FALSE);
	m_btnAbout.SetState(FALSE);
	
	btn->SetState(TRUE);
}

void CURDlg::OnFileListClicked()
{
	SetActiveButton(&m_btnFileList);

	// ·ÀÖ¹ÆÁÄ»ÉÁË¸
	if(GetPage(IDD_PAGE_FILELIST)->IsActive())
		return;
	SetPage(IDD_PAGE_FILELIST);
}

void CURDlg::OnReplaceClicked()
{
	SetActiveButton(&m_btnReplace);

	// ·ÀÖ¹ÆÁÄ»ÉÁË¸
	if(GetPage(IDD_PAGE_REPLACE)->IsActive())
		return;
	SetPage(IDD_PAGE_REPLACE);
}

void CURDlg::OnResultClicked()
{
	SetActiveButton(&m_btnResult);

	// ·ÀÖ¹ÆÁÄ»ÉÁË¸
	if(GetPage(IDD_PAGE_RESULT)->IsActive())
		return;
	SetPage(IDD_PAGE_RESULT);
}

void CURDlg::OnSettingClicked()
{
	SetActiveButton(&m_btnSetting);

	// ·ÀÖ¹ÆÁÄ»ÉÁË¸
	if(GetPage(IDD_PAGE_SETTING)->IsActive())
		return;
	SetPage(IDD_PAGE_SETTING);
}

void CURDlg::OnAboutClicked()
{
	SetActiveButton(&m_btnAbout);

	// ·ÀÖ¹ÆÁÄ»ÉÁË¸
	if(GetPage(IDD_PAGE_ABOUT)->IsActive())
		return;
	SetPage(IDD_PAGE_ABOUT);
}

void CURDlg::InitStackPage()
{
	AddPage(IDD_PAGE_FILELIST);
	AddPage(IDD_PAGE_REPLACE);
	AddPage(IDD_PAGE_RESULT);
	AddPage(IDD_PAGE_SETTING);
	AddPage(IDD_PAGE_ABOUT);

	SetPage(IDD_PAGE_FILELIST);

	return;
}

void CURDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(MessageBox("È·¶¨ÒªÍË³öÂð?",
		"Ultra Replace",
		MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;

	TStackedDialog::OnClose();
}

void CURDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	if(MessageBox("È·¶¨ÒªÍË³öÂð?",
		"Ultra Replace",
		MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;

	TStackedDialog::OnOK();
}
