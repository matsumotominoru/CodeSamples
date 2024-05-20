// sntpcl.cpp
#pragma warning(disable : 4996)

#define WIN32_LEAN_AND_MEAN
#define ID_MYTIMER 1000

#include <windows.h>
#include <winsock2.h>
#include <time.h>
#include "resource.h"

BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL MyConnect(HWND);

char szAppName[] = "猫でもわかる時刻合わせ";
u_int sport = 123, port;
char szServer[256];

// パケットを構造体に定義
typedef struct _tagPacket {
    int Control_Word;
    int root_delay;
    int root_dispersion;
    int reference_identifier;
    __int64 reference_timestamp;
    __int64 originate_timestamp;
    __int64 receive_timestamp;
    int transmit_timestamp_seconds;
    int transmit_timestamp_fractions;
} MYPACKET;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    // ダイアログボックスを生成
    DialogBox(hCurInst, "MYDLG", NULL, (DLGPROC)MyDlgProc);
    return 0;
}

// ダイアログボックスのプロシージャ
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    SYSTEMTIME st;
    char szTime[64];
    BOOL suc;

    switch (msg) {
        case WM_INITDIALOG:
            // サーバのポート番号（123）を表示
            SetDlgItemInt(hDlg, IDC_SPORT, sport, FALSE);
            // タイマーを作成
            if (SetTimer(hDlg, ID_MYTIMER, 200, NULL) == 0) {
                MessageBox(hDlg, "タイマーの作成失敗しました",
                    szAppName, MB_OK | MB_ICONEXCLAMATION);
                return TRUE;
            }
            return TRUE;
        case WM_TIMER:
            if (wp != ID_MYTIMER)
                return FALSE;
            // コンピュータの時刻を取得
            GetLocalTime(&st);
            // 日時を表す文字列を作成
            wsprintf(szTime, "%d/%02d/%02d %02d:%02d:%02d",
                st.wYear, st.wMonth, st.wDay,
                st.wHour, st.wMinute, st.wSecond);
            // 日時をダイアログボックスに表示
            SetWindowText(GetDlgItem(hDlg, IDC_MYTIME), szTime);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:        // 「OK」ボタン
                    // サーバ名、サーバのポート番号、受信ポート番号を取得
                    GetDlgItemText(hDlg, IDC_SERVER,
                        szServer, (int)sizeof(szServer));
                    sport = (u_int)GetDlgItemInt(hDlg,
                        IDC_SPORT, &suc, FALSE);
                    port = (u_int)GetDlgItemInt(hDlg,
                        IDC_PORT, &suc, FALSE);

                    if (strcmp(szServer, "") == 0 || port == 0) {
                        MessageBox(hDlg, 
                            "サーバまたはポート番号が指定されていません",
                            "Error", MB_OK | MB_ICONEXCLAMATION);
                        return TRUE;
                    }

                    MyConnect(hDlg);
                    return TRUE;
                case IDCANCEL:    // 「終了」ボタン
                    KillTimer(hDlg, ID_MYTIMER);    // タイマーを破棄
                    EndDialog(hDlg, IDCANCEL);      // ダイアログを破棄
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

BOOL MyConnect(HWND hDlg)
{
    WSADATA wsaData;
    SOCKADDR_IN myaddr, serveraddr;
    int nRtn;
    SOCKET s;
    HOSTENT *lpHostent;
    unsigned int addr;
    MYPACKET packet;
    int fromlen;
    time_t server_tm;
    struct tm *lpgtime;
    SYSTEMTIME st;

    // ① WinSockを初期化
    nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (nRtn != 0) {
        MessageBox(hDlg, 
            "Winsock初期化失敗です", 
            szAppName, 
            MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    // ② ソケットをオープン
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET) {
        MessageBox(hDlg, "socket失敗", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return FALSE;
    }

    // ③ SOCKADDR_IN構造体のメンバをセット
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    // ④ ソケットに名前を付ける
    nRtn = bind(s, (SOCKADDR *)&myaddr, sizeof(myaddr));
    if (nRtn != 0) {
        MessageBox(hDlg, "bind Error", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // ⑤ ホスト情報を取得
    lpHostent = gethostbyname(szServer);
    if (lpHostent == NULL) {
        addr = inet_addr(szServer);
        lpHostent = gethostbyaddr((char *)&addr, 4, AF_INET);
        if (lpHostent == NULL) {
            MessageBox(hDlg, "ホストを特定できません",
                szAppName, MB_OK | MB_ICONEXCLAMATION);
            closesocket(s);
            WSACleanup();
            return FALSE;
        }
    }

    // ⑥ SOCKADDR_IN構造体のメンバにサーバ情報をセット
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(sport);
    serveraddr.sin_addr.s_addr = 
        *((unsigned long *)lpHostent->h_addr);

    // ⑦ Control_Wordメンバに0x0B000000をセット
    memset(&packet, 0, sizeof(MYPACKET));
    packet.Control_Word = htonl(0x0B000000);

    // ⑧ パケットを送信
    nRtn = sendto(s, (const char *)&packet, sizeof(MYPACKET), 
        0, (SOCKADDR *)&serveraddr,sizeof(serveraddr));
    if (nRtn == SOCKET_ERROR) {
        MessageBox(hDlg, "パケット送信エラーです", szAppName,
            MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // ⑨ サーバからの返事を待機
    fromlen = sizeof(SOCKADDR_IN);
    nRtn = recvfrom(s, (char *)&packet, sizeof(MYPACKET), 
        0, (SOCKADDR *)&serveraddr, &fromlen);
    if (nRtn == SOCKET_ERROR) {
        MessageBox(hDlg, "受信エラーです", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // サーバから返された時刻を変数に保管
    server_tm =
        ntohl(packet.transmit_timestamp_seconds) - 2208988800;
    // サーバからの時刻をtm構造体に変換
    lpgtime = gmtime(&server_tm);

    // SYSTEMTIME構造体のメンバをセット
    st.wYear = lpgtime->tm_year + 1900;
    st.wMonth = lpgtime->tm_mon + 1;
    st.wDay = lpgtime->tm_mday;
    st.wHour = lpgtime->tm_hour;
    st.wMinute = lpgtime->tm_min;
    st.wSecond = lpgtime->tm_sec;
    st.wMilliseconds = 0;

    // コンピュータの時刻を、サーバから取得した時刻に合わせる
    if (SetSystemTime(&st) != 0) {
        MessageBox(hDlg, "システム時間をサーバ時間に合わせました",
            szAppName, MB_OK);
    }

    closesocket(s);          // ソケットをクローズ
    WSACleanup();            // WinSockのリソースを解放

    return TRUE;
}
