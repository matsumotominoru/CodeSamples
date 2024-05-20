// wclient.cpp

#define WIN32_LEAN_AND_MEAN
#define MY_MSG (WM_USER + 1)     // 自前のメッセージ

#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include "resource.h"

BOOL CALLBACK MyClientProc(HWND, UINT, WPARAM, LPARAM);

char szAppName[] = "猫でもわかるTCPクライアント";
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    WSADATA wsaData;
    hInst = hCurInst;

    // WinSockを初期化
    if (WSAStartup(MAKEWORD(1, 1), &wsaData)) {
        MessageBox(NULL, "WSAStartupに失敗しました", szAppName,
            MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return -1;
    }

    // ダイアログボックスを生成
    DialogBox(hCurInst, "MYCLIENT", NULL, (DLGPROC)MyClientProc);

    // WinSockのリソースを解放
    if (WSACleanup() == SOCKET_ERROR)
        MessageBox(NULL, "WSACleanup失敗です", szAppName, MB_OK);

    MessageBox(NULL, "終了します", szAppName, MB_OK);
    return 0;
}

// ダイアログボックスのプロシージャ
BOOL CALLBACK MyClientProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static SOCKET s;
    static SOCKADDR_IN saddr;
    char szBuf[1024];
    static char szAllBuf[1024 * 50];
    char szServer[1024];
    static HOSTENT *lpHost;
    static u_short uport;
    BOOL bSuccess;
    unsigned int addr;
    int nEvent, nResult;
    static BOOL bConnect = FALSE;
    static HWND hInfo, hSendBtn, hStart;
    HICON hIcon;

    switch (msg) {
        case WM_INITDIALOG:
            // アイコンリソースの読み込み
            hIcon = (HICON)LoadImage(hInst, "MYICON",
                IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_SHARED);
            // アイコンを登録
            SendMessage(
                hDlg, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
            // コントロールのハンドルを取得
            hInfo = GetDlgItem(hDlg, IDC_INFO);
            hSendBtn = GetDlgItem(hDlg, IDC_SENDBTN);
            hStart = GetDlgItem(hDlg, IDC_START);
            // 「送信」ボタンを使用不可に設定
            EnableWindow(hSendBtn, FALSE);
            return FALSE;
        case MY_MSG:
            nEvent = WSAGETSELECTEVENT(lp);
            switch (nEvent) {
                case FD_CONNECT:
                    strcpy_s(szBuf, "クライアントは接続完了しています");
                    nResult = send(s, szBuf, (int)strlen(szBuf), 0);
                    if (nResult == SOCKET_ERROR) {
                        MessageBox(hDlg, 
                            "サーバが起動していないか、"
                            "他のクライアントが接続"
                            "している可能性があります",
                            szAppName, MB_OK);
                        if (bConnect) {
                            closesocket(s);
                            bConnect = FALSE;
                        }
                        EnableWindow(hStart, TRUE);
                        return TRUE;
                    }
                    MessageBox(hDlg, "サーバに接続しました",
                        szAppName, MB_OK);
                    EnableWindow(hSendBtn, TRUE);
                    EnableWindow(hStart, FALSE);
                    return TRUE;
                case FD_READ:
                    nResult = recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
                    szBuf[nResult] = '\0';
                    strcat_s(szAllBuf, "Server: ");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    SendMessage(hInfo, EM_LINESCROLL,
                        0, Edit_GetLineCount(hInfo));
                    return TRUE;
                case FD_CLOSE:
                    MessageBox(hDlg, "サーバから切断されました", 
                        szAppName, MB_OK);
                    if (closesocket(s) == SOCKET_ERROR)
                        MessageBox(hDlg, "ソケットクローズ失敗", 
                        szAppName, MB_OK);
                    bConnect = FALSE;
                    EnableWindow(hSendBtn, FALSE);
                    EnableWindow(hStart, TRUE);
                    return TRUE;
            }
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDC_SENDBTN:    // 「送信」ボタン
                    // IDC_SENDの内容を送信
                    GetDlgItemText(
                        hDlg, IDC_SEND, szBuf, (int)sizeof(szBuf));
                    nResult = send(s, szBuf, (int)strlen(szBuf), 0);

                    if (nResult == SOCKET_ERROR) {
                        MessageBox(hDlg, "sendエラーです", szAppName, MB_OK);
                        closesocket(s);
                        bConnect = FALSE;
                        return FALSE;
                    }
                    // 文字列の体裁を整え、メッセージ欄に表示
                    strcat_s(szAllBuf, "Client: ");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    // メッセージ欄をスクロール
                    SendMessage(hInfo, EM_LINESCROLL,
                        0, Edit_GetLineCount(hInfo));
                    // IDC_SENDの文字列を削除
                    SetDlgItemText(hDlg, IDC_SEND, "");
                    // IDC_SENDにフォーカスを設定
                    SetFocus(GetDlgItem(hDlg, IDC_SEND));
                    return TRUE;
                case IDC_START:      // 「接続」ボタン
                    // ポート番号を取得
                    uport = GetDlgItemInt(
                        hDlg, IDC_PORT, &bSuccess, FALSE);
                    if (!bSuccess) {
                        MessageBox(hDlg, "ポート番号が正しくないです",
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        return FALSE;
                    }
                    // サーバ名を取得
                    GetDlgItemText(
                        hDlg, IDC_SERVER, szServer, sizeof(szServer));
                    if (strcmp(szServer, "") == 0) {
                        MessageBox(hDlg,
                            "サーバ名を入力してください",
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        return FALSE;
                    }
                    // ソケットをオープン
                    s = socket(AF_INET, SOCK_STREAM, 0);
                    if (s < 0) {
                        MessageBox(hDlg, "ソケットオープンエラー",
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        return TRUE;
                    }
                    bConnect = TRUE;
                    // サーバ情報を取得
                    lpHost = gethostbyname(szServer);
                    if (lpHost == NULL) {
                        addr = inet_addr(szServer);
                        lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
                    }
                    if (lpHost == NULL) {
                        MessageBox(hDlg, 
                            "ホスト情報を取得できません", 
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        closesocket(s);
                        bConnect = FALSE;
                        return TRUE;
                    }

                    // ソケットを非同期モードに
                    WSAAsyncSelect(s, hDlg, MY_MSG, 
                        FD_CONNECT | FD_READ | FD_CLOSE);

                    // SOCKADDR_IN構造体に必要事項をセット
                    memset(&saddr, 0, sizeof(SOCKADDR_IN));
                    saddr.sin_family = lpHost->h_addrtype;
                    saddr.sin_port = htons(uport);
                    saddr.sin_addr.s_addr = *((u_long *)lpHost->h_addr);
                    // クライアントソケットをサーバに接続
                    if (connect(s, (SOCKADDR *)&saddr, 
                            sizeof(saddr)) == SOCKET_ERROR) {
                        // エラーの種類を特定
                        if (WSAGetLastError() != WSAEWOULDBLOCK) {
                            MessageBox(hDlg, "connect Error",
                                szAppName, MB_OK | MB_ICONEXCLAMATION);
                            closesocket(s);
                            bConnect = FALSE;
                            return FALSE;
                        } else {
                            MessageBox(hDlg, "接続待機中", szAppName, MB_OK);
                        }
                    }  else {
                        MessageBox(hDlg, "connect OK", szAppName, MB_OK);
                    } 
                    return TRUE;
                case IDCANCEL:       // 「閉じる」ボタン
                case IDOK:           // 「終了」ボタン
                    if (bConnect) {
                        if (shutdown(s, SD_BOTH) == SOCKET_ERROR) {
                            MessageBox(hDlg, 
                                "shutdownに失敗しました。",
                                szAppName, MB_OK);
                        }
                        if (closesocket(s) != 0) {
                            MessageBox(hDlg, 
                                "ソケットをクローズできませんでした", 
                                szAppName, MB_OK | MB_ICONEXCLAMATION);
                        }
                    }
                    EndDialog(hDlg, IDOK);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}
