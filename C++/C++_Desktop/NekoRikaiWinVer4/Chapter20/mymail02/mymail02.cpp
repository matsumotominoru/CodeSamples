// mymail02.cpp

#define WIN32_LEAN_AND_MEAN
#define MYTIMER 100
#define MYLOG "mylog.log"

#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include <Mmsystem.h>
#include <stdlib.h>
#include "resource.h"

BOOL CALLBACK MainProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
int MyMailCheck(HWND);
BOOL WriteMyLog(char *);

char szClassName[] = "mymail02";    // �E�B���h�E�N���X
char szPopName[64], szID[32], szPass[32], szPort[8], szMin[8];
u_short port = 110;
int nMin = 3;
HINSTANCE hInst;
HWND hStart, hStop, hOption, hOK;
BOOL bConnect = FALSE;              // �ڑ������ǂ���

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    hInst = hCurInst;
    DialogBox(hCurInst, "MAINDLG", NULL, (DLGPROC)MainProc);
    return 0;
}

BOOL CALLBACK MainProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static BOOL bTimer = FALSE;   // �^�C�}�[�����삵�Ă��邩�ǂ���

    switch (msg) {
        case WM_INITDIALOG:
            // �{�^���̃E�B���h�E�n���h�����擾
            hStart = GetDlgItem(hDlg, IDC_START);
            hStop = GetDlgItem(hDlg, IDC_STOP);
            hOption = GetDlgItem(hDlg, IDC_OPTION);
            hOK = GetDlgItem(hDlg, IDOK);
            // �u�X�^�[�g�v�u�`�F�b�N���~�v�{�^�����g�p�s��
            EnableWindow(hStart, FALSE);
            EnableWindow(hStop, FALSE);
            // ���O�t�@�C���ɋL�^
            WriteMyLog("�v���O�����J�n\r\n");
            return TRUE;
        case WM_TIMER:
            if (wp != MYTIMER) 
                return FALSE;
            // ���[�����T�[�o�ɂ��邩�ǂ������`�F�b�N
            if (MyMailCheck(hDlg) != 0) {
                MessageBox(hDlg, "�ُ킪���������̂ŏI�����܂�",
                    "Error", MB_OK | MB_ICONEXCLAMATION);
                KillTimer(hDlg, MYTIMER);
                EndDialog(hDlg, IDCANCEL);
            }
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:                // �u�I���v�{�^��
                case IDCANCEL:            // �u����v�{�^��
                    if (bConnect) {       // �T�[�o�ɐڑ������H
                        MessageBox(hDlg,
                            "�`�F�b�N�𒆎~���Ă���I�����Ă�������",
                            "�x��", MB_OK);
                        return FALSE;
                    }
                    if (bTimer) {         // �^�C�}�[�����쒆�H
                        if (KillTimer(hDlg, MYTIMER) == 0)
                            MessageBox(hDlg, "KillTimer���s",
                                "Error", MB_OK);
                    }
                    // ���O�t�@�C���ɋL�^
                    WriteMyLog("�v���O�����I��\r\n");

                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDC_START:           // �u�X�^�[�g�v�{�^��
                    SetTimer(hDlg, MYTIMER, 1000 * 60 * nMin, NULL);
                    bTimer = TRUE;

                    // �{�^���̎g�p�\�E�s��ݒ�
                    EnableWindow(hStart, FALSE);
                    EnableWindow(hStop, TRUE);
                    EnableWindow(hOption, FALSE);
                    EnableWindow(hOK, FALSE);

                    // ���O�t�@�C���ɋL�^
                    WriteMyLog("���b�Z�[�W�`�F�b�N�J�n\r\n");

                    // ���[�����`�F�b�N
                    if (MyMailCheck(hDlg) != 0) {
                        MessageBox(hDlg, "�ُ킪���������̂ŏI�����܂�",
                            "Error", MB_OK | MB_ICONEXCLAMATION);
                        KillTimer(hDlg, MYTIMER);
                        EndDialog(hDlg, IDCANCEL);
                        return FALSE;
                    }
                    return TRUE;
                case IDC_STOP:            // �u�`�F�b�N���~�v�{�^��
                    if (bConnect) {       // �T�[�o�ɐڑ������H
                        MessageBox(hDlg, 
                            "�ڑ����ł�\n�ォ���蒼���Ă�������",
                            "�ڑ���", MB_OK | MB_ICONEXCLAMATION);
                        return FALSE;
                    }
                    KillTimer(hDlg, MYTIMER);
                    bTimer = FALSE;

                    // �{�^���̎g�p�\�E�s��ݒ�
                    EnableWindow(hStop, FALSE);
                    EnableWindow(hStart, TRUE);
                    EnableWindow(hOption, TRUE);
                    EnableWindow(hOK, TRUE);
                    return TRUE;
                case IDC_OPTION:          // �u�I�v�V�����v�{�^��
                    DialogBox(hInst, "MYDLG", hDlg, (DLGPROC)MyDlgProc);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

int MyMailCheck(HWND hWnd)
{
    WSADATA wsaData;
    SOCKET s;
    char szBuf[1024];
    char szList[1024];
    LPHOSTENT lpHost;
    SOCKADDR_IN sockaddr;
    HWND hInfo;

    memset(szList, '\0', sizeof(szList));

    hInfo = GetDlgItem(hWnd, IDC_INFO);

    // WinSock��������
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        MessageBox(hWnd, "WSAStartup�֐����s�ł�",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        WriteMyLog("WSAStartup�֐����s");
        return -1;
    }

    bConnect = TRUE;

    // �\�P�b�g���I�[�v������
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        MessageBox(hWnd, "�\�P�b�g�쐬���s�ł�",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        WriteMyLog("WSAStartup�֐����s");
        WSACleanup();
        bConnect = FALSE;
        return -2;
    }

    // �z�X�g�����擾
    lpHost = gethostbyname(szPopName);
    if (lpHost == NULL) {
        MessageBox(hWnd, "�z�X�g���擾���s���܂���",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        bConnect = FALSE;
        return -3;
    }

    // SOCKADDR_IN�\���̂ɕK�v�������Z�b�g
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

    // �\�P�b�g�ɐڑ�
    if (connect(s, (PSOCKADDR)&sockaddr, sizeof(sockaddr)) != 0) {
        MessageBox(hWnd, "�\�P�b�g�ɐڑ��ł��܂���ł���",
            "Error", MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        bConnect = FALSE;
        return -4;
    }

    // �f�[�^����M
    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd, "�G���[���������܂���", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        bConnect = FALSE;
        return -5;
    }
    WriteMyLog(szBuf);

    // ���[�U�[ID�𑗐M
    wsprintf(szBuf, "USER %s\r\n", szID);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    WriteMyLog(szBuf);

    // �p�X���[�h�𑗐M
    wsprintf(szBuf, "PASS %s\r\n", szPass);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd, "�p�X���[�h���s���ł�", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        bConnect = FALSE;
        return -6;
    }

    WriteMyLog(szBuf);
    Edit_SetText(hInfo, "�T�[�o�`�F�b�N��!");

    // LIST�R�}���h�𑗐M
    strcpy_s(szBuf, "LIST\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);

    while (1) {  // ".\r\n"����M����܂ŁA�J��Ԃ�recv�֐����Ăяo��
        memset(szBuf, '\0', sizeof(szBuf));
        recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
        strcat_s(szList, szBuf);
        WriteMyLog(szBuf);
        if (strstr(szBuf, ".\r\n"))
            break;
    }

    if (strstr(szList, "1")) {
        Edit_SetText(hInfo, "���b�Z�[�W���͂��Ă��܂�");
    } else {
        Edit_SetText(hInfo, "���b�Z�[�W�͂���܂���");
    }
    PlaySound("test.wav", NULL, SND_SYNC);    // ����炷

    // QUIT�R�}���h�𑗐M
    strcpy_s(szBuf, "QUIT\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    WriteMyLog(szBuf);

    closesocket(s);
    WSACleanup();
    bConnect = FALSE;
    return 0;
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hPopName, hID, hPass, hPort, hMin;

    switch (msg) {
        case WM_INITDIALOG:
            // �R���g���[���̃n���h�����擾
            hPopName = GetDlgItem(hDlg, IDC_POP3);
            hID = GetDlgItem(hDlg, IDC_ID);
            hPass = GetDlgItem(hDlg, IDC_PASS);
            hPort = GetDlgItem(hDlg, IDC_PORT);
            hMin = GetDlgItem(hDlg, IDC_MIN);
            // �O���[�o���ϐ��̒l���R���g���[���ɕ\��
            Edit_SetText(hPopName, szPopName);
            Edit_SetText(hID, szID);
            Edit_SetText(hPass, szPass);
            wsprintf(szPort, "%d", port);
            Edit_SetText(hPort, szPort);
            wsprintf(szMin, "%d", nMin);
            Edit_SetText(hMin, szMin);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:
                    // �R���g���[���̒l���O���[�o���ϐ��ɕۊ�
                    Edit_GetText(
                        hPopName, szPopName, sizeof(szPopName));
                    Edit_GetText(hID, szID, sizeof(szID));
                    Edit_GetText(hPass, szPass, sizeof(szPass));
                    Edit_GetText(hPort, szPort, sizeof(szPort));
                    port = atoi(szPort);
                    Edit_GetText(hMin, szMin, sizeof(szMin));
                    nMin = atoi(szMin);
                    // �L���R�ꂪ�Ȃ����ǂ����`�F�b�N
                    if (strcmp(szPopName, "") == 0 ||
                        strcmp(szID, "") == 0 ||
                        strcmp(szPass, "") == 0 ||
                        strcmp(szPort, "") == 0 ||
                        strcmp(szMin, "0") == 0 ||
                        strcmp(szMin, "") == 0) {
                            MessageBox(hDlg, 
                                "�ݒ肵�Ă��Ȃ����ڂ�����܂��B",
                                "Error", MB_OK | MB_ICONEXCLAMATION);
                            return FALSE;
                        } else {
                            // �u�X�^�[�g�v�{�^�����g�p�\�ɂ���
                            EnableWindow(hStart, TRUE);
                        }
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDCANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

BOOL WriteMyLog(char *lpszBuf)
{
    HANDLE hFile;
    DWORD dwWritten;
    SYSTEMTIME st;
    char szBuf[256];

    hFile = CreateFile(                     // �t�@�C�����J��
        MYLOG, GENERIC_WRITE, 0, 0, 
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    SetFilePointer(hFile, 0, 0, FILE_END);  // �t�@�C���̖����ֈړ�
    GetLocalTime(&st);                      // ���݂̓������擾
    wsprintf(szBuf, "[%d/%02d/%02d %02d:%02d:%02d]\r\n",
        st.wYear, st.wMonth, st.wDay,
        st.wHour, st.wMinute, st.wSecond);
    WriteFile(                              // ��������������
        hFile, szBuf, (DWORD)strlen(szBuf), &dwWritten, NULL);
    WriteFile(                              // �����̕��������������
        hFile, lpszBuf, (DWORD)strlen(lpszBuf), &dwWritten, NULL);
    CloseHandle(hFile);
    return TRUE;
}
