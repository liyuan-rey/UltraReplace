#if !defined(AFX_DOTNETBTN_H__3DBD7C37_B357_4870_8253_ED97007AEBB1__INCLUDED_)
#define AFX_DOTNETBTN_H__3DBD7C37_B357_4870_8253_ED97007AEBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DotNetBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDotNetBtn window

class CDotNetBtn : public CWnd
{
// Construction
public:
	CDotNetBtn();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDotNetBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetState(BOOL bPressed);
	BOOL m_bMouseOnButton;
	BOOL m_bPressed;
	BOOL m_bDrawPressed;
	BOOL m_bEnabled;
	UINT m_nID;
	CString m_strCaption;
	UINT m_nImagePos;
	CImageList* m_pImageList;
	CWnd* m_pParentWnd;
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CImageList* pImageList, UINT nImagePos);
	virtual ~CDotNetBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDotNetBtn)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOTNETBTN_H__3DBD7C37_B357_4870_8253_ED97007AEBB1__INCLUDED_)
