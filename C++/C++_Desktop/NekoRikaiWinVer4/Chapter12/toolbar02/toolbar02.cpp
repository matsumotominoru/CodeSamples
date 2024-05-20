// toolbar02.cpp

#define ID_TOOLBAR 100

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND MyCreateToolbar(HWND);

TCHAR szClassName[] = TEXT("toolbar02");  // ウィンドウクラス
int nType = 0;    // 0:旧タイプ 1:フラットタイプ 2:透明タイプ

TBBUTTON tbb[] = {
    { 0,                 IDM_MARU,    TBSTATE_ENABLED, BTNS_BUTTON },
    { 1,                 IDM_SANKAKU, TBSTATE_ENABLED, BTNS_BUTTON },
    { 2,                 IDM_SHIKAKU, TBSTATE_ENABLED, BTNS_BUTTON },
    // 以下の4つは標準ボタン
    { STD_FILENEW,       IDM_NEW,     TBSTATE_ENABLED, BTNS_BUTTON },
    { STD_FILEOPEN,      IDM_OPEN,    TBSTATE_ENABLED, BTNS_BUTTON },
    { STD_DELETE,        IDM_DELETE,  TBSTATE_ENABLED, BTNS_BUTTON },
    { VIEW_PARENTFOLDER, IDM_PARENT,  TBSTATE_ENABLED, BTNS_BUTTON }
};

TBBUTTON tb_sep = {0, 0, TBSTATE_ENABLED, BTNS_SEP};  // 区切り用ボタン


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
    wc.lpfnWndProc = WndProc;    // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;        // インスタンス
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = TEXT("MYMENU");  // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるツールバー"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
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
	LONG_PTR lStyle;
	MENUITEMINFO mi;
	static HMENU hMenu;

	switch (msg) {
		case WM_CREATE:
			hMenu = GetMenu(hWnd);
			cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
			cc.dwICC = ICC_BAR_CLASSES;
			InitCommonControlsEx(&cc);
			hTool = MyCreateToolbar(hWnd);
			break;
		case WM_COMMAND:
			switch (LOWORD(wp)) {
				case IDM_END:
					SendMessage(hWnd, WM_CLOSE, 0, 0);
					break;
				case IDM_MARU:
					MessageBox(hWnd, 
						TEXT("丸が選択されました"),
						TEXT("オプション"),
						MB_OK);
					break;
				case IDM_SANKAKU:
					MessageBox(hWnd,
						TEXT("三角が選択されました"),
						TEXT("オプション"),
						MB_OK);
					break;
				case IDM_SHIKAKU:
					MessageBox(hWnd, 
						TEXT("四角が選択されました"),
						TEXT("オプション"),
						MB_OK);
					break;
				case IDM_NEW:
					MessageBox(hWnd, 
						TEXT("新規作成"),
						TEXT("猫でもわかるツールバー"),
						MB_OK);
					break;
				case IDM_OPEN:
					MessageBox(hWnd,
						TEXT("開く"),
						TEXT("猫でもわかるツールバー"),
						MB_OK);
					break;
				case IDM_DELETE:
					MessageBox(hWnd, 
						TEXT("削除"),
						TEXT("猫でもわかるツールバー"),
						MB_OK);
					break;
				case IDM_PARENT:
					MessageBox(hWnd, 
						TEXT("一つ上に"),
						TEXT("猫でもわかるツールバー"),
						MB_OK);
					break;
				case IDM_OLD:
					lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
					lStyle = lStyle & ~TBSTYLE_FLAT &~TBSTYLE_TRANSPARENT;
					SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
					InvalidateRect(hTool, NULL, TRUE);
					nType = 0;
					break;
				case IDM_FLAT:
					lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
					lStyle = (lStyle | TBSTYLE_FLAT) & ~TBSTYLE_TRANSPARENT;
					SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
					InvalidateRect(hTool, NULL, TRUE);
					nType = 1;
					break;
				case IDM_TRANSPARENT:
					lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
					lStyle = lStyle | TBSTYLE_FLAT | TBSTYLE_TRANSPARENT;
					SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
					InvalidateRect(hTool, NULL, TRUE);
					nType = 2;
			}
			break;
		case WM_SIZE:
			SendMessage(hTool, TB_AUTOSIZE, 0, 0);
			break;
		case WM_INITMENU:
			mi.cbSize = sizeof(MENUITEMINFO);
			mi.fMask = MIIM_STATE;
			switch (nType) {
				case 0:
					mi.fState = MFS_CHECKED;
					SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
					mi.fState = MFS_UNCHECKED;
					SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
					SetMenuItemInfo(hMenu, IDM_TRANSPARENT, FALSE, &mi);
					break;
				case 1:
					mi.fState = MFS_CHECKED;
					SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
					mi.fState = MFS_UNCHECKED;
					SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
					SetMenuItemInfo(hMenu, IDM_TRANSPARENT, FALSE, &mi);
					break;
				case 2:
					mi.fState = MFS_CHECKED;
					SetMenuItemInfo(hMenu, IDM_TRANSPARENT, FALSE, &mi);
					mi.fState = MFS_UNCHECKED;
					SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
					SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
					break;
			}
			DrawMenuBar(hWnd);
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

HWND MyCreateToolbar(HWND hWnd)
{
    HINSTANCE hInst;
    HWND hTool;
    TBADDBITMAP tb;
    int stdid;

    // インスタンスハンドルを取得
    hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);

    hTool = CreateToolbarEx(
        hWnd,                    // 親ウィンドウ
        WS_CHILD | WS_VISIBLE,   // ウィンドウスタイル
        ID_TOOLBAR,              // コントロールID
        3,                       // イメージの数
        hInst,                   // インスタンスハンドル
        IDR_TOOLBAR1,            // ツールバーのID
        tbb,                     // TBBUTTON構造体
        3,                       // ボタンの数
        0,                       // ボタンの幅
        0,                       // ボタンの高さ
        0,                       // イメージの幅
        0,                       // イメージの高さ
        sizeof(TBBUTTON));

    // TBADDBITMAP構造体のメンバをセットして
    // TB_ADDBITMAPメッセージを送る
    tb.hInst = HINST_COMMCTRL;
    tb.nID = IDB_STD_SMALL_COLOR;
    stdid = SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);

    // TBBUTTON構造体のiBitmapメンバを修正し、
    // TB_ADDBUTTONSメッセージを送る
    tbb[3].iBitmap += stdid;
    tbb[4].iBitmap += stdid;
    tbb[5].iBitmap += stdid;
    SendMessage(hTool, TB_ADDBUTTONS, (WPARAM)3, (LPARAM)&tbb[3]);

    // ボタンの系統（VIEW系）が違うので、再度同様の操作をする
    tb.hInst = HINST_COMMCTRL;
    tb.nID = IDB_VIEW_SMALL_COLOR;
    stdid = SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);
    tbb[6].iBitmap += stdid;
    SendMessage(hTool, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&tbb[6]);

    // セパレーターの挿入
    SendMessage(hTool, TB_INSERTBUTTON, (WPARAM)3, (LPARAM)&tb_sep);

    return hTool;
}
