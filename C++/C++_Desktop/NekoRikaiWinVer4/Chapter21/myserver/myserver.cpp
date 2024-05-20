// myserver.cpp

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    SOCKET listen_s, s;
    WSADATA wsaData;
    SOCKADDR_IN saddr, from;
    char szBuf[1024];
    int fromlen, nRcv;
    u_short uport;

    printf("使用するポート番号---");
    gets_s(szBuf);
    uport = atoi(szBuf);

    // ① WinSockを初期化
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        printf("Error\n");
        WSACleanup();
        return -1;
    }

    // ② リスンソケットをオープン
    listen_s = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_s < 0) {
        printf( "ソケットオープンエラー\n" );
        WSACleanup();
        return -2;
    } else {
        printf("ソケットオープンしました\n");
    }

    // SOCKADDR_IN構造体のメンバをセット
    memset(&saddr, 0, sizeof(SOCKADDR_IN));  // ゼロクリア
    saddr.sin_family = AF_INET;              // アドレスファミリ
    saddr.sin_port = htons(uport);           // ポート番号
    saddr.sin_addr.s_addr = INADDR_ANY;      // IPアドレス

    // ③ リスンソケットに名前を付ける
    if (bind(listen_s, (struct sockaddr *)&saddr, sizeof(saddr)) ==
            SOCKET_ERROR) {
        printf("bind Error");
        closesocket(listen_s);
        WSACleanup();
        return -3;
    }  else {
        printf("bind関数成功です\n");
    }

    // ④ リスンソケットを接続待ち状態にする
    if (listen(listen_s, 0) == SOCKET_ERROR) {
        printf("listen Error\n");
        closesocket(listen_s);
        WSACleanup();
        return -4; 
    } else {
        printf("listen関数成功です\naccept関数で待機します\n");
    }

    // ⑤ クライアントからの接続を受け入れる
    fromlen = (int)sizeof(from);
    s = accept(listen_s, (SOCKADDR *)&from, &fromlen);
    if (s == INVALID_SOCKET) {
        printf("accept error");
        closesocket(listen_s);
        WSACleanup();
        return -5;
    } else {
        printf("%sが接続してきました\n", inet_ntoa(from.sin_addr));
        printf("accept関数成功です\n会話に入ります\n\n");
    }

    // リスンソケットはもう不要
    closesocket(listen_s);

    while (1) {            // ⑧ このループで、⑥⑦の処理を繰り返す
        printf("受信を待っています...\n");

        // ⑥ クライアントからのデータを受信
        nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);

        if (nRcv == SOCKET_ERROR) {         // エラー処理
            printf("recvエラーです\n");
            break;
        }
        szBuf[nRcv] = '\0';                 // 末尾にヌル文字を付加
        if (strcmp(szBuf, "c_end") == 0) {  // "c_end"なら終了
            printf("クライアントが接続を切りました\n");
            break;
        }

        // ⑦ サーバからの返事をクライアントに送信
        printf("受信---%s\n", szBuf);       // 受信データを出力
        printf("送信---");
        gets_s(szBuf);                      // 送信データを取得
        if (strcmp(szBuf, "s_end") == 0) {  // 送信データが"s_end"なら、
            send(s, szBuf,                  // それをクライアントに
                (int)strlen(szBuf), 0);     // 送信し、
            break;                          // ループを抜ける
        }
        send(s, szBuf, (int)strlen(szBuf), 0);
    }

    shutdown(s, SD_BOTH);
    closesocket(s);          // ⑨ ソケットをクローズ
    WSACleanup();            // ⑩ WinSockのリソースを解放

    printf("サーバ終了\n");
    _getch();

    return 0;
}
