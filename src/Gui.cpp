#include "Gui.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

/// we need a backup of the games original WndProc, otherwise we wont be able to move the ImGui Window!
WNDPROC OriginalWndProc{ nullptr };
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Gui::Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (pDevice && !Gui::bIsInitilised)
	{
		D3DDEVICE_CREATION_PARAMETERS d3dcp = { NULL };
		if (pDevice->GetCreationParameters(&d3dcp) != S_OK)
		{
			return false;
		}

		HWND hWnd = d3dcp.hFocusWindow;

		if (!hWnd)
		{
			return false;
		}

		::OriginalWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (uintptr_t)WindowProcess);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX9_Init(pDevice);

		Gui::bIsInitilised = true;
		return true;
	}

	return false;
}

void Gui::Shutdown(void)
{
	if (Gui::bIsInitilised)
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX9_Shutdown();
		ImGui::DestroyContext();
	}
}

void Gui::Render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello, World");

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (Gui::bRender && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return 1L;
	}

	return CallWindowProc(::OriginalWndProc, hWnd, msg, wParam, lParam);
}
