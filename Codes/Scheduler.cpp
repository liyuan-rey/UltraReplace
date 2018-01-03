// Scheduler.cpp: implementation of the CScheduler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ur.h"
#include "Scheduler.h"

#include <sys/stat.h> // for SetFileList
#include <direct.h>
#include "URDlg.h"
#include "ResultPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScheduler::CScheduler()
{
	m_strFiltrate = URR_FILTERSTRING;
}

CScheduler::~CScheduler()
{

}

bool CScheduler::SetMaskString(CString strMask)
{
	if (strMask.FindOneOf("\\/:\"<>") != -1)
	{
//		MessageBox(AfxGetMainWnd()->m_hWnd, _T("过滤字符串包含非法字符:\n\\ / : \" < >"), _T("错误"), MB_ICONWARNING | MB_OK);
		AfxMessageBox(_T("过滤字符串包含非法字符:\n\\ / : \" < >"));
		return false;
	}

	m_strFiltrate = strMask;

	return true;
}

bool CScheduler::SetFileList(HDROP hFileDroped, bool bIncludeSubFld, CStringArray &listFileName)
{
	//
	// Get the number of pathnames (files or folders) dropped
	//
	UINT nNumFilesDropped = DragQueryFile(hFileDroped, 0xFFFFFFFF, NULL, 0);

	//
	// Iterate through the pathnames and process each one
	//
	TCHAR szFilename[MAX_PATH + 1];
	CString csPathname;
	CString csExpandedFilename;

	for (UINT nFile = 0 ; nFile < nNumFilesDropped; nFile++)
	{
		//
		// Get the pathname
		//
		DragQueryFile(hFileDroped, nFile, szFilename, MAX_PATH + 1);

		//
		// It might be shortcut, so try and expand it
		//
		csPathname = szFilename;
		csExpandedFilename = ExpandShortcut(csPathname);
		if(!csExpandedFilename.IsEmpty())
		{
			csPathname = csExpandedFilename;
		}

		//
		// Get some info about that path so we can filter out dirs
		// and files if need be
		//
		struct _stat buf;
		int result = _tstat( csPathname, &buf );
		if( result == 0 )
		{
			//
			// Do we have a directory? (if we want dirs)
			//
			if (bIncludeSubFld && ((buf.st_mode & _S_IFDIR) == _S_IFDIR)) 
			{
				// enumerate folder and check every file in it
				EmuFiles(csPathname, listFileName);
			} 
			else if ((buf.st_mode & _S_IFREG) == _S_IFREG)
			{
				// do check file
				if (FilterFile(csPathname))
					listFileName.Add(csPathname);
			}
			else
			{
				AfxMessageBox("UnKnown droped object!");
				return false;
			}
		}
		else
		{
			AfxMessageBox("Parse file list false!");
			return false;
		}
	}

	return true;
}

CString CScheduler::ExpandShortcut(CString &csFilename) const
{
	USES_CONVERSION;		// For T2COLE() below
	CString csExpandedFile;

	//
    // Make sure we have a path
	//
	if(csFilename.IsEmpty())
	{
		ASSERT(FALSE);
		return csExpandedFile;
	}

	//
    // Get a pointer to the IShellLink interface
	//
    HRESULT hr;
    IShellLink* pIShellLink;

	// here has some error!!
    hr = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
							IID_IShellLink, (LPVOID*) &pIShellLink);

    if (SUCCEEDED(hr))
    {

		//
        // Get a pointer to the persist file interface
		//
		IPersistFile* pIPersistFile;
        hr = pIShellLink->QueryInterface(IID_IPersistFile, (LPVOID*) &pIPersistFile);

        if (SUCCEEDED(hr))
        {
			//
            // Load the shortcut and resolve the path
			//
            // IPersistFile::Load() expects a UNICODE string
			// so we're using the T2COLE macro for the conversion
			//
			// For more info, check out MFC Technical note TN059
			// (these macros are also supported in ATL and are
			// so much better than the ::MultiByteToWideChar() family)
			//
            hr = pIPersistFile->Load(T2COLE(csFilename), STGM_READ);
			
			if (SUCCEEDED(hr))
			{
				WIN32_FIND_DATA wfd;
				hr = pIShellLink->GetPath(csExpandedFile.GetBuffer(MAX_PATH),
										  MAX_PATH,
										  &wfd,
										  SLGP_UNCPRIORITY);

				csExpandedFile.ReleaseBuffer(-1);
            }
            pIPersistFile->Release();
        }
        pIShellLink->Release();
    }

    return csExpandedFile;
}

void CScheduler::EmuFiles(CString csPath, CStringArray &arrFileName)
{
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	hFind = FindFirstFile(csPath + "\\*.*", &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		// handle some error

		return;
	}

	DWORD dwResult;
	do
	{
		CString strPath = FindFileData.cFileName;
		// pass . and .. directory
		if(strPath == "." || strPath == "..")
		{
			dwResult = FindNextFile(hFind, &FindFileData);
			continue;
		}

//		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY == FILE_ATTRIBUTE_DIRECTORY)
//		TRACE1("%d\n",
//			FindFileData.dwFileAttributes);
//		TRACE1("%d\n",
//			FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
//		TRACE1("%d\n",
//			FILE_ATTRIBUTE_DIRECTORY);

		if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
		{
			// this is a sub directory
			// recursive get every file in folder
			EmuFiles(csPath + "\\" + strPath, arrFileName);
		}
		else
		{
			// this is a file
			// check it
			if (FilterFile(strPath))
				arrFileName.Add(csPath + "\\" + strPath);
		}

		dwResult = FindNextFile(hFind, &FindFileData);
	}
	while(dwResult != ERROR_NO_MORE_FILES && dwResult != 0);

	if(dwResult == 0)
	{
		// handle some error
		;
	}

	FindClose(hFind);
}

bool CScheduler::FilterFile(const CString csFileName)
{
	// 确定需要过滤
	if(csFileName.IsEmpty())
		return false;

	CStringArray arrFiltrate;
	CString strTemp;

	int nLength = m_strFiltrate.GetLength();
	int nFrom = 0;
	int nTo = m_strFiltrate.Find('|', 0);
	while(1)
	{
		// 字符串开头
		if(nTo == -1 && nFrom == 0)
		{
			strTemp = m_strFiltrate;
			arrFiltrate.Add(strTemp);
			break;
		}

		// 字符串结尾
		if(nTo == -1 && nFrom != 0)
		{
			strTemp = m_strFiltrate.Right(nLength - nFrom - 1);
			arrFiltrate.Add(strTemp);
			break;
		}

		if(nTo != -1 && nFrom == 0)
		{
			strTemp = m_strFiltrate.Mid(nFrom, nTo - nFrom);
		}

		if(nTo != -1 && nFrom != 0)
		{
			strTemp = m_strFiltrate.Mid(nFrom + 1, nTo - nFrom - 2);
		}
		
		arrFiltrate.Add(strTemp);

		nFrom = nTo;
		nTo = m_strFiltrate.Find('|', nFrom + 1);
	}

	CString strFileName = csFileName.Right(csFileName.GetLength() - csFileName.ReverseFind('\\') - 1);

	bool bPass = false;
	for(int i = 0; i < arrFiltrate.GetSize(); i++)
	{
		TCHAR filtrate[MAX_PATH], filename[MAX_PATH];
		_tcscpy(filtrate, (LPCTSTR)(arrFiltrate.GetAt(i)));
		_tcscpy(filename, (LPCTSTR)strFileName);
		if(wildcmp(filtrate, filename))
		{
			bPass = true;
			break;
		}
	}	
	
	return bPass;
}

bool CScheduler::wildcmp(char *wild, char *string)
{
//	if(strcmp(*temp, "*.*") == 0)
//		return true;

	char *cp, *mp;
	
	while ((*string) && (*wild != '*'))
	{
		if ((*wild != *string) && (*wild != '?'))
		{
			return false;
		}
		wild++;
		string++;
	}
	
	while (*string)
	{
		if (*wild == '*')
		{
			if (!*++wild)
			{
				return true;
			}
			mp = wild;
			cp = string+1;
		}
		else if ((*wild == *string) || (*wild == '?'))
		{
			wild++;
			string++;
		}
		else
		{
			wild = mp;
			string = cp++;
		}
	}
	
	while (*wild == '*')
	{
		wild++;
	}
	return !*wild;
}

BOOL CScheduler::AddSimpleTask(CSimpleTask& task)
{
	m_arrSampleTask.Add(task);

	return TRUE;
}

BOOL CScheduler::SetTaskState(CString strTaskName, BOOL bRun)
{
	int nSize = m_arrSampleTask.GetSize();
	BOOL bFound = FALSE;
	for(int i = 0; i < nSize; i++)
	{
		CString strComp = m_arrSampleTask[i].m_strTaskName;
		if(strTaskName.Compare(strComp) == 0)
		{
			m_arrSampleTask[i].m_bRun = bRun;
			bFound = TRUE;
			break;
		}
	}

	if(!bFound)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}

BOOL CScheduler::ModifyTask(CSimpleTask& task)
{
	int nSize = m_arrSampleTask.GetSize();
	BOOL bFound = FALSE;
	for(int i = 0; i < nSize; i++)
	{
		CString strComp = m_arrSampleTask[i].m_strTaskName;
		if(task.m_strTaskName.Compare(strComp) == 0)
		{
			task.m_bRun = m_arrSampleTask[i].m_bRun;
			m_arrSampleTask.RemoveAt(i);
			m_arrSampleTask.Add(task);
			m_arrSampleTask.FreeExtra();
			bFound = TRUE;
			break;
		}
	}
	
	if(!bFound)
	{
		ASSERT(FALSE);
		return FALSE;
	}
	
	return TRUE;	
}

#define FILE_READ_BLOCKSIZE 51200 // 50 * 1024 =51200
BOOL CScheduler::SimpleReplace(CStringArray &arrFileName)
{
	CWaitCursor waitCursor;
	m_bNewBackup = TRUE;
	// 设置文件列表
	m_listFile.RemoveAll();
	m_listFile.Copy(arrFileName);
	
	// 构造可执行任务列表
	CArray<CSimpleTask, CSimpleTask> arrTask; 
	int nTaskNum = m_arrSampleTask.GetSize();
	for(int i = 0; i < nTaskNum; i++)
	{
		if(m_arrSampleTask[i].m_bRun)
			arrTask.Add(m_arrSampleTask[i]);
	}

	// 替换操作
	nTaskNum = arrTask.GetSize();
	for(i = 0; i < nTaskNum; i++)
	{
		CSimpleResult result;
		result.m_strTaskName = arrTask.GetAt(i).m_strTaskName;

		// 文件循环
		int nFileNum = m_listFile.GetSize();
		for(int j = 0; j < nFileNum; j++)
		{
			// 打开目标文件
			CString strFileName = m_listFile.GetAt(j);
			CFile stdFile;
			if(!stdFile.Open(strFileName, CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary))
			{
				// 文件访问失败
				result.m_arrAccessErr.Add(strFileName);
				continue;
			}
			
			BOOL bReplace = !(arrTask.GetAt(i).m_bIsSearchOnly);
			// 得到临时文件
			TCHAR tmpPath[MAX_PATH] = "";
			TCHAR tmpFileName[MAX_PATH] = "";
			CFile tmpFile;
			if(bReplace)
			{
				::GetTempPath(MAX_PATH, tmpPath);
				::GetTempFileName(tmpPath, "~urr", 0, tmpFileName);
				ASSERT(tmpFileName != "");

				if(!tmpFile.Open(tmpFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite/*shareExclusive*/ | CFile::typeBinary))
				{
					result.m_arrAccessErr.Add(strFileName);
					continue;
				}
			}

			// 打开文件成功, 构造查找字串
			CString strSearch = arrTask.GetAt(i).m_strSearch;
			CString strReplace = arrTask.GetAt(i).m_strReplace;
			// 全字匹配
			if(arrTask.GetAt(i).m_bIsWholeWord)
				strSearch.Format(" %s ", strSearch);

			// 不区分大小写
			if(arrTask.GetAt(i).m_bIsIgnoreCase)
				strSearch.MakeLower();

			TCHAR tBuffer[FILE_READ_BLOCKSIZE + 1] = "";
			int nSearchLength = strSearch.GetLength();
			int nReplaceLength = strReplace.GetLength();

			DWORD dwReadPos = 0;

			DWORD nBytesRead = FILE_READ_BLOCKSIZE;
			BOOL bFound = TRUE;
			while(nBytesRead == FILE_READ_BLOCKSIZE || bFound)
			{
				stdFile.Seek(dwReadPos, CFile::begin);
				nBytesRead = stdFile.Read(tBuffer, FILE_READ_BLOCKSIZE);
				if(nBytesRead == FILE_READ_BLOCKSIZE)
					tBuffer[FILE_READ_BLOCKSIZE] = '\0';
				else
					tBuffer[nBytesRead] = '\0';
				CString srhText = tBuffer;
				CString strToWrite = srhText;

				// 不区分大小写
				if(arrTask.GetAt(i).m_bIsIgnoreCase)
					srhText.MakeLower();

				// 查找字串
				int nRet = srhText.Find(strSearch);
				if(nRet == -1)
				{
					// 没找到
					if(bReplace)
					{
						tmpFile.Write((LPCTSTR)strToWrite, strToWrite.GetLength());
						tmpFile.Seek(-(nSearchLength - 1), CFile::current);
					}

					bFound = FALSE;
					dwReadPos += nBytesRead - (nSearchLength - 1);
					continue;
				}

				// 找到一个匹配
				bFound = TRUE;
				CString strPos;
				strPos.Format("%d", dwReadPos + nRet);

				if(!bReplace)
				{
					result.m_arrMatch.Add(strFileName + "|" + strPos + "|0");
				}
				else
				{
					// 替换
					int nWrited = 0;
					tmpFile.Write((LPCTSTR)strToWrite, nRet);
					
					tmpFile.Write((LPCTSTR)strReplace, nReplaceLength);

					// 文件搜索完毕
					if(nBytesRead != FILE_READ_BLOCKSIZE)
					{
						CString strTemp = strToWrite.Right(strToWrite.GetLength() - nRet - nSearchLength);
						tmpFile.Write((LPCTSTR)strTemp, strTemp.GetLength());
					}

					result.m_arrMatch.Add(strFileName + "|" + strPos + "|1");
				}
				
				dwReadPos += nRet + nSearchLength;
			}
			
			stdFile.Close();
			if(bReplace)
				tmpFile.Close();
			
			// 备份文件
			if(bReplace)
				if(!Backup(strFileName, tmpFileName))
					result.m_arrBackupErr.Add(strFileName);
		}
		
		ProceedResult(result);
	}

	return TRUE;
}

void CScheduler::ProceedResult(CSimpleResult result)
{
	m_arrSampleResult.Add(result);
	// 添加到列表
	CListCtrl* pListCtrl = &(((CResultPage*)(((CURDlg*)AfxGetMainWnd())->GetPage(IDD_PAGE_RESULT))->GetPage())->m_ResultListCtrl);
	ASSERT(pListCtrl != NULL);

//	result.m_arrAccessErr.FreeExtra();
//	result.m_arrBackupErr.FreeExtra();
	result.m_arrMatch.FreeExtra();

	pListCtrl->SetRedraw(FALSE);
	int nCount = result.m_arrMatch.GetSize();
	CString strItemText = "";
	for(int i = 0; i < nCount; i++)
	{
		CString strResult = result.m_arrMatch.GetAt(i);
		int nPos1 = strResult.Find('|');
		strItemText.Format("任务 %s 文件 %s ", result.m_strTaskName, strResult.Left(nPos1));
		CString strTemp = strItemText;
		int nPos2 = strResult.Find('|', nPos1 + 1);
		strItemText.Format("%s位置 %s 匹配查找", strTemp, strResult.Mid(nPos1 + 1, nPos2 - nPos1 - 1));
		if(strResult.Right(1) == "1")
			strItemText += "且替换完成";

		pListCtrl->InsertItem(pListCtrl->GetItemCount(), strItemText);
	}
	pListCtrl->SetRedraw();
}

int CScheduler::GetRunTaskCount()
{
	int nRet = 0;
	m_arrSampleTask.FreeExtra();
	int nSize = m_arrSampleTask.GetSize();
	for(int i = 0; i < nSize; i++)
		if(m_arrSampleTask[i].m_bRun == TRUE)
			nRet++;

	return nRet;
}

BOOL CScheduler::Backup(CString strFile, CString strReplace)
{
	_mkdir(".\\Backup");
	// 文件操作
	int nRet = 0;
	SHFILEOPSTRUCT shFileOP;
	shFileOP.hwnd = NULL;
	shFileOP.fFlags = FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
	shFileOP.lpszProgressTitle = NULL;
	shFileOP.hNameMappings = NULL;
	shFileOP.hNameMappings = NULL;

	if(m_bNewBackup)
	{
		shFileOP.wFunc = FO_DELETE;
		shFileOP.pFrom = ".\\Backup\\URB*.*\0";
		shFileOP.pTo = "\0";

		if(SHFileOperation(&shFileOP))
			return FALSE;
	}

	// 备份原文件
	shFileOP.wFunc = FO_COPY;
	strFile += '\0';
	shFileOP.pFrom = strFile;
	TCHAR tmpFileName[MAX_PATH + 1] = "";
	::GetTempFileName(".\\Backup", "URB", 0, tmpFileName);
	shFileOP.pTo = tmpFileName;
	
	if(SHFileOperation(&shFileOP))
	{
#ifdef _DEBUG
		DWORD dwErr = GetLastError();
		TCHAR tchar[260] = "";
		FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM, 0, 
			dwErr,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),tchar, 259, 0);
#endif

		return FALSE;
	}
	
	// 拷贝替换文件
	shFileOP.wFunc = FO_MOVE;
	strReplace += '\0';
	shFileOP.pFrom = strReplace;
	shFileOP.pTo = strFile;
	
	if(SHFileOperation(&shFileOP))
		return FALSE;
	
	// 写文件映射
	CStdioFile fileMap;
	BOOL bOpened = FALSE;
	if(m_bNewBackup)
	{
		// create new map
		bOpened = fileMap.Open(".\\Backup\\URBackup.map", CFile::modeWrite | CFile::shareDenyWrite | CFile::modeCreate | CFile::typeText);
	}
	else
	{
		bOpened = fileMap.Open(".\\Backup\\URBackup.map", CFile::modeWrite | CFile::shareDenyWrite | CFile::typeText);
	}

	if(!bOpened)
		return FALSE;

	fileMap.SeekToEnd();
	CString strInfo = tmpFileName;
	strInfo += "=";
	strInfo += strFile + "\n";
	fileMap.WriteString(strInfo);
	fileMap.Close();

	m_bNewBackup = FALSE;
	return TRUE;
}

CSimpleTask CScheduler::GetTask(CString strTaskName)
{
	CSimpleTask retTask;
	int nSize = m_arrSampleTask.GetSize();
	BOOL bFound = FALSE;
	for(int i = 0; i < nSize; i++)
	{
		CString strComp = m_arrSampleTask[i].m_strTaskName;
		if(strTaskName.Compare(strComp) == 0)
		{
			retTask = m_arrSampleTask.GetAt(i);
			bFound = TRUE;
			break;
		}
	}
	VERIFY(bFound);

	return retTask;
}
