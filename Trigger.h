#include <Windows.h>
#include <thread>
#include "offsets.h"
#include "Bindings.h"


void Trigger(HWND hWnd, DWORD clientdll, HANDLE hProcess) {
	DWORD playerbase;
	int playernumber;

	ReadProcessMemory(hProcess, (LPCVOID)(clientdll + LocalPlayer), &playerbase, sizeof(playerbase), NULL);
	if (playerbase == NULL) {
		return;
	}

	ReadProcessMemory(hProcess, (LPCVOID)(playerbase + CrosshairIDOffset), &playernumber, sizeof(playernumber), NULL);
	if (playernumber < 1 || playernumber > 64 || playernumber == NULL) {
		return;
	}
	else {
		DWORD entity;
		bool dormant;
		int Eteam;
		int Iteam;
		ReadProcessMemory(hProcess, (LPCVOID)(clientdll + EntityListOff + ((playernumber - 1) * 0x10)), &entity, sizeof(entity), NULL);
		ReadProcessMemory(hProcess, (LPCVOID)(entity + 0xE9), &dormant, sizeof(dormant), NULL);
		ReadProcessMemory(hProcess, (LPCVOID)(entity + 0xF0), &Eteam, sizeof(Eteam), NULL);
		ReadProcessMemory(hProcess, (LPCVOID)(playerbase + 0xF0), &Iteam, sizeof(Iteam), NULL);
		if (entity == NULL || Eteam == NULL || Iteam == NULL) {
			return;
		}

		if (Eteam != Iteam && !dormant) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(1);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		}
	}
	while (true) {
		if (GetAsyncKeyState(TriggerBind) & pressed && bTrigger == true) {
			Trigger(hWnd, clientdll, hProcess);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	}
}
