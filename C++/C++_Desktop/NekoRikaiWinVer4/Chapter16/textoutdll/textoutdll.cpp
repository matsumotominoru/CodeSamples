// textoutdll.cpp

#include <windows.h>
#include "textoutdll.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // DLL���W���[���̃n���h��
    DWORD fdwReason,     // �֐����Ăяo�����R
    LPVOID lpvReserved   // �\��ς�
) {
    return TRUE;
}

EXPORT BOOL MyTextOut(HDC hdc, int x, int y, LPCTSTR lpszText)
{
    TextOut(hdc, x, y, lpszText, lstrlen(lpszText));
    return TRUE;
}
