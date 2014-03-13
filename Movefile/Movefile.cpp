// Movefile.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Movefile.h"
#include <shlwapi.h>
// #import <msxml4.dll>
// using namespace MSXML2;;
// #pragma comment(lib,"msxml2.lib")
// CComPtr<IXMLDOMDocument> spXMLDocument;
// CComPtr<IXMLDOMNode> spXMLNode;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;
void GetApplicationdirectory(CStringA *directory);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	//CoInitialize(NULL);

	CString fileDirectory;
	GetApplicationdirectory(&fileDirectory);
	CString strconfig;
	strconfig=fileDirectory+"\\config.ini";
	if (!PathFileExists(strconfig))
	{
		int x =MessageBox(NULL,"δ���������ļ�config.ini,�Ƿ񴴽�,Ĭ���ļ���Ҫ�޸Ĳ���",NULL,MB_YESNO);
		if(x==6)
		{
			//::CreateFile(strconfig, NULL);
			::WritePrivateProfileStringA("dis_path","filePath","\\\\192.160.114.23\\media\\�V��؈D\\",strconfig);
		}
		
	}


	CTime time=CTime::GetCurrentTime();
	CString m=time.Format("%m%d");
	//CString dis_path("\\\\192.160.114.23\\media\\�V��؈D\\");
	CString dis_path;
	::GetPrivateProfileString("dis_path","filePath",NULL,dis_path.GetBufferSetLength(MAX_PATH+1),MAX_PATH,strconfig);
	dis_path.Append(m);
	if (!PathFileExists(dis_path))
	{
		::CreateDirectory(dis_path, NULL);
	}
	//��ȡ��������Ŀ¼	
	char m_path[MAX_PATH]={0};
	GetModuleFileName(NULL,m_path,MAX_PATH);
	char *ptemp=_tcsrchr(m_path, L'\\');
	if (ptemp)
	{
		ptemp[1]=0;
	}
	CString Tstr,Tstr1;
	Tstr=m_path;
	Tstr.Append("\\*.jpg");
	
	Tstr1=m_path;
	Tstr1.Append("\\*.JPG");

	CFileFind m_filefind;
	BOOL bWorking = m_filefind.FindFile(Tstr)||m_filefind.FindFile(Tstr1);
	while(bWorking)
	{
		bWorking = m_filefind.FindNextFile();
		CString filepath=m_filefind.GetFilePath();
		dis_path.Append(m_filefind.GetFileName());
		BOOL h=MoveFileEx(filepath,dis_path,MOVEFILE_CREATE_HARDLINK|MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING
			);
		//CreateDirectory(dis_path, NULL);
DWORD hw=GetLastError();
	}
	return nRetCode;
}

void GetApplicationdirectory(CStringA *directory)
{
	int pos;
	::GetModuleFileName(NULL,directory->GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	//TRACE(directory);
	pos=directory->ReverseFind('\\');
	*directory=directory->Left(pos);

}
