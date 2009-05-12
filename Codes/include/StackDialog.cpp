/*#############################################################################
# STACKDIALOG.CPP
#
# SCA Software International S.A.
# http://www.scasoftware.com
# scaadmin@scasoftware.com
#
# Copyright (c) 1999 SCA Software International S.A.
#
# Date: 17.12.1999.
# Author: Zoran M.Todorovic
#
# This software is provided "AS IS", without a warranty of any kind.
# You are free to use/modify this code but leave this header intact.
# 
#############################################################################*/

#include "stdafx.h"
#include "StackDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//=============================================================================
// Helper structure to maintain information about each page.
//
//=============================================================================

TStackedPageHelper::TStackedPageHelper()
{
  m_pDialog = NULL;
  m_bCreated = FALSE;
  m_bActive = FALSE;
}

TStackedPageHelper::TStackedPageHelper(const TStackedPageHelper& obj)
{ 
  *this = obj;
}

TStackedPageHelper::~TStackedPageHelper()
{
}

TStackedPageHelper& TStackedPageHelper::operator=(const TStackedPageHelper& obj)
{
  m_nDialogID = obj.m_nDialogID;
  m_pDialog = obj.m_pDialog;
  m_dwHelpID = obj.m_dwHelpID;
  m_bCreated = obj.m_bCreated;
  m_bActive = obj.m_bActive;
  m_dwData1 = obj.m_dwData1;
  m_dwData2 = obj.m_dwData2;
  return *this;
}

// Returns a pointer to child dialog associated with this page
TStackedPage *TStackedPageHelper::GetPage(void)
{
  return m_pDialog;
}

// Returns TRUE if the child dialog associated with this page is currently
// selected, visible and focused
BOOL TStackedPageHelper::IsActive(void)
{
  return m_bActive;
}

// Activate this page and associated child dialog
void TStackedPageHelper::Activate(void)
{
  m_pParent->SetPage(m_nDialogID);
}

// Deactivate this page and associated child dialog
void TStackedPageHelper::Deactivate(void)
{
  m_pParent->SetPage();
}

//=============================================================================
// class TStackedPage
//
//=============================================================================

BEGIN_MESSAGE_MAP(TStackedPage, CDialog)
	//{{AFX_MSG_MAP(TStackedPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

TStackedPage::TStackedPage(LPCTSTR lpszTemplateName, CWnd* pParent)
                   :CDialog(lpszTemplateName,pParent)
{
}

TStackedPage::TStackedPage(UINT nIDTemplate, CWnd* pParent)
                   :CDialog(nIDTemplate,pParent)
{
}

TStackedPage::~TStackedPage()
{
}

void TStackedPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TStackedPage)
	//}}AFX_DATA_MAP
}

void TStackedPage::OnOK()
{
}

void TStackedPage::OnCancel()
{
}

BOOL TStackedPage::OnInitDialog() 
{
	CDialog::OnInitDialog();

  DWORD style = GetStyle();
  ASSERT((style & WS_CHILD) != 0);
  ASSERT((style & WS_BORDER) == 0);
  ASSERT((style & WS_DISABLED) != 0);

  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Called when a page is displayed
void TStackedPage::OnSetActive(void)
{
}

// Called before a page becomes invisible
void TStackedPage::OnKillActive(void)
{
}

// Called after the page is created
void TStackedPage::OnCreatePage(void)
{
}

// Called before the page is destroyed
void TStackedPage::OnDestroyPage(void)
{
}

//=============================================================================
// class TStackedDialog
//
//=============================================================================

BEGIN_MESSAGE_MAP(TStackedDialog, CDialog)
	//{{AFX_MSG_MAP(TStackedDialog)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


TStackedDialog::TStackedDialog(UINT nPlaceholder, LPCTSTR lpszTemplateName, 
                               CWnd* pParent)
               :CDialog(lpszTemplateName,pParent)
{
  init(nPlaceholder);
}

TStackedDialog::TStackedDialog(UINT nPlaceholder, UINT nIDTemplate, 
                               CWnd* pParent)
               :CDialog(nIDTemplate,pParent)
{
  init(nPlaceholder);
}

TStackedDialog::~TStackedDialog()
{
}

void TStackedDialog::init(UINT placeholder)
{
  m_nPlaceholderID = placeholder;
}

void TStackedDialog::flush(void)
{
  TStackedPageHelper *pPage;
  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    pPage = &(*it);
    destroyPageDialog(pPage);
  }
  m_PageList.clear();
}

void TStackedDialog::destroyPageDialog(TStackedPageHelper *pPage)
{
  if (pPage->m_bCreated) {
    pPage->m_bCreated = FALSE;
    ASSERT(pPage->m_pDialog != NULL);
    pPage->m_pDialog->OnKillActive();
    pPage->m_pDialog->OnDestroyPage();
    pPage->m_pDialog->DestroyWindow();
    delete pPage->m_pDialog;
    pPage->m_pDialog = NULL;
  }
}

TStackedPageHelper *TStackedDialog::getFirst(void)
{
  TStackedPageHelperList::iterator it = m_PageList.begin();
  if (it != m_PageList.end())
    return &(*it);
  return NULL;
}

TStackedPageHelper *TStackedDialog::getCurrent(void)
{
  TStackedPageHelper *pPage = NULL;
  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    if (it->m_bActive) {
      pPage = &(*it);
      break;
    }
  }
  return pPage;
}

TStackedPageHelper *TStackedDialog::getNext(void)
{
  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    if (it->m_bActive) {
      it ++;
      if (it != m_PageList.end())
        return &(*it);
      return getFirst();
    }
  }
  return getFirst();
}

void TStackedDialog::activatePage(TStackedPageHelper *pPage)
{
  ASSERT(pPage != NULL);
  ASSERT(pPage->m_pDialog != NULL);
  ASSERT(pPage->m_bCreated != FALSE);
  TStackedPage *pDialog = pPage->m_pDialog;
  // Show and update window
  pDialog->ShowWindow(SW_SHOW);
  pDialog->InvalidateRect(NULL);
  pDialog->UpdateWindow();
  pDialog->OnSetActive();
  pPage->m_bActive = TRUE;
  OnPageChanged(pPage->m_nDialogID, TRUE);
}

void TStackedDialog::deactivatePage(TStackedPageHelper *pPage)
{
  ASSERT(pPage != NULL);
  ASSERT(pPage->m_pDialog != NULL);
  ASSERT(pPage->m_bCreated != FALSE);
  TStackedPage *pDialog = pPage->m_pDialog;
  pDialog->OnKillActive();
  pDialog->ShowWindow(SW_HIDE);
  pPage->m_bActive = FALSE;
  OnPageChanged(pPage->m_nDialogID, FALSE);
}

BOOL TStackedDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
  ModifyStyleEx (0, WS_EX_CONTROLPARENT);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void TStackedDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TStackedDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void TStackedDialog::OnDestroy() 
{
  flush();
  CDialog::OnDestroy();
}

// Add a new page (associated child dialog with resource nId) to the 
// stacked dialog. Returns a pointer to the internal helper object that 
// maintains the state of the page
TStackedPageHelper *TStackedDialog::AddPage(UINT nId, DWORD dwHelpId,
                                            DWORD dwData1, DWORD dwData2) 
{
  TStackedPageHelper page;
  page.m_nDialogID = nId;
  page.m_dwHelpID = dwHelpId;
  page.m_dwData1 = dwData1;
  page.m_dwData2 = dwData2;

  TStackedPageHelperList::iterator it;
  it = m_PageList.insert(m_PageList.end(), page);
  TStackedPageHelper *pPage = &(*it);

  pPage->m_pParent = this;

  pPage->m_pDialog = CreatePage(pPage->m_nDialogID);
  ASSERT(pPage->m_pDialog != NULL);
  pPage->m_pDialog->Create(pPage->m_nDialogID,this);
  ASSERT(IsWindow(pPage->m_pDialog->m_hWnd) != FALSE);

  CRect rect;
  CWnd *pWnd = GetDlgItem(m_nPlaceholderID);
  ASSERT(pWnd != NULL);
  ASSERT(IsWindow(pWnd->m_hWnd) != FALSE);
  pWnd->GetWindowRect(&rect);
  ScreenToClient(&rect);
  pPage->m_pDialog->SetWindowPos(NULL, rect.left, rect.top, 0, 0, 
                       SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
  pPage->m_pDialog->EnableWindow(TRUE);
  pPage->m_pDialog->OnCreatePage();
  pPage->m_bCreated = TRUE;

  return pPage;
}

// Delete page identified with a pointer to its helper object
void TStackedDialog::DelPage(TStackedPageHelper *pPage)
{
  ASSERT(pPage != NULL);
  destroyPageDialog(pPage);

  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    if (pPage == &(*it)) {
      m_PageList.erase(it);
      break;
    }
  }
}

// Activate no page (actually deactivates the active page)
void TStackedDialog::SetPage(void)
{
  TStackedPageHelper *pOldPage = NULL;
  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    if ((pOldPage == NULL) && it->m_bActive)
      pOldPage = &(*it);
  }
  if (pOldPage)
    deactivatePage(pOldPage);
}

// Activate the page with the specified child dialog resource
void TStackedDialog::SetPage(UINT nId)
{
  TStackedPageHelper *pOldPage = NULL, *pNewPage = NULL;

  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    if ((pNewPage == NULL) && (it->m_nDialogID == nId))
      pNewPage = &(*it);
    if ((pOldPage == NULL) && it->m_bActive)
      pOldPage = &(*it);
  }

  if (pOldPage)
    deactivatePage(pOldPage);
  if (pNewPage)
    activatePage(pNewPage);
}

// Set first page as active page
void TStackedDialog::SetFirstPage(void)
{
  TStackedPageHelper *pPage = getFirst();
  if (pPage)
    SetPage(pPage->m_nDialogID);
}

// Set next page as active page
void TStackedDialog::SetNextPage(void)
{
  TStackedPageHelper *pPage = getNext();
  if (pPage)
    SetPage(pPage->m_nDialogID);
}

// Get helper object associated with the currently active page
TStackedPageHelper *TStackedDialog::GetPage(void)
{
  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    if (it->m_bActive)
      return &(*it);
  }
  return NULL;
}

// Get helper object associated with the specified child resource id
TStackedPageHelper *TStackedDialog::GetPage(UINT nId)
{
  TStackedPageHelperList::iterator it;
  for (it = m_PageList.begin(); it != m_PageList.end(); it ++) {
    if (it->m_nDialogID == nId)
      return &(*it);
  }
  return NULL;
}

/*#############################################################################
# End of file STACKDIALOG.CPP
#############################################################################*/
