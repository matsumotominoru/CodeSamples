// wserver.cpp

#define WIN32_LEAN_AND_MEAN
#define MY_MSG (WM_USER + 1)     // 自前のメッセージ

#include <windows.h>
#include <winsock2.h>
#include <windowsx.h>
#include "resource.h"

BOOL CALLBACK MyServerProc(HWND, UINT, WPARAM, LPARAM);
int mystream(HWND, u_short);

HINSTANCE hInst;

SOCKET listen_s, s;             // リッスンソケットと通信用ソケット
BOOL bSOCKET_LISTEN = FALSE,    // リッスンソケットが有効かどうか
     bSOCKET_S = FALSE;         // 通信用ソケットが有効かどうか

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    WSADATA wsaData;
    hInst = hCurInst;

    // WinSockを初期化
    if (WSAStartup(MAKEWORD(1, 1), &wsaData)) {
        MessageBox(NULL, "初期化失敗", "Error",
            MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return -1;
    }

    // ダイアログボックスを生成
    DialogBox(hCurInst, "MYSERVER", NULL, (DLGPROC)MyServerProc);

    // WinSockのリソースを解放
    if (WSACleanup() != 0) {
        MessageBox(NULL, "WSACleanupエラーです", "Error", MB_OK);
    }

    MessageBox(NULL, "終了します", "終了", MB_OK);
    return 0;
}

// ダイアログボックスのプロシージャ
BOOL CALLBACK MyServerProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hStart, hInfo, hSendBtn;
    static u_short port;
    char szBuf[1024];
    static char szAllBuf[1024 * 10] = "";
    BOOL bSuccess;
    int nEvent, nRet, nAsync;
    SOCKADDR from;
    int fromlen, nError;
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
            hStart = GetDlgItem(hDlg, IDC_START);
            hInfo = GetDlgItem(hDlg, IDC_INFO);
            hSendBtn = GetDlgItem(hDlg, IDC_SENDBTN);
           // 「送信」ボタンを使用不可に設定
            EnableWindow(hSendBtn, FALSE);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDC_START:             // 「開始」ボタン
                    port = (u_short)GetDlgItemInt(
                        hDlg, IDC_PORT, &bSuccess, FALSE);
                    if (mystream(hDlg, port) == 0)
                        EnableWindow(hStart, FALSE);
                    return TRUE;
                case IDC_SENDBTN:           // 「送信」ボタン
                    // IDC_SENDの内容を送信
                    GetDlgItemText(
                        hDlg, IDC_SEND, szBuf, (int)sizeof(szBuf));
                    nRet = send(s, szBuf, (int)strlen(szBuf), 0);
                    // 文字列の体裁を整え、メッセージ欄に表示
                    strcat_s(szAllBuf, "Server:");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    // メッセージ欄をスクロール
                    SendMessage(hInfo,
                        EM_LINESCROLL, 0, Edit_GetLineCount(hInfo));
                    // IDC_SENDの文字列を削除
                    SetDlgItemText(hDlg, IDC_SEND, "");
                    // IDC_SENDにフォーカスを設定
                    SetFocus(GetDlgItem(hDlg, IDC_SEND));
                    return TRUE;
                case IDOK:                  // 「終了」ボタン
                case IDCANCEL:              // 「閉じる」ボタン
                    if (bSOCKET_S) {        // ソケットが有効な場合
                        nRet = shutdown(s, SD_BOTH);
                        if (nRet == SOCKET_ERROR) {
                            MessageBox(hDlg, "シャットダウン失敗",
                                "Error", MB_OK);
                        } else {
                            MessageBox(hDlg, "シャットダウン成功",
                                "shutdown", MB_OK);
                        }
                        if (closesocket(s)) {
                            MessageBox(hDlg, "ソケットクローズ失敗",
                                "Error", MB_ICONEXCLAMATION | MB_OK);
                        }
                    }
                    if (bSOCKET_LISTEN) {   // リスンソケットが有効な場合
                        if (closesocket(listen_s)) {
                            MessageBox(hDlg,
                                "リスンソケットクローズ失敗",
                                "Error", MB_ICONEXCLAMATION | MB_OK);
                        }
                    }
                    EndDialog(hDlg, IDOK);  // ダイアログを閉じる
                    return TRUE;
            }
            return FALSE;
        case MY_MSG:
            nEvent = WSAGETSELECTEVENT(lp);
            switch (nEvent) {
                case FD_CLOSE:
                    MessageBox(hDlg,
                        "クライアントが切断してきました\n"
                        "再待ち受けします",
                        "切断", MB_OK);
                    EnableWindow(hSendBtn, FALSE);
                    closesocket(s);
                    bSOCKET_S = FALSE;
                    mystream(hDlg, port);
                    return TRUE;
                case FD_READ:
                    nRet = recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
                    if (nRet == SOCKET_ERROR) {
                        MessageBox(hDlg, "recvエラー", "Error", MB_OK);
                        return FALSE;
                    }
                    szBuf[nRet] = '\0';
                    strcat_s(szAllBuf, "Client:");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    SendMessage(hInfo,
                        EM_LINESCROLL, 0, Edit_GetLineCount(hInfo));
                    return TRUE;
                case FD_ACCEPT:
                    memset(&from, 0, sizeof(SOCKADDR));
                    fromlen = sizeof(from);
                    s = accept(listen_s, (SOCKADDR *)&from, &fromlen);

                    // エラーチェック
                    if (s == INVALID_SOCKET) {
                        nError = WSAGetLastError();
                        if (nError != WSAEWOULDBLOCK) {
                            switch (nError) {
                                case WSANOTINITIALISED:
                                    MessageBox(hDlg,
                                        "WSANOTINITIALISED",
                                        "Error", MB_OK);
                                    break;
                                case WSAENETDOWN:
                                    MessageBox(hDlg,
                                        "WSAENETDOWN",
                                        "Error", MB_OK);
                                    break;
                                case WSAEFAULT:
                                    MessageBox(hDlg,
                                        "WSAEFAULT",
                                        "Error", MB_OK);
                                    break;
                                case WSAEINTR:
                                    MessageBox(hDlg,
                                        "WSAEINTR",
                                        "Error", MB_OK);
                                    break;
                                case WSAEINPROGRESS:
                                    MessageBox(hDlg,
                                        "WSAEINPROGRESS",
                                        "Error", MB_OK);
                                    break;
                                case WSAEINVAL:
                                    MessageBox(hDlg,
                                        "WSAEINVAL",
                                        "Error", MB_OK);
                                    break;
                                case WSAEMFILE:
                                    MessageBox(hDlg,
                                        "WSAEMFILE",
                                        "Error", MB_OK);
                                    break;
                                case WSAENOBUFS:
                                    MessageBox(hDlg,
                                        "WSAENOBUFS",
                                        "Error", MB_OK);
                                    break;
                                case WSAENOTSOCK:
                                    MessageBox(hDlg,
                                        "WSAENOTSOCK",
                                        "Error", MB_OK);
                                    break;
                                case WSAEOPNOTSUPP:
                                    MessageBox(hDlg,
                                        "WSAEOPNOTSUPP",
                                        "Error", MB_OK);
                                    break;
                                default:
                                    MessageBox(hDlg,
                                        "不明のエラーです",
                                        "Error", MB_OK);
                                    break;
                            }
                            MessageBox(hDlg, "accept error", "Error", MB_OK);
                            closesocket(listen_s);
                            bSOCKET_LISTEN = FALSE;
                            return TRUE;
                        }
                    }  // エラーチェック、ここまで

                    if (closesocket(listen_s) != 0) {
                        MessageBox(hDlg, "Error", "Error", MB_OK);
                        return TRUE;
                    }
                    bSOCKET_LISTEN = FALSE;
                    bSOCKET_S = TRUE;

                    // 非同期化
                    nAsync = WSAAsyncSelect(
                        s, hDlg, MY_MSG, FD_CLOSE | FD_READ);
                    if (nAsync != 0) {
                        MessageBox(hDlg, "非同期化失敗",
                            "Error", MB_OK | MB_ICONEXCLAMATION);
                        closesocket(s);
                        bSOCKET_S = FALSE;
                        return TRUE;
                    }

                    EnableWindow(hSendBtn, TRUE);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

int mystream(HWND hDlg, u_short uport)
{
    SOCKADDR_IN saddr;
    int nAsync;

    // リスンソケットをオープン
    listen_s = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_s < 0) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            MessageBox(hDlg, "ソケットオープンエラー",
                "Error", MB_OK | MB_ICONEXCLAMATION);
            return -1;
        }
    } else {
        MessageBox(NULL, "ソケットオープンしました",
            "socket成功", MB_OK);
    }
    bSOCKET_LISTEN = TRUE;

    // リスンソケットを非同期モードに
    nAsync = WSAAsyncSelect(listen_s, hDlg, MY_MSG, FD_ACCEPT);
    if (nAsync != 0) {
        MessageBox(hDlg, "非同期化失敗1", "Error", 
            MB_OK | MB_ICONEXCLAMATION);
        closesocket(listen_s);
        bSOCKET_LISTEN = FALSE;
        return -2;
    } 

    // SOCKADDR_IN構造体に必要事項をセット
    memset(&saddr, 0, sizeof(SOCKADDR_IN));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(uport);
    saddr.sin_addr.s_addr = INADDR_ANY;

    // リスンソケットに名前を付ける
    if (bind(listen_s, (SOCKADDR *)&saddr, sizeof(saddr)) ==
            SOCKET_ERROR) {
        MessageBox(hDlg, 
            "bind Error\n別なポート番号でもう一度試してください。",
            "Error", MB_OK);
        closesocket(listen_s);
        bSOCKET_LISTEN = FALSE;
        return -3;
    }

    // リスンソケットを接続待ち状態にする
    if (listen(listen_s, 0) == SOCKET_ERROR) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            MessageBox(hDlg, "listen Error", "Error", MB_OK);
            closesocket(listen_s);
            bSOCKET_LISTEN = FALSE;
            return -4;
        }
    } else {
        MessageBox(hDlg, "クライアントの接続待ちです", "OK", MB_OK);
    }

    return 0;
}

