// sntpcl.cpp
#pragma warning(disable : 4996)

#define WIN32_LEAN_AND_MEAN
#define ID_MYTIMER 1000

#include <windows.h>
#include <winsock2.h>
#include <time.h>
#include "resource.h"

BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL MyConnect(HWND);

char szAppName[] = "�L�ł��킩�鎞�����킹";
u_int sport = 123, port;
char szServer[256];

// �p�P�b�g���\���̂ɒ�`
typedef struct _tagPacket {
    int Control_Word;
    int root_delay;
    int root_dispersion;
    int reference_identifier;
    __int64 reference_timestamp;
    __int64 originate_timestamp;
    __int64 receive_timestamp;
    int transmit_timestamp_seconds;
    int transmit_timestamp_fractions;
} MYPACKET;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    // �_�C�A���O�{�b�N�X�𐶐�
    DialogBox(hCurInst, "MYDLG", NULL, (DLGPROC)MyDlgProc);
    return 0;
}

// �_�C�A���O�{�b�N�X�̃v���V�[�W��
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    SYSTEMTIME st;
    char szTime[64];
    BOOL suc;

    switch (msg) {
        case WM_INITDIALOG:
            // �T�[�o�̃|�[�g�ԍ��i123�j��\��
            SetDlgItemInt(hDlg, IDC_SPORT, sport, FALSE);
            // �^�C�}�[���쐬
            if (SetTimer(hDlg, ID_MYTIMER, 200, NULL) == 0) {
                MessageBox(hDlg, "�^�C�}�[�̍쐬���s���܂���",
                    szAppName, MB_OK | MB_ICONEXCLAMATION);
                return TRUE;
            }
            return TRUE;
        case WM_TIMER:
            if (wp != ID_MYTIMER)
                return FALSE;
            // �R���s���[�^�̎������擾
            GetLocalTime(&st);
            // ������\����������쐬
            wsprintf(szTime, "%d/%02d/%02d %02d:%02d:%02d",
                st.wYear, st.wMonth, st.wDay,
                st.wHour, st.wMinute, st.wSecond);
            // �������_�C�A���O�{�b�N�X�ɕ\��
            SetWindowText(GetDlgItem(hDlg, IDC_MYTIME), szTime);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:        // �uOK�v�{�^��
                    // �T�[�o���A�T�[�o�̃|�[�g�ԍ��A��M�|�[�g�ԍ����擾
                    GetDlgItemText(hDlg, IDC_SERVER,
                        szServer, (int)sizeof(szServer));
                    sport = (u_int)GetDlgItemInt(hDlg,
                        IDC_SPORT, &suc, FALSE);
                    port = (u_int)GetDlgItemInt(hDlg,
                        IDC_PORT, &suc, FALSE);

                    if (strcmp(szServer, "") == 0 || port == 0) {
                        MessageBox(hDlg, 
                            "�T�[�o�܂��̓|�[�g�ԍ����w�肳��Ă��܂���",
                            "Error", MB_OK | MB_ICONEXCLAMATION);
                        return TRUE;
                    }

                    MyConnect(hDlg);
                    return TRUE;
                case IDCANCEL:    // �u�I���v�{�^��
                    KillTimer(hDlg, ID_MYTIMER);    // �^�C�}�[��j��
                    EndDialog(hDlg, IDCANCEL);      // �_�C�A���O��j��
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

BOOL MyConnect(HWND hDlg)
{
    WSADATA wsaData;
    SOCKADDR_IN myaddr, serveraddr;
    int nRtn;
    SOCKET s;
    HOSTENT *lpHostent;
    unsigned int addr;
    MYPACKET packet;
    int fromlen;
    time_t server_tm;
    struct tm *lpgtime;
    SYSTEMTIME st;

    // �@ WinSock��������
    nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (nRtn != 0) {
        MessageBox(hDlg, 
            "Winsock���������s�ł�", 
            szAppName, 
            MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    // �A �\�P�b�g���I�[�v��
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET) {
        MessageBox(hDlg, "socket���s", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return FALSE;
    }

    // �B SOCKADDR_IN�\���̂̃����o���Z�b�g
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    // �C �\�P�b�g�ɖ��O��t����
    nRtn = bind(s, (SOCKADDR *)&myaddr, sizeof(myaddr));
    if (nRtn != 0) {
        MessageBox(hDlg, "bind Error", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // �D �z�X�g�����擾
    lpHostent = gethostbyname(szServer);
    if (lpHostent == NULL) {
        addr = inet_addr(szServer);
        lpHostent = gethostbyaddr((char *)&addr, 4, AF_INET);
        if (lpHostent == NULL) {
            MessageBox(hDlg, "�z�X�g�����ł��܂���",
                szAppName, MB_OK | MB_ICONEXCLAMATION);
            closesocket(s);
            WSACleanup();
            return FALSE;
        }
    }

    // �E SOCKADDR_IN�\���̂̃����o�ɃT�[�o�����Z�b�g
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(sport);
    serveraddr.sin_addr.s_addr = 
        *((unsigned long *)lpHostent->h_addr);

    // �F Control_Word�����o��0x0B000000���Z�b�g
    memset(&packet, 0, sizeof(MYPACKET));
    packet.Control_Word = htonl(0x0B000000);

    // �G �p�P�b�g�𑗐M
    nRtn = sendto(s, (const char *)&packet, sizeof(MYPACKET), 
        0, (SOCKADDR *)&serveraddr,sizeof(serveraddr));
    if (nRtn == SOCKET_ERROR) {
        MessageBox(hDlg, "�p�P�b�g���M�G���[�ł�", szAppName,
            MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // �H �T�[�o����̕Ԏ���ҋ@
    fromlen = sizeof(SOCKADDR_IN);
    nRtn = recvfrom(s, (char *)&packet, sizeof(MYPACKET), 
        0, (SOCKADDR *)&serveraddr, &fromlen);
    if (nRtn == SOCKET_ERROR) {
        MessageBox(hDlg, "��M�G���[�ł�", 
            szAppName, MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return FALSE;
    }

    // �T�[�o����Ԃ��ꂽ������ϐ��ɕۊ�
    server_tm =
        ntohl(packet.transmit_timestamp_seconds) - 2208988800;
    // �T�[�o����̎�����tm�\���̂ɕϊ�
    lpgtime = gmtime(&server_tm);

    // SYSTEMTIME�\���̂̃����o���Z�b�g
    st.wYear = lpgtime->tm_year + 1900;
    st.wMonth = lpgtime->tm_mon + 1;
    st.wDay = lpgtime->tm_mday;
    st.wHour = lpgtime->tm_hour;
    st.wMinute = lpgtime->tm_min;
    st.wSecond = lpgtime->tm_sec;
    st.wMilliseconds = 0;

    // �R���s���[�^�̎������A�T�[�o����擾���������ɍ��킹��
    if (SetSystemTime(&st) != 0) {
        MessageBox(hDlg, "�V�X�e�����Ԃ��T�[�o���Ԃɍ��킹�܂���",
            szAppName, MB_OK);
    }

    closesocket(s);          // �\�P�b�g���N���[�Y
    WSACleanup();            // WinSock�̃��\�[�X�����

    return TRUE;
}
