// dialog02.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("dialog02");    // �E�B���h�E�N���X
HINSTANCE hInst;    // �C���X�^���X�n���h��
HWND hDlg;          // ���[�h���X�_�C�A���O�{�b�N�X�̃n���h��
TCHAR szName[32];   // �_�C�A���O�{�b�N�X������͂��ꂽ������
HWND hMain;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;
    HACCEL hAccel;

    hInst = hCurInst; // �O���[�o���ϐ��ɃC���X�^���X�n���h�����R�s�[
    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow))
        return FALSE;
    hAccel = LoadAccelerators(hCurInst, TEXT("MYACCEL"));
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
            break;
        } else {
            if (!hDlg || !IsDialogMessage(hDlg, &msg)) {
                if (!TranslateAccelerator(hMain, hAccel, &msg)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
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
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
                    IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = TEXT("MYMENU");  // ���j���[��o�^
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
               TEXT("�L�ł��킩�郂�[�h���X�_�C�A���O�{�b�N�X"),
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT,
               CW_USEDEFAULT, CW_USEDEFAULT,
               NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    hMain = hWnd;
    return TRUE;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HMENU hMenu;
    TCHAR szBuf[64];
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_CREATE:
            hMenu = GetMenu(hWnd);      // ���j���[�n���h�����擾
            break;
        case WM_INITMENU:               // �����Ń��j���[������������
            if (IsWindow(hDlg)) {
                EnableMenuItem(hMenu, IDM_DLG,
                               MF_BYCOMMAND | MF_GRAYED);
                EnableMenuItem(hMenu, IDM_CLOSEDLG,
                               MF_BYCOMMAND | MF_ENABLED);
            } else {
                EnableMenuItem(hMenu, IDM_DLG,
                               MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, IDM_CLOSEDLG,
                               MF_BYCOMMAND | MF_GRAYED);
            }
            DrawMenuBar(hWnd);
            break;
        case WM_PAINT:                  // �`�揈��
            if (lstrcmp(szName, TEXT("")) == 0)
                lstrcpy(szBuf, TEXT("�܂����O�̓��͂͂���܂���"));
            else
                wsprintf(szBuf, TEXT("���͂��ꂽ������%s����ł�"),
                         szName);
            hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, 10, 10, szBuf, lstrlen(szBuf));
            EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:                // ���j���[�R�}���h�̏���
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_DLG:
                    // ���[�h���X�_�C�A���O�{�b�N�X���쐬
                    hDlg = CreateDialog(
                        hInst, TEXT("MYDLG"), hWnd, (DLGPROC)MyDlgProc);
                    ShowWindow(hDlg, SW_NORMAL);   // �_�C�A���O��\��
                    break;
                case IDM_CLOSEDLG:
                    DestroyWindow(hDlg);           // �_�C�A���O��j��
                    break;
            }
            break;
        case WM_CLOSE:
            if (IsWindow(hDlg)) {
                MessageBox(hWnd, TEXT("�_�C�A���O��j�����܂�"),
                           TEXT("�j��"), MB_OK);
                DestroyWindow(hDlg);               // �_�C�A���O��j��
            }
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

// �_�C�A���O�v���V�[�W��
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hParent;

    switch (msg) {
        case WM_INITDIALOG:
            hParent = GetParent(hDlg);    // �e�E�B���h�E�̃n���h�����擾
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDOK:                // �uOK�v�{�^���������ꂽ
                    // �G�f�B�b�g�R���g���[�����當������擾
                    GetDlgItemText(hDlg, IDC_EDIT1, szName,
                                   (int)sizeof(szName) - 1);
                    InvalidateRect(hParent, NULL, TRUE);
                    return TRUE;
                case IDCANCEL:            // �u�N���A�v�{�^���������ꂽ
                    // �G�f�B�b�g�R���g���[���ɕ�������Z�b�g
                    SetDlgItemText(hDlg, IDC_EDIT1, TEXT(""));
                    return TRUE;
                case IDC_CLOSE:           // �u����v�{�^���������ꂽ
                    DestroyWindow(hDlg);  // �_�C�A���O��j��
                    return TRUE;
            }

            return FALSE;
    }
    return FALSE;
}
