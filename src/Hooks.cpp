#include "Hooks.hpp"
#include "Gui.hpp"
#include "D3D9/D3D9_Drawing.hpp"

void __stdcall Hooks::HkEndScene(LPDIRECT3DDEVICE9 Original_pDevice)
{
	if (!D3D9::pDevice)
	{
		D3D9::pDevice = Original_pDevice;
	}

	D3D9::DrawFont("Hello, World!", { 500, 500 }, D3DCOLOR_ARGB(255, 255, 255, 255));

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		Gui::bRender = !Gui::bRender;
	}

	if (Gui::bRender && Gui::bIsInitilised)
	{
		Gui::Render();
	}

	::g_EndSceneTrampoline(Original_pDevice);
}