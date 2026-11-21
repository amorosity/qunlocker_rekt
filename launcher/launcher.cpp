#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main()
{
	DWORD pid = 0;
	HWND hwnd = FindWindowA(nullptr, "Q DBD UNLOCKER");
	if (hwnd)
		GetWindowThreadProcessId(hwnd, &pid);
	else
	{
		MessageBoxA(0, "failed to find unlocker process.", 0, MB_TOPMOST | MB_ICONERROR);
		exit(0);
	}

	auto p = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	auto m = VirtualAllocEx(p, 0, 32, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	WriteProcessMemory(p, m, "crack.dll", 10, 0);
	CreateRemoteThread(p, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA"), m, 0, 0);
}
