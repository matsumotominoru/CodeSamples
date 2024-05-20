#define STRICT
#include <windows.h>
#include "resource.h"

#define APPBAR_CALLBACK WM_APP+1

HINSTANCE		   Instance;

CHAR	szAppName[]   = "AppBar Test";
CHAR	szClassName[]  = "AppBar Test";

//App Bar登録
BOOL AppBar_Register(HWND hWnd)
{
	APPBARDATA abd;
	
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = hWnd;
	abd.uCallbackMessage = APPBAR_CALLBACK;

	return SHAppBarMessage(ABM_NEW, &abd);
}

//App Bar登録解除
BOOL AppBar_UnRegister(HWND hWnd)
{
	APPBARDATA abd;
	
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = hWnd;

	return	SHAppBarMessage(ABM_REMOVE, &abd);
}		

//App Barの位置とサイズを設定
void AppBar_QuerySetPos(UINT uEdge, LPSIZE lpsize, PAPPBARDATA pabd) 
{ 
    int iHeight = 0; 
    int iWidth = 0; 
 
    pabd->uEdge = uEdge; 
 
	pabd->rc.top = 0; 
	pabd->rc.bottom = GetSystemMetrics(SM_CYSCREEN); 
	pabd->rc.left = 0; 
	pabd->rc.right = GetSystemMetrics(SM_CXSCREEN); 

	switch(uEdge){
		case ABE_LEFT:
			pabd->rc.right=pabd->rc.left+lpsize->cx;
			break;
		case ABE_RIGHT:
			pabd->rc.left=pabd->rc.right-lpsize->cx;
			break;
		case ABE_TOP:
			pabd->rc.bottom=pabd->rc.top+lpsize->cy;
			break;
		case ABE_BOTTOM:
			pabd->rc.top=pabd->rc.bottom-lpsize->cy;
			break;
	}

	//システムにサイズを調整してもらう
    SHAppBarMessage(ABM_QUERYPOS, pabd); 

    switch (uEdge) { 
        case ABE_LEFT: 
            pabd->rc.right = pabd->rc.left + lpsize->cx; 
            break; 
 
        case ABE_RIGHT: 
            pabd->rc.left = pabd->rc.right - lpsize->cx; 
            break; 
 
        case ABE_TOP: 
            pabd->rc.bottom = pabd->rc.top + lpsize->cy; 
            break; 
 
        case ABE_BOTTOM: 
            pabd->rc.top = pabd->rc.bottom - lpsize->cy; 
            break; 
    } 

	//最終的なサイズをシステムに伝える
    SHAppBarMessage(ABM_SETPOS, pabd); 

	//ウインドウの大きさを変える
    MoveWindow(pabd->hWnd, pabd->rc.left, pabd->rc.top, 
        pabd->rc.right - pabd->rc.left, 
        pabd->rc.bottom - pabd->rc.top, TRUE); 
}

//App Barの位置とサイズを設定（AppBar_QuerySetPosを使いやすくしたもの）
void AppBar_PosChanged(HWND hWnd)
{
	RECT		rc;
	SIZE		size;
	APPBARDATA	abd;

	abd.cbSize = sizeof(abd);
	abd.hWnd = hWnd;

	GetWindowRect(hWnd,&rc);

	size.cx=rc.right-rc.left;
	size.cy=rc.bottom-rc.top;

	AppBar_QuerySetPos(ABE_TOP, &size, &abd);

}

//WM_ACTIVATEの時の処理
void AppBar_Activate(HWND hWnd)
{
	APPBARDATA abd;
	
	// Always send the activate message to the system
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = hWnd;
	abd.lParam = 0;
	SHAppBarMessage(ABM_ACTIVATE, &abd);
}

//WM_WINDOWPOSCHANGEDの時の処理
void AppBar_WindowPosChanged(HWND hWnd)
{
	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = hWnd;
	abd.lParam = 0;

	SHAppBarMessage(ABM_WINDOWPOSCHANGED, &abd);
}

//WM_WINDOWPOSCHANGEDの時の処理
//変な側をサイズ変更できないようにする
int AppBar_NcHittest(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	LRESULT	lHitTest;

	lHitTest=DefWindowProc(hWnd, WM_NCHITTEST, wParam, lParam);

	if (lHitTest == HTBOTTOM) return HTBOTTOM;

	return HTCLIENT;							
}

//小さくなりすぎると困るので、最小値の設定
void AppBar_GetMinMaxInfo(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	((LPMINMAXINFO) lParam)->ptMinTrackSize.y=40;
}

//App Barからのメッセージの処理
void AppBar_Callback(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch(wParam){
		case ABN_POSCHANGED:
			AppBar_PosChanged(hWnd);
			break;
	}
}

int CALLBACK WndProc(HWND hWnd, unsigned wMessage,WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (wMessage)
	{
		case WM_CREATE:
			//AppBarの登録
			AppBar_Register(hWnd);
			//AppBarのサイズ設定
			AppBar_PosChanged(hWnd);
			return	0;

		case WM_DESTROY:
			//AppBarの登録解除
			AppBar_UnRegister(hWnd);
			PostQuitMessage(0);
			return	0;

		case WM_ACTIVATE:
			AppBar_Activate(hWnd);
			return	0;

		case WM_WINDOWPOSCHANGED:
			AppBar_WindowPosChanged(hWnd);
			break;

		case WM_EXITSIZEMOVE:
			AppBar_PosChanged(hWnd);
			break;

		case WM_NCHITTEST:
			return	AppBar_NcHittest(hWnd,wParam,lParam);

		case WM_GETMINMAXINFO:
			AppBar_GetMinMaxInfo(hWnd,wParam,lParam);
			return	0;

		case WM_PAINT:
			hdc = BeginPaint (hWnd, &ps);
			EndPaint (hWnd, &ps);
			return	0;

		case APPBAR_CALLBACK:
			AppBar_Callback(hWnd,wParam,lParam);
			return	0;
	}
	return (DefWindowProc(hWnd, wMessage, wParam, lParam));
}

HWND InitWindow(void)
{
	WNDCLASS	wndclass;
	HWND		hWnd;

	wndclass.style			= 0;
	wndclass.lpfnWndProc	= (WNDPROC) WndProc;
	wndclass.cbClsExtra 	= 0;
	wndclass.cbWndExtra 	= 0;
	wndclass.hInstance		= Instance;
#ifdef IDI_ICON1
	wndclass.hIcon			= LoadIcon(Instance, MAKEINTRESOURCE(IDI_ICON1));
#else
	wndclass.hIcon			= NULL;
#endif
	wndclass.hCursor		= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szClassName;

	if (!RegisterClass (&wndclass)) 	return NULL;


	hWnd = CreateWindowEx( WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
						  szClassName,
						  szAppName,
						  WS_POPUP | WS_THICKFRAME | WS_CLIPCHILDREN,
						  CW_USEDEFAULT,
						  CW_USEDEFAULT,
						  400,
						  50,
						  NULL,
						  NULL,
						  Instance,
						  NULL);
	return	hWnd;

}


int PASCAL WinMain (_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmd, _In_ int nCmdShow)
{
	MSG 		msg;
	HWND		hWnd;


	Instance = hInstance;

	if((hWnd=InitWindow())==NULL) return FALSE;
	ShowWindow (hWnd, nCmdShow);

	/* Enter message loop */
	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return msg.wParam;
}


