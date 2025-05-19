#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace D3D9
{
	inline LPDIRECT3DDEVICE9 pDevice{ nullptr };

	bool GetD3D9DeviceVTable(LPVOID OutTable[], SIZE_T TableLen);
}



