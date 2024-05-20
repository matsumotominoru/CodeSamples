// font01.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

HFONT MyCreateFont(int, DWORD, LPCTSTR);

TCHAR szClassName[] = TEXT("font01");	//ウィンドウクラス


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
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

//ウィンドウ・クラスの登録

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
	wc.lpszMenuName = NULL;	//メニュー名
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
		TEXT("猫でもわかるFont"), //タイトルバーにこの名前が表示されます
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
	static HFONT hFont1, hFont2, hFont3;
	PAINTSTRUCT ps;
	HDC hdc;
	LPCTSTR lpszName1 = TEXT("粂井康孝");
	LPCTSTR lpszName2 = TEXT("Yasutaka Kumei");


	switch (msg) {
	case WM_CREATE:
		hFont1 = MyCreateFont(40, SHIFTJIS_CHARSET, TEXT("HG行書体"));
		hFont2 = MyCreateFont(40, ANSI_CHARSET, TEXT("Fraktur JS"));
		hFont3 = MyCreateFont(40, SHIFTJIS_CHARSET, TEXT("ＭＳ 明朝"));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hFont1);
		TextOut(hdc, 0, 0, lpszName1, lstrlen(lpszName1));
		SelectObject(hdc, hFont2);
		TextOut(hdc, 0, 60, lpszName2, lstrlen(lpszName2));
		SelectObject(hdc, hFont3);
		TextOut(hdc, 0, 120, lpszName1, lstrlen(lpszName1));
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		id = MessageBox(hWnd, TEXT("終了してもよろしいですか"),TEXT("終了確認"),MB_YESNO | MB_ICONQUESTION);
		if (id == IDYES) {
			DeleteObject(hFont1);
			DeleteObject(hFont2);
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
	return(CreateFont(nHeight, 0, 0, 0,
		FW_DONTCARE,
		FALSE, FALSE, FALSE,
		dwCharSet,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		lpName));
}

