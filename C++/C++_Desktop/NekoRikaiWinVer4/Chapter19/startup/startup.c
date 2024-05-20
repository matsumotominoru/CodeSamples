// startup.c

#include <stdio.h>
#include <winsock2.h>

int main()
{
    WSADATA wsaData;
    int nRtn;

    // WinSock��������
    nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (nRtn != 0) {
        fprintf(stderr, "WSAStartup���s�ł�\n");
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
    printf("WSAStartup�����ł�\n");

    nRtn = WSACleanup();    // WinSock�̃��\�[�X�����
    if (nRtn == SOCKET_ERROR) {
        fprintf(stderr, "WSACleanup���s�ł�\n");
        return -2;
    }
    printf("WSACleanup�����ł�\n");
    return 0;
}
