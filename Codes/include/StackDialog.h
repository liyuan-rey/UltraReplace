/*#############################################################################
# STACKDIALOG.H
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

#ifndef __STACKDIALOG_H__
#define __STACKDIALOG_H__

#include <list>

using namespace std;

class TStackedPage;
class TStackedDialog;

//=============================================================================
// Helper structure to maintain information about each page.
//
//=============================================================================

class TStackedPageHelper {
private:
  BOOL m_bCreated;          // True if m_pDialog is created
  BOOL m_bActive;           // True if dialog is active (has focus)
  UINT m_nDialogID;         // Resource ID of this page
  TStackedPage *m_pDialog;  // Child dialog of this page
  TStackedDialog *m_pParent; // Parent dialog

public:
  DWORD m_dwHelpID;         // Help ID for this page
  DWORD m_dwData1;          // User defined data
  DWORD m_dwData2;          // User defined data

public:
  TStackedPageHelper();
  TStackedPageHelper(const TStackedPageHelper& obj);
  ~TStackedPageHelper();
  TStackedPageHelper& operator=(const TStackedPageHelper& obj);

  TStackedPage *GetPage(void);
  BOOL IsActive(void);
  void Activate(void);
  void Deactivate(void);

  friend class TStackedDialog;
};

typedef list<TStackedPageHelper> TStackedPageHelperList;

//=============================================================================
// This is a stacked dialog page class declaration. 
//
//=============================================================================

class TStackedPage : public CDialog {
public:
	TStackedPage(LPCTSTR lpszTemplateName, CWnd* pParent = NULL);
  TStackedPage(UINT nIDTemplate, CWnd* pParent = NULL);
  virtual ~TStackedPage();

  virtual void OnSetActive(void);
  virtual void OnKillActive(void);
  virtual void OnCreatePage(void);
  virtual void OnDestroyPage(void);

	//{{AFX_VIRTUAL(TStackedPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(TStackedPage)
  virtual void OnOK();
  virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//=============================================================================
// This is a stacked dialog class declaration. This is an abstract class.
// Must derive a class and implement CreatePage() member function.
//
//=============================================================================

class TStackedDialog : public CDialog {
protected:
  UINT m_nPlaceholderID;
  TStackedPageHelperList m_PageList;

private:
  void init(UINT placeholder);
  void flush(void);
  void destroyPageDialog(TStackedPageHelper *pPage);
  TStackedPageHelper *getFirst(void);
  TStackedPageHelper *getCurrent(void);
  TStackedPageHelper *getNext(void);

protected:
  void activatePage(TStackedPageHelper *pPage);
  void deactivatePage(TStackedPageHelper *pPage);

public:
	TStackedDialog(UINT nId, LPCTSTR lpszTemplate, CWnd* pParent = NULL);
  TStackedDialog(UINT nId, UINT nIDTemplate, CWnd* pParent = NULL);
  virtual ~TStackedDialog();

  TStackedPageHelper *AddPage(UINT nId, DWORD dwHelpId = 0L,
                              DWORD dwData1 = 0, DWORD dwData2 = 0);
  void DelPage(TStackedPageHelper *pPage);

  void SetPage(void);
  void SetPage(UINT nId);
  void SetFirstPage(void);
  void SetNextPage(void);

  TStackedPageHelper *GetPage(void);
  TStackedPageHelper *GetPage(UINT nId);

  virtual TStackedPage *CreatePage(UINT nId) = 0;
  virtual void OnPageChanged(UINT nId, BOOL bActivated) = 0;

	//{{AFX_VIRTUAL(TStackedDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(TStackedDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

/*#############################################################################
# End of file STACKDIALOG.H
#############################################################################*/

