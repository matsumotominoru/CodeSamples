// graphics02.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("graphics02");	//ウィンドウクラス


int WINAPI WinMain(_In_ HINSTANCE hCurInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpsCmdLine, _In_ int nCmdShow)
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
			TEXT("猫でもわかるグラフィックス"), //タイトルバーにこの名前が表示されます
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
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen1, hPen2, hPen3, hPen4, hPen5;

	switch (msg) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			hPen1 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			SelectObject(hdc, hPen1);
			MoveToEx(hdc, 20, 20, NULL);
			LineTo(hdc, 250, 20);
			hPen2 = CreatePen(PS_DASH, 0, RGB(0, 0, 255));
			SelectObject(hdc, hPen2);
			MoveToEx(hdc, 20, 40, NULL);
			LineTo(hdc, 250, 40);
			hPen3 = CreatePen(PS_DOT, 0, RGB(0, 255, 0));
			SelectObject(hdc, hPen3);
			MoveToEx(hdc,20, 60, NULL);
			LineTo(hdc, 250, 60);
			hPen4 = CreatePen(PS_DASHDOT, 0, RGB(255, 0, 0));
			SelectObject(hdc, hPen4);
			MoveToEx(hdc, 20, 80, NULL);
			LineTo(hdc, 250, 80);
			hPen5 = CreatePen(PS_DASHDOTDOT, 0, RGB(0, 0, 255));
			SelectObject(hdc, hPen5);
			MoveToEx(hdc, 20, 100, NULL);
			LineTo(hdc, 250, 100);
			DeleteObject(hPen1);
			DeleteObject(hPen2);
			DeleteObject(hPen3);
			DeleteObject(hPen4);
			DeleteObject(hPen5);
			EndPaint(hWnd, &ps);
			break;
		case WM_CLOSE:
			id = MessageBox(hWnd,
				TEXT("終了してもよろしいですか"),
				TEXT("終了確認"),
				MB_YESNO | MB_ICONQUESTION);
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
