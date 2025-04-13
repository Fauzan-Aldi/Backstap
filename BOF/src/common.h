#pragma once
#include <windows.h>
#include <stdio.h>

#define STATUS_SUCCESS   ((NTSTATUS)0x00000000L)
#define MAX_BUF 2056 + 1

BOOL Error(LPSTR szMethod);
BOOL Info(LPSTR szMethod);
BOOL Success(LPSTR szMethod);

PVOID GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName);

BOOL InitializeNecessaryNtAddresses();

LPWSTR charToWChar(LPCSTR szSource);


