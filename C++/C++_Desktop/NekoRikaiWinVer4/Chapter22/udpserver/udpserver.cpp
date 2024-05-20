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

    printf("�|�[�g---");
    gets_s(szBuf);

    port = atoi(szBuf);

    // �@ WinSock��������
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        perror("WSAStartup Error\n");
        return -1;
    }

    // �A �\�P�b�g���I�[�v���iSOCK_DGRAM���w��j
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket���s\n");
        WSACleanup();
        return -2;
    }

    // SOCKADDR_IN�\���̂̃����o���Z�b�g
    memset(&addrin, 0, sizeof(addrin));
    addrin.sin_port = htons(port);
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = htonl(INADDR_ANY);

    // �B �\�P�b�g�ɖ��O��t����
    nRtn = bind(s, (LPSOCKADDR)&addrin, (int)sizeof(addrin));
    if (nRtn == SOCKET_ERROR) {
        perror("bind�G���[�ł�\n");
        closesocket(s);
        WSACleanup();
        return -3;
    }

    while (1) {
        fromlen = (int)sizeof(from);

        // �C �N���C�A���g����̒ʐM��҂�
        nRtn = recvfrom(s,           // �\�P�b�g
            szBuf,                   // �o�b�t�@
            (int)sizeof(szBuf) - 1,  // �o�b�t�@�̃T�C�Y
            0,                       // �Ăяo�����@�̃t���O
            (SOCKADDR *)&from,       // ���M���̏��
            &fromlen);               // from�̃T�C�Y

        if (nRtn == SOCKET_ERROR) {
            perror("recvform�G���[�ł�\n");
            closesocket(s);
            WSACleanup();
            return -4;
        }
        szBuf[nRtn] = '\0';                 // �����Ƀk��������t��

        if (strcmp(szBuf, "c_end") == 0) {  // "c_end"�Ȃ�I��
            printf("�T�[�o�[���I�����܂�\n");
            break;
        }

        // ���M���̃l�b�g���[�N�A�h���X���h�b�g�t���W���t�H�[�}�b�g�ŕ\��
        printf("%s>%s\n", inet_ntoa(from.sin_addr), szBuf);
    }

    closesocket(s);          // �D �\�P�b�g���N���[�Y
    WSACleanup();            // �E WinSock�̃��\�[�X�����
    printf("�I���ł�\n");

    return 0;
}
