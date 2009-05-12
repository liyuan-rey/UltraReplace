// URDlg.h : header file
//

#if !defined(AFX_URDLG_H__1B1235DD_D2E6_4BDE_B235_B3420301165C__INCLUDED_)
#define AFX_URDLG_H__1B1235DD_D2E6_4BDE_B235_B3420301165C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DotNetBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CURDlg dialog

class CURDlg : public TStackedDialog
{
// Construction
public:
	CURDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CURDlg)
	enum { IDD = IDD_UR_DIALOG };
	CCJFlatButton	m_btnOK;
	CCJFlatButton	m_btnHelp;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CURDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

protected:
	void SetActiveButton(CDotNetBtn *btn);
	CImageList m_ImageList;
	CDotNetBtn m_btnFileList;
	CDotNetBtn m_btnReplace;
	CDotNetBtn m_btnResult;
	CDotNetBtn m_btnSetting;
	CDotNetBtn m_btnAbout;
	void OnPageChanged(UINT nId, BOOL bActivated);
	TStackedPage* CreatePage(UINT nId);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CURDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnOk();
	//}}AFX_MSG
	public:
	afx_msg void OnFileListClicked();
	afx_msg void OnReplaceClicked();
	afx_msg void OnResultClicked();
	afx_msg void OnSettingClicked();
	afx_msg void OnAboutClicked();
	DECLARE_MESSAGE_MAP()
private:
	void InitStackPage();
	BOOL InitNetBar();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URDLG_H__1B1235DD_D2E6_4BDE_B235_B3420301165C__INCLUDED_)
