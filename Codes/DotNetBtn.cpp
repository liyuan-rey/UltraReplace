// DotNetBtn.cpp : implementation file
//

#include "stdafx.h"
#include "UR.h"
#include "DotNetBtn.h"

#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDotNetBtn

CDotNetBtn::CDotNetBtn()
{
	m_bEnabled = FALSE;
	m_bDrawPressed = FALSE;
	m_bPressed = FALSE;
	m_bMouseOnButton = FALSE;
}

CDotNetBtn::~CDotNetBtn()
{
}


BEGIN_MESSAGE_MAP(CDotNetBtn, CWnd)
	//{{AFX_MSG_MAP(CDotNetBtn)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDotNetBtn message handlers

BOOL CDotNetBtn::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CImageList *pImageList, UINT nImagePos)
{
	m_pParentWnd = pParentWnd->GetParent();
	m_pImageList = pImageList;
	m_nImagePos = nImagePos;
	m_strCaption = lpszCaption;
	m_nID = nID;

	return CWnd::Create(NULL,NULL, dwStyle, rect, pParentWnd, nID);
}

BOOL CDotNetBtn::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;

	//return CWnd::OnEraseBkgnd(pDC);
}

void CDotNetBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bEnabled)
		return;

	m_bDrawPressed = TRUE;
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}

void CDotNetBtn::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bEnabled)
		return;

	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(&rect);

	if(rect.PtInRect(point))
	{
		m_bPressed = TRUE;
		m_bMouseOnButton = FALSE;
		m_pParentWnd->PostMessage(WM_COMMAND, m_nID, 0);
	}

	m_bDrawPressed = FALSE;
	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}

void CDotNetBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pWnd;
	CWnd* pParent;

	CWnd::OnMouseMove(nFlags, point);

	// If the mouse enter the button with the left button pressed
	// then do nothing
	if (nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE)
		return;

	if(!m_bEnabled)
		return;

	pWnd = GetActiveWindow();
	pParent = GetOwner();

	if((GetCapture() != this) && (pParent != NULL))
	{
		m_bMouseOnButton = TRUE;
		SetCapture();
		Invalidate();
	}
	else
	{
		POINT pt = point;
		ClientToScreen(&pt);
		CWnd* pWndUnderMouse = WindowFromPoint(pt);

		if(pWndUnderMouse && (pWndUnderMouse->m_hWnd != this->m_hWnd))
		{
			// Redraw only if mouse goes out
			if(m_bMouseOnButton)
			{
				m_bMouseOnButton = FALSE;
				Invalidate();
			}

			// If user is NOT pressing left button,
			// then release capture!
			if(!(nFlags & MK_LBUTTON))
				ReleaseCapture();
		}
	}
}

void CDotNetBtn::SetState(BOOL bPressed)
{
	m_bPressed = bPressed;
	Invalidate();
}

void CDotNetBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	COLORREF clrWhite = GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF clrDkGrey = RGB(10, 36, 106);
	COLORREF clrMedGrey = RGB(133, 146, 181);
	COLORREF clrLtGrey = RGB(182, 189, 210);
	COLORREF clrBlack = GetSysColor(COLOR_BTNTEXT);
	COLORREF clrBtnFace = GetSysColor(COLOR_BTNFACE);

	CMemDC dcMem(&dc);

	CRect rect;
	GetClientRect(rect);

	if (m_bMouseOnButton) // mouse on and pressed
		dcMem.FillRect(rect, &CBrush(clrMedGrey));
	else if (m_bPressed || m_bDrawPressed) // pressed but not mouse on
		dcMem.FillRect(rect, &CBrush(clrLtGrey));
	else
		dcMem.FillRect(rect,&CBrush(clrBtnFace)); // not pressed or mouse on
/* // move to end of draw image block
	rect.DeflateRect(0, 0, 4, 0);
	if (m_bMouseOnButton || m_bPressed || m_bDrawPressed)
		dcMem.Draw3dRect(rect, clrDkGrey, clrDkGrey);
*/
	// Center image
	CPoint pt;

	if (m_bPressed || m_bDrawPressed)
	{
		pt.x = ((rect.Width()  - 32) / 2) + 1;
		pt.y = ((rect.Height() - 32) / 2) - 8 + 1;
	}
	else
	{
		pt.x = (rect.Width()  - 32) / 2;
		pt.y = ((rect.Height() - 32) / 2) - 8;
	}

	dcMem.SetBkMode(TRANSPARENT);

	CBitmap bmpList;
	bmpList.LoadBitmap(IDB_BARBMP);
	
	CBitmap bmpMask;
	bmpMask.CreateBitmap(160, 32, 1, 1, NULL);
	
	CDC dcSrc;
	dcSrc.CreateCompatibleDC(NULL);
	CDC dcDst;
	dcDst.CreateCompatibleDC(NULL);
	
	CBitmap* pbmpSrcT = dcSrc.SelectObject(&bmpList);
	CBitmap* pbmpDstT = dcDst.SelectObject(&bmpMask);
	
	COLORREF clrTopLeft = dcSrc.GetPixel(0, 0);
	COLORREF clrSaveBk = dcSrc.SetBkColor(clrTopLeft);
	
	// This call sets up the mask bitmap.
	dcDst.BitBlt(0, 0, 160, 32, &dcSrc, 0, 0, SRCCOPY);
	
	COLORREF clrSaveDstText = dcSrc.SetTextColor(RGB(255,255,255));
	dcSrc.SetBkColor(RGB(0,0,0));

	dcSrc.BitBlt(0, 0, 160, 32, &dcDst, 0, 0, SRCAND);
	
	dcMem.BitBlt(pt.x, pt.y, 32, 32, &dcDst, 32 * m_nImagePos, 0, SRCAND);
	dcMem.BitBlt(pt.x, pt.y, 32, 32, &dcSrc, 32 * m_nImagePos, 0, SRCPAINT);
	
	// Clean up by deselecting any objects, and delete the 
	// DC's.
	dcDst.SetTextColor(clrSaveDstText);
	dcSrc.SetBkColor(clrSaveBk);
	dcSrc.SelectObject(pbmpSrcT);
	dcDst.SelectObject(pbmpDstT);
	
	DeleteDC(dcSrc);
	DeleteDC(dcDst);
	
	rect.DeflateRect(0, 0, 4, 0);
	if (m_bMouseOnButton || m_bPressed || m_bDrawPressed)
		dcMem.Draw3dRect(rect, clrDkGrey, clrDkGrey);
/*
	HICON hicon;
	hicon = m_pImageList->ExtractIcon(m_nImagePos);
	CSize sz = CSize(32, 32);

	if (m_bEnabled)
		dcMem.DrawState(pt, sz, hicon, DST_ICON | DSS_NORMAL, CBrush());
	else
		dcMem.DrawState(pt, sz, hicon, DST_ICON | DSS_DISABLED, CBrush());
*/
	CFont *pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	dcMem.SelectObject(pFont);

	CRect rcText;
	rcText.SetRect(0, pt.y+32+8, rect.Width(), pt.y+32+8);
	rcText.InflateRect(0, 20);

	if (m_bPressed || m_bDrawPressed)
		rcText.OffsetRect(1, 0);

	if (m_bEnabled)
	{
		if (m_bMouseOnButton)
			dcMem.SetTextColor(clrWhite);
		else
			dcMem.SetTextColor(clrBlack);
		
		dcMem.DrawText(m_strCaption, rcText, DT_VCENTER|DT_SINGLELINE|DT_CENTER);
	}
	else
	{
		dcMem.SetTextColor(clrBlack);
		dcMem.DrawText(m_strCaption, rcText, DT_VCENTER|DT_SINGLELINE|DT_CENTER);

		rcText.OffsetRect(1, 1);
		dcMem.SetTextColor(clrWhite);
		dcMem.DrawText(m_strCaption, rcText, DT_VCENTER|DT_SINGLELINE|DT_CENTER);
	}

	// Do not call CWnd::OnPaint() for painting messages
}
