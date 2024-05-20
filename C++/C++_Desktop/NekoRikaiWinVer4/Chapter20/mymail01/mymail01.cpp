// mymail01.cpp

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <winsock2.h>
#include <stdlib.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyMailCheck(HWND);

char szClassName[] = "mymail01";    // �E�B���h�E�N���X
HINSTANCE hInst;                    // �C���X�^���X
u_short port = 110;                 // �|�[�g�ԍ�

// �T�[�o���A���[�U�[ID�A�p�X���[�h�A�|�[�g
char szPopName[64], szID[32], szPass[32], szPort[8];


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
				   LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	
	hInst = hCurInst;

	if (!InitApp(hCurInst))
		return FALSE;
	if (!InitInstance(hCurInst, nCmdShow)) 
		return FALSE;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

// �E�B���h�E�N���X�̓o�^
ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// �v���V�[�W����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;		// �C���X�^���X
	wc.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MYMENU";	// ���j���[��
	wc.lpszClassName = (LPCSTR)szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			"�L�ł��킩�郁�[���`�F�b�J�[", // �^�C�g���o�[�ɂ��̖��O���\��
			WS_OVERLAPPEDWINDOW,          // �E�B���h�E�̎��
			CW_USEDEFAULT,	// �w���W
			CW_USEDEFAULT,	// �x���W
			CW_USEDEFAULT,	// ��
			CW_USEDEFAULT,	// ����
			NULL,  // �e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
			NULL,  // ���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
			hInst, // �C���X�^���X�n���h��
			NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;

    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_SETTING:    // �u�I�v�V�����v���u�ݒ�v
                    DialogBox(hInst, "MYDLG", hWnd, (DLGPROC)MyDlgProc);
                    break;
                case IDM_END:        // �u�t�@�C���v���u�I���v
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_CHECK:      // �u�t�@�C���v���u���[���`�F�b�N�v
                    MyMailCheck(hWnd);
                    break;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, "�I�����Ă���낵���ł���",
                "�m�F", MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES)
                DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

int MyMailCheck(HWND hWnd)
{
    WSADATA wsaData;
    SOCKET s;
    char szBuf[1024];
    LPHOSTENT lpHost;
    SOCKADDR_IN sockaddr;

    // WinSock��������
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        MessageBox(hWnd,  "WSAStartup�֐����s�ł�", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        return -1;
    }

    // �\�P�b�g���I�[�v������
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        MessageBox(hWnd,  "�\�P�b�g�쐬���s�ł�", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        WSACleanup();
        return -2;
    }

    // �z�X�g�����擾
    lpHost = gethostbyname(szPopName);
    if (lpHost == NULL) {
        MessageBox(hWnd,  "�z�X�g���擾���s���܂���", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return -3;
    }

    // SOCKADDR_IN�\���̂ɕK�v�������Z�b�g
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

    // �\�P�b�g�ɐڑ�
    if (connect(s, (PSOCKADDR)&sockaddr, sizeof(sockaddr)) != 0) {
        MessageBox(hWnd,  "�\�P�b�g�ɐڑ��ł��܂���ł���", 
            "Error",  MB_OK | MB_ICONEXCLAMATION);
        closesocket(s);
        WSACleanup();
        return -4;
    }

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd,  "�G���[���������܂���", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        return -5;
    }
    MessageBox(hWnd, szBuf, "connect�֐�����", MB_OK);

    // ���[�U�[ID�𑗐M
    wsprintf(szBuf, "USER %s\r\n", szID);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    MessageBox(hWnd, szBuf, "���[�U�[ID����", MB_OK);

    // �p�X���[�h�𑗐M
    wsprintf(szBuf, "PASS %s\r\n", szPass);
    send(s, szBuf, (int)strlen(szBuf), 0);

    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    if (strstr(szBuf, "+OK") == NULL) {
        MessageBox(hWnd,  "�p�X���[�h���s���ł�", "Error", MB_OK);
        closesocket(s);
        WSACleanup();
        return -6;
    }
    MessageBox(hWnd, szBuf, "�p�X���[�h����", MB_OK);

    // �ڑ���؂�
    MessageBox(hWnd, "���ꂩ��ڑ���؂�܂�", "OK", MB_OK);
    strcpy_s(szBuf, "QUIT\r\n");
    send(s, szBuf, (int)strlen(szBuf), 0);
    memset(szBuf, '\0', sizeof(szBuf));
    recv(s, szBuf, (int)sizeof(szBuf) - 1, 0);
    MessageBox(hWnd, szBuf, "QUIT���M��", MB_OK);

    closesocket(s);
    WSACleanup();
    return 0;
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hPopName, hID, hPass, hPort;

    switch (msg) {
        case WM_INITDIALOG:
            // �R���g���[���̃n���h�����擾
            hPopName = GetDlgItem(hDlg, IDC_POP3);
            hID = GetDlgItem(hDlg, IDC_ID);
            hPass = GetDlgItem(hDlg, IDC_PASS);
            hPort = GetDlgItem(hDlg, IDC_PORT);
            // �O���[�o���ϐ��̒l���R���g���[���ɕ\��
            Edit_SetText(hPopName, szPopName);
            Edit_SetText(hID, szID);
            Edit_SetText(hPass, szPass);
            wsprintf(szPort, "%d", port);
            Edit_SetText(hPort, szPort);
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
