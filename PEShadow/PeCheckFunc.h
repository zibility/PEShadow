#pragma once


#include "Common.h"

BOOL	LoadFileData(WCHAR* wzFilePath,CHAR** szFileData,ULONG* ulLow);
BOOL    IsPEFile(CHAR* szFileData,PETYPE* PeType);