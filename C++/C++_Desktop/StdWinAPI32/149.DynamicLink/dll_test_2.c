#include <windows.h>
#include "dll_test_2.h"

int WINAPI DllEntryPoint(HINSTANCE hInstance , DWORD fdwReason , PVOID pvReserved) {
    return TRUE;
}

DLL_EXPORT BOOL CALLBACK GetCenter(LPRECT lpParent , LPRECT lpChild) {
    if (lpParent->right < lpChild->right || lpParent->bottom < lpChild->bottom)
        return FALSE;

    lpChild->left = lpParent->right / 2 - lpChild->right / 2;
    lpChild->top = lpParent->bottom / 2 - lpChild->bottom / 2;
    lpChild->right += lpChild->left;
    lpChild->bottom += lpChild->top;
    return TRUE;
}
