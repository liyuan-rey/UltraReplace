#if !defined(AFX_REPLACEADVSETTING_H__0EAD090A_639E_4746_BA1E_CA7B7E1DF9DA__INCLUDED_)
#define AFX_REPLACEADVSETTING_H__0EAD090A_639E_4746_BA1E_CA7B7E1DF9DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplaceAdvSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplaceAdvSetting dialog

class CReplaceAdvSetting : public CPropertyPage
{
	DECLARE_DYNCREATE(CReplaceAdvSetting)

// Construction
public:
	CReplaceAdvSetting();
	~CReplaceAdvSetting();

// Dialog Data
	//{{AFX_DATA(CReplaceAdvSetting)
	enum { IDD = IDD_PAGE_REPLACE_ADVANCED };
	CListCtrl	m_VarListCtrl;
	int		m_bIsQueryInclude;
	int		m_bIsAllInclude;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReplaceAdvSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CReplaceAdvSetting)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACEADVSETTING_H__0EAD090A_639E_4746_BA1E_CA7B7E1DF9DA__INCLUDED_)
