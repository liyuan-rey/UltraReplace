// SimpleTask.h: interface for the CSimpleTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLETASK_H__8610B93F_2E52_4EC1_B5C8_FFDF5EBA9701__INCLUDED_)
#define AFX_SIMPLETASK_H__8610B93F_2E52_4EC1_B5C8_FFDF5EBA9701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSimpleTask : public CObject  
{
public:
	BOOL m_bRun;
	CString m_strTaskName;
	BOOL m_bIsSearchOnly;
	BOOL m_bIsWholeWord;
	BOOL m_bIsIgnoreCase;
	CString m_strSearch;
	CString m_strReplace;

	CSimpleTask();
	CSimpleTask(const CSimpleTask &);
	virtual ~CSimpleTask();
	CSimpleTask& operator = (const CSimpleTask&);
};

#endif // !defined(AFX_SIMPLETASK_H__8610B93F_2E52_4EC1_B5C8_FFDF5EBA9701__INCLUDED_)
