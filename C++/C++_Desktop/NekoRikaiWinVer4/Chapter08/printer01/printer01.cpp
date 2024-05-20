// printer01.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyPrint(HWND);

TCHAR szClassName[] = TEXT("printer01");  // ウィンドウクラス

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

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるプリンタ"),
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
    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_PRINT:
                    MyPrint(hWnd);    // 印刷用の関数を呼び出す
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}


int MyPrint(HWND hWnd)
{
    int i;
    PRINTDLG pd;
    DOCINFO di;
    TEXTMETRIC tm;

    LPTSTR lpszBuf = TEXT("ここが印刷されます");

    // PRINTDLG構造体の設定
    memset(&pd, 0, sizeof(PRINTDLG));

    pd.lStructSize = sizeof(PRINTDLG);
    pd.hwndOwner = hWnd;
    pd.hDevMode = NULL;
    pd.hDevNames = NULL;
    pd.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC |
        PD_NOPAGENUMS | PD_NOSELECTION | PD_HIDEPRINTTOFILE;

    pd.nMinPage = 1;
    pd.nMaxPage = 1;
    pd.nFromPage = 1;
    pd.nToPage = 1;
    pd.nCopies = 1;

    // 「印刷」ダイアログを表示
    if (PrintDlg(&pd) == 0)
        return -1;

    // DOCINFO構造体の設定
    memset(&di, 0, sizeof(DOCINFO));
    di.cbSize = sizeof(DOCINFO);
    di.lpszDocName = TEXT("Test");

    // 印刷ジョブ
    StartDoc(pd.hDC, &di);        // 印刷ジョブを開始
    StartPage(pd.hDC);            // プリンタドライバに準備を要請
    GetTextMetrics(pd.hDC, &tm);  // フォントの情報を取得
    for (i = 0; i < 10; i++) {
        SetTextColor(pd.hDC, RGB(255, 0, 0));
        // デバイスコンテキストに文字列を書き込む
        TextOut(pd.hDC, 10, 10 + (tm.tmHeight * i + 20),
                lpszBuf, lstrlen(lpszBuf));
    }
    EndPage(pd.hDC);              // 書き込み完了をデバイスに通知
    EndDoc(pd.hDC);               // 印刷ジョブを終了
    DeleteDC(pd.hDC);             // デバイスコンテキストを破棄

    return 0;
}
