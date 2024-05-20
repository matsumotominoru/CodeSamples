// controls01.cpp

#include <windows.h>
#include <windowsx.h>        // コントロール関連のマクロを使うため
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("controls01");  // ウィンドウクラス
HINSTANCE hInst;
TCHAR szText[6][64];
int nSex, nNation, n20, nPet, nAddress, nPos = 50;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;      // インスタンスハンドルをグローバル変数に保管
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

    hWnd = CreateWindow(szClassName, TEXT("猫でもわかるコントロール"),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            270, 200, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int n;
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            for (n = 0; n < 6; n++)
                TextOut(hdc, 10, 20 * n + 10, szText[n],
                        lstrlen(szText[n]));
            EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_DLG:
                    // ダイアログボックスを表示する
                    DialogBox(hInst, TEXT("MYDLG"), hWnd,
                              (DLGPROC)MyDlgProc);
                    break;
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

//ダイアログボックスのプロシージャ
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hRadio1, hRadio2, hRadio3, hRadio4;
    static HWND hCheck1, hCombo1, hList1, hEdit1, hScrol1;
    TCHAR szBuf[64];
    TCHAR szList[5][16] = { TEXT("飼っていない"), TEXT("犬"),
                            TEXT("猫"), TEXT("ねずみ"), TEXT("馬")};
    TCHAR szCombo[6][16] = { TEXT("北海道"), TEXT("本州"), TEXT("四国"),
                             TEXT("九州"), TEXT("沖縄"), TEXT("その他") };
    static HWND hMain;
    int id, n;
    BOOL bSuccess;

    switch (msg) {
        case WM_HSCROLL:        // スクロールイベントの処理
            if (lp != (LPARAM)hScrol1)
                return FALSE;
            switch (LOWORD(wp)) {
                case SB_LEFT:
                    nPos = 0;
                    break;
                case SB_RIGHT:
                    nPos = 100;
                    break;
                case SB_LINELEFT:
                    nPos--;
                    if (nPos < 0)   nPos = 0;
                    break;
                case SB_LINERIGHT:
                    nPos++;
                    if (nPos > 100) nPos = 100;
                    break;
                case SB_PAGELEFT:
                    nPos -= 10;
                    if (nPos > 100) nPos = 100;
                    break;
                case SB_PAGERIGHT:
                    nPos += 10;
                    if (nPos < 0)   nPos = 0;
                    break;
                case SB_THUMBTRACK:
                case SB_THUMBPOSITION:
                    nPos = HIWORD(wp);
                    break;
                
            }

            // スクロールつまみを移動させる
            ScrollBar_SetPos(hScrol1, nPos, TRUE);

            wsprintf(szBuf, TEXT("%03d"), nPos);
            Edit_SetText(hEdit1, szBuf);
            wsprintf(szText[5],
                TEXT("スクロールバーの位置=%03d"), nPos);
            InvalidateRect(hMain, NULL, TRUE);
            return TRUE;
        case WM_INITDIALOG:
            //親ウィンドウのハンドル取得
            hMain = GetParent(hDlg);
            //各コントロールのハンドルを取得
            hRadio1 = GetDlgItem(hDlg, IDC_RADIO1);
            hRadio2 = GetDlgItem(hDlg, IDC_RADIO2);
            hRadio3 = GetDlgItem(hDlg, IDC_RADIO3);
            hRadio4 = GetDlgItem(hDlg, IDC_RADIO4);
            hCheck1 = GetDlgItem(hDlg, IDC_CHECK1);
            hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
            hList1 = GetDlgItem(hDlg, IDC_LIST1);
            hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
            hScrol1 = GetDlgItem(hDlg, IDC_SCROLLBAR1);
            //スクロールバーの初期設定
            ScrollBar_SetRange(hScrol1, 0, 100, TRUE);
            ScrollBar_SetPos(hScrol1, nPos, TRUE);
            //ラジオグループの初期設定
            if (nSex == 0)
                Button_SetCheck(hRadio1, BST_CHECKED);
            else
                Button_SetCheck(hRadio2, BST_CHECKED);
            if (nNation == 0)
                Button_SetCheck(hRadio3, BST_CHECKED);
            else
                Button_SetCheck(hRadio4, BST_CHECKED);
            //チェックボックスの設定
            if (n20 == 1)
                Button_SetCheck(hCheck1, BST_CHECKED);
            else
                Button_SetCheck(hCheck1, BST_UNCHECKED);
            //コンボボックスに文字列を加える
            for (n = 0; n < 6; n++)
                ComboBox_AddString(hCombo1, szCombo[n]);
            //リストボックスに文字列を加える
            for (n = 0; n < 5; n++)
                ListBox_AddString(hList1, szList[n]);
            //コンボボックスの初期値
            ComboBox_SetCurSel(hCombo1, nAddress);
            ListBox_SetCurSel(hList1, nPet);
            wsprintf(szBuf, TEXT("%03d"), nPos);
            Edit_SetText(hEdit1, szBuf);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDCANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
                case IDOK:
                    if (nSex == 0)
                        lstrcpy(szText[0], TEXT("男が選択されました"));
                    else
                        lstrcpy(szText[0], TEXT("女が選択されました"));
                    if (nNation == 0)
                        lstrcpy(szText[1], TEXT("日本が選択されました"));
                    else
                        lstrcpy(szText[1], 
                        TEXT("日本以外が選択されました"));
                    if (n20 == 0)
                        lstrcpy(szText[2], TEXT("20歳未満です"));
                    else
                        lstrcpy(szText[2], TEXT("20歳以上です"));
                    wsprintf(szText[3], TEXT("%sが選択されました"),
                             szCombo[nAddress]);
                    wsprintf(szText[4], TEXT("%sが選択されました"),
                             szList[nPet]);
                    wsprintf(szText[5],
                             TEXT("スクロールバーの位置=%03d"), nPos);
                    InvalidateRect(hMain, NULL, TRUE);
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDC_RADIO1:
                    nSex = 0;
                    lstrcpy(szText[0], TEXT("男が選択されました"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_RADIO2:
                    nSex = 1;
                    lstrcpy(szText[0], TEXT("女が選択されました"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_RADIO3:
                    nNation = 0;
                    lstrcpy(szText[1], TEXT("日本が選択されました"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_RADIO4:
                    nNation = 1;
                    lstrcpy(szText[1], TEXT("日本以外が選択されました"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_CHECK1:
                    if (Button_GetCheck(hCheck1) == BST_CHECKED) {
                        n20 = 1;
                        lstrcpy(szText[2], TEXT("20歳以上です"));
                    } else {
                        n20 = 0;
                        lstrcpy(szText[2], TEXT("20歳未満です"));
                    }
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_COMBO1:
                    id = ComboBox_GetCurSel(hCombo1);
                    wsprintf(szText[3],
                             TEXT("%sが選択されました"), szCombo[id]);
                    InvalidateRect(hMain, NULL, TRUE);
                    nAddress = id;
                    return TRUE;
                case IDC_LIST1:
                    id = ListBox_GetCurSel(hList1);
                    wsprintf(szText[4],
                             TEXT("%sが選択されました"), szList[id]);
                    InvalidateRect(hMain, NULL, TRUE);
                    nPet = id;
                    return TRUE;
                case IDC_EDIT1:
                    nPos = GetDlgItemInt(
                        hDlg, IDC_EDIT1, &bSuccess, FALSE);
                    if (nPos > 100)
                        nPos = 100;
                    if (nPos < 0)
                        nPos = 0;
                    ScrollBar_SetPos(hScrol1, nPos, TRUE);
                    wsprintf(szText[5],
                             TEXT("スクロールバーの位置=%03d"), nPos);
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}
