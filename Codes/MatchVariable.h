// MatchVariable.h: interface for the CMatchVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATCHVARIABLE_H__B128788E_8428_4A1D_9291_8F9FE5ACB57E__INCLUDED_)
#define AFX_MATCHVARIABLE_H__B128788E_8428_4A1D_9291_8F9FE5ACB57E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMatchVariable : public CObject  
{
public:
    CString m_strVarName; 
    UINT m_nVarType; 
    BOOL m_bQuestionIsInclude; 
    BOOL m_bUseBlur; 
    UINT m_nQuestionType; 
    CString m_strCustomQuestion; 
    BOOL m_bStarIsInclude; 
    UINT m_nStarType; 
	CString m_strCustomStar;

	CMatchVariable();
	virtual ~CMatchVariable();
	CMatchVariable& operator = (const CMatchVariable &);
};

#endif // !defined(AFX_MATCHVARIABLE_H__B128788E_8428_4A1D_9291_8F9FE5ACB57E__INCLUDED_)
