#pragma once

#include "common.h"
#include <psapi.h>
#include <tlhelp32.h>
#include <winternl.h>

#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004
#define CONST_SYSTEM_HANDLE_INFORMATION 16
#define CONST_OBJECT_BASIC_INFORMATION 0
#define CONST_OBJECT_NAME_INFORMATION 1
#define CONST_OBJECT_TYPE_INFORMATION 2


typedef NTSTATUS(WINAPI* fNtQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength);

typedef NTSTATUS(NTAPI* fNtDuplicateObject)(
	HANDLE SourceProcessHandle,
	HANDLE SourceHandle,
	HANDLE TargetProcessHandle,
	PHANDLE TargetHandle,
	ACCESS_MASK DesiredAccess,
	ULONG Attributes,
	ULONG Options
	);


typedef NTSTATUS(NTAPI* fNtQueryObject)(
	HANDLE ObjectHandle,
	ULONG ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);



typedef enum _POOL_TYPE
{
	NonPagedPool,
	PagedPool,
	NonPagedPoolMustSucceed,
	DontUseThisType,
	NonPagedPoolCacheAligned,
	PagedPoolCacheAligned,
	NonPagedPoolCacheAlignedMustS
}
POOL_TYPE, * PPOOL_TYPE;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;			
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, * PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _THREAD_CONTEXT
{
	HANDLE hDup;
	char   szFileName[MAX_PATH];
}
THREAD_CONTEXT, * PTHREAD_CONTEXT;

typedef struct
{
	char   szFileName[MAX_PATH];
	char   szProcessName[MAX_PATH];
	HANDLE FileHandle;
	ULONG  ProcessId;
}
HANDLE_INFO, * PHANDLE_INFO;
HANDLE _DuplicateHandle(HANDLE hSrcProcess, USHORT usHandleValue);



VOID PrintHandleInformation(HANDLE hContainingProcess, USHORT usHandleValue);

VOID ListProcessHandles(HANDLE hProcess, HANDLE hProcExpDevice);

BOOL GetProcessPIDFromName(LPSTR szProcessName, PDWORD lpPID);

PVOID GetObjectAddressFromHandle(DWORD dwPID, USHORT usTargetHandle);

PSYSTEM_HANDLE_INFORMATION GetHandleInformationTable();

PSYSTEM_HANDLE_INFORMATION ReAllocateHandleInfoTableSize(ULONG ulTable_size, PSYSTEM_HANDLE_INFORMATION handleInformationTable);

VOID KillProcessHandles(HANDLE hProcess, HANDLE hProcExpDevice);
