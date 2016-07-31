
#include "stdafx.h"
#include "PeCheckFunc.h"



BOOL LoadFileData(WCHAR* wzFilePath,CHAR** szFileData,ULONG* ulLow)
{

	HANDLE hFile;
	ULONG ulHigh = 0;
	ULONG ulReturn = 0;

	if (wzFilePath==NULL)
	{
		return FALSE;
	}

	hFile = CreateFileW(wzFilePath,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	*ulLow = GetFileSize(hFile,&ulHigh); 

	*szFileData = new char[*ulLow + 20];

	if (ReadFile(hFile,*szFileData,*ulLow,&ulReturn,NULL)==0)
	{
		CloseHandle(hFile);
		delete *szFileData;
		return FALSE;
	}

	return TRUE;
}

BOOL	IsPEFile(CHAR* szFileData,PETYPE* PeType)
{
	PIMAGE_DOS_HEADER	DosHead =NULL;
	PIMAGE_NT_HEADERS	NtHead = NULL;
	IMAGE_FILE_HEADER	FileHead = {0};

	DosHead = (PIMAGE_DOS_HEADER)szFileData;
	if (DosHead->e_magic!=IMAGE_DOS_SIGNATURE)
	{
		return FALSE;
	}

	NtHead = (PIMAGE_NT_HEADERS)((ULONG)szFileData+DosHead->e_lfanew);

	if (NtHead->Signature!=IMAGE_NT_SIGNATURE)
	{
		return FALSE;
	}

	FileHead = NtHead->FileHeader;
	switch(FileHead.Machine)   //根据NT头中的FileHeader.Machine判断是哪种32or64PE文件
	{
	case IMAGE_FILE_MACHINE_IA64:
	case IMAGE_FILE_MACHINE_AMD64:
		{
			*PeType = Bit64;
			break;
		}
	case IMAGE_FILE_MACHINE_I386:
		{
			*PeType = Bit32;
			break;
		}


	default: *PeType = Unkonw;
	}

	return TRUE;


}