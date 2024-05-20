// printer01.cpp

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyPrint(HWND);

TCHAR szClassName[] = TEXT("printer01");  // �E�B���h�E�N���X

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

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩��v�����^"),
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
    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_PRINT:
                    MyPrint(hWnd);    // ����p�̊֐����Ăяo��
                    break;
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


int MyPrint(HWND hWnd)
{
    int i;
    PRINTDLG pd;
    DOCINFO di;
    TEXTMETRIC tm;

    LPTSTR lpszBuf = TEXT("�������������܂�");

    // PRINTDLG�\���̂̐ݒ�
    memset(&pd, 0, sizeof(PRINTDLG));

    pd.lStructSize = sizeof(PRINTDLG);
    pd.hwndOwner = hWnd;
    pd.hDevMode = NULL;
    pd.hDevNames = NULL;
    pd.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC |
        PD_NOPAGENUMS | PD_NOSELECTION | PD_HIDEPRINTTOFILE;

    pd.nMinPage = 1;
    pd.nMaxPage = 1;
    pd.nFromPage = 1;
    pd.nToPage = 1;
    pd.nCopies = 1;

    // �u����v�_�C�A���O��\��
    if (PrintDlg(&pd) == 0)
        return -1;

    // DOCINFO�\���̂̐ݒ�
    memset(&di, 0, sizeof(DOCINFO));
    di.cbSize = sizeof(DOCINFO);
    di.lpszDocName = TEXT("Test");

    // ����W���u
    StartDoc(pd.hDC, &di);        // ����W���u���J�n
    StartPage(pd.hDC);            // �v�����^�h���C�o�ɏ�����v��
    GetTextMetrics(pd.hDC, &tm);  // �t�H���g�̏����擾
    for (i = 0; i < 10; i++) {
        SetTextColor(pd.hDC, RGB(255, 0, 0));
        // �f�o�C�X�R���e�L�X�g�ɕ��������������
        TextOut(pd.hDC, 10, 10 + (tm.tmHeight * i + 20),
                lpszBuf, lstrlen(lpszBuf));
    }
    EndPage(pd.hDC);              // �������݊������f�o�C�X�ɒʒm
    EndDoc(pd.hDC);               // ����W���u���I��
    DeleteDC(pd.hDC);             // �f�o�C�X�R���e�L�X�g��j��

    return 0;
}
