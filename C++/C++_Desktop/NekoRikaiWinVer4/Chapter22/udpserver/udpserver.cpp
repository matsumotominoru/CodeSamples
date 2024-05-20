// udpserver.cpp

#include <stdio.h>
#include <winsock.h>

int main()
{
    WSADATA wsaData;
    SOCKET s;
    SOCKADDR_IN addrin;
    SOCKADDR_IN from;
    int fromlen;
    int nRtn;
    u_short port;
    char szBuf[256];

    printf("ポート---");
    gets_s(szBuf);

    port = atoi(szBuf);

    // ① WinSockを初期化
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        perror("WSAStartup Error\n");
        return -1;
    }

    // ② ソケットをオープン（SOCK_DGRAMを指定）
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket失敗\n");
        WSACleanup();
        return -2;
    }

    // SOCKADDR_IN構造体のメンバをセット
    memset(&addrin, 0, sizeof(addrin));
    addrin.sin_port = htons(port);
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = htonl(INADDR_ANY);

    // ③ ソケットに名前を付ける
    nRtn = bind(s, (LPSOCKADDR)&addrin, (int)sizeof(addrin));
    if (nRtn == SOCKET_ERROR) {
        perror("bindエラーです\n");
        closesocket(s);
        WSACleanup();
        return -3;
    }

    while (1) {
        fromlen = (int)sizeof(from);

        // ④ クライアントからの通信を待つ
        nRtn = recvfrom(s,           // ソケット
            szBuf,                   // バッファ
            (int)sizeof(szBuf) - 1,  // バッファのサイズ
            0,                       // 呼び出し方法のフラグ
            (SOCKADDR *)&from,       // 送信元の情報
            &fromlen);               // fromのサイズ

        if (nRtn == SOCKET_ERROR) {
            perror("recvformエラーです\n");
            closesocket(s);
            WSACleanup();
            return -4;
        }
        szBuf[nRtn] = '\0';                 // 末尾にヌル文字を付加

        if (strcmp(szBuf, "c_end") == 0) {  // "c_end"なら終了
            printf("サーバーを終了します\n");
            break;
        }

        // 送信元のネットワークアドレスをドット付き標準フォーマットで表示
        printf("%s>%s\n", inet_ntoa(from.sin_addr), szBuf);
    }

    closesocket(s);          // ⑤ ソケットをクローズ
    WSACleanup();            // ⑥ WinSockのリソースを解放
    printf("終了です\n");

    return 0;
}
