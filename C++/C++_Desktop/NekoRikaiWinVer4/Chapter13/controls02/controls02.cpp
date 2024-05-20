// controls02.cpp

#define ID_BUTTON 100
#define ID_EDIT 101

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("controls02");  // ウィンドウクラス
HINSTANCE hInst;

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

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるコントロール"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, 230, 125, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// ウィンドウプロシージャ
#include <windowsx.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    static HWND hBtn, hEdit;
    TCHAR szBuf[64];

    switch (msg) {
        case WM_CREATE:
            // エディットコントロールを作成
            hEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                10, 10, 200, 25, hWnd, (HMENU)ID_EDIT, hInst, NULL);
            // ボタンを作成
            hBtn = CreateWindow(TEXT("BUTTON"), TEXT("押す"),
                WS_CHILD | WS_VISIBLE,  85, 45, 50, 30,
                hWnd, (HMENU)ID_BUTTON, hInst, NULL);
            // エディットコントロールにフォーカスを与える
            SendMessage(hEdit, EM_SETLIMITTEXT, (WPARAM)63, 0);
            break;
        case WM_SETFOCUS:
            SetFocus(hEdit);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case ID_BUTTON:
                    GetWindowText(hEdit, szBuf, 64);
                    MessageBox(hWnd, szBuf,
                            TEXT("猫でもわかるコントロール"), MB_OK);
                    SetWindowText(hEdit, TEXT(""));
                    break;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd,
                TEXT("終了してもよろしいですか"),
                TEXT("確認"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                DestroyWindow(hEdit);
                DestroyWindow(hBtn);
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
