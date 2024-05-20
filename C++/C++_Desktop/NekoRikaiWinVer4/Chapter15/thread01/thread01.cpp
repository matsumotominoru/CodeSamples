// thread01.cpp

#include <windows.h>

typedef struct _tagMYDATA {
    HWND hWnd;
    HDC hdc_mem;
    BOOL bEnd;
} MYDATA;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
DWORD WINAPI MyThread(LPVOID);
HFONT MyCreateFont(LPCTSTR, int);

LPCTSTR lpszClassName = TEXT("thread01");    // �E�B���h�E�N���X
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
    wc.lpfnWndProc = WndProc;   //�v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;       //�C���X�^���X
    wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;    //���j���[��
    wc.lpszClassName = lpszClassName;
    wc.hIconSm = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
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
    static HANDLE hTh;
    static DWORD dwID;
    static MYDATA data;
    static HDC hdc_mem;
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_CREATE:
            data.hWnd = hWnd;
            data.bEnd = FALSE;
            hTh = CreateThread(          // �q�X���b�h���쐬
                NULL, 0, (LPTHREAD_START_ROUTINE)MyThread,
                (LPVOID)&data, 0, &dwID);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            BitBlt(hdc, 0, 0, 600, 400, data.hdc_mem, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                TEXT("�I���m�F"), MB_YESNO);
            if (id == IDYES) {
                data.bEnd = TRUE;
                WaitForSingleObject(     // �X���b�h�̏I����ҋ@
                    hTh, INFINITE);
                if (CloseHandle(hTh))    // �X���b�h�n���h����j��
                    MessageBox(hWnd,
                    TEXT("�X���b�h�n���h���N���[�Y���܂���"),
                    TEXT("�X���b�h�I��"), MB_OK);
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

DWORD WINAPI MyThread(LPVOID lpdata)
{
    MYDATA *lpmydata;
    HWND hWnd;
    HDC hdc, hdc_cat;
    HBITMAP hBmp, hBmpCat;
    SYSTEMTIME st;
    TCHAR szBuf[64];
    DWORD dwStart, dwEnd, dwMSec;
    HFONT hFont;
    lpmydata = (MYDATA *)lpdata;    // �������R�s�[

    hWnd = lpmydata->hWnd;
    lpmydata->hdc_mem = CreateCompatibleDC(NULL);

    hdc = GetDC(hWnd);
    hBmp = CreateCompatibleBitmap(hdc, 600, 400);
    hBmpCat = (HBITMAP)LoadImage(hInst,
        TEXT("MYBMP"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    hdc_cat = CreateCompatibleDC(NULL);
    SelectObject(hdc_cat, hBmpCat);
    SelectObject(lpmydata->hdc_mem, hBmp);
    ReleaseDC(hWnd, hdc);

    hFont = MyCreateFont(TEXT("�l�r �S�V�b�N"), 80);
    SelectObject(lpmydata->hdc_mem, hFont);

    SetTextColor(lpmydata->hdc_mem, RGB(255, 0, 0));
    SetBkMode(lpmydata->hdc_mem, TRANSPARENT);

    while (!lpmydata->bEnd) {
        timeBeginPeriod(40);
        dwStart = timeGetTime();
        timeEndPeriod(40);

        PatBlt(lpmydata->hdc_mem, 0, 0, 600, 400, WHITENESS);
        BitBlt(lpmydata->hdc_mem,
            0, 0, 600, 400, hdc_cat, 0, 0, SRCCOPY);

        GetLocalTime(&st);
        wsprintf(szBuf, TEXT("%02d:%02d:%02d"),
            st.wHour, st.wMinute, st.wSecond);
        TextOut(lpmydata->hdc_mem, 10, 10, szBuf, lstrlen(szBuf));

        InvalidateRect(hWnd, NULL, FALSE);
        timeBeginPeriod(40);
        dwEnd = timeGetTime();
        timeEndPeriod(40);

        dwMSec = dwEnd - dwStart;
        Sleep(40 - dwMSec);
    }
    DeleteObject(hBmp);
    DeleteObject(hFont);
    DeleteDC(lpmydata->hdc_mem);
    return 0;
}

HFONT MyCreateFont(LPCTSTR face, int h)
{
    HFONT hFont;
    hFont = CreateFont(h,         // �t�H���g����
        0,                        // ������
        0,                        // �e�L�X�g�̊p�x
        0,                        // �x�[�X���C����x���Ƃ̊p�x
        FW_BOLD,                  // �t�H���g�̏d���i�����j
        FALSE,                    // �C�^���b�N��
        FALSE,                    // �A���_�[���C��
        FALSE,                    // �ł�������
        SHIFTJIS_CHARSET,         // �����Z�b�g
        OUT_DEFAULT_PRECIS,       // �o�͐��x
        CLIP_DEFAULT_PRECIS,      // �N���b�s���O���x
        PROOF_QUALITY,            // �o�͕i��
        FIXED_PITCH | FF_MODERN,  // �s�b�`�ƃt�@�~���[
        face);                    // ���̖�
    return hFont;
}
