// Scheduler.h: interface for the CScheduler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEDULER_H__045DC75B_8066_4A75_82AE_C6868D941E4C__INCLUDED_)
#define AFX_SCHEDULER_H__045DC75B_8066_4A75_82AE_C6868D941E4C__INCLUDED_

#include "SimpleTask.h"
#include "SimpleResult.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScheduler : public CObject
{
public:
	CSimpleTask GetTask(CString strTaskName);
	int GetRunTaskCount();
	void ProceedResult(CSimpleResult result);
	BOOL SimpleReplace(CStringArray& arrFileName);
	BOOL ModifyTask(CSimpleTask& task);
	CArray<CSimpleTask, CSimpleTask> m_arrSampleTask;
	CArray<CSimpleResult, CSimpleResult> m_arrSampleResult;
	BOOL SetTaskState(CString strTaskName, BOOL bRun);
	BOOL AddSimpleTask(CSimpleTask& task);
	bool FilterFile(const CString csFileName);
	bool SetFileList(HDROP hFileDroped, bool bIncludeSubFld, CStringArray& listFileName);
	bool SetMaskString(CString strMask);
	CScheduler();
	virtual ~CScheduler();

protected:
	BOOL m_bNewBackup;
	BOOL Backup(CString strFile, CString strReplace);
	CStringArray m_listFile;
	CString m_strFiltrate;

private:
	bool wildcmp(char *wild, char *string);
	void EmuFiles(CString csPath, CStringArray& arrFileName);
	CString ExpandShortcut(CString& csFilename) const;
};

#endif // !defined(AFX_SCHEDULER_H__045DC75B_8066_4A75_82AE_C6868D941E4C__INCLUDED_)
