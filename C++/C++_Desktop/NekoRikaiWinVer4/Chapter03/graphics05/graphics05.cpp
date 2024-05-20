// graphics05.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("graphics05");	//ウィンドウクラス


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
			TEXT("猫でもわかる多角形"), //タイトルバーにこの名前が表示されます
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
	HBRUSH hBrush, hOldBrush;
	static POINT pt[4], poly[7];
	static INT nC[2];


	switch (msg) {
		case WM_CREATE:
			//Polygon関数のための配列
			pt[0].x = 20;
			pt[0].y = 20;
			pt[1].x = 20;
			pt[1].y = 80;
			pt[2].x = 120;
			pt[2].y = 50;
			pt[3].x = 100;
			pt[3].y = 100;
			//PolyPolygon関数のための配列
			poly[0].x = 150;
			poly[0].y = 20;
			poly[1].x = 200;
			poly[1].y = 25;
			poly[2].x = 210;
			poly[2].y = 70;
			poly[3].x = 145;
			poly[3].y = 65;
			poly[4].x = 180;
			poly[4].y = 10;
			poly[5].x = 160;
			poly[5].y = 90;
			poly[6].x = 205;
			poly[6].y = 100;
			//複数の多角形の頂点の数の配列
			nC[0] = 4;
			nC[1] = 3;
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Polygon(hdc, pt, 4);
			PolyPolygon(hdc, poly, nC, 2);
			DeleteObject(hBrush);
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
