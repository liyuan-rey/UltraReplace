// SimpleResult.cpp: implementation of the CSimpleResult class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ur.h"
#include "SimpleResult.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimpleResult::CSimpleResult()
{
}

CSimpleResult::~CSimpleResult()
{

}

CSimpleResult::CSimpleResult(const CSimpleResult & rhs)
{
	m_strTaskName = rhs.m_strTaskName;
	Clean();
	m_arrAccessErr.Copy(rhs.m_arrAccessErr);
	m_arrMatch.Copy(rhs.m_arrMatch);
	m_arrBackupErr.Copy(rhs.m_arrBackupErr);
}

CSimpleResult& CSimpleResult::operator = (const CSimpleResult& rhs)
{
	if(this == &rhs)
		return *this;

	m_strTaskName = rhs.m_strTaskName;
	Clean();
	m_arrAccessErr.Copy(rhs.m_arrAccessErr);
	m_arrMatch.Copy(rhs.m_arrMatch);
	m_arrBackupErr.Copy(rhs.m_arrBackupErr);

	return *this;
}

void CSimpleResult::Clean()
{
	m_arrAccessErr.RemoveAll();
	m_arrAccessErr.FreeExtra();

	m_arrMatch.RemoveAll();
	m_arrMatch.FreeExtra();

	m_arrBackupErr.RemoveAll();
	m_arrBackupErr.FreeExtra();
}
