// sample01.cpp

#include <windows.h>
#define TM_COUNT1 1
#define TM_COUNT2 2

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
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rctSize;
    static int iCount1 = 0, iCount2 = 0;
    static TCHAR strCount[64];

    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
        SetTimer(hwnd, TM_COUNT1, 100, NULL);
        SetTimer(hwnd, TM_COUNT2, 500, NULL);
        return 0;
    case WM_TIMER:
        switch (wp) {
        case TM_COUNT1:
            iCount1++;
            break;
        case TM_COUNT2:
            iCount2++;
            break;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        wsprintf(strCount, TEXT("TM_COUNT1 = %d\nTM_COUNT2 = %d"),
            iCount1, iCount2
        );
        GetClientRect(hwnd, &rctSize);
        DrawText(hdc, strCount, -1, &rctSize, DT_LEFT);
        EndPaint(hwnd, &ps);
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

