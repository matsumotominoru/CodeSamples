// textoutdll.cpp

#include <windows.h>
#include "textoutdll.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // DLLモジュールのハンドル
    DWORD fdwReason,     // 関数を呼び出す理由
    LPVOID lpvReserved   // 予約済み
) {
    return TRUE;
}

EXPORT BOOL MyTextOut(HDC hdc, int x, int y, LPCTSTR lpszText)
{
    TextOut(hdc, x, y, lpszText, lstrlen(lpszText));
    return TRUE;
}
