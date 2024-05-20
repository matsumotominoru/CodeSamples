// textout02.cpp �����I�Ăяo��

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

//�Ăяo�������֐��̌^��typedef���Ă����܂�
typedef BOOL (*LPFUNC)(HDC, int, int, LPCTSTR);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCTSTR lpszClassName = TEXT("textout02");	//�E�B���h�E�N���X


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
				   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

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
    wc.lpszMenuName = NULL;      // ���j���[��
    wc.lpszClassName = lpszClassName;
    wc.hIconSm = (HICON)LoadImage(NULL,
        MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(lpszClassName,
        TEXT("�L�ł��킩��Windows�v���O���~���O"), WS_OVERLAPPEDWINDOW,
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
    int id;
    HDC hdc;
    PAINTSTRUCT ps;
    LPCTSTR lpszStr = TEXT("�L�ł��킩��Windows�v���O���~���O");
    static HMODULE hLib;
    static LPFUNC lpFunc;

    switch (msg) {
        case WM_CREATE:
            hLib = LoadLibrary(TEXT("textoutdll.dll"));  // DLL�̓ǂݍ���
            if (hLib == NULL) {
                MessageBox(hWnd, TEXT("dll�ǂݍ��ݎ��s"),
                    TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
                SendMessage(hWnd, WM_CLOSE, 0, 0);
                return 0;
            }
            // MyTextOut�֐��̃|�C���^���擾
            lpFunc = (LPFUNC)GetProcAddress(hLib, "MyTextOut");
            if (lpFunc == NULL) {
                FreeLibrary(hLib);
                SendMessage(hWnd, WM_CLOSE, 0, 0);
                return 0;
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // DLL�̃G�N�X�|�[�g�֐��iMyTextOut�j�����s
            (*lpFunc)(hdc, 10, 10, lpszStr);
            EndPaint(hWnd, &ps);
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                TEXT("�I���m�F"), MB_YESNO);
            if (id == IDYES) {
                FreeLibrary(hLib);    // ���W���[���n���h����j��
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
