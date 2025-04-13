#pragma once

#include "common.h"


#define STATUS_IMAGE_ALREADY_LOADED 0xC000010E
#define STATUS_OBJECT_NAME_COLLISION 0xC0000035

typedef void (WINAPI* fRtlInitUnicodeString)(PUNICODE_STRING, PCWSTR);
typedef NTSTATUS(*fNtLoadDriver)(IN PUNICODE_STRING DriverServiceName);
typedef NTSTATUS(*fNtUnLoadDriver)(IN PUNICODE_STRING DriverServiceName);

BOOL LoadDriver(LPWSTR szPath, LPWSTR szServiceName);

BOOL UnloadDriver(LPWSTR szDriverPath, LPWSTR szServiceName);