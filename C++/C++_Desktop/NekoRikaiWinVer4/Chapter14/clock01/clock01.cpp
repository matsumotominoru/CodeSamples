// clock01.cpp

#include <windows.h>
#define ID_MYTIMER 100    // タイマーID

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HFONT MyCreateFont(int, DWORD, LPCTSTR);

TCHAR szClassName[] = TEXT("clock01");    // ウィンドウクラス

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
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = WndProc;  // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;      // インスタンス
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
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

    hWnd = CreateWindow(szClassName, TEXT(""),
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 148, 82,
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
    int id;
    HDC hdc;
    PAINTSTRUCT ps;
    static TCHAR szTime[64], szDate[64];
    SYSTEMTIME st;
    HFONT hFont1, hFont2;

    switch (msg) {
        case WM_CREATE:
            SetTimer(hWnd, ID_MYTIMER, 500, NULL);  // タイマーを作成
            break;
        case WM_TIMER:
            // 関係ないタイマーイベントはDefWindowProcに任せる
            if (wp != ID_MYTIMER)
                return (DefWindowProc(hWnd, msg, wp, lp));

            GetLocalTime(&st);    // 現在の日時を取得
            wsprintf(szTime, TEXT("%02d:%02d:%02d"), st.wHour,
                     st.wMinute, st.wSecond);
            wsprintf(szDate, TEXT("%d年%02d月%02d日"), st.wYear,
                     st.wMonth, st.wDay);

            // クライアント領域全体を更新
            InvalidateRect(hWnd, NULL, TRUE);
            // タイトルバーに時刻を表す文字列を設定
            SetWindowText(hWnd, szTime);
            break;
        case WM_LBUTTONDBLCLK:
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            hFont1 = MyCreateFont(12, SHIFTJIS_CHARSET,
                                  TEXT("ＭＳ ゴシック"));
            SelectObject(hdc, hFont1);
            TextOut(hdc, 5, 5, szDate, lstrlen(szDate));
            hFont2 = MyCreateFont(30, ANSI_CHARSET,
                                  TEXT("ＭＳ ゴシック"));
            SelectObject(hdc, hFont2);
            SetTextColor(hdc, RGB(0, 0, 255));
            TextOut(hdc, 10, 20, szTime, lstrlen(szTime));
            DeleteObject(hFont1);
            DeleteObject(hFont2);
            EndPaint(hWnd, &ps);
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("終了してもよろしいですか"),
                TEXT("確認"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                // タイマーを破棄
                if (KillTimer(hWnd, ID_MYTIMER) == 0) {
                    MessageBox(hWnd, TEXT("KillTimer Error!"),
                        TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
                }
                DestroyWindow(hWnd);
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

HFONT MyCreateFont(int nHeight, DWORD dwCharSet, LPCTSTR lpName)
{
	return(	CreateFont(nHeight, 0, 0, 0,
				FW_DONTCARE,
				FALSE, FALSE, FALSE,
				dwCharSet,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				lpName));
}