// udpclient.cpp

#include <stdio.h>
#include <winsock2.h>
#include <conio.h>

int main()
{
    WSADATA wsaData;
    SOCKET s;
    SOCKADDR_IN addrin;
    HOSTENT *lpHostEnt;
    unsigned int addr;
    int nRtn, nNo = 5;
    u_short port;
    char szBuf[1024], szServer[64];

    // ユーザーに、ポート番号を入力してもらう
    printf("ポート---");
    gets_s(szBuf);
    port = atoi(szBuf);
    // ユーザーに、サーバを入力してもらう
    printf("サーバ---");
    gets_s(szServer);

    // ① WinSockを初期化
    nRtn = WSAStartup(MAKEWORD(1,1), &wsaData);
    if (nRtn != 0) {
        perror("WSAStartupエラーです\n");
        return -1;
    }

    // ② ソケットをオープン（SOCK_DGRAMを指定）
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("ソケットエラーです\n");
        WSACleanup();
        return -2;
    }

    // サーバのホスト情報を取得
    lpHostEnt = gethostbyname(szServer);
    if (lpHostEnt == NULL) {
        addr = inet_addr(szServer);
        lpHostEnt = gethostbyaddr((char *)&addr, 4, AF_INET);
        if (lpHostEnt == NULL) {
            perror("サーバを特定できません\n");
            _getch();
            return -3;
        }
    }

    memset(&addrin, 0, sizeof(addrin));
    memcpy(&(addrin.sin_addr),
        lpHostEnt->h_addr_list[0],
        lpHostEnt->h_length);
    addrin.sin_port = htons(port);
    addrin.sin_family = AF_INET;
    // addrin.sin_addr.s_addr =
    //     *((unsigned long *)lpHostEnt->h_addr);

    while(1) {
        printf("送信---");
        gets_s(szBuf);

        // ③ データを送信
        nRtn = sendto(s, szBuf, (int)strlen(szBuf) + 1, 0, 
            (LPSOCKADDR)&addrin, sizeof(addrin));

        if (nRtn != (int)strlen(szBuf) + 1) {
            perror("送信エラーです\n");
            closesocket(s);
            WSACleanup();
            return -4;
        }

        if (strcmp(szBuf, "cend") == 0) {
            printf("終了します\n");
            _getch();
            break;
        }
    }

    closesocket(s);          // ④ ソケットをクローズ
    WSACleanup();            // ⑤ WinSockのリソースを解放
    return 0;
}
