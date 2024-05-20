// status01.cpp

#define MY_STATUS 100                    // ステータスバーのID
#include <windows.h>
#include <commctrl.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND MyCreateStatusbar(HWND hWnd);

TCHAR szClassName[] = TEXT("status01");  // ウィンドウクラス
HINSTANCE hInst;                         // インスタンスハンドル

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
    wc.lpfnWndProc = WndProc;  // プロシージャ名
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;      // インスタンス
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;    // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるステータスバー"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    INITCOMMONCONTROLSEX ic;
    static HWND hStatus;

    switch (msg) {
        case WM_CREATE:
            // コモンコントロールを初期化
            ic.dwICC = ICC_BAR_CLASSES;
            ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
            InitCommonControlsEx(&ic);
            // ステータスバーを作成
            hStatus = MyCreateStatusbar(hWnd);
            break;
        case WM_SIZE:
            SendMessage(hStatus, msg, wp, lp);
            break;
        case WM_DESTROY:
            DestroyWindow(hStatus);
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

HWND MyCreateStatusbar(HWND hWnd)
{
    HWND hStatus;

    hStatus = CreateWindowEx(
        0,                  //拡張スタイル
        STATUSCLASSNAME,    //ウィンドウクラス
        NULL,               //タイトル
        // ウィンドウスタイル
        //   WS_VISIBLEを指定しないときは必ずShowWindow関数を呼ぶ
        WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM | WS_VISIBLE,
        0, 0, 0, 0,         // x座標, y座標, ウィンドウ幅, 高さ
        hWnd,               //親ウィンドウ
        (HMENU)MY_STATUS,   //ステータスバーのID
        hInst,              //インスタンスハンドル
        NULL);
    SendMessage(hStatus, SB_SIMPLE, 0, 0);
	SendMessage(hStatus, SB_SETTEXT, 0 | 0,
                (LPARAM)TEXT("猫でもわかるステータスバー"));
    return hStatus;
}
