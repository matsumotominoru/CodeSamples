// popup01.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("popup01");  // ウィンドウクラス
HINSTANCE hInst;    // インスタンスハンドル（LoadMenu関数で使う）

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;      // インスタンスハンドルをグローバル変数に保管
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
    wc.lpfnWndProc = WndProc;          // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;              // インスタンス
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
                    IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;            // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるポップアップ"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HMENU hMenu, hSubMenu;
    POINT pt;

    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:         // 「終了」の処理
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_POPUP1:      // 「ポップアップ1」の処理
                    MessageBox(hWnd, TEXT("ポップアップ1です"),
                        TEXT("Popup1"), MB_OK);
                    break;
                case IDM_POPUP2:      // 「ポップアップ2」の処理
                    MessageBox(hWnd, TEXT("ポップアップ2です"),
                        TEXT("Popup2"), MB_OK);
                    break;
                default:
                    return (DefWindowProc(hWnd, msg, wp, lp));
            }
            break;
        case WM_RBUTTONDOWN:
            hMenu = LoadMenu(hInst, TEXT("MYPOPUP"));
            hSubMenu = GetSubMenu(hMenu, 0);  // サブメニューのハンドルを取得

            pt.x = LOWORD(lp);  // クリック位置のx座標（クライアント座標）
            pt.y = HIWORD(lp);  // クリック位置のy座標（クライアント座標）
            ClientToScreen(hWnd, &pt);  // スクリーン座標に変換

            // サブメニューのハンドルを指定して、ポップアップメニューを表示
            TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);

            DestroyMenu(hMenu);
            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}
