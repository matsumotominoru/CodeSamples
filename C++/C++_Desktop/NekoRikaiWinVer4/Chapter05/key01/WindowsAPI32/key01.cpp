// key01.cpp

#include <windows.h>
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int TypeStart(HWND);

TCHAR szClassName[] = TEXT("key01");	//ウィンドウクラス
TCHAR szMondai[32], szInput[32], szCheck[32];
int iMon;
DWORD dwStart, dwEnd;
BOOL bStart = FALSE, bSeikai = TRUE;

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

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるキー入力"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        240, 180, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static HMENU hMenu;
    MMTIME mm;

    switch (msg) {
    case WM_CREATE:
        srand((unsigned)time(NULL));    // 乱数の種をまく
        hMenu = GetMenu(hWnd);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 0, 0, szMondai, lstrlen(szMondai));
        TextOut(hdc, 0, 40, szInput, lstrlen(szInput));
        if (bSeikai)
            SetTextColor(hdc, RGB(0, 0, 0));
        else
            SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, 0, 80, szCheck, lstrlen(szCheck));
        EndPaint(hWnd, &ps);
        break;
    case WM_CHAR:         // ここでキー入力を処理する
        if (wp == VK_SPACE && !bStart) {
            bStart = TRUE;
            TypeStart(hWnd);
            break;
        }
        if (bStart == FALSE)
            return DefWindowProc(hWnd, msg, wp, lp);
        if (wp == VK_ESCAPE) {
            lstrcpy(szMondai, TEXT(""));
            lstrcpy(szInput, TEXT(""));
            lstrcpy(szCheck, TEXT(""));
            InvalidateRect(hWnd, NULL, TRUE);
            bStart = FALSE;
            break;
        }
        wsprintf(szInput, TEXT("あなたの入力=\"%c\""), (int)wp);
        if (iMon == (int)wp) {
            bSeikai = TRUE;

            // システム時刻をミリセコンド単位で取得
            mm.wType = TIME_MS;
            timeGetSystemTime(&mm, sizeof(MMTIME));
            dwEnd = mm.u.ms;

            wsprintf(szCheck, TEXT("反応時間[%dミリ秒]"), dwEnd - dwStart);
            TypeStart(hWnd);
        }
        else {
            bSeikai = FALSE;
            MessageBeep(MB_OK);
            lstrcpy(szCheck, TEXT("タイプミス！"));
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

int TypeStart(HWND hWnd)
{
    int n;
    MMTIME mm;

    n = rand() % 26;          // 0から25までの整数値をランダムに生成
    iMon = 'a' + n;
    wsprintf(szMondai, TEXT("問題=\"%c\""), iMon);

    // システム時刻を取得
    mm.wType = TIME_MS;
    timeGetSystemTime(&mm, sizeof(MMTIME));
    dwStart = mm.u.ms;

    InvalidateRect(hWnd, NULL, TRUE);
    return 0;
}
