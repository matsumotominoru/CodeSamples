// memo02.cpp

#define ID_EDIT  100    // 入力用エディットコントロールのID
#define ID_EDIT2 101    // 情報ウィンドウ用エディットコントロールのID
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MyEditProc(HWND, UINT, WPARAM, LPARAM);

ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyNew(HWND);
int MyOpen(HWND);
int MySave(HWND);
int MySaveAs(HWND);
int MyConfirm(HWND);
int MyYmd(HWND, HWND, int);
int MySetInfo(HWND hEdit, HWND hEdit2);

TCHAR szClassName[] = TEXT("memo02");  // ウィンドウクラス
HINSTANCE hInst;                       // インスタンスハンドル
TCHAR szTitle[128] = TEXT("猫でもわかるメモ帳もどき");
TCHAR szTitle_org[] = TEXT("猫でもわかるメモ帳もどき[%s](%dバイト)");
TCHAR szFile[MAX_PATH];
TCHAR szFileTitle[MAX_PATH];
HWND hMain;             // メインウィンドウのハンドル
HWND hSubEdit;
BOOL bInfo = TRUE;     // 情報ウィンドウの表示・非表示
WNDPROC OrgEditProc;   // プロシージャアドレスを格納するための変数

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;
    HACCEL hAccel;

    hInst = hCurInst;
    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow))
        return FALSE;

    hAccel = LoadAccelerators(hCurInst, TEXT("MYACCEL"));

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
            break;
        } else {
            if (!TranslateAccelerator(hMain, hAccel, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
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
    wc.hIcon = (HICON)LoadImage(hInst, TEXT("MYICON"), IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = TEXT("MYMENU");  // メニュー名
    wc.lpszClassName = szClassName;
    wc.hIconSm = (HICON)LoadImage(hInst, TEXT("MYICON"), IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, szTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    hMain = hWnd;
    return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id, w, h, info_h, nStart, nEnd;
    static HWND hEdit, hEdit2;
    static HMENU hMenu;
    HICON hIcon;
    HDC hdc, hdc_mem;
    PAINTSTRUCT ps;
    HBITMAP hBmp;
    BITMAP bmp_info;
    RECT rc;
    MENUITEMINFO mi;

    switch (msg) {
        case WM_CREATE:
            hMenu = GetMenu(hWnd);    // メニューハンドルを取得

            // 入力用エディットコントロールを作成
            hEdit = CreateWindow(TEXT("EDIT"), NULL,
                WS_CHILD | WS_VISIBLE | ES_WANTRETURN |
                ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL |
                ES_AUTOHSCROLL | WS_HSCROLL,
                0, 0, 0, 0, hWnd, (HMENU)ID_EDIT, hInst, NULL);
            // 情報ウィンドウ用エディットコントロールを作成
            hEdit2 = CreateWindow(TEXT("EDIT"), NULL,
                WS_CHILD | WS_VISIBLE | ES_WANTRETURN |
                ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                0, 0, 0, 0, hWnd, (HMENU)ID_EDIT2, hInst, NULL);

            hSubEdit = hEdit2;
            lstrcat(szTitle, TEXT("[無題]"));
            SetWindowText(hWnd, szTitle);
            Edit_LimitText(hEdit, 0);

            // 情報ウィンドウにマージンを設定
            SendMessage(hEdit2, EM_SETMARGINS,
                EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(20, 20));

            // エディットコントロールをサブクラス化
            OrgEditProc = (WNDPROC)SetWindowLongPtr(
                hEdit, GWL_WNDPROC, (LONG)MyEditProc);
            break;
        case WM_SIZE:
            if (bInfo)          // 「情報ウィンドウ」が表示状態の場合
                info_h = 50;
            else
                info_h = 0;
            MoveWindow(hEdit, 0, 0, LOWORD(lp),
                       HIWORD(lp) - info_h, TRUE);
            if (bInfo)
                MoveWindow(hEdit2, 150, HIWORD(lp) - 50,
                           LOWORD(lp) - 150, 50, TRUE);
            break;
        case WM_PAINT:
            if (bInfo) {
                GetClientRect(hWnd, &rc);
                hdc = BeginPaint(hWnd, &ps);
                hBmp = (HBITMAP)LoadImage(hInst, TEXT("MYBMP"),
                           IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
                GetObject(hBmp, (int)sizeof(BITMAP), &bmp_info);
                w = bmp_info.bmWidth;
                h = bmp_info.bmHeight;
                hdc_mem = CreateCompatibleDC(hdc);
                SelectObject(hdc_mem, hBmp);
                BitBlt(hdc, 0, rc.bottom - 50, w, h,
                       hdc_mem, 0, 0, SRCCOPY);
                DeleteObject(hBmp);
                DeleteDC(hdc_mem);
                EndPaint(hWnd, &ps);
            }
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_NEW:
                    MyNew(hEdit);
                    break;
                case IDM_OPEN:
                    MyOpen(hEdit);
                    break;
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_SAVE:
                    MySave(hEdit);
                    break;
                case IDM_SAVEAS:
                    MySaveAs(hEdit);
                    break;
                case IDM_UNDO:
                    SendMessage(hEdit, EM_UNDO, 0, 0);
                    break;
                case IDM_CUT:
                    SendMessage(hEdit, WM_CUT, 0, 0);
                    break;
                case IDM_COPY:
                    SendMessage(hEdit, WM_COPY, 0, 0);
                    break;
                case IDM_PASTE:
                    SendMessage(hEdit, WM_PASTE, 0, 0);
                    break;
                case IDM_DEL:
                    SendMessage(hEdit, WM_CLEAR, 0, 0);
                    break;
                case IDM_ALL:
                    SendMessage(hEdit, EM_SETSEL, 0, -1);
                    break;
                case IDM_ABOUT:
                    hIcon = (HICON)LoadImage(hInst, TEXT("MYICON"),
                        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
                    ShellAbout(hWnd,
                        TEXT("猫でもわかるメモ帳もどき#")
                        TEXT("猫でもわかるメモ帳もどきVer.0.500"),
                        TEXT("Copyright (C) 2012 Y.Kumei"), hIcon);
                    break;
                case IDM_INFO:
                    GetWindowRect(hWnd, &rc);
                    if (bInfo) {
                        bInfo = FALSE;
                        ShowWindow(hEdit2, SW_HIDE);
                    } else {
                        bInfo = TRUE;
                        ShowWindow(hEdit2, SW_NORMAL);
                    }
                    GetClientRect(hWnd, &rc);
                    SendMessage(hWnd, WM_SIZE, (WPARAM)SIZE_RESTORED,
                        MAKELPARAM(rc.right, rc.bottom));
                    UpdateWindow(hEdit);
                    break;
                case IDM_YMD1:
                    MyYmd(hEdit, hEdit2, 1);
                    break;
                case IDM_YMD2:
                    MyYmd(hEdit, hEdit2, 2);
                    break;
                case IDM_HMS1:
                    MyYmd(hEdit, hEdit2, 3);
                    break;
                case IDM_HMS2:
                    MyYmd(hEdit, hEdit2, 4);
                    break;
            }
            if (lp != (LPARAM)hEdit)
                return DefWindowProc(hWnd, msg, wp, lp);
            switch (HIWORD(wp)) {
                case EN_CHANGE:
                    MySetInfo(hEdit, hEdit2);
                    break;
            }
            break;
        case WM_SETFOCUS:
            SetFocus(hEdit);
            break;
        case WM_INITMENU:
            if (SendMessage(hEdit, EM_CANUNDO, 0, 0) == 0) {
                EnableMenuItem(
                    hMenu, IDM_UNDO, MF_BYCOMMAND | MF_GRAYED);
            } else {
                EnableMenuItem(
                    hMenu, IDM_UNDO, MF_BYCOMMAND | MF_ENABLED);
            }
            mi.cbSize = sizeof(MENUITEMINFO);
            mi.fMask = MIIM_STATE;
            if (bInfo) {
                mi.fState = MFS_CHECKED;
                SetMenuItemInfo(hMenu, IDM_INFO, FALSE, &mi);
            } else {
                mi.fState = MFS_UNCHECKED;
                SetMenuItemInfo(hMenu, IDM_INFO, FALSE, &mi);
            }
            SendMessage(
                hEdit, EM_GETSEL, (WPARAM)&nStart, (LPARAM)&nEnd);
            if (nStart == nEnd) {
                EnableMenuItem(
                    hMenu, IDM_CUT, MF_BYCOMMAND | MF_GRAYED);
                EnableMenuItem(
                    hMenu, IDM_COPY, MF_BYCOMMAND | MF_GRAYED);
            } else {
                EnableMenuItem(
                    hMenu, IDM_CUT, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(
                    hMenu, IDM_COPY, MF_BYCOMMAND | MF_ENABLED);
            }
            if (IsClipboardFormatAvailable(CF_TEXT)) {
                EnableMenuItem(
                    hMenu, IDM_PASTE, MF_BYCOMMAND | MF_ENABLED);
            } else {
                EnableMenuItem(
                    hMenu, IDM_PASTE, MF_BYCOMMAND | MF_GRAYED);
            }
            DrawMenuBar(hWnd);
            break;
        case WM_CLOSE:
            id = MyConfirm(hEdit);
            if (id == IDCANCEL)
                break;
            id = MessageBox(hWnd, TEXT("終了してもよろしいですか"),
                            TEXT("確認"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                SetWindowLongPtr(hEdit, GWL_WNDPROC, (LONG)OrgEditProc);
                DestroyWindow(hEdit);
                DestroyWindow(hEdit2);
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

int MyNew(HWND hEdit)
{
    int id;
    id = MyConfirm(hEdit);
    if (id == IDCANCEL) {
        return -1;
    }
    Edit_SetText(hEdit, TEXT(""));
    SetWindowText(GetParent(hEdit),
                  TEXT("猫でもわかるメモ帳もどき[無題]"));
    lstrcpy(szFile, TEXT(""));
    return 0;
}

int MyOpen(HWND hEdit)
{
    int id;
    HWND hMain;
    DWORD dwSize = 0L;
    OPENFILENAME ofn;
    HANDLE hFile;
    DWORD dwAccBytes;
    LPTSTR lpszBuf;

    HGLOBAL hMem;

    id = MyConfirm(hEdit);
    if (id == IDCANCEL)
        return -1;

    // OPENFILENAME構造体を設定
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hEdit;
    ofn.lpstrFilter =
        TEXT("text(*.txt)\0*.txt\0All files(*.*)\0*.*\0\0");
    ofn.lpstrFile = szFile;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = TEXT("txt");
    ofn.lpstrTitle = TEXT("猫でもわかるファイルオープン");

    if(GetOpenFileName(&ofn) == 0)  // 「ファイルを開く」ダイアログ
        return -1;

    hFile = CreateFile(szFile,  // ファイル名
        GENERIC_READ,           // 読み取り/書き込みアクセス
        0,                      // 共有設定 0だと共有対象としない
        NULL,                   // セキュリティ属性
        OPEN_ALWAYS,            // ファイルがすでに存在しているかどうか
        FILE_ATTRIBUTE_NORMAL,  // ファイル属性
        NULL);
    dwSize = GetFileSize(hFile, NULL);  // ファイルサイズを取得

    // メモリを動的に確保
    hMem = GlobalAlloc(GHND, dwSize + sizeof(TCHAR));
    if (hMem == NULL) {
        MessageBox(hEdit, TEXT("メモリを確保できません"),
                   TEXT("猫でもわかるメモ帳もどき"),
                   MB_ICONEXCLAMATION | MB_OK);
        return -1;
    }
    lpszBuf = (LPTSTR)GlobalLock(hMem);

    // ファイルを読み込み、エディットコントロールに表示する
    ReadFile(hFile, lpszBuf, dwSize, &dwAccBytes, NULL);
    lpszBuf[dwAccBytes] = TEXT('\0');
    Edit_SetText(hEdit, lpszBuf);

    // タイトルバーの設定
    wsprintf(szTitle, szTitle_org, szFileTitle, dwSize);
    hMain = GetParent(hEdit);
    SetWindowText(hMain, szTitle);

    CloseHandle(hFile);
    GlobalUnlock(hMem);
    GlobalFree(hMem);

    return 0;
}

int MySaveAs(HWND hEdit)
{
    OPENFILENAME ofn;
    HANDLE hFile;
    DWORD dwAccBytes;

    LPTSTR lpszBuf;
    int nLen;
    HGLOBAL hMem;

    // エディットコントロールに書き込まれている文字数を取得し、
    // それに見合うメモリを動的に確保
    nLen = GetWindowTextLength(hEdit);
    hMem = GlobalAlloc(GHND, sizeof(TCHAR) * (nLen + 1));
    lpszBuf = (LPTSTR)GlobalLock(hMem);

    // エディットコントロールの内容をlpszBufに保管
    GetWindowText(hEdit, lpszBuf, nLen + 1);

    // OPENFILENAME構造体を設定
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hEdit;
    ofn.lpstrFilter =
        TEXT("text(*.txt)\0*.txt\0All files(*.*)\0*.*\0\0");
    ofn.lpstrFile = szFile;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nFilterIndex = 1;
    ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = TEXT("txt");
    ofn.lpstrTitle = TEXT("名前を付けて保存する");

    if(GetSaveFileName(&ofn) == 0)  // 「ファイルを保存」ダイアログ
        return -1;

    // ファイルにlpszBufの内容を書き込む
    hFile = CreateFile(szFile, GENERIC_WRITE, 0, NULL,
                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hFile, lpszBuf, (DWORD)lstrlen(lpszBuf),
              &dwAccBytes, NULL);

    // タイトルバーの設定
    wsprintf(szTitle, szTitle_org, szFileTitle, nLen);
    SetWindowText(GetParent(hEdit), szTitle);

    if(CloseHandle(hFile) == 0)
        MessageBox(hEdit, TEXT("Error CloseHandle"),
                   TEXT("Error"), MB_OK);

    // エディットコントロールの変更フラグをFALSEに設定
    SendMessage(hEdit, EM_SETMODIFY, FALSE, 0);

    GlobalUnlock(hMem);
    GlobalFree(hMem);

    return 0;
}

int MySave(HWND hEdit)
{
    HANDLE hFile;
    DWORD dwAccBytes;
    int nLen;
    LPTSTR lpszBuf;
    HGLOBAL hMem;

    if (lstrcmp(szFile, TEXT("") ) == 0) {
        MessageBox(hEdit, TEXT("ファイル名が付けられていません"),
                   TEXT("猫でもわかるメモ帳もどき"), MB_OK);
        MySaveAs(hEdit);
        return -1;
    }

    // エディットコントロールに書き込まれている文字数を取得し、
    // それに見合うメモリを動的に確保
    nLen = GetWindowTextLength(hEdit);
    hMem = GlobalAlloc(GHND, nLen + sizeof(TCHAR));
    lpszBuf = (LPTSTR)GlobalLock(hMem);

    // エディットコントロールの内容をlpszBufに保管
    GetWindowText(hEdit, lpszBuf, nLen + 1);

    // ファイルにlpszBufの内容を書き込む
    hFile = CreateFile(szFile, GENERIC_WRITE, 0, NULL,
                TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hFile, lpszBuf, (DWORD)lstrlen(lpszBuf),
              &dwAccBytes, NULL);

    GlobalUnlock(hMem);
    GlobalFree(hMem);

    // エディットコントロールの変更フラグをFALSEに設定
    SendMessage(hEdit, EM_SETMODIFY, FALSE, 0);

    wsprintf(szTitle, szTitle_org, szFileTitle, nLen);
    SetWindowText(GetParent(hEdit), szTitle);
    if (CloseHandle(hFile) == 0) {
        MessageBox(hEdit, TEXT("Error CloseHandle"),
                   TEXT("Error"), MB_OK);
        return -1;
    }

    return 0;
}

int MyConfirm(HWND hEdit)
{
    int id;

    if (SendMessage(hEdit, EM_GETMODIFY, 0, 0) == TRUE) {
        id = MessageBox(hEdit,
            TEXT("文書が更新されています。\n変更を保存しますか?"),
            TEXT("猫でもわかるメモ帳もどき"),
            MB_YESNOCANCEL | MB_ICONEXCLAMATION);
        if (id == IDYES) {
            MySave(hEdit);
        } else if (id == IDCANCEL) {
            return IDCANCEL;
        } else if (id ==  IDNO) {
            return IDNO;
        }
    }
    return 0;
}

int MyYmd(HWND hEdit, HWND hEdit2, int nOption)
{
    SYSTEMTIME st;
    TCHAR szBuf[64];

    GetLocalTime(&st);
    switch (nOption) {
        case 1:
            wsprintf(szBuf, TEXT("%d年%02d月%02d日"),
                     st.wYear, st.wMonth, st.wDay);
            break;
        case 2:
            wsprintf(szBuf, TEXT("%d/%02d/%02d"),
                     st.wYear, st.wMonth, st.wDay);
            break;
        case 3:
            wsprintf(szBuf, TEXT("%02d時%02d分%02d秒"),
                st.wHour, st.wMinute, st.wSecond);
            break;
        case 4:
            wsprintf(szBuf, TEXT("%02d:%02d:%02d"),
                     st.wHour, st.wMinute, st.wSecond);
            break;
    }

    SetWindowText(hEdit2, szBuf);           // hEdit2に日時を表示
    SendMessage(hEdit2, EM_SETSEL, 0, -1);  // hEdit2の文字列をすべて選択
    SendMessage(hEdit2, WM_COPY, 0, 0);     // 選択した文字列をコピー
    SendMessage(hEdit, WM_PASTE, 0, 0);     // hEditに貼り付け

    return 0;
}

int MySetInfo(HWND hEdit, HWND hEdit2)
{
    TCHAR szBuf[256], szBuf2[64];
    int nLen, nLine, nStart, nEnd;

    nLen = GetWindowTextLength(hEdit);
    nLine = (int)SendMessage(hEdit, EM_GETLINECOUNT, 0, 0);
    wsprintf(szBuf, 
        TEXT("文字数= %d 文字\t行 = %d "), nLen, nLine);
    SendMessage(hEdit, EM_GETSEL, (WPARAM)&nStart, (LPARAM)&nEnd);
    if (nStart != nEnd) {
        wsprintf(szBuf2, TEXT("\r\n選択開始位置 = %d, 終了位置 = %d"),
                 nStart, nEnd);
        lstrcat(szBuf, szBuf2);
    }
    SetWindowText(hEdit2, szBuf);
    return 0;
}

LRESULT CALLBACK MyEditProc(HWND hEdit, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
        case WM_LBUTTONUP:
        case WM_KEYUP:
            MySetInfo(hEdit, hSubEdit);
            break;
    }
    return CallWindowProc(OrgEditProc, hEdit, msg, wp, lp);
}
