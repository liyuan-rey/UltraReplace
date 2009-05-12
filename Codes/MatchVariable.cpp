// MatchVariable.cpp: implementation of the CMatchVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ur.h"
#include "MatchVariable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatchVariable::CMatchVariable()
{

}

CMatchVariable::~CMatchVariable()
{

}

CMatchVariable& CMatchVariable::operator = (const CMatchVariable& rhs)
{
	if(this == &rhs)
		return *this;

	m_bQuestionIsInclude = rhs.m_bQuestionIsInclude;
    m_strVarName = rhs.m_strVarName; 
    m_nVarType = rhs.m_nVarType; 
    m_bUseBlur = rhs.m_bUseBlur; 
    m_nQuestionType = rhs.m_nQuestionType; 
    m_strCustomQuestion =rhs.m_strCustomQuestion; 
    m_bStarIsInclude = rhs.m_bStarIsInclude; 
    m_nStarType = rhs.m_nStarType; 
	m_strCustomStar = rhs.m_strCustomStar;
	
	return *this;
}
