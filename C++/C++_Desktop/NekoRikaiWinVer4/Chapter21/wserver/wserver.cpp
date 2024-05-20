// wserver.cpp

#define WIN32_LEAN_AND_MEAN
#define MY_MSG (WM_USER + 1)     // ���O�̃��b�Z�[�W

#include <windows.h>
#include <winsock2.h>
#include <windowsx.h>
#include "resource.h"

BOOL CALLBACK MyServerProc(HWND, UINT, WPARAM, LPARAM);
int mystream(HWND, u_short);

HINSTANCE hInst;

SOCKET listen_s, s;             // ���b�X���\�P�b�g�ƒʐM�p�\�P�b�g
BOOL bSOCKET_LISTEN = FALSE,    // ���b�X���\�P�b�g���L�����ǂ���
     bSOCKET_S = FALSE;         // �ʐM�p�\�P�b�g���L�����ǂ���

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    WSADATA wsaData;
    hInst = hCurInst;

    // WinSock��������
    if (WSAStartup(MAKEWORD(1, 1), &wsaData)) {
        MessageBox(NULL, "���������s", "Error",
            MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return -1;
    }

    // �_�C�A���O�{�b�N�X�𐶐�
    DialogBox(hCurInst, "MYSERVER", NULL, (DLGPROC)MyServerProc);

    // WinSock�̃��\�[�X�����
    if (WSACleanup() != 0) {
        MessageBox(NULL, "WSACleanup�G���[�ł�", "Error", MB_OK);
    }

    MessageBox(NULL, "�I�����܂�", "�I��", MB_OK);
    return 0;
}

// �_�C�A���O�{�b�N�X�̃v���V�[�W��
BOOL CALLBACK MyServerProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hStart, hInfo, hSendBtn;
    static u_short port;
    char szBuf[1024];
    static char szAllBuf[1024 * 10] = "";
    BOOL bSuccess;
    int nEvent, nRet, nAsync;
    SOCKADDR from;
    int fromlen, nError;
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
            hStart = GetDlgItem(hDlg, IDC_START);
            hInfo = GetDlgItem(hDlg, IDC_INFO);
            hSendBtn = GetDlgItem(hDlg, IDC_SENDBTN);
           // �u���M�v�{�^�����g�p�s�ɐݒ�
            EnableWindow(hSendBtn, FALSE);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDC_START:             // �u�J�n�v�{�^��
                    port = (u_short)GetDlgItemInt(
                        hDlg, IDC_PORT, &bSuccess, FALSE);
                    if (mystream(hDlg, port) == 0)
                        EnableWindow(hStart, FALSE);
                    return TRUE;
                case IDC_SENDBTN:           // �u���M�v�{�^��
                    // IDC_SEND�̓��e�𑗐M
                    GetDlgItemText(
                        hDlg, IDC_SEND, szBuf, (int)sizeof(szBuf));
                    nRet = send(s, szBuf, (int)strlen(szBuf), 0);
                    // ������̑̍ق𐮂��A���b�Z�[�W���ɕ\��
                    strcat_s(szAllBuf, "Server:");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    // ���b�Z�[�W�����X�N���[��
                    SendMessage(hInfo,
                        EM_LINESCROLL, 0, Edit_GetLineCount(hInfo));
                    // IDC_SEND�̕�������폜
                    SetDlgItemText(hDlg, IDC_SEND, "");
                    // IDC_SEND�Ƀt�H�[�J�X��ݒ�
                    SetFocus(GetDlgItem(hDlg, IDC_SEND));
                    return TRUE;
                case IDOK:                  // �u�I���v�{�^��
                case IDCANCEL:              // �u����v�{�^��
                    if (bSOCKET_S) {        // �\�P�b�g���L���ȏꍇ
                        nRet = shutdown(s, SD_BOTH);
                        if (nRet == SOCKET_ERROR) {
                            MessageBox(hDlg, "�V���b�g�_�E�����s",
                                "Error", MB_OK);
                        } else {
                            MessageBox(hDlg, "�V���b�g�_�E������",
                                "shutdown", MB_OK);
                        }
                        if (closesocket(s)) {
                            MessageBox(hDlg, "�\�P�b�g�N���[�Y���s",
                                "Error", MB_ICONEXCLAMATION | MB_OK);
                        }
                    }
                    if (bSOCKET_LISTEN) {   // ���X���\�P�b�g���L���ȏꍇ
                        if (closesocket(listen_s)) {
                            MessageBox(hDlg,
                                "���X���\�P�b�g�N���[�Y���s",
                                "Error", MB_ICONEXCLAMATION | MB_OK);
                        }
                    }
                    EndDialog(hDlg, IDOK);  // �_�C�A���O�����
                    return TRUE;
            }
            return FALSE;
        case MY_MSG:
            nEvent = WSAGETSELECTEVENT(lp);
            switch (nEvent) {
                case FD_CLOSE:
                    MessageBox(hDlg,
                        "�N���C�A���g���ؒf���Ă��܂���\n"
                        "�đ҂��󂯂��܂�",
                        "�ؒf", MB_OK);
                    EnableWindow(hSendBtn, FALSE);
                    closesocket(s);
                    bSOCKET_S = FALSE;
                    mystream(hDlg, port);
                    return TRUE;
                case FD_READ:
                    nRet = recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
                    if (nRet == SOCKET_ERROR) {
                        MessageBox(hDlg, "recv�G���[", "Error", MB_OK);
                        return FALSE;
                    }
                    szBuf[nRet] = '\0';
                    strcat_s(szAllBuf, "Client:");
                    strcat_s(szAllBuf, szBuf);
                    strcat_s(szAllBuf, "\r\n");
                    SetDlgItemText(hDlg, IDC_INFO, szAllBuf);
                    SendMessage(hInfo,
                        EM_LINESCROLL, 0, Edit_GetLineCount(hInfo));
                    return TRUE;
                case FD_ACCEPT:
                    memset(&from, 0, sizeof(SOCKADDR));
                    fromlen = sizeof(from);
                    s = accept(listen_s, (SOCKADDR *)&from, &fromlen);

                    // �G���[�`�F�b�N
                    if (s == INVALID_SOCKET) {
                        nError = WSAGetLastError();
                        if (nError != WSAEWOULDBLOCK) {
                            switch (nError) {
                                case WSANOTINITIALISED:
                                    MessageBox(hDlg,
                                        "WSANOTINITIALISED",
                                        "Error", MB_OK);
                                    break;
                                case WSAENETDOWN:
                                    MessageBox(hDlg,
                                        "WSAENETDOWN",
                                        "Error", MB_OK);
                                    break;
                                case WSAEFAULT:
                                    MessageBox(hDlg,
                                        "WSAEFAULT",
                                        "Error", MB_OK);
                                    break;
                                case WSAEINTR:
                                    MessageBox(hDlg,
                                        "WSAEINTR",
                                        "Error", MB_OK);
                                    break;
                                case WSAEINPROGRESS:
                                    MessageBox(hDlg,
                                        "WSAEINPROGRESS",
                                        "Error", MB_OK);
                                    break;
                                case WSAEINVAL:
                                    MessageBox(hDlg,
                                        "WSAEINVAL",
                                        "Error", MB_OK);
                                    break;
                                case WSAEMFILE:
                                    MessageBox(hDlg,
                                        "WSAEMFILE",
                                        "Error", MB_OK);
                                    break;
                                case WSAENOBUFS:
                                    MessageBox(hDlg,
                                        "WSAENOBUFS",
                                        "Error", MB_OK);
                                    break;
                                case WSAENOTSOCK:
                                    MessageBox(hDlg,
                                        "WSAENOTSOCK",
                                        "Error", MB_OK);
                                    break;
                                case WSAEOPNOTSUPP:
                                    MessageBox(hDlg,
                                        "WSAEOPNOTSUPP",
                                        "Error", MB_OK);
                                    break;
                                default:
                                    MessageBox(hDlg,
                                        "�s���̃G���[�ł�",
                                        "Error", MB_OK);
                                    break;
                            }
                            MessageBox(hDlg, "accept error", "Error", MB_OK);
                            closesocket(listen_s);
                            bSOCKET_LISTEN = FALSE;
                            return TRUE;
                        }
                    }  // �G���[�`�F�b�N�A�����܂�

                    if (closesocket(listen_s) != 0) {
                        MessageBox(hDlg, "Error", "Error", MB_OK);
                        return TRUE;
                    }
                    bSOCKET_LISTEN = FALSE;
                    bSOCKET_S = TRUE;

                    // �񓯊���
                    nAsync = WSAAsyncSelect(
                        s, hDlg, MY_MSG, FD_CLOSE | FD_READ);
                    if (nAsync != 0) {
                        MessageBox(hDlg, "�񓯊������s",
                            "Error", MB_OK | MB_ICONEXCLAMATION);
                        closesocket(s);
                        bSOCKET_S = FALSE;
                        return TRUE;
                    }

                    EnableWindow(hSendBtn, TRUE);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

int mystream(HWND hDlg, u_short uport)
{
    SOCKADDR_IN saddr;
    int nAsync;

    // ���X���\�P�b�g���I�[�v��
    listen_s = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_s < 0) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            MessageBox(hDlg, "�\�P�b�g�I�[�v���G���[",
                "Error", MB_OK | MB_ICONEXCLAMATION);
            return -1;
        }
    } else {
        MessageBox(NULL, "�\�P�b�g�I�[�v�����܂���",
            "socket����", MB_OK);
    }
    bSOCKET_LISTEN = TRUE;

    // ���X���\�P�b�g��񓯊����[�h��
    nAsync = WSAAsyncSelect(listen_s, hDlg, MY_MSG, FD_ACCEPT);
    if (nAsync != 0) {
        MessageBox(hDlg, "�񓯊������s1", "Error", 
            MB_OK | MB_ICONEXCLAMATION);
        closesocket(listen_s);
        bSOCKET_LISTEN = FALSE;
        return -2;
    } 

    // SOCKADDR_IN�\���̂ɕK�v�������Z�b�g
    memset(&saddr, 0, sizeof(SOCKADDR_IN));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(uport);
    saddr.sin_addr.s_addr = INADDR_ANY;

    // ���X���\�P�b�g�ɖ��O��t����
    if (bind(listen_s, (SOCKADDR *)&saddr, sizeof(saddr)) ==
            SOCKET_ERROR) {
        MessageBox(hDlg, 
            "bind Error\n�ʂȃ|�[�g�ԍ��ł�����x�����Ă��������B",
            "Error", MB_OK);
        closesocket(listen_s);
        bSOCKET_LISTEN = FALSE;
        return -3;
    }

    // ���X���\�P�b�g��ڑ��҂���Ԃɂ���
    if (listen(listen_s, 0) == SOCKET_ERROR) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            MessageBox(hDlg, "listen Error", "Error", MB_OK);
            closesocket(listen_s);
            bSOCKET_LISTEN = FALSE;
            return -4;
        }
    } else {
        MessageBox(hDlg, "�N���C�A���g�̐ڑ��҂��ł�", "OK", MB_OK);
    }

    return 0;
}

