// Screen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>


int screenWidth;
int screenHeight;
int interval = 100;

LRESULT CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		HDC desktop = GetDC(HWND_DESKTOP);
		HDC window = GetDC(hWnd);

		BitBlt(window, 0, 0, screenWidth, screenHeight, desktop, 0, 0, SRCCOPY);

		ReleaseDC(hWnd, window);
		ReleaseDC(HWND_DESKTOP, desktop);

		SetTimer(hWnd,0,interval,0);
		ShowWindow(hWnd, SW_SHOW);


		break;
	}

	case WM_PAINT:
	{
		ValidateRect(hWnd, 0);

		break;
	}
	case WM_TIMER:
	{
		HDC wndw = GetDC(hWnd);

		int x = (rand() % screenWidth) - (200 / 2);
		int y = (rand() % 15);

		int width = (rand() % 200);

		BitBlt(wndw, x, y, width, screenHeight, wndw, x, 0, SRCCOPY);

		ReleaseDC(hWnd, wndw);

		break;
	}

	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);

		PostQuitMessage(0);
		break;
	}

	return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}

int APIENTRY main(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int ShowCmd) 
{
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CXSCREEN);

	WNDCLASS wndClass = { 0, Melt,0,0,inst,0, LoadCursorW(0,IDC_ARROW), 0,0, L"ScreenMelting" };

	if (RegisterClass(&wndClass)) 
	{
		HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelting", 0, WS_POPUP, 0, 0, screenWidth, screenHeight,
			HWND_DESKTOP, 0, inst, 0);
			
		if (hWnd)
		{
			srand(GetTickCount());

			MSG msg = { 0 };

			while (msg.message != WM_QUIT) 
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);

					DispatchMessage(&msg);
				}
			}
		}
	}
}