#include "D3D9_Drawing.hpp"
#include "D3D9_Device.hpp"

void D3D9::DrawRect(Vector2 vecPos, Vector2 vecSize, D3DCOLOR color)
{
	D3DRECT rect{ vecPos.x, vecPos.y, vecPos.x + vecSize.x, vecPos.y + vecSize.y };
	D3D9::pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void D3D9::DrawLine(Vector2 vecSrc, Vector2 vecDst, int iThickness, D3DCOLOR color)
{
	ID3DXLine* lpLine;
	D3DXCreateLine(D3D9::pDevice, &lpLine);
	lpLine->SetWidth(iThickness);

	D3DXVECTOR2 aLines[2];
	aLines[0] = { vecSrc.x, vecSrc.y };
	aLines[1] = { vecDst.x, vecDst.y };
	lpLine->Draw(aLines, 2, color);
	lpLine->Release();
}

void D3D9::DrawFont(LPCSTR fmt, Vector2 vecPos, D3DCOLOR color)
{
	if (D3D9::pFont == nullptr)
	{
		HRESULT status = D3DXCreateFontA(pDevice, 32, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "serif", &pFont);

		if (status != S_OK)
		{
			return;
		}
	}

	RECT rect{ vecPos.x + 1, vecPos.y + 1, vecPos.x + 1, vecPos.y + 1 };
	pFont->DrawTextA(NULL, fmt, -1, &rect, DT_CENTER | DT_NOCLIP, color);
}
