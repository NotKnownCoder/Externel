#include <Windows.h>
#include <TlHelp32.h>

DWORD GetModuleBaseExtern(const DWORD dwProcessId, const char *szModuleName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (!hSnap) return 0;

	MODULEENTRY32 me;
	me.dwSize = sizeof(MODULEENTRY32);

	DWORD dwReturn = 0;

	if (Module32First(hSnap, &me)) {
		while (Module32Next(hSnap, &me)) {
			if (lstrcmpi(me.szModule, szModuleName) == 0) {
				dwReturn = (DWORD)me.modBaseAddr;
				break;
			}
		}
	}

	CloseHandle(hSnap);

	return dwReturn;
}
