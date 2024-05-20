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

    // ���[�U�[�ɁA�|�[�g�ԍ�����͂��Ă��炤
    printf("�|�[�g---");
    gets_s(szBuf);
    port = atoi(szBuf);
    // ���[�U�[�ɁA�T�[�o����͂��Ă��炤
    printf("�T�[�o---");
    gets_s(szServer);

    // �@ WinSock��������
    nRtn = WSAStartup(MAKEWORD(1,1), &wsaData);
    if (nRtn != 0) {
        perror("WSAStartup�G���[�ł�\n");
        return -1;
    }

    // �A �\�P�b�g���I�[�v���iSOCK_DGRAM���w��j
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("�\�P�b�g�G���[�ł�\n");
        WSACleanup();
        return -2;
    }

    // �T�[�o�̃z�X�g�����擾
    lpHostEnt = gethostbyname(szServer);
    if (lpHostEnt == NULL) {
        addr = inet_addr(szServer);
        lpHostEnt = gethostbyaddr((char *)&addr, 4, AF_INET);
        if (lpHostEnt == NULL) {
            perror("�T�[�o�����ł��܂���\n");
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
        printf("���M---");
        gets_s(szBuf);

        // �B �f�[�^�𑗐M
        nRtn = sendto(s, szBuf, (int)strlen(szBuf) + 1, 0, 
            (LPSOCKADDR)&addrin, sizeof(addrin));

        if (nRtn != (int)strlen(szBuf) + 1) {
            perror("���M�G���[�ł�\n");
            closesocket(s);
            WSACleanup();
            return -4;
        }

        if (strcmp(szBuf, "cend") == 0) {
            printf("�I�����܂�\n");
            _getch();
            break;
        }
    }

    closesocket(s);          // �C �\�P�b�g���N���[�Y
    WSACleanup();            // �D WinSock�̃��\�[�X�����
    return 0;
}
