#include <windows.h>
#include "beacon.h"

typedef int WINBASEAPI(*MultiByteToWideChar_t)(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
typedef HANDLE WINBASEAPI(*GetCurrentProcess_t)(VOID);
typedef HANDLE WINBASEAPI(*CreateToolhelp32Snapshot_t)(DWORD dwFlags, DWORD th32ProcessID);
typedef HANDLE WINBASEAPI(*OpenProcess_t)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
typedef HANDLE WINBASEAPI(*CreateFileA_t)(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef HANDLE WINBASEAPI(*CreateFileW_t)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef HANDLE WINBASEAPI(*GetProcessHeap_t)();
typedef BOOL WINBASEAPI (*MoveFileW_t)(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName);
typedef BOOL WINBASEAPI(*CloseHandle_t)(HANDLE hObject);
typedef BOOL WINBASEAPI(*Process32First_t)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL WINBASEAPI(*Process32Next_t)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL WINBASEAPI(*DeviceIoControl_t)(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
typedef BOOL WINBASEAPI(*GetExitCodeProcess_t)(HANDLE hProcess, LPDWORD lpExitCode);
typedef BOOL WINBASEAPI(*WriteFile_t)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
typedef BOOL WINBASEAPI(*DeleteFileW_t)(LPCWSTR lpFileName);
typedef BOOL WINBASEAPI(*GetProcessInformation_t)(HANDLE hProcess, PROCESS_INFORMATION_CLASS ProcessInformationClass, LPVOID ProcessInformation, DWORD ProcessInformationSize);
typedef BOOL WINBASEAPI(*HeapFree_t)(HANDLE, DWORD, PVOID);
typedef DWORD WINBASEAPI(*GetCurrentDirectoryW_t)(DWORD nBufferLength, LPWSTR lpBuffer);
typedef DWORD WINBASEAPI(*GetProcessId_t)(HANDLE Process);
DECLSPEC_IMPORT HLOCAL WINAPI KERNEL32$LocalAlloc(UINT, SIZE_T);
DECLSPEC_IMPORT HLOCAL WINAPI KERNEL32$LocalFree(HLOCAL);
#define MoveFileW ((MoveFileW_t)DynamicLoad("KERNEL32", "MoveFileW"))
#define MultiByteToWideChar ((MultiByteToWideChar_t)DynamicLoad("KERNEL32", "MultiByteToWideChar"))
#define GetCurrentProcess ((GetCurrentProcess_t)DynamicLoad("KERNEL32", "GetCurrentProcess"))
#define CreateToolhelp32Snapshot ((CreateToolhelp32Snapshot_t)DynamicLoad("KERNEL32", "CreateToolhelp32Snapshot"))
#define OpenProcess ((OpenProcess_t)DynamicLoad("KERNEL32", "OpenProcess"))
#define CreateFileA ((CreateFileA_t)DynamicLoad("KERNEL32", "CreateFileA"))
#define CreateFileW ((CreateFileW_t)DynamicLoad("KERNEL32", "CreateFileW"))
#define GetProcessHeap ((GetProcessHeap_t)DynamicLoad("KERNEL32", "GetProcessHeap"))
#define CloseHandle ((CloseHandle_t)DynamicLoad("KERNEL32", "CloseHandle"))
#define Process32First ((Process32First_t)DynamicLoad("KERNEL32", "Process32First"))
#define Process32Next ((Process32Next_t)DynamicLoad("KERNEL32", "Process32Next"))
#define DeviceIoControl ((DeviceIoControl_t)DynamicLoad("KERNEL32", "DeviceIoControl"))
#define GetExitCodeProcess ((GetExitCodeProcess_t)DynamicLoad("KERNEL32", "GetExitCodeProcess"))
#define WriteFile ((WriteFile_t)DynamicLoad("KERNEL32", "WriteFile"))
#define DeleteFileW ((DeleteFileW_t)DynamicLoad("KERNEL32", "DeleteFileW"))
#define GetProcessInformation ((GetProcessInformation_t)DynamicLoad("KERNEL32", "GetProcessInformation"))
#define HeapFree ((HeapFree_t)DynamicLoad("KERNEL32", "HeapFree"))
#define GetCurrentDirectoryW ((GetCurrentDirectoryW_t)DynamicLoad("KERNEL32", "GetCurrentDirectoryW"))
#define GetProcessId ((GetProcessId_t)DynamicLoad("KERNEL32", "GetProcessId"))
#define LocalAlloc KERNEL32$LocalAlloc
#define LocalFree KERNEL32$LocalFree
#define DYNAMIC_LIB_COUNT 1
#ifdef DYNAMIC_LIB_COUNT
typedef struct loadedLibrary {
    HMODULE hMod; 
    const char * name; 
}loadedLibrary, *ploadedLibrary;
loadedLibrary loadedLibraries[DYNAMIC_LIB_COUNT] __attribute__((section (".data"))) = {0};
DWORD loadedLibrariesCount __attribute__((section (".data"))) = 0;

BOOL intstrcmp(LPCSTR szLibrary, LPCSTR sztarget)
{
    BOOL bmatch = FALSE;
    DWORD pos = 0;
    while(szLibrary[pos] && sztarget[pos])
    {
        if(szLibrary[pos] != sztarget[pos])
        {
            goto end;
        }
        pos++;
    }
    if(szLibrary[pos] | sztarget[pos]) 
        {goto end;}
    bmatch = TRUE;

    end:
    return bmatch;
}

FARPROC DynamicLoad(const char * szLibrary, const char * szFunction)
{
    FARPROC fp = NULL;
    HMODULE hMod = NULL;
    DWORD i = 0;
    DWORD liblen = 0;
    for(i = 0; i < loadedLibrariesCount; i++)
    {
        if(intstrcmp(szLibrary, loadedLibraries[i].name))
        {
            hMod = loadedLibraries[i].hMod;
        }
    }
    if(!hMod)
    {
        hMod = LoadLibraryA(szLibrary);
        if(!hMod){ 
            BeaconPrintf(CALLBACK_ERROR, "*** DynamicLoad(%s) FAILED!\nCould not find library to load.", szLibrary);
            return NULL;
        }
        loadedLibraries[loadedLibrariesCount].hMod = hMod;
        loadedLibraries[loadedLibrariesCount].name = szLibrary;
        loadedLibrariesCount++;
    }
    fp = GetProcAddress(hMod, szFunction);

    if (NULL == fp)
    {
        BeaconPrintf(CALLBACK_ERROR, "*** DynamicLoad(%s) FAILED!\n", szFunction);
    }
    return fp;
}
#endif
