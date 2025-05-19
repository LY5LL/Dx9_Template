#pragma once
#include <d3d9.h>
#include <d3dx9.h>

namespace Gui
{
	inline bool bIsInitilised{ false };
	inline bool bRender{ false };

	bool Init(LPDIRECT3DDEVICE9 pDevice);
	void Shutdown(void);

	void Render(void);
}

