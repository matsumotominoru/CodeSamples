// startupwin.cpp

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include "resource.h"

typedef struct _MYDATA {
    BYTE bMajor;
    BYTE bMinor;
    char szText[6][128];
} MYDATA, *LPMYDATA;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyStartupProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyStartup(HWND, LPMYDATA);

char szClassName[] = "startupwin";    // �E�B���h�E�N���X
char szAppName[] = "�L�ł��킩��Windows�v���O���~���O";
HINSTANCE hInst;                      // �C���X�^���X�n���h��

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;    // �C���X�^���X�n���h�����O���[�o���ϐ��ɃR�s�[
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
    wc.lpfnWndProc = WndProc;    // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;        // �C���X�^���X
    wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = "MYMENU";  // ���j���[��
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.hIconSm = (HICON)LoadImage(NULL,
        MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, szAppName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 313, 227,
        NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id, i;
    static MYDATA mydata;
    INT_PTR ret;        // Visual C++ 6.0����т���ȑO�ł�int
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:           // �u�I���v���j���[����
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_STARTUP:       // �uWSAStartup�v���j���[����
                    // �_�C�A���O�{�b�N�X��\��
                    ret = DialogBoxParam(hInst, "MYSTARTUP",
                        hWnd,  (DLGPROC)MyStartupProc, (LPARAM)&mydata);
                    if (ret == IDOK) {  // �_�C�A���O��OK�������ꂽ
                        id = MyStartup(hWnd, &mydata);
                        if (id == 0) {
                            InvalidateRect(hWnd, NULL, TRUE);
                        }
                    }
                    break;
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            for (i = 0; i < 6; i++)
                TextOut(hdc,  10, 10 * 2 * (i + 1), mydata.szText[i],
                    (int)strlen(mydata.szText[i]));
            EndPaint(hWnd, &ps);
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

// �_�C�A���O�{�b�N�X�̃v���V�[�W��
BOOL CALLBACK MyStartupProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    BOOL bSuccess;
    static LPMYDATA lpdata;

    switch (msg) {
        case WM_INITDIALOG:
            lpdata = (LPMYDATA)lp;    // mydata�̃|�C���^��ۊ�
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:            // �uOK�v�{�^����������
                    // �G�f�B�b�g�R���g���[�����琔�l��ǂݏo����
                    // lpdata�ɏ����o��
                    lpdata->bMajor = GetDlgItemInt(
                        hDlg, IDC_MAJOR, &bSuccess, FALSE);
                    lpdata->bMinor = GetDlgItemInt(
                        hDlg, IDC_MINOR, &bSuccess, FALSE);

                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDCANCEL:        // �u�L�����Z���v�{�^���������ꂽ
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}

int MyStartup(HWND hWnd, LPMYDATA lpmydata)
{
    WSADATA wsaData;
    WORD wVersion;

    // �󂯎����lpmydata����o�[�W�����ԍ���WORD�l�𐶐�
    wVersion = MAKEWORD(lpmydata->bMajor, lpmydata->bMinor);
    // WinSock��������
    if (WSAStartup(wVersion, &wsaData) != 0) {
        MessageBox(hWnd, "WSAStartup�֐����s", szAppName, MB_OK);
        return -1;
    }

    // WSADATA�\���̂Ɋi�[����Ă���f�[�^��
    // lpmydata�̊e�����o�ɏ�������
    wsprintf(lpmydata->szText[0], "wVersion = %d.%d", 
        LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
    wsprintf(lpmydata->szText[1], "wHighVersion = %d.%d",
        LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
    wsprintf(lpmydata->szText[2], "szDescription = %s",
        wsaData.szDescription);
    wsprintf(lpmydata->szText[3], "szSystemStatus = %s",
        wsaData.szSystemStatus);
    wsprintf(lpmydata->szText[4], "iMaxSockets = %d",
        wsaData.iMaxSockets);
    wsprintf(lpmydata->szText[5], "iMaxUdpDg = %d",
        wsaData.iMaxUdpDg);

    WSACleanup();    // WinSock�̃��\�[�X�����
    return 0;
}
