// mymail02.cpp

#define WIN32_LEAN_AND_MEAN
#define MYTIMER 100
#define MYLOG "mylog.log"

#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include <Mmsystem.h>
#include <stdlib.h>
#include "resource.h"

BOOL CALLBACK MainProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
int MyMailCheck(HWND);
BOOL WriteMyLog(char *);

char szClassName[] = "mymail02";    // ウィンドウクラス
char szPopName[64], szID[32], szPass[32], szPort[8], szMin[8];
u_short port = 110;
int nMin = 3;
HINSTANCE hInst;
HWND hStart, hStop, hOption, hOK;
BOOL bConnect = FALSE;              // 接続中かどうか

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    hInst = hCurInst;
    DialogBox(hCurInst, "MAINDLG", NULL, (DLGPROC)MainProc);
    return 0;
}

BOOL CALLBACK MainProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static BOOL bTimer = FALSE;   // タイマーが動作しているかどうか

    switch (msg) {
        case WM_INITDIALOG:
            // ボタンのウィンドウハンドルを取得
            hStart = GetDlgItem(hDlg, IDC_START);
            hStop = GetDlgItem(hDlg, IDC_STOP);
            hOption = GetDlgItem(hDlg, IDC_OPTION);
            hOK = GetDlgItem(hDlg, IDOK);
            // 「スタート」「チェック中止」ボタンを使用不可に
            EnableWindow(hStart, FALSE);
            EnableWindow(hStop, FALSE);
            // ログファイルに記録
            WriteMyLog("プログラム開始\r\n");
            return TRUE;
        case WM_TIMER:
            if (wp != MYTIMER) 
                return FALSE;
            // メールがサーバにあるかどうかをチェック
            if (MyMailCheck(hDlg) != 0) {
                MessageBox(hDlg, "異常が発生したので終了します",
                    "Error", MB_OK | MB_ICONEXCLAMATION);
                KillTimer(hDlg, MYTIMER);
                EndDialog(hDlg, IDCANCEL);
            }
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:                // 「終了」ボタン
                case IDCANCEL:            // 「閉じる」ボタン
                    if (bConnect) {       // サーバに接続中か？
                        MessageBox(hDlg,
                            "チェックを中止してから終了してください",
                            "警告", MB_OK);
                        return FALSE;
                    }
                    if (bTimer) {         // タイマーが動作中？
                        if (KillTimer(hDlg, MYTIMER) == 0)
                            MessageBox(hDlg, "KillTimer失敗",
                                "Error", MB_OK);
                    }
                    // ログファイルに記録
                    WriteMyLog("プログラム終了\r\n");

                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDC_START:           // 「スタート」ボタン
                    SetTimer(hDlg, MYTIMER, 1000 * 60 * nMin, NULL);
                    bTimer = TRUE;

                    // ボタンの使用可能・不可を設定
                    EnableWindow(hStart, FALSE);
                    EnableWindow(hStop, TRUE);
                    EnableWindow(hOption, FALSE);
                    EnableWindow(hOK, FALSE);

                    // ログファイルに記録
                    WriteMyLog("メッセージチェック開始\r\n");

                    // メールをチェック
                    if (MyMailCheck(hDlg) != 0) {
                        MessageBox(hDlg, "異常が発生したので終了します",
                            "Error", MB_OK | MB_ICONEXCLAMATION);
                        KillTimer(hDlg, MYTIMER);
                        EndDialog(hDlg, IDCANCEL);
                        return FALSE;
                    }
                    return TRUE;
                case IDC_STOP:            // 「チェック中止」ボタン
                    if (bConnect) {       // サーバに接続中か？
                        MessageBox(hDlg, 
                            "接続中です\n後からやり直してください",
                            "接続中", MB_OK | MB_ICONEXCLAMATION);
                        return FALSE;
                    }
                    KillTimer(hDlg, MYTIMER);
                    bTimer = FALSE;

                    // ボタンの使用可能・不可を設定
                    EnableWindow(hStop, FALSE);
                    EnableWindow(hStart, TRUE);
                    EnableWindow(hOption, TRUE);
                    EnableWindow(hOK, TRUE);
                    return TRUE;
                case IDC_OPTION:          // 「オプション」ボタン
                    DialogBox(hInst, "MYDLG", hDlg, (DLGPROC)MyDlgProc);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

int MyMailCheck(HWND hWnd)
{
    WSADATA wsaData;
    SOCKET s;
    char szBuf[1024];
    char szList[1024];
    LPHOSTENT lpHost;
    SOCKADDR_IN sockaddr;
    HWND hInfo;

    memset(szList, '\0', sizeof(szList));

    hInfo = GetDlgItem(hWnd, IDC_INFO);

    // WinSockを初期化
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        MessageBox(hWnd, "WSAStartup関数失敗です",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        WriteMyLog("WSAStartup関数失敗");
        return -1;
    }

    bConnect = TRUE;

    // ソケットをオープンする
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        MessageBox(hWnd, "ソケット作成失敗です",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        WriteMyLog("WSAStartup関数失敗");
        WSACleanup();
        bConnect = FALSE;
        return -2;
    }

    // ホスト情報を取得
    lpHost = gethostbyname(szPopName);
    if (lpHost == NULL) {
        MessageBox(hWnd, "ホスト情報取得失敗しました",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        bConnect = FALSE;
        return -3;
    }

    // SOCKADDR_IN構造体に必要事項をセット
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

    // ソケットに接続
    if (connect(s, (PSOCKADDR)&sockaddr, sizeof(sockaddr)) != 0) {
        MessageBox(hWnd, "ソケットに接続できませんでした",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        bConnect = FALSE;
        return -4;
    }

    // データを受信
    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd, "エラーが発生しました", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        bConnect = FALSE;
        return -5;
    }
    WriteMyLog(szBuf);

    // ユーザーIDを送信
    wsprintf(szBuf, "USER %s\r\n", szID);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    WriteMyLog(szBuf);

    // パスワードを送信
    wsprintf(szBuf, "PASS %s\r\n", szPass);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd, "パスワードが不正です", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        bConnect = FALSE;
        return -6;
    }

    WriteMyLog(szBuf);
    Edit_SetText(hInfo, "サーバチェック中!");

    // LISTコマンドを送信
    strcpy_s(szBuf, "LIST\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);

    while (1) {  // ".\r\n"を受信するまで、繰り返しrecv関数を呼び出す
        memset(szBuf, '\0', sizeof(szBuf));
        recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
        strcat_s(szList, szBuf);
        WriteMyLog(szBuf);
        if (strstr(szBuf, ".\r\n"))
            break;
    }

    if (strstr(szList, "1")) {
        Edit_SetText(hInfo, "メッセージが届いています");
    } else {
        Edit_SetText(hInfo, "メッセージはありません");
    }
    PlaySound("test.wav", NULL, SND_SYNC);    // 音を鳴らす

    // QUITコマンドを送信
    strcpy_s(szBuf, "QUIT\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    WriteMyLog(szBuf);

    closesocket(s);
    WSACleanup();
    bConnect = FALSE;
    return 0;
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hPopName, hID, hPass, hPort, hMin;

    switch (msg) {
        case WM_INITDIALOG:
            // コントロールのハンドルを取得
            hPopName = GetDlgItem(hDlg, IDC_POP3);
            hID = GetDlgItem(hDlg, IDC_ID);
            hPass = GetDlgItem(hDlg, IDC_PASS);
            hPort = GetDlgItem(hDlg, IDC_PORT);
            hMin = GetDlgItem(hDlg, IDC_MIN);
            // グローバル変数の値をコントロールに表示
            Edit_SetText(hPopName, szPopName);
            Edit_SetText(hID, szID);
            Edit_SetText(hPass, szPass);
            wsprintf(szPort, "%d", port);
            Edit_SetText(hPort, szPort);
            wsprintf(szMin, "%d", nMin);
            Edit_SetText(hMin, szMin);
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
                    Edit_GetText(hMin, szMin, sizeof(szMin));
                    nMin = atoi(szMin);
                    // 記入漏れがないかどうかチェック
                    if (strcmp(szPopName, "") == 0 ||
                        strcmp(szID, "") == 0 ||
                        strcmp(szPass, "") == 0 ||
                        strcmp(szPort, "") == 0 ||
                        strcmp(szMin, "0") == 0 ||
                        strcmp(szMin, "") == 0) {
                            MessageBox(hDlg, 
                                "設定していない項目があります。",
                                "Error", MB_OK | MB_ICONEXCLAMATION);
                            return FALSE;
                        } else {
                            // 「スタート」ボタンを使用可能にする
                            EnableWindow(hStart, TRUE);
                        }
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

BOOL WriteMyLog(char *lpszBuf)
{
    HANDLE hFile;
    DWORD dwWritten;
    SYSTEMTIME st;
    char szBuf[256];

    hFile = CreateFile(                     // ファイルを開く
        MYLOG, GENERIC_WRITE, 0, 0, 
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    SetFilePointer(hFile, 0, 0, FILE_END);  // ファイルの末尾へ移動
    GetLocalTime(&st);                      // 現在の日時を取得
    wsprintf(szBuf, "[%d/%02d/%02d %02d:%02d:%02d]\r\n",
        st.wYear, st.wMonth, st.wDay,
        st.wHour, st.wMinute, st.wSecond);
    WriteFile(                              // 日時を書き込む
        hFile, szBuf, (DWORD)strlen(szBuf), &dwWritten, NULL);
    WriteFile(                              // 引数の文字列を書き込む
        hFile, lpszBuf, (DWORD)strlen(lpszBuf), &dwWritten, NULL);
    CloseHandle(hFile);
    return TRUE;
}
