// startup.c

#include <stdio.h>
#include <winsock2.h>

int main()
{
    WSADATA wsaData;
    int nRtn;

    // WinSockを初期化
    nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (nRtn != 0) {
        fprintf(stderr, "WSAStartup失敗です\n");
        return -1;
    }

    printf("wVersion = %d.%d\n", 
        LOBYTE(wsaData.wVersion),
        HIBYTE(wsaData.wVersion));
    printf("wHighVersion = %d.%d\n",
        LOBYTE(wsaData.wHighVersion),
        HIBYTE(wsaData.wHighVersion));
    printf("szDescription = %s\n", wsaData.szDescription);
    printf("szSystemStatus = %s\n", wsaData.szSystemStatus);
    printf("iMaxSockets= %d\n", wsaData.iMaxSockets);
    printf("iMaxUdpDg = %d\n", wsaData.iMaxUdpDg);
    printf("WSAStartup成功です\n");

    nRtn = WSACleanup();    // WinSockのリソースを解放
    if (nRtn == SOCKET_ERROR) {
        fprintf(stderr, "WSACleanup失敗です\n");
        return -2;
    }
    printf("WSACleanup成功です\n");
    return 0;
}
