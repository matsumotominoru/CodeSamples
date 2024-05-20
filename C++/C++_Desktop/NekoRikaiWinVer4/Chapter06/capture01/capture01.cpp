// capture01.cpp

#define BMPW 300
#define BMPH 50

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCTSTR lpszClassName = TEXT("capture01");     // �E�B���h�E�N���X

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
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
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
    static int mousex, mousey;
    HDC hdc;
    static HDC hdc_mem;
    HBITMAP hBmp;
    PAINTSTRUCT ps;
    TCHAR szBuf[64], szUmu[8],
          szFormat[] = TEXT("(x = %d, y = %d) Capture = %s");
    static BOOL bCap;
    POINTS pts;

    switch (msg) {
        case WM_CREATE:
            hdc = GetDC(hWnd);
            hdc_mem = CreateCompatibleDC(NULL);
            hBmp = CreateCompatibleBitmap(hdc, BMPW, BMPH);
            SelectObject(hdc_mem, hBmp);
            PatBlt(hdc_mem, 0, 0, BMPW, BMPH, WHITENESS);
            wsprintf(szBuf, szFormat, 0, 0, TEXT("����"));
            TextOut(hdc_mem, 10, 10, szBuf, lstrlen(szBuf));

            ReleaseDC(hWnd, hdc);    // �f�o�C�X�R���e�L�X�g��j��
            DeleteObject(hBmp);      // �r�b�g�}�b�v��j��
            break;
        case WM_LBUTTONDOWN:
            if (!bCap) {
                SetCapture(hWnd);    // �L���v�`���J�n
                bCap = TRUE;
            }
            pts.x = LOWORD(lp);      // �}�E�X�ʒu��x���W
            pts.y = HIWORD(lp);      // �}�E�X�ʒu��y���W
            wsprintf(szBuf, szFormat, pts.x, pts.y, TEXT("�L��"));
            PatBlt(hdc_mem, 0, 0, BMPW, BMPH, WHITENESS);
            TextOut(hdc_mem, 10, 10, szBuf, lstrlen(szBuf));
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case WM_LBUTTONUP:
            if (bCap) {
                ReleaseCapture();    // �L���v�`���I��
                bCap = FALSE;
            }
            pts.x = LOWORD(lp);      // �}�E�X�ʒu��x���W
            pts.y = HIWORD(lp);      // �}�E�X�ʒu��y���W

            wsprintf(szBuf, szFormat, pts.x, pts.y, TEXT("����"));
            PatBlt(hdc_mem, 0, 0, BMPW, BMPH, WHITENESS);
            TextOut(hdc_mem, 10, 10, szBuf, lstrlen(szBuf));
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case WM_MOUSEMOVE:
            pts.x = LOWORD(lp);      // �}�E�X�ʒu��x���W
            pts.y = HIWORD(lp);      // �}�E�X�ʒu��y���W
            if (bCap)
                lstrcpy(szUmu, TEXT("�L��"));
            else
                lstrcpy(szUmu, TEXT("����"));

            wsprintf(szBuf, szFormat, pts.x, pts.y, szUmu);
            PatBlt(hdc_mem, 0, 0, BMPW, BMPH, WHITENESS);
            TextOut(hdc_mem, 10, 10, szBuf, lstrlen(szBuf));
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            BitBlt(hdc, 0, 0, BMPW, BMPH, hdc_mem, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                TEXT("�m�F"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES)
                DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            DeleteDC(hdc_mem);
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}
