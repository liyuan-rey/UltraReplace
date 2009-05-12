// UserData.cpp: implementation of the CUserData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ur.h"
#include "UserData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserData::CUserData()
{

}

CUserData::~CUserData()
{

}

CUserData& CUserData::operator = (const CUserData& rhs)
{
	if(this == &rhs)
		return *this;
	
	m_bIsAdvanced = rhs.m_bIsAdvanced;
	m_bIsSearchOnly = rhs.m_bIsSearchOnly;
	m_bIsWholeWord = rhs.m_bIsWholeWord;
	m_bIsIgnoreCase = rhs.m_bIsIgnoreCase;
	m_strSearch = rhs.m_strSearch;
	m_strReplace = rhs.m_strReplace;
	m_pVariableList = rhs.m_pVariableList;
	
	return *this;	
}
