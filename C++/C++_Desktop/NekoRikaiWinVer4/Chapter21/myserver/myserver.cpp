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

    printf("�g�p����|�[�g�ԍ�---");
    gets_s(szBuf);
    uport = atoi(szBuf);

    // �@ WinSock��������
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        printf("Error\n");
        WSACleanup();
        return -1;
    }

    // �A ���X���\�P�b�g���I�[�v��
    listen_s = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_s < 0) {
        printf( "�\�P�b�g�I�[�v���G���[\n" );
        WSACleanup();
        return -2;
    } else {
        printf("�\�P�b�g�I�[�v�����܂���\n");
    }

    // SOCKADDR_IN�\���̂̃����o���Z�b�g
    memset(&saddr, 0, sizeof(SOCKADDR_IN));  // �[���N���A
    saddr.sin_family = AF_INET;              // �A�h���X�t�@�~��
    saddr.sin_port = htons(uport);           // �|�[�g�ԍ�
    saddr.sin_addr.s_addr = INADDR_ANY;      // IP�A�h���X

    // �B ���X���\�P�b�g�ɖ��O��t����
    if (bind(listen_s, (struct sockaddr *)&saddr, sizeof(saddr)) ==
            SOCKET_ERROR) {
        printf("bind Error");
        closesocket(listen_s);
        WSACleanup();
        return -3;
    }  else {
        printf("bind�֐������ł�\n");
    }

    // �C ���X���\�P�b�g��ڑ��҂���Ԃɂ���
    if (listen(listen_s, 0) == SOCKET_ERROR) {
        printf("listen Error\n");
        closesocket(listen_s);
        WSACleanup();
        return -4; 
    } else {
        printf("listen�֐������ł�\naccept�֐��őҋ@���܂�\n");
    }

    // �D �N���C�A���g����̐ڑ����󂯓����
    fromlen = (int)sizeof(from);
    s = accept(listen_s, (SOCKADDR *)&from, &fromlen);
    if (s == INVALID_SOCKET) {
        printf("accept error");
        closesocket(listen_s);
        WSACleanup();
        return -5;
    } else {
        printf("%s���ڑ����Ă��܂���\n", inet_ntoa(from.sin_addr));
        printf("accept�֐������ł�\n��b�ɓ���܂�\n\n");
    }

    // ���X���\�P�b�g�͂����s�v
    closesocket(listen_s);

    while (1) {            // �G ���̃��[�v�ŁA�E�F�̏������J��Ԃ�
        printf("��M��҂��Ă��܂�...\n");

        // �E �N���C�A���g����̃f�[�^����M
        nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);

        if (nRcv == SOCKET_ERROR) {         // �G���[����
            printf("recv�G���[�ł�\n");
            break;
        }
        szBuf[nRcv] = '\0';                 // �����Ƀk��������t��
        if (strcmp(szBuf, "c_end") == 0) {  // "c_end"�Ȃ�I��
            printf("�N���C�A���g���ڑ���؂�܂���\n");
            break;
        }

        // �F �T�[�o����̕Ԏ����N���C�A���g�ɑ��M
        printf("��M---%s\n", szBuf);       // ��M�f�[�^���o��
        printf("���M---");
        gets_s(szBuf);                      // ���M�f�[�^���擾
        if (strcmp(szBuf, "s_end") == 0) {  // ���M�f�[�^��"s_end"�Ȃ�A
            send(s, szBuf,                  // ������N���C�A���g��
                (int)strlen(szBuf), 0);     // ���M���A
            break;                          // ���[�v�𔲂���
        }
        send(s, szBuf, (int)strlen(szBuf), 0);
    }

    shutdown(s, SD_BOTH);
    closesocket(s);          // �H �\�P�b�g���N���[�Y
    WSACleanup();            // �I WinSock�̃��\�[�X�����

    printf("�T�[�o�I��\n");
    _getch();

    return 0;
}
