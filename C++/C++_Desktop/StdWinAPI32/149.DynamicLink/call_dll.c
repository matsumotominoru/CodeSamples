#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) {
    static HINSTANCE hDLL;
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
        hDLL = LoadLibrary(TEXT("DLL_TEST.DLL"));
        return 0;
    case WM_LBUTTONUP:
        if (hDLL) FreeLibrary(hDLL);
        return 0;
    }
    return DefWindowProc(hWnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance , PSTR lpCmdLine , int nCmdShow) {
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
