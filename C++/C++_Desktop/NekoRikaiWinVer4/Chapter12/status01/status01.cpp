// status01.cpp

#define MY_STATUS 100                    // �X�e�[�^�X�o�[��ID
#include <windows.h>
#include <commctrl.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND MyCreateStatusbar(HWND hWnd);

TCHAR szClassName[] = TEXT("status01");  // �E�B���h�E�N���X
HINSTANCE hInst;                         // �C���X�^���X�n���h��

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
    wc.lpfnWndProc = WndProc;  // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;      // �C���X�^���X
    wc.hIcon = NULL;
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;    // ���j���[��
    wc.lpszClassName = szClassName;
    wc.hIconSm = NULL;

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩��X�e�[�^�X�o�["),
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
    INITCOMMONCONTROLSEX ic;
    static HWND hStatus;

    switch (msg) {
        case WM_CREATE:
            // �R�����R���g���[����������
            ic.dwICC = ICC_BAR_CLASSES;
            ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
            InitCommonControlsEx(&ic);
            // �X�e�[�^�X�o�[���쐬
            hStatus = MyCreateStatusbar(hWnd);
            break;
        case WM_SIZE:
            SendMessage(hStatus, msg, wp, lp);
            break;
        case WM_DESTROY:
            DestroyWindow(hStatus);
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

HWND MyCreateStatusbar(HWND hWnd)
{
    HWND hStatus;

    hStatus = CreateWindowEx(
        0,                  //�g���X�^�C��
        STATUSCLASSNAME,    //�E�B���h�E�N���X
        NULL,               //�^�C�g��
        // �E�B���h�E�X�^�C��
        //   WS_VISIBLE���w�肵�Ȃ��Ƃ��͕K��ShowWindow�֐����Ă�
        WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM | WS_VISIBLE,
        0, 0, 0, 0,         // x���W, y���W, �E�B���h�E��, ����
        hWnd,               //�e�E�B���h�E
        (HMENU)MY_STATUS,   //�X�e�[�^�X�o�[��ID
        hInst,              //�C���X�^���X�n���h��
        NULL);
    SendMessage(hStatus, SB_SIMPLE, 0, 0);
	SendMessage(hStatus, SB_SETTEXT, 0 | 0,
                (LPARAM)TEXT("�L�ł��킩��X�e�[�^�X�o�["));
    return hStatus;
}
