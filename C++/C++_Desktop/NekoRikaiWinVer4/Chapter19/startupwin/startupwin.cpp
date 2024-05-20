// startupwin.cpp

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include "resource.h"

typedef struct _MYDATA {
    BYTE bMajor;
    BYTE bMinor;
    char szText[6][128];
} MYDATA, *LPMYDATA;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyStartupProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyStartup(HWND, LPMYDATA);

char szClassName[] = "startupwin";    // ウィンドウクラス
char szAppName[] = "猫でもわかるWindowsプログラミング";
HINSTANCE hInst;                      // インスタンスハンドル

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;    // インスタンスハンドルをグローバル変数にコピー
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
    wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = "MYMENU";  // メニュー名
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.hIconSm = (HICON)LoadImage(NULL,
        MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, szAppName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 313, 227,
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
    int id, i;
    static MYDATA mydata;
    INT_PTR ret;        // Visual C++ 6.0およびそれ以前ではint
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:           // 「終了」メニュー項目
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_STARTUP:       // 「WSAStartup」メニュー項目
                    // ダイアログボックスを表示
                    ret = DialogBoxParam(hInst, "MYSTARTUP",
                        hWnd,  (DLGPROC)MyStartupProc, (LPARAM)&mydata);
                    if (ret == IDOK) {  // ダイアログでOKが押された
                        id = MyStartup(hWnd, &mydata);
                        if (id == 0) {
                            InvalidateRect(hWnd, NULL, TRUE);
                        }
                    }
                    break;
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            for (i = 0; i < 6; i++)
                TextOut(hdc,  10, 10 * 2 * (i + 1), mydata.szText[i],
                    (int)strlen(mydata.szText[i]));
            EndPaint(hWnd, &ps);
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, "終了してもよろしいですか",
                "確認", MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES)
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

// ダイアログボックスのプロシージャ
BOOL CALLBACK MyStartupProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    BOOL bSuccess;
    static LPMYDATA lpdata;

    switch (msg) {
        case WM_INITDIALOG:
            lpdata = (LPMYDATA)lp;    // mydataのポインタを保管
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:            // 「OK」ボタンが押さた
                    // エディットコントロールから数値を読み出して
                    // lpdataに書き出す
                    lpdata->bMajor = GetDlgItemInt(
                        hDlg, IDC_MAJOR, &bSuccess, FALSE);
                    lpdata->bMinor = GetDlgItemInt(
                        hDlg, IDC_MINOR, &bSuccess, FALSE);

                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDCANCEL:        // 「キャンセル」ボタンが押された
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

int MyStartup(HWND hWnd, LPMYDATA lpmydata)
{
    WSADATA wsaData;
    WORD wVersion;

    // 受け取ったlpmydataからバージョン番号のWORD値を生成
    wVersion = MAKEWORD(lpmydata->bMajor, lpmydata->bMinor);
    // WinSockを初期化
    if (WSAStartup(wVersion, &wsaData) != 0) {
        MessageBox(hWnd, "WSAStartup関数失敗", szAppName, MB_OK);
        return -1;
    }

    // WSADATA構造体に格納されているデータを
    // lpmydataの各メンバに書き込む
    wsprintf(lpmydata->szText[0], "wVersion = %d.%d", 
        LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
    wsprintf(lpmydata->szText[1], "wHighVersion = %d.%d",
        LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
    wsprintf(lpmydata->szText[2], "szDescription = %s",
        wsaData.szDescription);
    wsprintf(lpmydata->szText[3], "szSystemStatus = %s",
        wsaData.szSystemStatus);
    wsprintf(lpmydata->szText[4], "iMaxSockets = %d",
        wsaData.iMaxSockets);
    wsprintf(lpmydata->szText[5], "iMaxUdpDg = %d",
        wsaData.iMaxUdpDg);

    WSACleanup();    // WinSockのリソースを解放
    return 0;
}
