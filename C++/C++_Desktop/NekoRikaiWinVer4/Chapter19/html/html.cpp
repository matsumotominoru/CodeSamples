// html.cpp

#include <stdio.h>
#include <winsock2.h>

int main()
{
    WSADATA wsaData;
    LPHOSTENT lpHost;
    SOCKET s;
    int nRtn;
    SOCKADDR_IN sockadd;
    char szServer[256], szURL[256], szStrRcv[1024], szPort[8];
    char szStr[256], szYN[4];
    u_short port;
    unsigned int addr;

    while (1) {
        // WinSockを初期化
        if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
            perror("WSAStartupエラーです\n");
            return -1;
        }

        // サーバ名、ポート番号、ファイル名を取得
        printf("Webサーバ名----");
        gets_s(szServer);
        printf("ポート番号----");
        gets_s(szPort);
        if (strcmp(szPort, "") == 0)
            strcpy_s(szPort, "80");
        port = (u_short)atoi(szPort);
        printf("ファイル名----");
        gets_s(szURL);
        if (strcmp(szURL, "") == 0)
            strcpy_s(szURL, "/");

        // ソケットをオープン
        s = socket(PF_INET, SOCK_STREAM, 0);
        if (s == INVALID_SOCKET) {
            perror("ソケットをオープンできません\n");
            WSACleanup();
            return -2;
        }

        // ホスト名からホスト情報を取得
        lpHost = gethostbyname(szServer);
        if (lpHost == NULL) {
            // アドレスを表す文字列を数値表現に変換
            addr = inet_addr(szServer);
            // ネットワークアドレスからホスト情報を取得
            lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
            if (lpHost == NULL) {
                wsprintf(szStr, "%sが見つかりません\n", szServer);
                perror(szStr);
                WSACleanup();
                return -3;
            }
        }

        // SOCKADDR_IN構造体に必要事項をセット
        memset(&sockadd, 0, sizeof(sockadd));
        sockadd.sin_family = AF_INET;
        sockadd.sin_port = htons(port);
        sockadd.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

        // ソケットに接続
        if (connect(s, (PSOCKADDR)&sockadd, sizeof(sockadd)) != 0) {
            perror("サーバソケットに接続失敗\n");
            closesocket(s);
            WSACleanup();
            return -4;
        }

        // GETリクエストを送信
        wsprintf(szStr, "GET %s HTTP/1.0\r\n\r\n", szURL);
        nRtn = send(s, szStr, (int)strlen(szStr), 0);

        while(1) {
            // 受信用バッファ（szStrRcv）をゼロクリア
            memset(szStrRcv, '\0', sizeof(szStrRcv));
            // データを受信
            nRtn = recv(s, szStrRcv, (int)sizeof(szStrRcv) - 1, 0);
            // 受信したデータを標準出力に書き出す
            printf("%s", szStrRcv);

            if (nRtn == 0)
                break;
            if (nRtn == SOCKET_ERROR) {
                perror("recvエラーです\n");
                break;
            }
        }

        if (shutdown(s, SD_BOTH) != 0) {  // シャットダウン
            perror("シャットダウンに失敗しました\n");
        }
        closesocket(s);                   // ソケットをクローズ
        WSACleanup();                     // WinSockのリソースを解放

        printf("\nもう一度実行しますか(Y/N)----");
        gets_s(szYN);
        if (strcmp(szYN, "n") == 0 || strcmp(szYN, "N") == 0)
            break;
    }

    return 0;
}
