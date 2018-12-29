#include <iostream>
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
#include <Thread>
#include <stdlib.h>
#include "offsets.h"
#include "Trigger.h"
#include "Module.h"

int main() {
	TriggerBind = 0x63;
	HWND hWnd;
	DWORD pID;

	hWnd = FindWindow(0, "Counter-Strike: Global Offensive");
	while (!hWnd)
	{
		std::cout << "Open CS:GO";
		Sleep(5000);
		hWnd = FindWindow(0, "Counter-Strike: Global Offensive");
	}

	GetWindowThreadProcessId(hWnd, &pID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (!hProcess)
	{
		std::cout << "Can't open process";
	}

	DWORD clientdll = GetModuleBaseExtern(pID, "client.dll");
	DWORD enginedll = GetModuleBaseExtern(pID, "engine.dll");


	std::thread THTrigger(Trigger, std::ref(hProcess), std::ref(hWnd), std::ref(clientdll));
	while (true) {
		Sleep(100000);
	}
}
