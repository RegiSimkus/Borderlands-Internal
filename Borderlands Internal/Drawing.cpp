#include "pch.h"
#include "IncDX9.h"
#include "Drawing.h"

D3DCOLOR color_white = D3DCOLOR_RGBA(255, 255, 255, 255);

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR col)
{
	D3DRECT rect = {
		x, y,
		x + w,
		y + h
	};

	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, col, 0, 0);
}