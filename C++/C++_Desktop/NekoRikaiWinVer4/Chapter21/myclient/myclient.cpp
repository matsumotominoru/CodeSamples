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

    // ���[�U�[�ɁA�|�[�g�ԍ�����͂��Ă��炤
    printf("�g�p����|�[�g�ԍ�---");
    gets_s(szBuf);
    uport = atoi(szBuf);

    // ���[�U�[�ɁA�T�[�o����͂��Ă��炤
    printf("�T�[�o---");
    gets_s(szServer);

    // �@ WinSock��������
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        printf("WSAStartup�֐��̎��s�ł�\n");
        WSACleanup();
        _getch();
        return -1;
    }

    // �A �\�P�b�g���I�[�v��
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("�\�P�b�g�I�[�v���G���[\n");
        WSACleanup();
        _getch();
        return -2;
    }

    // �z�X�g�����擾
    lpHost = gethostbyname(szServer);  // ���[�U�[�̓z�X�g������͂����Ɖ���
    if (lpHost == NULL) {              // ���s������
        addr = inet_addr(szServer);    // �A�h���X����͂����ƌ��Ȃ�
        lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
    }
    if (lpHost == NULL) {
        printf("�G���[�ł�\n");
        closesocket(s);
        WSACleanup();
        _getch();
        return -3;
    }

    // SOCKADDR_IN�\���̂̃����o���Z�b�g
    memset(&saddr, 0, sizeof(SOCKADDR_IN));
    saddr.sin_family = lpHost->h_addrtype;
    saddr.sin_port = htons(uport);
    saddr.sin_addr.s_addr = *((u_long *)lpHost->h_addr);

    // �B �N���C�A���g�\�P�b�g���T�[�o�\�P�b�g�ɐڑ�
    if (connect(s, (SOCKADDR *)&saddr, sizeof(saddr)) ==
            SOCKET_ERROR) {
        printf("connect Error\n");
        closesocket(s);
        WSACleanup();
        return -4;
    }  else {
        printf("connect OK\n");
    }

    while (1) {       // �E ���̃��[�v�ŁA�C�D�̏������J��Ԃ�
        // �C �f�[�^���T�[�o�ɑ��M
        printf("���M---");
        gets_s(szBuf);                      // ���M�f�[�^���擾
        if (strcmp(szBuf, "c_end") == 0) {  // ���M�f�[�^��"c_end"�Ȃ�A
            send(s, szBuf,                  // ������T�[�o�ɑ��M���A
                (int)strlen(szBuf), 0);
            break;                          // ���[�v�𔲂���
        }
        send(s, szBuf, (int)strlen(szBuf), 0);
        printf("�T�[�o����̑��M��҂��Ă��܂�...\n");

        // �D �T�[�o����̃f�[�^����M
        nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);

        if (nRcv == SOCKET_ERROR) {         // �G���[����
            printf("recv Error\n");
            break;
        }
        szBuf[nRcv] = '\0';                 // �����Ƀk��������t��
        if (strcmp(szBuf, "s_end") == 0) {  // "s_end"�Ȃ�I��
            printf("�T�[�o���ڑ���؂�܂���\n");
            break;
        }
        printf("��M---%s\n", szBuf);       // ��M�f�[�^���o��
    }

    shutdown(s, SD_BOTH);
    closesocket(s);          // �F �\�P�b�g���N���[�Y
    WSACleanup();            // �G WinSock�̃��\�[�X�����
    printf("�I�����܂�\n");
    _getch();
    return 0;
}
