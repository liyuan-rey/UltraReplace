// URListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "URListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CURApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CURListCtrl

CURListCtrl::CURListCtrl()
{
	//init member variable
	m_hDragOutCursor = LoadCursor(theApp.m_hInstance, MAKEINTRESOURCE(IDC_DRAGOUT));
	m_hHotCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	m_bIsNormalCursor = FALSE;
	m_bDragDrop = FALSE;
}

CURListCtrl::~CURListCtrl()
{
}


BEGIN_MESSAGE_MAP(CURListCtrl, CCJListCtrl)
	//{{AFX_MSG_MAP(CURListCtrl)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CURListCtrl message handlers

void CURListCtrl::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
//	AfxMessageBox("Files droped!");

	CStringArray arrFileName;
	LPSCHEDULER(pScheduler);
	if(pScheduler->SetFileList(hDropInfo, true, arrFileName))
	{
		// remove duplicate items, and add item to list view
		int i, iTemp, nInserted;
		iTemp = arrFileName.GetSize();
		nInserted = GetItemCount();

		SetRedraw(FALSE);
		for(i = 0; i < iTemp; i++)
		{
			bool bExisted = false;

			// GetSize every time, 
			// becuz array(m_arrFileName) maybe modify
			int j, jTemp;
/*			jTemp = m_arrFileName.GetSize();
			for(j = 0; j < jTemp; j++)
				if(arrFileName.GetAt(i) == m_arrFileName.GetAt(j))
				{
					bExisted = true;
					break;
				}
*/
			jTemp = GetItemCount();
			for(j = 0; j < jTemp; j++)
				if(arrFileName.GetAt(i) == GetItemText(j, 0))
				{
					bExisted = true;
					break;
				}

			if(!bExisted)
			{
				InsertItem(nInserted, _T(arrFileName.GetAt(i)));
				nInserted++;
//				m_arrFileName.Add(arrFileName.GetAt(i));
			}
		}
		SetRedraw();
	}
	else
		AfxMessageBox("SetFileList false!");
	
	//
	// Free the dropped-file info that was allocated by windows
	//
	DragFinish(hDropInfo);

	// 发送拖完成消息
	::SendMessage(GetParent()->m_hWnd, URLC_LISTENDDROP, 0, 0);
	
	//	CCJListCtrl::OnDropFiles(hDropInfo);
}

void CURListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bCanDrag = TRUE;

	CCJListCtrl::OnLButtonDown(nFlags, point);
}

void CURListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bCanDrag)
	{
		m_bCanDrag = FALSE;

		if(m_bDragDrop)
		{
			// drag out is over
			CRect rect;
			GetWindowRect(rect);
			ScreenToClient(rect);
			if(rect.PtInRect(point))
			{
//				AfxMessageBox("File drag out!");
				ReleaseCapture();

				return;
			}

			//do drag out file handle, emu select item
			POSITION pos = GetFirstSelectedItemPosition();
			if (pos != NULL)
			{
				while (pos)
				{
					// Do NOT use GetNextSelectedItem(pos),
					// becuz we will delete item from listview
					int nItem = GetNextSelectedItem(pos);
					// remove selected item
//					CString strRemove = GetItemText(nItem, 0);
//					for(int i = 0; i < m_arrFileName.GetSize(); i++)
//					{
//						if(m_arrFileName.GetAt(i) == strRemove)
//							m_arrFileName.RemoveAt(i);
//					}

					DeleteItem(nItem);
					// Do NOT use GetNextSelectedItem(pos),
					// becuz we will delete item from listview
					pos = GetFirstSelectedItemPosition();
				}
				// free extra memory
//				m_arrFileName.FreeExtra();
			}

			ReleaseCapture();

			// 发送放完成消息
			::SendMessage(GetParent()->m_hWnd, URLC_LISTENDDRAG, 0, 0);
		}
	}
	
	CCJListCtrl::OnLButtonUp(nFlags, point);
}

void CURListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bDragDrop && m_bCanDrag && (nFlags == MK_LBUTTON))
	{
		SetCapture();
		if(m_hDragOutCursor != GetCursor())
			SetCursor(m_hDragOutCursor);
	}
	
	CCJListCtrl::OnMouseMove(nFlags, point);
}

void CURListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bCanDrag = FALSE;

	// 检测选中消息
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = GetNextSelectedItem(pos);
		// 发送消息
		LVITEM item;
		item.mask = LVIF_TEXT;
		item.iItem = nItem;
		item.iSubItem = 0;
		item.pszText = "";
		item.state = 0;
		item.stateMask = 0;
		item.iImage = 0;
		item.lParam = 0;
		
		::SendMessage(GetParent()->m_hWnd, URLC_ITEMSELECTED, 0, (LPARAM)(&item));
	}

	CCJListCtrl::OnLButtonDblClk(nFlags, point);
}

void CURListCtrl::SetDragDrop(BOOL bAccept/*= TRUE*/)
{
	DragAcceptFiles(bAccept);
	m_bDragDrop = bAccept;
}

void CURListCtrl::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	int nItem = GetItemCount();

	if(GetItemCount() != 0)
		Default();
	else
	{
		if ( nItem >= 0 )
		{
			CPaintDC dc( this );
			int nSavedDC = dc.SaveDC();
        
			CRect rc;
			GetWindowRect( &rc );
			ScreenToClient( &rc );
        
			CHeaderCtrl* pHC;
			pHC = GetHeaderCtrl();
			if (pHC != NULL)
			{
				CRect rcH;
				pHC->GetItemRect( 0, &rcH );
				rc.top += rcH.bottom;
			}
			rc.top += 10;
        
			dc.SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
			dc.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );

			CFont font;
			NONCLIENTMETRICS ncm;
			ncm.cbSize = sizeof(ncm);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
			ncm.lfMessageFont.lfWeight = 700;
			VERIFY(font.CreateFontIndirect(&ncm.lfMessageFont));

			dc.SelectObject(&font);
			dc.DrawText( m_strEmptyText, -1, 
						 rc, 
						 DT_CENTER | DT_WORDBREAK | DT_NOPREFIX | DT_NOCLIP );

			font.DeleteObject();
			dc.RestoreDC(nSavedDC);
		}
	}

	// Do not call CCJListCtrl::OnPaint() for painting messages
}

bool CURListCtrl::SortList(int nCol, bool bAscending)
{
	TRACE2("Column sort on column index %d, ascending=%d\n", nCol, bAscending);

	CCJSortClass sortClass(this, nCol);
	sortClass.Sort(bAscending, DT_STRING);

	return true;
}

void CURListCtrl::ShowEmptyText(CString strText)
{
	m_strEmptyText = strText;
	Invalidate();
}

void CURListCtrl::SetNormalCursor(BOOL bEnable)
{
	if(bEnable)
	{
		if(!m_bIsNormalCursor)
		{
			m_hHotCursor = SetHotCursor(m_hHotCursor);
			m_bIsNormalCursor = FALSE;
		}
	}
	else
	{
		if(m_bIsNormalCursor)
		{
			m_hHotCursor = SetHotCursor(m_hHotCursor);
			m_bIsNormalCursor = TRUE;
		}
	}
}
