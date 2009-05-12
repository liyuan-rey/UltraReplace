#if !defined(AFX_REPLACEPAGE_H__5D84A91B_4BC4_46FE_AD76_7470559575BB__INCLUDED_)
#define AFX_REPLACEPAGE_H__5D84A91B_4BC4_46FE_AD76_7470559575BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplacePage.h : header file
//

#include "URListCtrl.h"
#include "FlatPropSheet.h"
#include "ReplaceCommon.h"
#include "ReplaceAdvSetting.h"
#include "EditListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CReplacePage dialog

class CReplacePage : public TStackedPage
{
// Construction
public:
	CFlatPropSheet* m_pFlatSheet;
	CReplacePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReplacePage)
	enum { IDD = IDD_PAGE_REPLACE };
	CURListCtrl 	m_TaskListCtrl;
	CCJFlatButton	m_btnRun;
	CCJFlatButton	m_btnImport;
	CCJFlatButton	m_btnExport;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplacePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBtnState();
	virtual ~CReplacePage();

protected:
	CReplaceAdvSetting m_pageAdvSetting;
	CReplaceCommon m_pageCommon;
	
	// Generated message map functions
	//{{AFX_MSG(CReplacePage)
	afx_msg void OnReplaceRun();
	afx_msg void OnReplaceImport();
	afx_msg void OnReplaceExport();
	//}}AFX_MSG
	afx_msg LRESULT OnListItemSelected(WPARAM wParam, LPARAM lParam);
	afx_msg void OnListItemCheckChanged(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACEPAGE_H__5D84A91B_4BC4_46FE_AD76_7470559575BB__INCLUDED_)
