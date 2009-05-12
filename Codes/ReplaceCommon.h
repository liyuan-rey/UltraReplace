#if !defined(AFX_REPLACECOMMON_H__EE0A780F_6F48_44A6_8F07_4BF4DCA7F1DE__INCLUDED_)
#define AFX_REPLACECOMMON_H__EE0A780F_6F48_44A6_8F07_4BF4DCA7F1DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplaceCommon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplaceCommon dialog

class CReplaceCommon : public CPropertyPage
{
	DECLARE_DYNCREATE(CReplaceCommon)

// Construction
public:
	CReplaceCommon();
	~CReplaceCommon();

// Dialog Data
	//{{AFX_DATA(CReplaceCommon)
	enum { IDD = IDD_PAGE_REPLACE_COMMON };
	CCJFlatButton	m_btnSaveNewTask;
	CCJFlatButton	m_btnModifyTask;
	CCJFlatButton	m_btnClear;
	BOOL	m_bAdvanced;
	BOOL	m_bWholeWord;
	BOOL	m_bIgnoreCase;
	BOOL	m_bSearchOnly;
	CString	m_strSearch;
	CString	m_strReplace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReplaceCommon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL VerifyData();
	// Generated message map functions
	//{{AFX_MSG(CReplaceCommon)
	virtual BOOL OnInitDialog();
	afx_msg void OnReplaceCommonClear();
	afx_msg void OnReplaceCommonModifytask();
	afx_msg void OnReplaceCommonSavenewtask();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACECOMMON_H__EE0A780F_6F48_44A6_8F07_4BF4DCA7F1DE__INCLUDED_)
