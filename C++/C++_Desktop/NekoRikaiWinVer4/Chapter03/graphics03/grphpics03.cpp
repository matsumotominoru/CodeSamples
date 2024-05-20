// graphics03.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("graphics03");	//ウィンドウクラス


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
			TEXT("猫でもわかる四角形"), //タイトルバーにこの名前が表示されます
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
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	switch (msg) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
			hOldPen = (HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, 10, 10, 100, 100);
			
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 50, 50, 150, 150);
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 100, 100, 200, 200);
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 255));
			SelectObject(hdc,hBrush);
			Rectangle(hdc, 150, 150, 250, 250);
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 200, 200, 300, 300);
			DeleteObject(hBrush);
			hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 250, 250, 350, 350);
			DeleteObject(hPen);
			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			EndPaint(hWnd, &ps);
			break;
		case WM_CLOSE:
			id = MessageBox(hWnd,
				TEXT("終了してもよろしいですか"),
				TEXT("確認"),
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

