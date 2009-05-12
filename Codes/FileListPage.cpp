// FileListPage.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "FileListPage.h"
#include "FileFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern theScheduler;

/////////////////////////////////////////////////////////////////////////////
// CFileListPage dialog


CFileListPage::CFileListPage(CWnd* pParent /*=NULL*/)
	: TStackedPage(CFileListPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileListPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFileListPage::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileListPage)
	DDX_Control(pDX, IDC_FILELIST_IMPORT, m_btnImport);
	DDX_Control(pDX, IDC_FILELIST_FILTER, m_btnFilter);
	DDX_Control(pDX, IDC_FILELIST_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_FILELIST, m_FileListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileListPage, TStackedPage)
	//{{AFX_MSG_MAP(CFileListPage)
	ON_BN_CLICKED(IDC_FILELIST_EXPORT, OnFilelistExport)
	ON_BN_CLICKED(IDC_FILELIST_FILTER, OnFilelistFilter)
	ON_BN_CLICKED(IDC_FILELIST_IMPORT, OnFilelistImport)
	//}}AFX_MSG_MAP
	ON_MESSAGE(URLC_LISTENDDROP, OnListEndDrop)
	ON_MESSAGE(URLC_LISTENDDRAG, OnListEndDrag)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileListPage message handlers

BOOL CFileListPage::OnInitDialog() 
{
	TStackedPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	//////////////////////////////////
	// init filelist
	// add a column, and give it much length
	CRect rect;
	m_FileListCtrl.GetWindowRect(rect);
	m_FileListCtrl.AddColumn(_T("文件名"), rect.Width()-4);

	m_FileListCtrl.SubclassHeader(true); // set flat headctrl
	m_FileListCtrl.SetDragDrop(TRUE); // enable drag&drop
	m_FileListCtrl.SetExtendedStyle(
		m_FileListCtrl.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
		| LVS_EX_ONECLICKACTIVATE | LVS_EX_FLATSB); // set style
	m_FileListCtrl.SetNormalCursor(); // set nomal cursor

	// set empty-show string
	CString strEmpty;
	strEmpty.LoadString(IDS_FILELIST_EMPTY);
	m_FileListCtrl.ShowEmptyText(strEmpty);
	// end init listctrl
	///////////////////////////////////////

	// init force flat button
	m_btnExport.ForceFlatLook(TRUE);
	m_btnFilter.ForceFlatLook(TRUE);
	m_btnImport.ForceFlatLook(TRUE);
	SetBtnState();

	// init filter string
	m_strFilter = URR_FILTERSTRING;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileListPage::OnFilelistImport() 
{
	// TODO: Add your control notification handler code here
	CString strFilter, strFileName;
	DWORD dwFlags;

	strFilter.LoadString(IDS_FILTER_FILELIST);
	dwFlags = OFN_EXPLORER | OFN_FILEMUSTEXIST
		| OFN_HIDEREADONLY | OFN_NOCHANGEDIR
		| OFN_PATHMUSTEXIST | OFN_SHOWHELP;
	CFileDialog fileDlg(TRUE, _T("ufl"), _T("FileList"),
		dwFlags, _T(strFilter), GetParent());
	fileDlg.m_ofn.lpstrInitialDir = ".";

	if (fileDlg.DoModal() == IDCANCEL)
		return;

	// 验证
	strFileName = fileDlg.GetPathName();
	if (fileDlg.GetFileExt() != "ufl")
	{
		MessageBox(_T("试图打开的文件:\n" + strFileName	+ "\n不是有效的 Ultra Replace 文件列表文件."), _T("提示"), MB_ICONINFORMATION | MB_OK);
		return;
	}

	TRY
	{
		CStdioFile listFile(_T(strFileName),
			CFile::modeRead | CFile::shareExclusive | CFile::typeText);

		CString scLine, scComp;
		bool bPassed = false;
		
		if(listFile.ReadString(scLine))
		{
			scComp.LoadString(IDS_FILELIST_FILEHEAD_TITTLE);
			if(scLine == scComp)
			{
				scComp.LoadString(IDS_FILELIST_FILEHEAD_VARINFO);
				if(listFile.ReadString(scLine) && scLine == scComp)
					bPassed = true;
			}
		}
		
		if(!bPassed)
		{
			MessageBox(_T("试图打开的文件:\n" + strFileName + "\n不是有效的 Ultra Replace 文件列表文件."), _T("提示"), MB_ICONINFORMATION | MB_OK);
			return;
		}
		
		// read and record file list information which from the file
		BOOL bFliterOut = FALSE;
		BOOL bMantion = FALSE;
		while(listFile.ReadString(scLine))
		{
			if(scLine.IsEmpty())
				continue;
			
			scLine.TrimLeft();
			if (scLine.Left(2) == "//")
				continue;
			
			// recoard a information
			LPSCHEDULER(pScheduler);
			if(!pScheduler->FilterFile(scLine))
			{
				if(!bMantion)
				{
					if(IDYES == MessageBox("在导入的文件列表中存在于当前过滤设置冲突的文件, 要将这些文件滤出吗?", _T("提示"), MB_ICONQUESTION | MB_YESNO))
						bFliterOut = TRUE;
					else
						bFliterOut = FALSE;

					bMantion = TRUE;
				}

				if(bFliterOut)
					continue;				
			}

			m_FileListCtrl.InsertItem(m_FileListCtrl.GetItemCount(), _T(scLine));
		}

		listFile.Close();
	}
	CATCH(CFileException, pfe)
	{
		MessageBox(_T("找不到指定的文件!"), _T("错误"), MB_ICONWARNING | MB_OK);
	}
	END_CATCH
}

void CFileListPage::OnFilelistExport() 
{
	// TODO: Add your control notification handler code here
	// ensure we have some to esport
	int num;
	num = m_FileListCtrl.GetItemCount();
	if(!num)
		return;

	CString strFilter, strFileName;
	DWORD dwFlags;

	strFilter.LoadString(IDS_FILTER_FILELIST);
	dwFlags = OFN_EXPLORER | OFN_OVERWRITEPROMPT
		| OFN_HIDEREADONLY | OFN_NOCHANGEDIR
		| OFN_PATHMUSTEXIST | OFN_SHOWHELP;
	CFileDialog fileDlg(FALSE, _T("ufl"), _T("FileList"),
		dwFlags, _T(strFilter), GetParent());
	fileDlg.m_ofn.lpstrInitialDir = ".";

	if (fileDlg.DoModal() == IDCANCEL)
		return;

	// 验证
	strFileName = fileDlg.GetPathName();
	if (fileDlg.GetFileExt() != "ufl")
	{
		MessageBox(_T("试图打开的文件:\n" + strFileName	+ "\n不是有效的 Ultra Replace 文件列表文件."), _T("提示"), MB_ICONINFORMATION | MB_OK);
		return;
	}

	TRY
	{
		CStdioFile listFile(_T(strFileName),
			CFile::modeCreate | CFile::modeWrite
			| CFile::shareExclusive | CFile::typeText);
		CString csLine;

		// write file head
		csLine.LoadString(IDS_FILELIST_FILEHEAD_TITTLE);
		listFile.WriteString(csLine + "\n");
		csLine.LoadString(IDS_FILELIST_FILEHEAD_VARINFO);
		listFile.WriteString(csLine + "\n");
		listFile.WriteString("\n//\n//Please do NOT edit!\n//\n\n");

		// write file list
		int i;

		for (i = 0; i < num; i++)
			listFile.WriteString(m_FileListCtrl.GetItemText(i, 0) + "\n");

		listFile.Close();
	}
	CATCH(CFileException, pfe)
	{
		 MessageBox(_T("找不到指定的文件!"), _T("错误"), MB_ICONWARNING | MB_OK);
	}
	END_CATCH
}

void CFileListPage::OnFilelistFilter() 
{
	// TODO: Add your control notification handler code here
	CFileFilter dlgFilter;
	dlgFilter.m_strFilter = m_strFilter;

	if (dlgFilter.DoModal() == IDCANCEL)
		return;

	m_strFilter = dlgFilter.m_strFilter;

	// 重新过滤列表项
	BOOL bFliterOut = FALSE;
	BOOL bMantion = FALSE;
	CString strFile = "";
	for(int i = 0; i < m_FileListCtrl.GetItemCount(); i++)
	{
		LPSCHEDULER(pScheduler);
		strFile = m_FileListCtrl.GetItemText(i, 0);
		if(!pScheduler->FilterFile(strFile))
		{
			if(!bMantion)
			{
				if(IDYES == MessageBox("文件列表中存在于当前过滤设置冲突的文件, 要将这些文件滤出吗?", _T("提示"), MB_ICONQUESTION | MB_YESNO))
					bFliterOut = TRUE;
				else
					bFliterOut = FALSE;

				bMantion = TRUE;
			}

			if(bFliterOut)
			{
				m_FileListCtrl.DeleteItem(i);
				i--;
			}	
		}
	}
}

LRESULT CFileListPage::OnListEndDrop(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetBtnState();

	return 0L;
}

LRESULT CFileListPage::OnListEndDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetBtnState();

	return 0L;
}

void CFileListPage::SetBtnState()
{
	if(m_FileListCtrl.GetItemCount() < 1)
		m_btnExport.EnableWindow(FALSE);
	else
		m_btnExport.EnableWindow();	
}
