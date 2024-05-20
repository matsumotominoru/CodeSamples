// dialog02.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("dialog02");    // ウィンドウクラス
HINSTANCE hInst;    // インスタンスハンドル
HWND hDlg;          // モードレスダイアログボックスのハンドル
TCHAR szName[32];   // ダイアログボックスから入力された文字列
HWND hMain;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;
    HACCEL hAccel;

    hInst = hCurInst; // グローバル変数にインスタンスハンドルをコピー
    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow))
        return FALSE;
    hAccel = LoadAccelerators(hCurInst, TEXT("MYACCEL"));
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
            break;
        } else {
            if (!hDlg || !IsDialogMessage(hDlg, &msg)) {
                if (!TranslateAccelerator(hMain, hAccel, &msg)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
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
    wc.lpszMenuName = TEXT("MYMENU");  // メニューを登録
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
               TEXT("猫でもわかるモードレスダイアログボックス"),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT,
               CW_USEDEFAULT, CW_USEDEFAULT,
               NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    hMain = hWnd;
    return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HMENU hMenu;
    TCHAR szBuf[64];
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_CREATE:
            hMenu = GetMenu(hWnd);      // メニューハンドルを取得
            break;
        case WM_INITMENU:               // ここでメニューを初期化する
            if (IsWindow(hDlg)) {
                EnableMenuItem(hMenu, IDM_DLG,
                               MF_BYCOMMAND | MF_GRAYED);
                EnableMenuItem(hMenu, IDM_CLOSEDLG,
                               MF_BYCOMMAND | MF_ENABLED);
            } else {
                EnableMenuItem(hMenu, IDM_DLG,
                               MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, IDM_CLOSEDLG,
                               MF_BYCOMMAND | MF_GRAYED);
            }
            DrawMenuBar(hWnd);
            break;
        case WM_PAINT:                  // 描画処理
            if (lstrcmp(szName, TEXT("")) == 0)
                lstrcpy(szBuf, TEXT("まだ名前の入力はありません"));
            else
                wsprintf(szBuf, TEXT("入力された氏名は%sさんです"),
                         szName);
            hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, 10, 10, szBuf, lstrlen(szBuf));
            EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:                // メニューコマンドの処理
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_DLG:
                    // モードレスダイアログボックスを作成
                    hDlg = CreateDialog(
                        hInst, TEXT("MYDLG"), hWnd, (DLGPROC)MyDlgProc);
                    ShowWindow(hDlg, SW_NORMAL);   // ダイアログを表示
                    break;
                case IDM_CLOSEDLG:
                    DestroyWindow(hDlg);           // ダイアログを破棄
                    break;
            }
            break;
        case WM_CLOSE:
            if (IsWindow(hDlg)) {
                MessageBox(hWnd, TEXT("ダイアログを破棄します"),
                           TEXT("破棄"), MB_OK);
                DestroyWindow(hDlg);               // ダイアログを破棄
            }
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

// ダイアログプロシージャ
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hParent;

    switch (msg) {
        case WM_INITDIALOG:
            hParent = GetParent(hDlg);    // 親ウィンドウのハンドルを取得
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:                // 「OK」ボタンが押された
                    // エディットコントロールから文字列を取得
                    GetDlgItemText(hDlg, IDC_EDIT1, szName,
                                   (int)sizeof(szName) - 1);
                    InvalidateRect(hParent, NULL, TRUE);
                    return TRUE;
                case IDCANCEL:            // 「クリア」ボタンが押された
                    // エディットコントロールに文字列をセット
                    SetDlgItemText(hDlg, IDC_EDIT1, TEXT(""));
                    return TRUE;
                case IDC_CLOSE:           // 「閉じる」ボタンが押された
                    DestroyWindow(hDlg);  // ダイアログを破棄
                    return TRUE;
            }

            return FALSE;
    }
    return FALSE;
}
