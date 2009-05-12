#if !defined(AFX_URLISTCTRL_H__76A55837_6869_4AB3_BFE5_02266C696665__INCLUDED_)
#define AFX_URLISTCTRL_H__76A55837_6869_4AB3_BFE5_02266C696665__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// URListCtrl.h : header file
//
#define URLC_ITEMSELECTED WM_USER + 700 // 自定义消息: 双击列表项
#define URLC_LISTENDDRAG WM_USER + 701 // 自定义消息: 列表项拖操作完成
#define URLC_LISTENDDROP WM_USER + 702 // 自定义消息: 列表项放操作完成
/////////////////////////////////////////////////////////////////////////////
// CURListCtrl window

class CURListCtrl : public CCJListCtrl
{
// Construction
public:
	CURListCtrl();

// Attributes
public:
//	CStringArray m_arrFileName;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CURListCtrl)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetNormalCursor(BOOL bEnable = TRUE);
	void ShowEmptyText(CString strText);
	void SetDragDrop(BOOL bAccept = TRUE);
	virtual ~CURListCtrl();

	// Generated message map functions
protected:
	BOOL m_bIsNormalCursor;
	HCURSOR m_hHotCursor;
	CString m_strEmptyText;
	bool SortList(int nCol, bool bAscending);
	HCURSOR m_hDragOutCursor;
	BOOL m_bCanDrag;
	BOOL m_bDragDrop;
	//{{AFX_MSG(CURListCtrl)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLISTCTRL_H__76A55837_6869_4AB3_BFE5_02266C696665__INCLUDED_)
