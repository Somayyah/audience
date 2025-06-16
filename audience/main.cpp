#include <windows.h>
#include <mmsystem.h>
#include "resource.h"

#pragma comment(lib, "winmm.lib")

HHOOK mouseHook;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN) {
            HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_CHEER_WAVE), L"WAVE");
            if (hrsrc) {
                HGLOBAL hres = LoadResource(NULL, hrsrc);
                if (hres) {
                    void* pSoundData = LockResource(hres);
                    DWORD dwSize = SizeofResource(NULL, hrsrc);
                    if (pSoundData && dwSize > 0) {
                        PlaySoundA((LPCSTR)pSoundData, NULL, SND_MEMORY | SND_ASYNC);
                    }
                }
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(mouseHook);
    return 0;
}
