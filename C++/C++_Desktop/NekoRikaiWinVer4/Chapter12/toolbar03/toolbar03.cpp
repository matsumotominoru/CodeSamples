// toolbar03.cpp

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND MyCreateToolbar(HWND);

TCHAR szClassName[] = TEXT("toolbar03");	//ウィンドウクラス

TBBUTTON tbb[] = {
    { STD_FILENEW,  IDM_NEW,  TBSTATE_ENABLED, BTNS_BUTTON },
    { STD_FILEOPEN, IDM_OPEN, TBSTATE_ENABLED, BTNS_BUTTON },
    { STD_COPY,     IDM_COPY, TBSTATE_ENABLED, BTNS_BUTTON },
    { STD_CUT,      IDM_CUT,  TBSTATE_ENABLED, BTNS_BUTTON },
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

//ウィンドウクラスの登録
ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	//プロシージャ名
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//インスタンス
	wc.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = TEXT("MYMENU");	//メニュー名
	wc.lpszClassName = szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			TEXT("猫でもわかるツールバー"), //タイトルバーにこの名前が表示されます
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

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int id;
	INITCOMMONCONTROLSEX cc;
	static HWND hTool;

	switch (msg) {
		case WM_CREATE:
			cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
			cc.dwICC = ICC_BAR_CLASSES;
			InitCommonControlsEx(&cc);
			hTool = MyCreateToolbar(hWnd);
			break;
		case WM_SIZE:
			SendMessage(hTool, WM_SIZE, wp, lp);
			break;
		case WM_COMMAND:
			switch (LOWORD(wp)) {
				case IDM_END:
					SendMessage(hWnd, WM_CLOSE, 0, 0);
					break;
				case IDM_NEW:
				case IDM_OPEN:
				case IDM_COPY:
				case IDM_CUT:
					MessageBox(hWnd, 
						TEXT("項目が選択されました"), 
						TEXT("猫でもわかるツールバー"), 
						MB_OK);
					break;
			}
			break;
		case WM_CLOSE:
			id = MessageBox(hWnd,
				TEXT("終了してもよろしいですか"),
				TEXT("確認"),
				MB_YESNO | MB_ICONQUESTION);
			if (id == IDYES) {
				DestroyWindow(hTool);
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

HWND MyCreateToolbar(HWND hWnd)
{
    HINSTANCE hInst;
    HWND hTool;
    TBADDBITMAP tb;
    int stdid, i;

    // インスタンスハンドルを取得
    hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);

    hTool = CreateWindow(
        TOOLBARCLASSNAME,        // ウィンドウクラス
        NULL,                    // タイトル
        WS_CHILD | WS_VISIBLE,   // ウィンドウスタイル
        0, 0, 0, 0,              // x座標, y座標, 幅, 高さ
        hWnd,                    // 親ウィンドウ
        NULL,                    // メニュー
        hInst,                   // インスタンス
        NULL                     // ウィンドウ作成データ
    );

    SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    tb.hInst = HINST_COMMCTRL;
    tb.nID = IDB_STD_SMALL_COLOR;
    stdid = (int)SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);

    for (i = 0; i < 4; i++) 
        tbb[i].iBitmap += stdid;
    SendMessage(hTool, TB_ADDBUTTONS, (WPARAM)4, (LPARAM)&tbb[0]);

    return hTool;
}
