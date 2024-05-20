// tasktray01.cpp

#define ID_MYTRAY 300                      // �^�X�N�g���C�A�C�R����ID
#define MYTRAY_MESSAGE (WM_APP + 1)        // �^�X�N�g���C��
                                           // �}�E�X�C�x���g�p���b�Z�[�W

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("tasktray01");
HINSTANCE hInst;
NOTIFYICONDATA ni;
BOOL bTray;            // �^�X�N�g���C�ɂ��邩�ǂ���

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
    wc.lpfnWndProc = WndProc;    // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;        // �C���X�^���X
    wc.hIcon = (HICON)LoadImage(hInst, TEXT("MYICON"),
        IMAGE_ICON, 0,0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;      // ���j���[��
    wc.lpszClassName = szClassName;
    wc.hIconSm = (HICON)LoadImage(hInst, TEXT("MYICON"),
        IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩��^�X�N�g���C"),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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
    HMENU hMenu, hSubMenu;
    POINT pt;

    switch (msg) {
        case WM_RBUTTONDOWN:
            // �N���b�N���ꂽ�ʒu�Ƀ|�b�v�A�b�v���j���[��\��
            hMenu = LoadMenu(hInst, TEXT("MYMENU"));
            hSubMenu = GetSubMenu(hMenu, 0);
            pt.x = LOWORD(lp);
            pt.y = HIWORD(lp);
            ClientToScreen(hWnd, &pt);
            TrackPopupMenu(
                hSubMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);
            DestroyMenu(hMenu);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_TRAY:   // �u�^�X�N�g���C�ɓ����v���j���[����
                    // NOTIFYICONDATA�\���̂̃����o���Z�b�g
                    memset(&ni, 0, sizeof(NOTIFYICONDATA));
                    ni.cbSize = sizeof(NOTIFYICONDATA);
                    ni.hWnd = hWnd;
                    ni.uID = ID_MYTRAY;
                    ni.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
                    ni.hIcon = (HICON)LoadImage(
                        hInst, TEXT("MYICON"), IMAGE_ICON, 0, 0, 0);
                    ni.uCallbackMessage = MYTRAY_MESSAGE;
                    lstrcpy(ni.szTip, TEXT("�L�ł��킩��^�X�N�g���C"));

                    // �^�X�N�g���C�ɃA�C�R����\��
                    Shell_NotifyIcon(NIM_ADD, &ni);
                    // ���C���E�B���h�E���\���ɂ���
                    ShowWindow(hWnd, SW_HIDE);

                    bTray = TRUE;
                    break;
                case IDM_OUT:    // �u�^�X�N�g���C���o���v���j���[����
                    // �^�X�N�g���C�̃A�C�R�����폜
                    Shell_NotifyIcon(NIM_DELETE, &ni);
                    // ���C���E�B���h�E��\��
                    ShowWindow(hWnd, SW_SHOWNORMAL);

                    bTray = FALSE;
                    break;
                case IDM_END:    // �u�I���v���j���[����
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;
        case MYTRAY_MESSAGE:     // �^�X�N�g���C��̃C�x���g
            switch(lp) {
                case WM_RBUTTONDOWN:
                    // �N���b�N���ꂽ�ʒu�Ƀ|�b�v�A�b�v���j���[��\��
                    hMenu = LoadMenu(hInst, TEXT("MYTRAY"));
                    hSubMenu = GetSubMenu(hMenu, 0);
                    GetCursorPos(&pt);    // �N���b�N�ʒu���擾
                    SetForegroundWindow(hWnd);
                    TrackPopupMenu(
                        hSubMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);
                    DestroyMenu(hMenu);
                    break;
                default:
                    return (DefWindowProc(hWnd, msg, wp, lp));
            }
            break;
        case WM_CLOSE:
            if (bTray)   // �^�X�N�g���C�ɃA�C�R��������Ȃ�c
                // �c�^�X�N�g���C�̃A�C�R�����폜
                Shell_NotifyIcon(NIM_DELETE, &ni);
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
