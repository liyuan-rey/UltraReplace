// UserData.h: interface for the CUserData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERDATA_H__56BE09D0_A683_40CB_91E4_222B58937956__INCLUDED_)
#define AFX_USERDATA_H__56BE09D0_A683_40CB_91E4_222B58937956__INCLUDED_

#include "MatchVariable.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserData : public CObject  
{
public:
	BOOL m_bIsAdvanced;
	BOOL m_bIsSearchOnly;
	BOOL m_bIsWholeWord;
	BOOL m_bIsIgnoreCase;
	CString m_strSearch;
	CString m_strReplace;
	CList<CMatchVariable, CMatchVariable&> *m_pVariableList;

	CUserData();
	virtual ~CUserData();
	CUserData& operator = (const CUserData&);		
};

#endif // !defined(AFX_USERDATA_H__56BE09D0_A683_40CB_91E4_222B58937956__INCLUDED_)
