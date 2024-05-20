// toolbar01.cpp

#define ID_TOOLBAR 100

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND MyCreateToolbar(HWND);

TCHAR szClassName[] = TEXT("toolbar01");  // ウィンドウクラス
int nType = 0;    // 0:旧タイプ 1:フラットタイプ 2:透明タイプ

// このように初期化するときは
// バージョンによるTBBUTTON構造体の大きさに注意
TBBUTTON tbb[] = {
    { 0, IDM_MARU,    TBSTATE_ENABLED, BTNS_BUTTON },
    { 1, IDM_SANKAKU, TBSTATE_ENABLED, BTNS_BUTTON },
    { 2, IDM_SHIKAKU, TBSTATE_ENABLED, BTNS_BUTTON },
};

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

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
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = TEXT("MYMENU");  // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるツールバー"),
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
    INITCOMMONCONTROLSEX cc;
    static HWND hTool;
    LONG lStyle;
    MENUITEMINFO mi;
    static HMENU hMenu;

    switch (msg) {
        case WM_CREATE:
            hMenu = GetMenu(hWnd);          // メニューハンドルを取得
            cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
            cc.dwICC = ICC_BAR_CLASSES;
            InitCommonControlsEx(&cc);      // コモンコントロールを初期化
            hTool = MyCreateToolbar(hWnd);  // ツールバーを作成
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_MARU:
                    MessageBox(hWnd, TEXT("丸が選択されました"),
                               TEXT("オプション"), MB_OK);
                    break;
                case IDM_SANKAKU:
                    MessageBox(hWnd, TEXT("三角が選択されました"),
                               TEXT("オプション"), MB_OK);
                    break;
                case IDM_SHIKAKU:
                    MessageBox(hWnd, TEXT("四角が選択されました"),
                               TEXT("オプション"), MB_OK);
                    break;
                case IDM_OLD:
                    // 「旧タイプ」のツールバーに変更
                    lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
                    lStyle = lStyle & ~TBSTYLE_FLAT &
                             ~TBSTYLE_TRANSPARENT;
                    SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
                    InvalidateRect(hTool, NULL, TRUE);
                    nType = 0;
                    break;
                case IDM_FLAT:
                    // 「フラットタイプ」のツールバーに変更
                    lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
                    lStyle = (lStyle | TBSTYLE_FLAT) &
                             ~TBSTYLE_TRANSPARENT;
                    SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
                    InvalidateRect(hTool, NULL, TRUE);
                    nType = 1;
                    break;
                case IDM_TRANSPARENT:
                    // 「透明タイプ」のツールバーに変更
                    lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
                    lStyle = lStyle | TBSTYLE_FLAT |
                             TBSTYLE_TRANSPARENT;
                    SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
                    InvalidateRect(hTool, NULL, TRUE);
                    nType = 2;
            }
            break;
        case WM_SIZE:
            // SendMessage(hTool, msg, wp, lp);を送ってもよい
            SendMessage(hTool, TB_AUTOSIZE, 0, 0);
            break;
        case WM_INITMENU:
            mi.cbSize = sizeof(MENUITEMINFO);
            mi.fMask = MIIM_STATE;
            switch (nType) {
                case 0:
                    mi.fState = MFS_CHECKED;
                    SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
                    mi.fState = MFS_UNCHECKED;
                    SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
                    SetMenuItemInfo(hMenu, IDM_TRANSPARENT,
                                    FALSE, &mi);
                    break;
                case 1:
                    mi.fState = MFS_CHECKED;
                    SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
                    mi.fState = MFS_UNCHECKED;
                    SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
                    SetMenuItemInfo(hMenu, IDM_TRANSPARENT,
                                    FALSE, &mi);
                    break;
                case 2:
                    mi.fState = MFS_CHECKED;
                    SetMenuItemInfo(hMenu, IDM_TRANSPARENT,
                                    FALSE, &mi);
                    mi.fState = MFS_UNCHECKED;
                    SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
                    SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
                    break;
            }
            DrawMenuBar(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

HWND MyCreateToolbar(HWND hWnd)
{
    HINSTANCE hInst;
    HWND hTool;

    // インスタンスハンドルを取得
    hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);

    hTool = CreateToolbarEx(
        hWnd,                   // 親ウィンドウ
        WS_CHILD | WS_VISIBLE,  // ウィンドウスタイル
        ID_TOOLBAR,             // コントロールID
        3,                      // イメージの数
        hInst,                  // インスタンスハンドル
        IDR_TOOLBAR1,           // ツールバーのID
        tbb,                    // TBBUTTON構造体
        3,                      // ボタンの数
        0,                      // ボタンの幅
        0,                      // ボタンの高さ
        0,                      // イメージの幅
        0,                      // イメージの高さ
        sizeof(TBBUTTON));
    return hTool;
}