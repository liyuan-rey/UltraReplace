// SimpleResult.h: interface for the CSimpleResult class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLERESULT_H__4681E045_0182_4748_BE8C_E6BBF73C5947__INCLUDED_)
#define AFX_SIMPLERESULT_H__4681E045_0182_4748_BE8C_E6BBF73C5947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSimpleResult : public CObject  
{
public:
	CString m_strTaskName;
	CStringArray m_arrAccessErr;
	CStringArray m_arrMatch;
	CStringArray m_arrBackupErr;
	CSimpleResult();
	CSimpleResult(const CSimpleResult &);
	virtual ~CSimpleResult();
	CSimpleResult& operator = (const CSimpleResult&);
protected:
	void Clean();
};

#endif // !defined(AFX_SIMPLERESULT_H__4681E045_0182_4748_BE8C_E6BBF73C5947__INCLUDED_)
