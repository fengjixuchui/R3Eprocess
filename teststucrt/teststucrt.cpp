//#include "stdafx.h"
//#include <windows.h>
////#include <cstdio>
////#include <winternl.h>
////#include <atlstr.h>
////
////typedef enum _MEMORY_INFORMATION_CLASS
////{
////	MemoryBasicInformation,
////	MemoryWorkingSetList,
////	MemorySectionName
////}MEMORY_INFORMATION_CLASS;
////
////typedef
////NTSTATUS
////(WINAPI *ZWQUERYVIRTUALMEMORY)
////(
////	IN HANDLE ProcessHandle,
////	IN PVOID BaseAddress,
////	IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
////	OUT PVOID MemoryInformation,
////	IN ULONG MemoryInformationLength,
////	OUT PULONG ReturnLength OPTIONAL
////	);
////
////
////VOID EnumProcessForModule()
////{
////	ZWQUERYVIRTUALMEMORY QueryVirtualMemoryFunction = NULL;
////	DWORD Index = 0;
////	NTSTATUS NtStatus = 0;
////	MEMORY_BASIC_INFORMATION InfoMation;
////	BYTE Buffer[MAX_PATH * 2 + 4] = { 0 };
////	PUNICODE_STRING SectionName = NULL;
////	DWORD Counter;
////	CString ModuleAddress;
////	CString ModuleName;
////
////	QueryVirtualMemoryFunction = (ZWQUERYVIRTUALMEMORY)
////		::GetProcAddress
////		(
////			GetModuleHandle("ntdll.dll"), //ntdll.dll=�ظ�
////			_T("ZwQueryVirtualMemory") //ZwQueryVirtualMemory=�����
////		);
////
////	if (QueryVirtualMemoryFunction == NULL)
////	{
////		printf("��ϹTM��������");
////	}
////	else
////	{
////		for (Index; Index < 0x80000000; Index += 0x1000)
////		{
////			NtStatus = QueryVirtualMemoryFunction
////			(
////				(HANDLE)-1,
////				(PULONG)Index,
////				MemoryBasicInformation,
////				&InfoMation,
////				sizeof(InfoMation),
////				NULL
////			);
////
////			if (NtStatus >= 0)
////			{
////				if (InfoMation.Type == MEM_IMAGE)
////				{
////					if ((DWORD)InfoMation.AllocationBase == Index)
////					{
////						//        ��ô����Ϊʲô,��Ϊ�㲻��������,���õ���ǧ��ģ��,Ϊʲô�أ���Ϊģ��֮�以��ӳ��,��,ͦ�ҵ�,ʵ��˵�ҽ��͵Ĳ�̫���,����������֪����Ҫ���������ڵ�ʱ��ȥ����ѧϰ��PE��,����㲻������Ͱ����ҵķ�����������,����ʵ���ǹ��˵�ͬ����ģ�顣
////						NtStatus = QueryVirtualMemoryFunction
////						(
////							(HANDLE)-1,
////							(PULONG)Index,
////							MemorySectionName,
////							Buffer,
////							//                                             typedef struct MEMORY_SECTION_NAME
////							//                                         {
////							//                                             UNICODE_STRING SectionFileName;
////							//                                             WCHAR       NameBuffer[ANYSIZE_ARRAY];
////							//                                         } *PMEMORY_SECTION_NAME;
////							// 
////							// ����Ϊʲô�������أ���Ϊ�����ײ�һЩ��R3���������鷳,���Է�����,����һ������ͬ����С������,һ�����Խ�������,�ؼ���������ߴ�����,��Ϊ����ṹ���ڿ��ֽڻ�����������������һ������ṹ�����ж������������һ����ԱUNICODE_STRING�������ֵ����MAX_PATH��
////							// �����ʾ260���ֽ�,����Ϊ���ǿ��ַ��������Ծ�Ҫ*2��,�������ڶ�����ԱWCHAR���֪�������[ANYSIZE_ARRAY]��ʾ2,ͬ����ΪUNICODE�Ĺ�ϵҪ*2Ҳ����4,��������ṹ��󲻻ᳬ��[MAX_PATH*2+4],��ô��������ߴ��һ������������ݾʹ´�������,���֪��������Ϊ������ʱ����Զ�����Ϊָ��, ��ô�����������ɣ�����......
////							sizeof(Buffer),
////							NULL
////						);
////
////						if (NtStatus >= 0)
////						{
////							SectionName = (PUNICODE_STRING)Buffer;
////							ModuleName = SectionName->Buffer;
////							printf("Address:%08X ModuleName %s \n",
////								Index, ModuleName);
////
////							//        ModuleAddress.Format(_T("%x"),Index);
////							//                                             Counter=ListGoodsFilter.InsertItem(Counter,ModuleAddress);
////							//                                             ListGoodsFilter.SetItemText(Counter,1,ModuleName);
////							//                                             ��Щ���ǽ����̺��ַ�������,�ҾͲ�������,
////						}
////					}
////				}
////			}
////		}
////	}
////}
////
////
////int  main()
////{
////	EnumProcessForModule();
////	system("pause");
////	return 0;
////}
////#include "sha256.h"
////#include <windows.h>
////#include <tchar.h>
////#include <stack>
////#include <iostream>
////using namespace std;
////typedef struct FILE_CHARACTERISTICS {
////	WORD struct_IMAGE_FILE_RELOCS_STRIPPED : 1;
////	WORD struct_IMAGE_FILE_EXECUTABLE_IMAGE : 1;
////	WORD struct_IMAGE_FILE_LINE_NUMS_STRIPPED : 1;
////	WORD struct_IMAGE_FILE_LOCAL_SYMS_STRIPPED : 1;
////	WORD struct_IMAGE_FILE_AGGRESIVE_WS_TRIM : 1;
////	WORD struct_IMAGE_FILE_LARGE_ADDRESS_AWARE : 1;
////	WORD struct_IMAGE_FILE_BYTES_REVERSED_LO : 1;
////	WORD struct_IMAGE_FILE_32BIT_MACHINE : 1;
////	WORD struct_IMAGE_FILE_DEBUG_STRIPPED : 1;
////	WORD struct_IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP : 1;
////	WORD struct_IMAGE_FILE_NET_RUN_FROM_SWAP : 1;
////	WORD struct_IMAGE_FILE_SYSTEM : 1;
////	WORD struct_IMAGE_FILE_DLL : 1;
////	WORD struct_IMAGE_FILE_UP_SYSTEM_ONLY : 1;
////	WORD struct_IMAGE_FILE_BYTES_REVERSED_HI : 1;
////}ST_Characteristics, *PST_Characteristics;
//////����ص�����
////typedef VOID(*FPTENUMCALLBACK)(LPCTSTR szFullPath, VOID *ptUser);
////std::string Get_PE_Sh256_By_Path(std::string path)
////{
////	//return "NULL";
////	SHA256 sha256;
////	std::string return_string = "NULL";
////	HANDLE hFile;
////	LARGE_INTEGER dwFileSize;
////	BYTE* g_pFileImageBase = NULL;
////	PIMAGE_NT_HEADERS g_pNt = 0;
////	try {
////		hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
////		//�������Ч�ľ��
////		if (hFile == INVALID_HANDLE_VALUE) {
////			//throw  1;
////			goto end;
////		}
////		//��ȡ�ļ���С
////		GetFileSizeEx(hFile, &dwFileSize);
////		LONGLONG L_fileSize = dwFileSize.QuadPart;
////		//�ж��ļ���С
////		if (L_fileSize < 0x40)
////		{
////			goto end;
////		}
////		//�ж��ļ���С
////		if (L_fileSize > 1024 * 1024 * 10)//50M
////		{
////			goto end;
////		}
////		g_pFileImageBase = new BYTE[dwFileSize.QuadPart]{};
////		DWORD dwRead;
////		if (g_pFileImageBase == NULL)
////		{
////			goto end;
////		}
////		bool bRet = ReadFile(hFile, g_pFileImageBase, 0x40, &dwRead, NULL);
////		if (!bRet)
////		{
////
////			goto end;
////		}
////		PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)g_pFileImageBase;
////		if (pDos->e_magic != IMAGE_DOS_SIGNATURE)//0x5A4D('MZ')
////		{
////			goto end;
////		}
////		bRet = ReadFile(hFile, g_pFileImageBase + 0x40, (pDos->e_lfanew - 0x40 + 4), &dwRead, NULL);
////		if (!bRet)
////		{
////
////			goto end;
////		}
////		g_pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + g_pFileImageBase);
////		if (g_pNt->Signature != IMAGE_NT_SIGNATURE)//0x00004550('PE')
////		{
////			goto end;
////		}
////		DWORD len = 0x40 + (pDos->e_lfanew - 0x40 + 4);
////		bRet = ReadFile(hFile, g_pFileImageBase + len, dwFileSize.QuadPart - len, &dwRead, NULL);
////		if (!bRet)
////		{
////
////			goto end;
////		}
////		PST_Characteristics pst_charter = (PST_Characteristics)&(g_pNt->FileHeader.Characteristics);//EXECUTABLE
////		if ((g_pNt->FileHeader.Characteristics&IMAGE_FILE_EXECUTABLE_IMAGE) != IMAGE_FILE_EXECUTABLE_IMAGE) {
////			goto end;
////		}
////		return_string = sha256((char*)g_pFileImageBase, dwFileSize.QuadPart);
////
////	}
////	catch (std::exception &e) {
////		if (hFile != NULL)
////		{
////			CloseHandle(hFile);
////		}
////		if (g_pFileImageBase != NULL)
////		{
////			delete[] g_pFileImageBase;
////			g_pFileImageBase = NULL;
////		}
////		return return_string;
////	};
////end:
////	if (hFile != NULL)
////	{
////		CloseHandle(hFile);
////	}
////	if (g_pFileImageBase != NULL)
////	{
////		delete[] g_pFileImageBase;
////		g_pFileImageBase = NULL;
////	}
////	return return_string;
////}
////
////
////VOID FilePath(LPCTSTR szFullPath, VOID *ptUser)
////{
////	if (NULL == szFullPath)
////	{
////		return;
////	}
////	//����������� 
////	printf("%s==%s\n", szFullPath, Get_PE_Sh256_By_Path(szFullPath).c_str());
////	 
////
////}
////
////
////BOOL EnumDirectory(LPCTSTR szDirectoryPath, FPTENUMCALLBACK EnumCallBack, VOID *ptUser)
////{
////	if (NULL == szDirectoryPath || NULL == EnumCallBack)
////	{
////		return FALSE;
////	}
////
////	LPTSTR szBaseDirectory = new TCHAR[MAX_PATH * 2];
////	if (NULL == szBaseDirectory)
////	{
////		return FALSE;
////	}
////
////	_tcscpy_s(szBaseDirectory, MAX_PATH * 2, szDirectoryPath);
////	if (_T('\\') != szBaseDirectory[_tcslen(szBaseDirectory) - 1])
////	{
////		_tcscat_s(szBaseDirectory, MAX_PATH * 2, _T("\\"));
////	}
////
////	stack<LPTSTR> skTasklist;
////	skTasklist.push(szBaseDirectory);
////
////	HANDLE hFind = NULL;
////	WIN32_FIND_DATA stFindData;
////
////	//��ʼ��������ջ
////	while (FALSE == skTasklist.empty())
////	{
////		LPTSTR szTask = skTasklist.top();
////		skTasklist.pop();
////
////		if (NULL == szTask)
////		{
////			continue;
////		}
////
////		_tcscat_s(szTask, MAX_PATH * 2, _T("*"));
////
////		hFind = FindFirstFile(szTask, &stFindData);
////		if (INVALID_HANDLE_VALUE == hFind)
////		{
////			delete[] szTask;
////			continue;
////		}
////
////		do
////		{
////			LPCTSTR szFileName = stFindData.cFileName;
////			if (0 == _tcscmp(szFileName, _T(".")) || 0 == _tcscmp(szFileName, _T("..")))
////			{
////				continue;
////			}
////
////			LPTSTR szFullFileName = new TCHAR[MAX_PATH * 2];
////			memset(szFullFileName, 0, sizeof(TCHAR) * MAX_PATH * 2);
////
////			_tcscpy_s(szFullFileName, MAX_PATH * 2, szTask);
////			_tcscpy_s(&(szFullFileName[_tcslen(szFullFileName) - 1]), MAX_PATH * 2, szFileName);
////			if (stFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
////			{
////				if (_T('\\') != szFullFileName[_tcslen(szFullFileName) - 1])
////				{
////					_tcscat_s(szFullFileName, MAX_PATH * 2, _T("\\"));
////				}
////				skTasklist.push(szFullFileName);
////			}
////			else
////			{
////				EnumCallBack(szFullFileName, ptUser);		//���ûص�����
////				delete[] szFullFileName;
////			}
////		} while (FindNextFile(hFind, &stFindData));
////
////		delete[] szTask;
////		FindClose(hFind);
////	}
////	return TRUE;
////}
//#include "stdio.h"
//
//typedef DWORD(WINAPI *ZWQUERYSYSTEMINFORMATION)(DWORD, PVOID, DWORD, PDWORD);
//typedef unsigned long ULONG;
//typedef ULONG *PULONG;
//typedef unsigned short USHORT;
//typedef USHORT *PUSHORT;
//typedef unsigned char UCHAR;
//typedef UCHAR *PUCHAR;
//typedef struct _UNICODE_STRING {
//	USHORT Length;
//	USHORT MaximumLength;
//	PWSTR  Buffer;
//} UNICODE_STRING;
//typedef struct _SYSTEM_PROCESS_INFORMATION {
//	DWORD   NextEntryDelta;
//	DWORD   ThreadCount;
//	DWORD   Reserved1[6];
//	FILETIME  ftCreateTime;
//	FILETIME  ftUserTime;
//	FILETIME  ftKernelTime;
//	UNICODE_STRING ProcessName;      // ������.
//	DWORD   BasePriority;
//	DWORD   ProcessId;
//	DWORD   InheritedFromProcessId;
//	DWORD   HandleCount;
//	DWORD   Reserved2[2];
//	DWORD   VmCounters;
//	DWORD   dCommitCharge;
//	PVOID   ThreadInfos[1];
//} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;
//
//#define SystemProcessesAndThreadsInformation 5
//
//void main2()
//{
//	HMODULE hNtDLL = GetModuleHandle("ntdll.dll");
//	if (!hNtDLL)
//		return;
//
//	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)
//		GetProcAddress(hNtDLL, "ZwQuerySystemInformation");
//
//	ULONG cbBuffer = 0x200000;  //Ĭ��
//	LPVOID pBuffer = NULL;
//	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, NULL, 0, &cbBuffer);//��ȡ��С
//	pBuffer = malloc(cbBuffer);
//
//	if (pBuffer == NULL)
//		return;
//
//	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, NULL);
//	PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;
//
//	for (;;)
//	{
//		printf("ProcessID: %d (%ls)\n", pInfo->ProcessId, pInfo->ProcessName.Buffer);
//
//		if (pInfo->NextEntryDelta == 0)
//			break;
//
//		// ������һ�����̵Ľṹ��ַ.
//		pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
//	}
//
//	free(pBuffer);
//	getchar();  //��ͣ.
//}
//
////int main(int argc, char* argv[]) {
////	while (1)
////	{
////		BOOL bError = EnumDirectory("C:", FilePath, NULL);
////	}
////	return 1;
////}
