// controls02.cpp

#define ID_BUTTON 100
#define ID_EDIT 101

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("controls02");  // �E�B���h�E�N���X
HINSTANCE hInst;

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

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩��R���g���[��"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, 230, 125, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// �E�B���h�E�v���V�[�W��
#include <windowsx.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    static HWND hBtn, hEdit;
    TCHAR szBuf[64];

    switch (msg) {
        case WM_CREATE:
            // �G�f�B�b�g�R���g���[�����쐬
            hEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                10, 10, 200, 25, hWnd, (HMENU)ID_EDIT, hInst, NULL);
            // �{�^�����쐬
            hBtn = CreateWindow(TEXT("BUTTON"), TEXT("����"),
                WS_CHILD | WS_VISIBLE,  85, 45, 50, 30,
                hWnd, (HMENU)ID_BUTTON, hInst, NULL);
            // �G�f�B�b�g�R���g���[���Ƀt�H�[�J�X��^����
            SendMessage(hEdit, EM_SETLIMITTEXT, (WPARAM)63, 0);
            break;
        case WM_SETFOCUS:
            SetFocus(hEdit);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case ID_BUTTON:
                    GetWindowText(hEdit, szBuf, 64);
                    MessageBox(hWnd, szBuf,
                            TEXT("�L�ł��킩��R���g���[��"), MB_OK);
                    SetWindowText(hEdit, TEXT(""));
                    break;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd,
                TEXT("�I�����Ă���낵���ł���"),
                TEXT("�m�F"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                DestroyWindow(hEdit);
                DestroyWindow(hBtn);
                DestroyWindow(hWnd);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}
