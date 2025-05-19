#include "D3D9_Device.hpp"

BOOL CALLBACK GetCurrentWindow(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcId{};
	GetWindowThreadProcessId(hWnd, &dwProcId);

	if (GetCurrentProcessId() == dwProcId)
	{
		*(HWND*)lParam = hWnd;
		return FALSE;
	}

	return TRUE;
}

bool D3D9::GetD3D9DeviceVTable(LPVOID OutTable[], SIZE_T TableLen)
{
	/// Pretty nice resource, explains most of the parameters used here:
	/// http://www.directxtutorial.com/LessonList.aspx?listid=9

	if (!OutTable)
	{
		return false;
	}

	LPDIRECT3D9 pD3D9{ nullptr };
	LPDIRECT3DDEVICE9 pDummyDevice{ nullptr };
	D3DPRESENT_PARAMETERS d3dpp = { NULL };

	pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D9)
	{
		return false;
	}

	EnumWindows(GetCurrentWindow, (LPARAM)&d3dpp.hDeviceWindow);
	if (!d3dpp.hDeviceWindow)
	{
		return false;
	}

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	HRESULT hr = pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (hr != S_OK) 
	{
		d3dpp.Windowed = FALSE;
		HRESULT hr = pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (hr != S_OK)
		{
			pD3D9->Release();
			return false;
		}
	}

	memcpy(OutTable, *(void***)pDummyDevice, TableLen);

	pDummyDevice->Release();
	pD3D9->Release();
	return true;
}
