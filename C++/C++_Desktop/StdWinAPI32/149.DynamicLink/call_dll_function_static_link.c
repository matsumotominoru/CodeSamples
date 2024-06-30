#include <windows.h>
#include "dll_test_2.h"

LRESULT CALLBACK WndProc(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) {
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rectParent , rectChild;

    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        rectChild.right = 200;
        rectChild.bottom = 100;
        GetClientRect(hWnd , &rectParent);

        hdc = BeginPaint(hWnd , &ps);
        if (!GetCenter(&rectParent , &rectChild))
            Rectangle(hdc , 0 , 0 ,
                rectParent.right , rectParent.bottom);
        else Rectangle(hdc , rectChild.left , rectChild.top ,
                rectChild.right , rectChild.bottom);
        EndPaint(hWnd , &ps);
    }
    return DefWindowProc(hWnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
            PSTR lpCmdLine , int nCmdShow) {
    HWND hWnd;
    MSG msg;
    WNDCLASS winc;

    winc.style         = CS_HREDRAW | CS_VREDRAW;
    winc.lpfnWndProc    = WndProc;
    winc.cbClsExtra    = winc.cbWndExtra    = 0;
    winc.hInstance        = hInstance;
    winc.hIcon        = LoadIcon(NULL , IDI_APPLICATION);
    winc.hCursor        = LoadCursor(NULL , IDC_ARROW);
    winc.hbrBackground    = GetStockObject(WHITE_BRUSH);
    winc.lpszMenuName    = NULL;
    winc.lpszClassName    = TEXT("KITTY");

    if (!RegisterClass(&winc)) return 1;

    hWnd = CreateWindow(
            TEXT("KITTY") , TEXT("Kitty on your lap") ,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
            CW_USEDEFAULT , CW_USEDEFAULT ,
            CW_USEDEFAULT , CW_USEDEFAULT ,
            NULL , NULL , hInstance , NULL
    );

    if (hWnd == NULL) return 1;

    while (GetMessage(&msg , NULL , 0 , 0 )) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
