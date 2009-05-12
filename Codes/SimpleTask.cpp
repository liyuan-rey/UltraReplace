// SimpleTask.cpp: implementation of the CSimpleTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ur.h"
#include "SimpleTask.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimpleTask::CSimpleTask()
{
	m_bIsSearchOnly = FALSE;
	m_bIsWholeWord = FALSE;
	m_bIsIgnoreCase = FALSE;
	m_strSearch = "";
	m_strReplace = "";
	m_strTaskName = "";
	m_bRun = FALSE;
}

CSimpleTask::CSimpleTask(const CSimpleTask & rhs)
{
	m_bIsSearchOnly = rhs.m_bIsSearchOnly;
	m_bIsWholeWord = rhs.m_bIsWholeWord;
	m_bIsIgnoreCase = rhs.m_bIsIgnoreCase;
	m_strSearch = rhs.m_strSearch;
	m_strReplace = rhs.m_strReplace;
	m_strTaskName = rhs.m_strTaskName;
	m_bRun = rhs.m_bRun;
}

CSimpleTask::~CSimpleTask()
{

}

CSimpleTask& CSimpleTask::operator = (const CSimpleTask& rhs)
{
	if(this == &rhs)
		return *this;

	m_bIsSearchOnly = rhs.m_bIsSearchOnly;
	m_bIsWholeWord = rhs.m_bIsWholeWord;
	m_bIsIgnoreCase = rhs.m_bIsIgnoreCase;
	m_strSearch = rhs.m_strSearch;
	m_strReplace = rhs.m_strReplace;
	m_strTaskName = rhs.m_strTaskName;
	m_bRun = rhs.m_bRun;
	
	return *this;
}


