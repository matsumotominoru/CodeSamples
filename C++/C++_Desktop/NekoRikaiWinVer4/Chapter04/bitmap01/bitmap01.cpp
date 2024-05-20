// bitmap01.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("bitmap01");  // ウィンドウクラス
HINSTANCE hInst;

int WINAPI WinMain(_In_ HINSTANCE hCurInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpsCmdLine, _In_ int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;

    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow))
        return FALSE;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
            break;
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

// ウィンドウクラスの登録
ATOM InitApp(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;  // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;      // インスタンス
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW,
                    IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;    // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
               TEXT("猫でもわかるビットマップ"),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT,
               CW_USEDEFAULT, CW_USEDEFAULT,
               NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HDC hdc, hdc_mem;
    PAINTSTRUCT ps;
    HBITMAP hBmp;
    BITMAP bmp_info;
    int w, h;

    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);

            // ビットマップリソース「MYBMP」を読み込む
            hBmp = LoadBitmap(hInst, TEXT("MYBMP"));

            // ビットマップの情報を取得し、幅と高さを変数に保管
            GetObject(hBmp, (int)sizeof(BITMAP), &bmp_info);
            w = bmp_info.bmWidth;
            h = bmp_info.bmHeight;

            // メモリデバイスコンテキストを作成
            hdc_mem = CreateCompatibleDC(hdc);

            // メモリデバイスコンテキストにビットマップを選択
            SelectObject(hdc_mem, hBmp);

            // ビットマップを転送
            BitBlt(hdc, 0, 0, w, h, hdc_mem, 0, 0, SRCCOPY);
            StretchBlt(hdc, w, 0, w * 2, h * 2, hdc_mem, 0, 0, w, h, SRCCOPY);

            DeleteDC(hdc_mem);   // メモリデバイスコンテキストを破棄
            DeleteObject(hBmp);  // ビットマップオブジェクトを破棄

            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}
