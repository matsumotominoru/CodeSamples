// popup01.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("popup01");  // �E�B���h�E�N���X
HINSTANCE hInst;    // �C���X�^���X�n���h���iLoadMenu�֐��Ŏg���j

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;      // �C���X�^���X�n���h�����O���[�o���ϐ��ɕۊ�
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
    wc.lpfnWndProc = WndProc;          // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;              // �C���X�^���X
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
                    IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;            // ���j���[��
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩��|�b�v�A�b�v"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
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
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:         // �u�I���v�̏���
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_POPUP1:      // �u�|�b�v�A�b�v1�v�̏���
                    MessageBox(hWnd, TEXT("�|�b�v�A�b�v1�ł�"),
                        TEXT("Popup1"), MB_OK);
                    break;
                case IDM_POPUP2:      // �u�|�b�v�A�b�v2�v�̏���
                    MessageBox(hWnd, TEXT("�|�b�v�A�b�v2�ł�"),
                        TEXT("Popup2"), MB_OK);
                    break;
                default:
                    return (DefWindowProc(hWnd, msg, wp, lp));
            }
            break;
        case WM_RBUTTONDOWN:
            hMenu = LoadMenu(hInst, TEXT("MYPOPUP"));
            hSubMenu = GetSubMenu(hMenu, 0);  // �T�u���j���[�̃n���h�����擾

            pt.x = LOWORD(lp);  // �N���b�N�ʒu��x���W�i�N���C�A���g���W�j
            pt.y = HIWORD(lp);  // �N���b�N�ʒu��y���W�i�N���C�A���g���W�j
            ClientToScreen(hWnd, &pt);  // �X�N���[�����W�ɕϊ�

            // �T�u���j���[�̃n���h�����w�肵�āA�|�b�v�A�b�v���j���[��\��
            TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);

            DestroyMenu(hMenu);
            break;
        case WM_CLOSE:
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
