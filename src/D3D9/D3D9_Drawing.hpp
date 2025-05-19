#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../Types.hpp"

namespace D3D9
{
	inline LPD3DXFONT pFont;

	void DrawRect(Vector2 vecPos, Vector2 vecSize, D3DCOLOR color);
	void DrawLine(Vector2 vecSrc, Vector2 vecDst, int iThickness, D3DCOLOR color);
	void DrawFont(LPCSTR fmt, Vector2 vecPos, D3DCOLOR color);
}

