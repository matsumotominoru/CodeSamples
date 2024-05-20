// event01.cpp

#include <windows.h>

typedef struct _tagMyData {
    HWND hWnd;
    BOOL bEnd;
} MYDATA, *LPMYDATA;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
DWORD WINAPI ThFunc(LPVOID);
HFONT MyCreateFont(LPCTSTR, int);

LPCTSTR lpszClassName = TEXT("event01");    // �E�B���h�E�N���X
HANDLE hEvent;

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
    static DWORD dwThID;
    static MYDATA mydata;
    static HANDLE hTh;
    static BOOL bSignal = FALSE;

    switch (msg) {
        case WM_CREATE:
            // �C�x���g�I�u�W�F�N�g���쐬
            hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("MyEvent"));
            mydata.bEnd = FALSE;
            mydata.hWnd = hWnd;
            hTh = CreateThread(NULL, 0,    // �q�X���b�h���쐬
                (LPTHREAD_START_ROUTINE)ThFunc, &mydata, 0, &dwThID);
            break;
        case WM_LBUTTONDOWN:
            if (bSignal) {
                ResetEvent(hEvent);        // ��V�O�i����ԂɕύX
                bSignal = FALSE;
            } else {
                SetEvent(hEvent);          // �V�O�i����ԂɕύX
                bSignal = TRUE;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                TEXT("�I���m�F"), MB_YESNO);
            if (id == IDYES) {
                if (!bSignal)            // �V�O�i����ԂłȂ��ꍇ��
                    SetEvent(hEvent);    // �V�O�i����ԂɕύX����
                mydata.bEnd = TRUE;
                WaitForSingleObject(hTh, INFINITE);
                CloseHandle(hTh);        // �X���b�h�n���h����j��
                CloseHandle(hEvent);     // �C�x���g�I�u�W�F�N�g��j��
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

DWORD WINAPI ThFunc(LPVOID lpdata)
{
	LPMYDATA lpd;
	HWND hWnd;
	HDC hdc;
	SYSTEMTIME st;
	TCHAR szBuf[64];
	HFONT hFont;	

	lpd = (LPMYDATA)lpdata;
	hWnd = lpd->hWnd;

	hdc = GetDC(hWnd);
	hFont = MyCreateFont(TEXT("�l�r �S�V�b�N"), 48);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 0, 0));
	
	while (!lpd->bEnd) {
		Sleep(10);
		GetLocalTime(&st);
		wsprintf(szBuf, TEXT("%02d:%02d:%02d-%03d"),
			st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		TextOut(hdc, 10, 10, szBuf, lstrlen(szBuf));
		WaitForSingleObject(hEvent, INFINITE);
	}
	DeleteObject(hFont);
	ReleaseDC(hWnd, hdc);
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
