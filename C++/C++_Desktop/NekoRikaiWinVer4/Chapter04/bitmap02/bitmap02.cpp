// bitmap02.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("bitmap02");	//ウィンドウクラス
HINSTANCE hInst;
HDC hdc_mem1, hdc_mem2;
int show_no = 1;

int WINAPI WinMain(_In_ HINSTANCE hCurInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpsCmdLine, _In_ int nCmdShow)
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
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW,
                    IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);  // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

//ウィンドウの生成

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			TEXT("猫でもわかるメモリデバイスコンテキスト"), //タイトルバーにこの名前が表示されます
			WS_OVERLAPPEDWINDOW, //ウィンドウの種類
			CW_USEDEFAULT,	//Ｘ座標
			CW_USEDEFAULT,	//Ｙ座標
			CW_USEDEFAULT,	//幅
			CW_USEDEFAULT,	//高さ
			NULL, //親ウィンドウのハンドル、親を作るときはNULL
			NULL, //メニューハンドル、クラスメニューを使うときはNULL
			hInst, //インスタンスハンドル
			NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBITMAP hBmp;
    HDC hdc_memx = NULL;

    switch (msg) {
        case WM_CREATE:
            hdc = GetDC(hWnd);

            // メモリデバイスコンテキストhdc_mem1に
            // ビットマップリソース「MYBMP1」を読み込む
            hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
            hdc_mem1 = CreateCompatibleDC(hdc);
            SelectObject(hdc_mem1, hBmp);
            DeleteObject(hBmp);

            // メモリデバイスコンテキストhdc_mem2に
            // ビットマップリソース「MYBMP2」を読み込む
            hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
            hdc_mem2 = CreateCompatibleDC(hdc);
            SelectObject(hdc_mem2, hBmp);
            DeleteObject(hBmp);

            ReleaseDC(hWnd, hdc);
            break;
        case WM_PAINT:
            BeginPaint(hWnd, &ps);
            if (show_no == 1)
                hdc_memx = hdc_mem1;
            if (show_no == 2)
                hdc_memx = hdc_mem2;

            // ビットマップを転送
            BitBlt(ps.hdc, ps.rcPaint.left, ps.rcPaint.top,
                   ps.rcPaint.right - ps.rcPaint.left,
                   ps.rcPaint.bottom - ps.rcPaint.top,
                   hdc_memx, ps.rcPaint.left, ps.rcPaint.top,
                   SRCCOPY);

            EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case ID_BITMAP_CAT1:
                    show_no = 1;
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
                case ID_BITMAP_CAT2:
                    show_no = 2;
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
                case ID_FILE_EXIT:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;
        case WM_DESTROY:
            DeleteDC(hdc_mem1);    // メモリデバイスコンテキストを破棄
            DeleteDC(hdc_mem2);    // メモリデバイスコンテキストを破棄

            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}
