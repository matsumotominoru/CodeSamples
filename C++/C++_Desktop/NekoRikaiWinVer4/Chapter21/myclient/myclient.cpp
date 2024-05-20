// myclient.cpp

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    SOCKET s;
    WSADATA wsaData;
    SOCKADDR_IN saddr;
    char szBuf[1024];
    char szServer[1024];
    HOSTENT *lpHost;
    unsigned int addr;

    int nRcv;
    u_short uport;

    // ユーザーに、ポート番号を入力してもらう
    printf("使用するポート番号---");
    gets_s(szBuf);
    uport = atoi(szBuf);

    // ユーザーに、サーバを入力してもらう
    printf("サーバ---");
    gets_s(szServer);

    // ① WinSockを初期化
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        printf("WSAStartup関数の失敗です\n");
        WSACleanup();
        _getch();
        return -1;
    }

    // ② ソケットをオープン
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("ソケットオープンエラー\n");
        WSACleanup();
        _getch();
        return -2;
    }

    // ホスト情報を取得
    lpHost = gethostbyname(szServer);  // ユーザーはホスト名を入力したと仮定
    if (lpHost == NULL) {              // 失敗したら
        addr = inet_addr(szServer);    // アドレスを入力したと見なす
        lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
    }
    if (lpHost == NULL) {
        printf("エラーです\n");
        closesocket(s);
        WSACleanup();
        _getch();
        return -3;
    }

    // SOCKADDR_IN構造体のメンバをセット
    memset(&saddr, 0, sizeof(SOCKADDR_IN));
    saddr.sin_family = lpHost->h_addrtype;
    saddr.sin_port = htons(uport);
    saddr.sin_addr.s_addr = *((u_long *)lpHost->h_addr);

    // ③ クライアントソケットをサーバソケットに接続
    if (connect(s, (SOCKADDR *)&saddr, sizeof(saddr)) ==
            SOCKET_ERROR) {
        printf("connect Error\n");
        closesocket(s);
        WSACleanup();
        return -4;
    }  else {
        printf("connect OK\n");
    }

    while (1) {       // ⑥ このループで、④⑤の処理を繰り返す
        // ④ データをサーバに送信
        printf("送信---");
        gets_s(szBuf);                      // 送信データを取得
        if (strcmp(szBuf, "c_end") == 0) {  // 送信データが"c_end"なら、
            send(s, szBuf,                  // それをサーバに送信し、
                (int)strlen(szBuf), 0);
            break;                          // ループを抜ける
        }
        send(s, szBuf, (int)strlen(szBuf), 0);
        printf("サーバからの送信を待っています...\n");

        // ⑤ サーバからのデータを受信
        nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);

        if (nRcv == SOCKET_ERROR) {         // エラー処理
            printf("recv Error\n");
            break;
        }
        szBuf[nRcv] = '\0';                 // 末尾にヌル文字を付加
        if (strcmp(szBuf, "s_end") == 0) {  // "s_end"なら終了
            printf("サーバが接続を切りました\n");
            break;
        }
        printf("受信---%s\n", szBuf);       // 受信データを出力
    }

    shutdown(s, SD_BOTH);
    closesocket(s);          // ⑦ ソケットをクローズ
    WSACleanup();            // ⑧ WinSockのリソースを解放
    printf("終了します\n");
    _getch();
    return 0;
}
