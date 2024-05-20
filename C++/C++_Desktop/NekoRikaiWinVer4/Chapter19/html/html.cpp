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
        // WinSock��������
        if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
            perror("WSAStartup�G���[�ł�\n");
            return -1;
        }

        // �T�[�o���A�|�[�g�ԍ��A�t�@�C�������擾
        printf("Web�T�[�o��----");
        gets_s(szServer);
        printf("�|�[�g�ԍ�----");
        gets_s(szPort);
        if (strcmp(szPort, "") == 0)
            strcpy_s(szPort, "80");
        port = (u_short)atoi(szPort);
        printf("�t�@�C����----");
        gets_s(szURL);
        if (strcmp(szURL, "") == 0)
            strcpy_s(szURL, "/");

        // �\�P�b�g���I�[�v��
        s = socket(PF_INET, SOCK_STREAM, 0);
        if (s == INVALID_SOCKET) {
            perror("�\�P�b�g���I�[�v���ł��܂���\n");
            WSACleanup();
            return -2;
        }

        // �z�X�g������z�X�g�����擾
        lpHost = gethostbyname(szServer);
        if (lpHost == NULL) {
            // �A�h���X��\��������𐔒l�\���ɕϊ�
            addr = inet_addr(szServer);
            // �l�b�g���[�N�A�h���X����z�X�g�����擾
            lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
            if (lpHost == NULL) {
                wsprintf(szStr, "%s��������܂���\n", szServer);
                perror(szStr);
                WSACleanup();
                return -3;
            }
        }

        // SOCKADDR_IN�\���̂ɕK�v�������Z�b�g
        memset(&sockadd, 0, sizeof(sockadd));
        sockadd.sin_family = AF_INET;
        sockadd.sin_port = htons(port);
        sockadd.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

        // �\�P�b�g�ɐڑ�
        if (connect(s, (PSOCKADDR)&sockadd, sizeof(sockadd)) != 0) {
            perror("�T�[�o�\�P�b�g�ɐڑ����s\n");
            closesocket(s);
            WSACleanup();
            return -4;
        }

        // GET���N�G�X�g�𑗐M
        wsprintf(szStr, "GET %s HTTP/1.0\r\n\r\n", szURL);
        nRtn = send(s, szStr, (int)strlen(szStr), 0);

        while(1) {
            // ��M�p�o�b�t�@�iszStrRcv�j���[���N���A
            memset(szStrRcv, '\0', sizeof(szStrRcv));
            // �f�[�^����M
            nRtn = recv(s, szStrRcv, (int)sizeof(szStrRcv) - 1, 0);
            // ��M�����f�[�^��W���o�͂ɏ����o��
            printf("%s", szStrRcv);

            if (nRtn == 0)
                break;
            if (nRtn == SOCKET_ERROR) {
                perror("recv�G���[�ł�\n");
                break;
            }
        }

        if (shutdown(s, SD_BOTH) != 0) {  // �V���b�g�_�E��
            perror("�V���b�g�_�E���Ɏ��s���܂���\n");
        }
        closesocket(s);                   // �\�P�b�g���N���[�Y
        WSACleanup();                     // WinSock�̃��\�[�X�����

        printf("\n������x���s���܂���(Y/N)----");
        gets_s(szYN);
        if (strcmp(szYN, "n") == 0 || strcmp(szYN, "N") == 0)
            break;
    }

    return 0;
}
