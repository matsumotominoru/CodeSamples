// event01.cpp

#include <windows.h>

typedef struct _tagMyData {
    HWND hWnd;
    BOOL bEnd;
} MYDATA, *LPMYDATA;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
DWORD WINAPI ThFunc(LPVOID);
HFONT MyCreateFont(LPCTSTR, int);

LPCTSTR lpszClassName = TEXT("event01");    // ウィンドウクラス
HANDLE hEvent;

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
    wc.lpfnWndProc = WndProc;   //プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;       //インスタンス
    wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;    //メニュー名
    wc.lpszClassName = lpszClassName;
    wc.hIconSm = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(lpszClassName,
        TEXT("猫でもわかるWindowsプログラミング"), WS_OVERLAPPEDWINDOW,
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
    int id;
    static DWORD dwThID;
    static MYDATA mydata;
    static HANDLE hTh;
    static BOOL bSignal = FALSE;

    switch (msg) {
        case WM_CREATE:
            // イベントオブジェクトを作成
            hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("MyEvent"));
            mydata.bEnd = FALSE;
            mydata.hWnd = hWnd;
            hTh = CreateThread(NULL, 0,    // 子スレッドを作成
                (LPTHREAD_START_ROUTINE)ThFunc, &mydata, 0, &dwThID);
            break;
        case WM_LBUTTONDOWN:
            if (bSignal) {
                ResetEvent(hEvent);        // 非シグナル状態に変更
                bSignal = FALSE;
            } else {
                SetEvent(hEvent);          // シグナル状態に変更
                bSignal = TRUE;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("終了してもよろしいですか"),
                TEXT("終了確認"), MB_YESNO);
            if (id == IDYES) {
                if (!bSignal)            // シグナル状態でない場合は
                    SetEvent(hEvent);    // シグナル状態に変更する
                mydata.bEnd = TRUE;
                WaitForSingleObject(hTh, INFINITE);
                CloseHandle(hTh);        // スレッドハンドルを破棄
                CloseHandle(hEvent);     // イベントオブジェクトを破棄
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

DWORD WINAPI ThFunc(LPVOID lpdata)
{
	LPMYDATA lpd;
	HWND hWnd;
	HDC hdc;
	SYSTEMTIME st;
	TCHAR szBuf[64];
	HFONT hFont;	

	lpd = (LPMYDATA)lpdata;
	hWnd = lpd->hWnd;

	hdc = GetDC(hWnd);
	hFont = MyCreateFont(TEXT("ＭＳ ゴシック"), 48);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 0, 0));
	
	while (!lpd->bEnd) {
		Sleep(10);
		GetLocalTime(&st);
		wsprintf(szBuf, TEXT("%02d:%02d:%02d-%03d"),
			st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		TextOut(hdc, 10, 10, szBuf, lstrlen(szBuf));
		WaitForSingleObject(hEvent, INFINITE);
	}
	DeleteObject(hFont);
	ReleaseDC(hWnd, hdc);
	return 0;
}

HFONT MyCreateFont(LPCTSTR face, int h)
{
    HFONT hFont;
    hFont = CreateFont(h,         // フォント高さ
        0,                        // 文字幅
        0,                        // テキストの角度
        0,                        // ベースラインとx軸との角度
        FW_BOLD,                  // フォントの重さ（太さ）
        FALSE,                    // イタリック体
        FALSE,                    // アンダーライン
        FALSE,                    // 打ち消し線
        SHIFTJIS_CHARSET,         // 文字セット
        OUT_DEFAULT_PRECIS,       // 出力精度
        CLIP_DEFAULT_PRECIS,      // クリッピング精度
        PROOF_QUALITY,            // 出力品質
        FIXED_PITCH | FF_MODERN,  // ピッチとファミリー
        face);                    // 書体名
    return hFont;
}
