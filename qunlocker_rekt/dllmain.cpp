#include <windows.h>
#include <iostream>
uintptr_t process_base = 0;

auto patch()
{
	AllocConsole();
	SetConsoleTitleA("Cracked by space785");
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	process_base = *(uintptr_t*)(__readgsqword(0x60) + 0x10);

	__try
	{
		*(uint8_t*)(process_base + 0x01E38B0) = 1;
		printf("> 0x01E38B0\n");

		*(uint8_t*)(process_base + 0x01E3BA9) = 1;
		printf("> 0x01E3BA9\n");

		*(float*)(process_base + 0x01E1458) = 0.0f;
		printf("> 0x01E1458\n");
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		printf("> EXCEPTION_EXECUTE_HANDLER = 0x%08lX\n", GetExceptionCode());
	}

	FreeConsole();
	return 1;
}

bool DllMain(void** dll, unsigned long nigger, void* reserved)
{
	if (nigger == 1)
		return patch();
}