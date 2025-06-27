#include <Windows.h>

#include "MinHook/Include/MinHook.h"
#include "D3D9/D3D9_Device.hpp"
#include "Hooks.hpp"
#include "Gui.hpp"

INT WINAPI HackThread(HINSTANCE hInstance)
{
	void* aD3D9DeviceVTable[119]{};

	if (!D3D9::GetD3D9DeviceVTable(aD3D9DeviceVTable, sizeof(aD3D9DeviceVTable)) || MH_Initialize() != MH_OK)
	{
		FreeLibraryAndExitThread(hInstance, 1);
	}

	if (MH_CreateHook(aD3D9DeviceVTable[42], Hooks::HkEndScene, (LPVOID*)&::g_EndSceneTrampoline) == MH_OK)
	{
		MH_EnableHook(MH_ALL_HOOKS);
	}

	else goto _exit;

	while (D3D9::pDevice == nullptr) Sleep(1);
	if (!Gui::Init(D3D9::pDevice))
	{
		goto _exit;
	}

	while (!GetAsyncKeyState(VK_F1));
_exit:
	MH_DisableHook(MH_ALL_HOOKS);

	if (Gui::bIsInitilised)
	{
		Gui::Shutdown();
	}
	MH_Uninitialize();
	FreeLibraryAndExitThread(hInstance, 0);
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID Reserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE hThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), hInstance, 0, nullptr);

		if (hThread)
		{
			CloseHandle(hThread);
		}
	}

	return TRUE;
}
