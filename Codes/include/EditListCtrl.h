#if !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
#define AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl window

class CEditListCtrl : public CCJListCtrl
{
public:
			CEditListCtrl (CString Text = "Some Text");
    virtual ~CEditListCtrl();

    CString DefaultText;

    CEdit*  EditSubItem (int Item, int Column);
    int	    HitTestEx (CPoint& Point, int* Column);
    int	    InsertItemEx (int Item);
    void    Resize (int cx, int cy);

    //{{AFX_VIRTUAL(CEditListCtrl)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CEditListCtrl)
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
