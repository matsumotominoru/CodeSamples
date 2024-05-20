// menu02.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("menu02");   // �E�B���h�E�N���X
HWND hParent;                           // �e�E�B���h�E�̃n���h��

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;
    HACCEL hAccel;                      // �A�N�Z�����[�^�n���h��

    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow))
        return FALSE;

    // �A�N�Z�����[�^�e�[�u����ǂݍ���
    hAccel = LoadAccelerators(hCurInst, TEXT("MYACCEL"));

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
            break;
        } else {
            if (!TranslateAccelerator(hParent, hAccel, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
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
    wc.lpfnWndProc = WndProc;          // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;              // �C���X�^���X
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
                    IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = TEXT("MYMENU");  // ���j���[��
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩�郁�j���["),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    hParent = hWnd;  // �O���[�o���ϐ��ɃE�B���h�E�n���h�����i�[
    return TRUE;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;

    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:         // �u�I���v�̏���
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_ABOUT:       // �uAbout�v�̏���
                    MessageBox(hWnd, TEXT("Copyright(C) 2012 Y.Kumei"),
                               TEXT("About"), MB_OK);
                    break;
                case IDM_OPT1:        // �u�I�v�V����1�v�̏���
                    MessageBox(hWnd, TEXT("�I�v�V����1�ł�"),
                               TEXT("Option1"), MB_OK);
                    break;
                case IDM_OPT2:        // �u�I�v�V����2�v�̏���
                    MessageBox(hWnd, TEXT("�I�v�V����2�ł�"),
                               TEXT("Option2"), MB_OK);
                    break;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                            TEXT("�m�F"), MB_YESNO | MB_ICONQUESTION);
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
