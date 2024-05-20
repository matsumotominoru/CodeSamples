// sample01.cpp

#include <windows.h>

VOID CALLBACK TimerProc(HWND, UINT, UINT, DWORD);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("sample01");    // ウィンドウクラス

int WINAPI WinMain(_In_ HINSTANCE hCurInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpsCmdLine, _In_ int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow))
        return FALSE;

    // メッセージを取得
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
            break;
        }
        else {
            TranslateMessage(&msg);    // メッセージを変換
            DispatchMessage(&msg);     // メッセージを送出
        }
    }

    return (int)msg.wParam;
}

// ウィンドウクラスの登録
ATOM InitApp(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);           // 構造体のサイズ
    wc.style = CS_HREDRAW | CS_VREDRAW;       // クラスのスタイル
    wc.lpfnWndProc = WndProc;                 // プロシージャ名
    wc.cbClsExtra = 0;                        // 補助メモリ
    wc.cbWndExtra = 0;                        // 補助メモリ
    wc.hInstance = hInst;                     // インスタンス
    wc.hIcon = (HICON)LoadImage(              // アイコン
        NULL, IDI_APPLICATION,
        IMAGE_ICON, 0, 0,
        LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(          // カーソル
        NULL, IDC_ARROW,
        IMAGE_CURSOR, 0, 0,
        LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground =                        // 背景ブラシ
        (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;                   // メニュー名
    wc.lpszClassName = szClassName;           // クラス名
    wc.hIconSm = (HICON)LoadImage(            // 小さいアイコン
        NULL, IDI_APPLICATION,
        IMAGE_ICON, 0, 0,
        LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, // クラス名
        TEXT("猫でもわかるWindowsプログラミング"),
        // ウィンドウ名
        WS_OVERLAPPEDWINDOW,     // ウィンドウスタイル
        CW_USEDEFAULT,           // x位置
        CW_USEDEFAULT,           // y位置
        CW_USEDEFAULT,           // ウィンドウ幅
        CW_USEDEFAULT,           // ウィンドウ高さ
        NULL,  // 親ウィンドウのハンドル、親を作るときはNULL
        NULL,  // メニューハンドル、クラスメニューを使うときはNULL
        hInst, // インスタンスハンドル
        NULL   // ウィンドウ作成データ
    );
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);  // ウィンドウの表示状態を設定
    UpdateWindow(hWnd);          // ウィンドウを更新
    return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
        SetTimer(hwnd, 1, 100, TimerProc);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
    HDC hdc;
    static int iCount = 0;
    TCHAR strCount[64];

    iCount++;
    if (iCount == 50) KillTimer(hwnd, 1);

    hdc = GetDC(hwnd);
    wsprintf(strCount, TEXT("%d"), iCount);
    TextOut(hdc, 10, 10, strCount, lstrlen(strCount));
    ReleaseDC(hwnd, hdc);
}