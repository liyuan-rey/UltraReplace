// TaskItem.h: interface for the CTaskItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKITEM_H__09E87BF1_2699_482C_A881_C28B4D68C90A__INCLUDED_)
#define AFX_TASKITEM_H__09E87BF1_2699_482C_A881_C28B4D68C90A__INCLUDED_

#include "UserData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTaskItem : public CObject  
{
public:
	BOOL m_IsToRun;
	CString m_strTaskName;
	CUserData m_UserData;

	CTaskItem();
	virtual ~CTaskItem();
	CTaskItem& operator = (const CTaskItem&);	
};

#endif // !defined(AFX_TASKITEM_H__09E87BF1_2699_482C_A881_C28B4D68C90A__INCLUDED_)
