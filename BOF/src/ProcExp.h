#pragma once

#include "common.h"
#include "Processes.h"

#define IOCTL_CLOSE_HANDLE 2201288708
#define IOCTL_OPEN_PROTECTED_PROCESS_HANDLE 2201288764
#define IOCTL_GET_HANDLE_NAME 2201288776
#define IOCTL_GET_HANDLE_TYPE 2201288780

typedef struct _ioControl
{
	ULONGLONG ulPID;
	PVOID lpObjectAddress;
	ULONGLONG ulSize;
	ULONGLONG ulHandle;
} PROCEXP_DATA_EXCHANGE, *PPROCEXP_DATA_EXCHANGE;


HANDLE ProcExpOpenProtectedProcess(ULONGLONG ulPID, HANDLE hProcExpDevice);

ULONGLONG ConvertInputHandleToULONG(LPSTR szHandle);


BOOL ProcExpKillHandle(DWORD PID, ULONGLONG usHandle, HANDLE hProcExpDevice);
HANDLE ConnectToProcExpDevice();

BOOL PrintProtectedHandleInformation(ULONGLONG ulPID, ULONGLONG ulProtectedHandle, PVOID lpObjectAddress, HANDLE hProcExpDevice);
>
BOOL ProcExpGetObjectInformation(PROCEXP_DATA_EXCHANGE data, DWORD dwIOCTL, LPWSTR szInfo, HANDLE hProcExpDevice);


