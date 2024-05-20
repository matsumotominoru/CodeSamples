// clock01.cpp

#include <windows.h>
#define ID_MYTIMER 100    // �^�C�}�[ID

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HFONT MyCreateFont(int, DWORD, LPCTSTR);

TCHAR szClassName[] = TEXT("clock01");    // �E�B���h�E�N���X

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
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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

    hWnd = CreateWindow(szClassName, TEXT(""),
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 148, 82,
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
    static TCHAR szTime[64], szDate[64];
    SYSTEMTIME st;
    HFONT hFont1, hFont2;

    switch (msg) {
        case WM_CREATE:
            SetTimer(hWnd, ID_MYTIMER, 500, NULL);  // �^�C�}�[���쐬
            break;
        case WM_TIMER:
            // �֌W�Ȃ��^�C�}�[�C�x���g��DefWindowProc�ɔC����
            if (wp != ID_MYTIMER)
                return (DefWindowProc(hWnd, msg, wp, lp));

            GetLocalTime(&st);    // ���݂̓������擾
            wsprintf(szTime, TEXT("%02d:%02d:%02d"), st.wHour,
                     st.wMinute, st.wSecond);
            wsprintf(szDate, TEXT("%d�N%02d��%02d��"), st.wYear,
                     st.wMonth, st.wDay);

            // �N���C�A���g�̈�S�̂��X�V
            InvalidateRect(hWnd, NULL, TRUE);
            // �^�C�g���o�[�Ɏ�����\���������ݒ�
            SetWindowText(hWnd, szTime);
            break;
        case WM_LBUTTONDBLCLK:
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            hFont1 = MyCreateFont(12, SHIFTJIS_CHARSET,
                                  TEXT("�l�r �S�V�b�N"));
            SelectObject(hdc, hFont1);
            TextOut(hdc, 5, 5, szDate, lstrlen(szDate));
            hFont2 = MyCreateFont(30, ANSI_CHARSET,
                                  TEXT("�l�r �S�V�b�N"));
            SelectObject(hdc, hFont2);
            SetTextColor(hdc, RGB(0, 0, 255));
            TextOut(hdc, 10, 20, szTime, lstrlen(szTime));
            DeleteObject(hFont1);
            DeleteObject(hFont2);
            EndPaint(hWnd, &ps);
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                TEXT("�m�F"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                // �^�C�}�[��j��
                if (KillTimer(hWnd, ID_MYTIMER) == 0) {
                    MessageBox(hWnd, TEXT("KillTimer Error!"),
                        TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
                }
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

HFONT MyCreateFont(int nHeight, DWORD dwCharSet, LPCTSTR lpName)
{
	return(	CreateFont(nHeight, 0, 0, 0,
				FW_DONTCARE,
				FALSE, FALSE, FALSE,
				dwCharSet,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				lpName));
}