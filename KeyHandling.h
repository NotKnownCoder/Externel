#include <windows.h>
#include <thread>
#include "offsets.h"
#include "Bindings.h"

void keys(HANDLE hProcess, DWORD clientdll, DWORD enginedll) {
	while (true) {
		if (GetAsyncKeyState(Num1) & pressed) {
			bTrigger = !bTrigger;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}
