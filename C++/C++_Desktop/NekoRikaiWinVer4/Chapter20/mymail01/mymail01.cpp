// mymail01.cpp

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include <stdlib.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyMailCheck(HWND);

char szClassName[] = "mymail01";    // ウィンドウクラス
HINSTANCE hInst;                    // インスタンス
u_short port = 110;                 // ポート番号

// サーバ名、ユーザーID、パスワード、ポート
char szPopName[64], szID[32], szPass[32], szPort[8];


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
				   LPSTR lpsCmdLine, int nCmdShow)
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
	wc.lpfnWndProc = WndProc;	// プロシージャ名
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;		// インスタンス
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
	wc.lpszMenuName = "MYMENU";	// メニュー名
	wc.lpszClassName = (LPCSTR)szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			"猫でもわかるメールチェッカー", // タイトルバーにこの名前が表示
			WS_OVERLAPPEDWINDOW,          // ウィンドウの種類
			CW_USEDEFAULT,	// Ｘ座標
			CW_USEDEFAULT,	// Ｙ座標
			CW_USEDEFAULT,	// 幅
			CW_USEDEFAULT,	// 高さ
			NULL,  // 親ウィンドウのハンドル、親を作るときはNULL
			NULL,  // メニューハンドル、クラスメニューを使うときはNULL
			hInst, // インスタンスハンドル
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
    int id;

    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_SETTING:    // 「オプション」→「設定」
                    DialogBox(hInst, "MYDLG", hWnd, (DLGPROC)MyDlgProc);
                    break;
                case IDM_END:        // 「ファイル」→「終了」
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_CHECK:      // 「ファイル」→「メールチェック」
                    MyMailCheck(hWnd);
                    break;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, "終了してもよろしいですか",
                "確認", MB_YESNO | MB_ICONQUESTION);
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

int MyMailCheck(HWND hWnd)
{
    WSADATA wsaData;
    SOCKET s;
    char szBuf[1024];
    LPHOSTENT lpHost;
    SOCKADDR_IN sockaddr;

    // WinSockを初期化
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        MessageBox(hWnd,  "WSAStartup関数失敗です", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        return -1;
    }

    // ソケットをオープンする
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        MessageBox(hWnd,  "ソケット作成失敗です", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return -2;
    }

    // ホスト情報を取得
    lpHost = gethostbyname(szPopName);
    if (lpHost == NULL) {
        MessageBox(hWnd,  "ホスト情報取得失敗しました", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return -3;
    }

    // SOCKADDR_IN構造体に必要事項をセット
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

    // ソケットに接続
    if (connect(s, (PSOCKADDR)&sockaddr, sizeof(sockaddr)) != 0) {
        MessageBox(hWnd,  "ソケットに接続できませんでした", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return -4;
    }

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd,  "エラーが発生しました", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        return -5;
    }
    MessageBox(hWnd, szBuf, "connect関数成功", MB_OK);

    // ユーザーIDを送信
    wsprintf(szBuf, "USER %s\r\n", szID);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    MessageBox(hWnd, szBuf, "ユーザーID成功", MB_OK);

    // パスワードを送信
    wsprintf(szBuf, "PASS %s\r\n", szPass);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd,  "パスワードが不正です", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        return -6;
    }
    MessageBox(hWnd, szBuf, "パスワード成功", MB_OK);

    // 接続を切る
    MessageBox(hWnd, "これから接続を切ります", "OK", MB_OK);
    strcpy_s(szBuf, "QUIT\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);
    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    MessageBox(hWnd, szBuf, "QUIT送信後", MB_OK);

    closesocket(s);
    WSACleanup();
    return 0;
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hPopName, hID, hPass, hPort;

    switch (msg) {
        case WM_INITDIALOG:
            // コントロールのハンドルを取得
            hPopName = GetDlgItem(hDlg, IDC_POP3);
            hID = GetDlgItem(hDlg, IDC_ID);
            hPass = GetDlgItem(hDlg, IDC_PASS);
            hPort = GetDlgItem(hDlg, IDC_PORT);
            // グローバル変数の値をコントロールに表示
            Edit_SetText(hPopName, szPopName);
            Edit_SetText(hID, szID);
            Edit_SetText(hPass, szPass);
            wsprintf(szPort, "%d", port);
            Edit_SetText(hPort, szPort);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:
                    // コントロールの値をグローバル変数に保管
                    Edit_GetText(
                        hPopName, szPopName, sizeof(szPopName));
                    Edit_GetText(hID, szID, sizeof(szID));
                    Edit_GetText(hPass, szPass, sizeof(szPass));
                    Edit_GetText(hPort, szPort, sizeof(szPort));
                    port = atoi(szPort);

                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDCANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}
