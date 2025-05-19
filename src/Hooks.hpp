#pragma once
#include <Windows.h>

#include "D3D9/D3D9_Device.hpp"

typedef void(__stdcall* EndScene) (LPDIRECT3DDEVICE9 pDevice);
inline EndScene g_EndSceneTrampoline{ nullptr };

namespace Hooks
{
	void __stdcall HkEndScene(LPDIRECT3DDEVICE9 Original_pDevice);
}

