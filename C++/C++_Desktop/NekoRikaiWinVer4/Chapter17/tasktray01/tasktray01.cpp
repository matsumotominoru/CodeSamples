// tasktray01.cpp

#define ID_MYTRAY 300                      // タスクトレイアイコンのID
#define MYTRAY_MESSAGE (WM_APP + 1)        // タスクトレイの
                                           // マウスイベント用メッセージ

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("tasktray01");
HINSTANCE hInst;
NOTIFYICONDATA ni;
BOOL bTray;            // タスクトレイにあるかどうか

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
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
    wc.lpfnWndProc = WndProc;    // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;        // インスタンス
    wc.hIcon = (HICON)LoadImage(hInst, TEXT("MYICON"),
        IMAGE_ICON, 0,0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;      // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = (HICON)LoadImage(hInst, TEXT("MYICON"),
        IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるタスクトレイ"),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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
    HMENU hMenu, hSubMenu;
    POINT pt;

    switch (msg) {
        case WM_RBUTTONDOWN:
            // クリックされた位置にポップアップメニューを表示
            hMenu = LoadMenu(hInst, TEXT("MYMENU"));
            hSubMenu = GetSubMenu(hMenu, 0);
            pt.x = LOWORD(lp);
            pt.y = HIWORD(lp);
            ClientToScreen(hWnd, &pt);
            TrackPopupMenu(
                hSubMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);
            DestroyMenu(hMenu);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_TRAY:   // 「タスクトレイに入れる」メニュー項目
                    // NOTIFYICONDATA構造体のメンバをセット
                    memset(&ni, 0, sizeof(NOTIFYICONDATA));
                    ni.cbSize = sizeof(NOTIFYICONDATA);
                    ni.hWnd = hWnd;
                    ni.uID = ID_MYTRAY;
                    ni.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
                    ni.hIcon = (HICON)LoadImage(
                        hInst, TEXT("MYICON"), IMAGE_ICON, 0, 0, 0);
                    ni.uCallbackMessage = MYTRAY_MESSAGE;
                    lstrcpy(ni.szTip, TEXT("猫でもわかるタスクトレイ"));

                    // タスクトレイにアイコンを表示
                    Shell_NotifyIcon(NIM_ADD, &ni);
                    // メインウィンドウを非表示にする
                    ShowWindow(hWnd, SW_HIDE);

                    bTray = TRUE;
                    break;
                case IDM_OUT:    // 「タスクトレイより出す」メニュー項目
                    // タスクトレイのアイコンを削除
                    Shell_NotifyIcon(NIM_DELETE, &ni);
                    // メインウィンドウを表示
                    ShowWindow(hWnd, SW_SHOWNORMAL);

                    bTray = FALSE;
                    break;
                case IDM_END:    // 「終了」メニュー項目
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;
        case MYTRAY_MESSAGE:     // タスクトレイ上のイベント
            switch(lp) {
                case WM_RBUTTONDOWN:
                    // クリックされた位置にポップアップメニューを表示
                    hMenu = LoadMenu(hInst, TEXT("MYTRAY"));
                    hSubMenu = GetSubMenu(hMenu, 0);
                    GetCursorPos(&pt);    // クリック位置を取得
                    SetForegroundWindow(hWnd);
                    TrackPopupMenu(
                        hSubMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);
                    DestroyMenu(hMenu);
                    break;
                default:
                    return (DefWindowProc(hWnd, msg, wp, lp));
            }
            break;
        case WM_CLOSE:
            if (bTray)   // タスクトレイにアイコンがあるなら…
                // …タスクトレイのアイコンを削除
                Shell_NotifyIcon(NIM_DELETE, &ni);
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
