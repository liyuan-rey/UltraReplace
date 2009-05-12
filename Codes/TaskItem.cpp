// TaskItem.cpp: implementation of the CTaskItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ur.h"
#include "TaskItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskItem::CTaskItem()
{

}

CTaskItem::~CTaskItem()
{

}

CTaskItem& CTaskItem::operator = (const CTaskItem& rhs)
{
	if(this == &rhs)
		return *this;
	
	m_IsToRun = rhs.m_IsToRun;
	m_strTaskName = rhs.m_strTaskName;
	m_UserData = rhs.m_UserData;
	
	return *this;	
}
