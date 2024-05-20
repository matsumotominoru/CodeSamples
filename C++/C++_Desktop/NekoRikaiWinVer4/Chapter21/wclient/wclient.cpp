// wclient.cpp

#define WIN32_LEAN_AND_MEAN
#define MY_MSG (WM_USER + 1)     // ���O�̃��b�Z�[�W

#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include "resource.h"

BOOL CALLBACK MyClientProc(HWND, UINT, WPARAM, LPARAM);

char szAppName[] = "�L�ł��킩��TCP�N���C�A���g";
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    WSADATA wsaData;
    hInst = hCurInst;

    // WinSock��������
    if (WSAStartup(MAKEWORD(1, 1), &wsaData)) {
        MessageBox(NULL, "WSAStartup�Ɏ��s���܂���", szAppName,
            MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return -1;
    }

    // �_�C�A���O�{�b�N�X�𐶐�
    DialogBox(hCurInst, "MYCLIENT", NULL, (DLGPROC)MyClientProc);

    // WinSock�̃��\�[�X�����
    if (WSACleanup() == SOCKET_ERROR)
        MessageBox(NULL, "WSACleanup���s�ł�", szAppName, MB_OK);

    MessageBox(NULL, "�I�����܂�", szAppName, MB_OK);
    return 0;
}

// �_�C�A���O�{�b�N�X�̃v���V�[�W��
BOOL CALLBACK MyClientProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static SOCKET s;
    static SOCKADDR_IN saddr;
    char szBuf[1024];
    static char szAllBuf[1024 * 50];
    char szServer[1024];
    static HOSTENT *lpHost;
    static u_short uport;
    BOOL bSuccess;
    unsigned int addr;
    int nEvent, nResult;
    static BOOL bConnect = FALSE;
    static HWND hInfo, hSendBtn, hStart;
    HICON hIcon;

    switch (msg) {
        case WM_INITDIALOG:
            // �A�C�R�����\�[�X�̓ǂݍ���
            hIcon = (HICON)LoadImage(hInst, "MYICON",
                IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_SHARED);
            // �A�C�R����o�^
            SendMessage(
                hDlg, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
            // �R���g���[���̃n���h�����擾
            hInfo = GetDlgItem(hDlg, IDC_INFO);
            hSendBtn = GetDlgItem(hDlg, IDC_SENDBTN);
            hStart = GetDlgItem(hDlg, IDC_START);
            // �u���M�v�{�^�����g�p�s�ɐݒ�
            EnableWindow(hSendBtn, FALSE);
            return FALSE;
        case MY_MSG:
            nEvent = WSAGETSELECTEVENT(lp);
            switch (nEvent) {
                case FD_CONNECT:
                    strcpy_s(szBuf, "�N���C�A���g�͐ڑ��������Ă��܂�");
                    nResult = send(s, szBuf, (int)strlen(szBuf), 0);
                    if (nResult == SOCKET_ERROR) {
                        MessageBox(hDlg, 
                            "�T�[�o���N�����Ă��Ȃ����A"
                            "���̃N���C�A���g���ڑ�"
                            "���Ă���\��������܂�",
                            szAppName, MB_OK);
                        if (bConnect) {
                            closesocket(s);
                            bConnect = FALSE;
                        }
                        EnableWindow(hStart, TRUE);
                        return TRUE;
                    }
                    MessageBox(hDlg, "�T�[�o�ɐڑ����܂���",
                        szAppName, MB_OK);
                    EnableWindow(hSendBtn, TRUE);
                    EnableWindow(hStart, FALSE);
                    return TRUE;
                case FD_READ:
                    nResult = recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
                    szBuf[nResult] = '\0';
                    strcat_s(szAllBuf, "Server: ");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    SendMessage(hInfo, EM_LINESCROLL,
                        0, Edit_GetLineCount(hInfo));
                    return TRUE;
                case FD_CLOSE:
                    MessageBox(hDlg, "�T�[�o����ؒf����܂���", 
                        szAppName, MB_OK);
                    if (closesocket(s) == SOCKET_ERROR)
                        MessageBox(hDlg, "�\�P�b�g�N���[�Y���s", 
                        szAppName, MB_OK);
                    bConnect = FALSE;
                    EnableWindow(hSendBtn, FALSE);
                    EnableWindow(hStart, TRUE);
                    return TRUE;
            }
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDC_SENDBTN:    // �u���M�v�{�^��
                    // IDC_SEND�̓��e�𑗐M
                    GetDlgItemText(
                        hDlg, IDC_SEND, szBuf, (int)sizeof(szBuf));
                    nResult = send(s, szBuf, (int)strlen(szBuf), 0);

                    if (nResult == SOCKET_ERROR) {
                        MessageBox(hDlg, "send�G���[�ł�", szAppName, MB_OK);
                        closesocket(s);
                        bConnect = FALSE;
                        return FALSE;
                    }
                    // ������̑̍ق𐮂��A���b�Z�[�W���ɕ\��
                    strcat_s(szAllBuf, "Client: ");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    // ���b�Z�[�W�����X�N���[��
                    SendMessage(hInfo, EM_LINESCROLL,
                        0, Edit_GetLineCount(hInfo));
                    // IDC_SEND�̕�������폜
                    SetDlgItemText(hDlg, IDC_SEND, "");
                    // IDC_SEND�Ƀt�H�[�J�X��ݒ�
                    SetFocus(GetDlgItem(hDlg, IDC_SEND));
                    return TRUE;
                case IDC_START:      // �u�ڑ��v�{�^��
                    // �|�[�g�ԍ����擾
                    uport = GetDlgItemInt(
                        hDlg, IDC_PORT, &bSuccess, FALSE);
                    if (!bSuccess) {
                        MessageBox(hDlg, "�|�[�g�ԍ����������Ȃ��ł�",
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        return FALSE;
                    }
                    // �T�[�o�����擾
                    GetDlgItemText(
                        hDlg, IDC_SERVER, szServer, sizeof(szServer));
                    if (strcmp(szServer, "") == 0) {
                        MessageBox(hDlg,
                            "�T�[�o������͂��Ă�������",
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        return FALSE;
                    }
                    // �\�P�b�g���I�[�v��
                    s = socket(AF_INET, SOCK_STREAM, 0);
                    if (s < 0) {
                        MessageBox(hDlg, "�\�P�b�g�I�[�v���G���[",
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        return TRUE;
                    }
                    bConnect = TRUE;
                    // �T�[�o�����擾
                    lpHost = gethostbyname(szServer);
                    if (lpHost == NULL) {
                        addr = inet_addr(szServer);
                        lpHost = gethostbyaddr((char *)&addr, 4, AF_INET);
                    }
                    if (lpHost == NULL) {
                        MessageBox(hDlg, 
                            "�z�X�g�����擾�ł��܂���", 
                            szAppName, MB_OK | MB_ICONEXCLAMATION);
                        closesocket(s);
                        bConnect = FALSE;
                        return TRUE;
                    }

                    // �\�P�b�g��񓯊����[�h��
                    WSAAsyncSelect(s, hDlg, MY_MSG, 
                        FD_CONNECT | FD_READ | FD_CLOSE);

                    // SOCKADDR_IN�\���̂ɕK�v�������Z�b�g
                    memset(&saddr, 0, sizeof(SOCKADDR_IN));
                    saddr.sin_family = lpHost->h_addrtype;
                    saddr.sin_port = htons(uport);
                    saddr.sin_addr.s_addr = *((u_long *)lpHost->h_addr);
                    // �N���C�A���g�\�P�b�g���T�[�o�ɐڑ�
                    if (connect(s, (SOCKADDR *)&saddr, 
                            sizeof(saddr)) == SOCKET_ERROR) {
                        // �G���[�̎�ނ����
                        if (WSAGetLastError() != WSAEWOULDBLOCK) {
                            MessageBox(hDlg, "connect Error",
                                szAppName, MB_OK | MB_ICONEXCLAMATION);
                            closesocket(s);
                            bConnect = FALSE;
                            return FALSE;
                        } else {
                            MessageBox(hDlg, "�ڑ��ҋ@��", szAppName, MB_OK);
                        }
                    }  else {
                        MessageBox(hDlg, "connect OK", szAppName, MB_OK);
                    } 
                    return TRUE;
                case IDCANCEL:       // �u����v�{�^��
                case IDOK:           // �u�I���v�{�^��
                    if (bConnect) {
                        if (shutdown(s, SD_BOTH) == SOCKET_ERROR) {
                            MessageBox(hDlg, 
                                "shutdown�Ɏ��s���܂����B",
                                szAppName, MB_OK);
                        }
                        if (closesocket(s) != 0) {
                            MessageBox(hDlg, 
                                "�\�P�b�g���N���[�Y�ł��܂���ł���", 
                                szAppName, MB_OK | MB_ICONEXCLAMATION);
                        }
                    }
                    EndDialog(hDlg, IDOK);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}
