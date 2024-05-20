// memo01.cpp

#define ID_EDIT 100
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
int MyNew(HWND);
int MyOpen(HWND);
int MySave(HWND);
int MySaveAs(HWND);
int MyConfirm(HWND);

TCHAR szClassName[] = TEXT("memo01");   // �E�B���h�E�N���X
HINSTANCE hInst;                        // �C���X�^���X�n���h��
TCHAR szTitle[128] = TEXT("�L�ł��킩�郁�������ǂ�");
TCHAR szTitle_org[] = TEXT("�L�ł��킩�郁�������ǂ�[%s](%d�o�C�g)");
TCHAR szFile[MAX_PATH];
TCHAR szFileTitle[MAX_PATH];

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
    wc.lpfnWndProc = WndProc;    // �v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;        // �C���X�^���X
    wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW),
        IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = TEXT("MYMENU");
    wc.lpszClassName = szClassName;
    wc.hIconSm = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION),
        IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

    return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName, szTitle, WS_OVERLAPPEDWINDOW,
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
    static HWND hEdit;

    switch (msg) {
        case WM_CREATE:
            // �G�f�B�b�g�R���g���[�����쐬
            hEdit = CreateWindow(TEXT("EDIT"), NULL,
                WS_CHILD | WS_VISIBLE | ES_WANTRETURN |
                ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL |
                ES_AUTOHSCROLL | WS_HSCROLL,
                0, 0, 0, 0, hWnd, (HMENU)ID_EDIT, hInst, NULL);
            lstrcat(szTitle, TEXT("[����]"));
            SetWindowText(hWnd, szTitle);
            Edit_LimitText(hEdit, 0);
            break;
        case WM_SIZE:
            // �E�B���h�E�T�C�Y�𒲐�
            MoveWindow(hEdit, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_NEW:
                    MyNew(hEdit);
                    break;
                case IDM_OPEN:
                    MyOpen(hEdit);
                    break;
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_SAVE:
                    MySave(hEdit);
                    break;
                case IDM_SAVEAS:
                    MySaveAs(hEdit);
                    break;
            }
            break;
        case WM_SETFOCUS:
            SetFocus(hEdit);  // �G�f�B�b�g�R���g���[���Ƀt�H�[�J�X��ݒ�
            break;
        case WM_CLOSE:
            id = MyConfirm(hEdit);
            if (id == IDCANCEL)
                break;
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                            TEXT("�m�F"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                DestroyWindow(hEdit);  // �G�f�B�b�g�R���g���[����j��
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

int MyNew(HWND hEdit)
{
    int id;
    id = MyConfirm(hEdit);
    if (id == IDCANCEL) {
        return -1;
    }
    Edit_SetText(hEdit, TEXT(""));
    SetWindowText(GetParent(hEdit),
                  TEXT("�L�ł��킩�郁�������ǂ�[����]"));
    lstrcpy(szFile, TEXT(""));
    return 0;
}

int MyOpen(HWND hEdit)
{
    int id;
    HWND hMain;
    DWORD dwSize = 0L;
    OPENFILENAME ofn;
    HANDLE hFile;
    DWORD dwAccBytes;
    LPTSTR lpszBuf;

    HGLOBAL hMem;

    id = MyConfirm(hEdit);
    if (id == IDCANCEL)
        return -1;

    // OPENFILENAME�\���̂�ݒ�
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hEdit;
    ofn.lpstrFilter =
        TEXT("text(*.txt)\0*.txt\0All files(*.*)\0*.*\0\0");
    ofn.lpstrFile = szFile;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = TEXT("txt");
    ofn.lpstrTitle = TEXT("�L�ł��킩��t�@�C���I�[�v��");

    if(GetOpenFileName(&ofn) == 0)  // �u�t�@�C�����J���v�_�C�A���O
        return -1;

    hFile = CreateFile(szFile,  // �t�@�C����
        GENERIC_READ,           // �ǂݎ��/�������݃A�N�Z�X
        0,                      // ���L�ݒ� 0���Ƌ��L�ΏۂƂ��Ȃ�
        NULL,                   // �Z�L�����e�B����
        OPEN_ALWAYS,            // �t�@�C�������łɑ��݂��Ă��邩�ǂ���
        FILE_ATTRIBUTE_NORMAL,  // �t�@�C������
        NULL);
    dwSize = GetFileSize(hFile, NULL);  // �t�@�C���T�C�Y���擾

    // �������𓮓I�Ɋm��
    hMem = GlobalAlloc(GHND, dwSize + sizeof(TCHAR));
    if (hMem == NULL) {
        MessageBox(hEdit, TEXT("���������m�ۂł��܂���"),
                   TEXT("�L�ł��킩�郁�������ǂ�"),
                   MB_ICONEXCLAMATION | MB_OK);
        return -1;
    }
    lpszBuf = (LPTSTR)GlobalLock(hMem);

    // �t�@�C����ǂݍ��݁A�G�f�B�b�g�R���g���[���ɕ\������
    ReadFile(hFile, lpszBuf, dwSize, &dwAccBytes, NULL);
    lpszBuf[dwAccBytes] = TEXT('\0');
    Edit_SetText(hEdit, lpszBuf);

    // �^�C�g���o�[�̐ݒ�
    wsprintf(szTitle, szTitle_org, szFileTitle, dwSize);
    hMain = GetParent(hEdit);
    SetWindowText(hMain, szTitle);

    CloseHandle(hFile);
    GlobalUnlock(hMem);
    GlobalFree(hMem);

    return 0;
}

int MySaveAs(HWND hEdit)
{
    OPENFILENAME ofn;
    HANDLE hFile;
    DWORD dwAccBytes;

    LPTSTR lpszBuf;
    int nLen;
    HGLOBAL hMem;

    // �G�f�B�b�g�R���g���[���ɏ������܂�Ă��镶�������擾���A
    // ����Ɍ������������𓮓I�Ɋm��
    nLen = GetWindowTextLength(hEdit);
    hMem = GlobalAlloc(GHND, sizeof(TCHAR) * (nLen + 1));
    lpszBuf = (LPTSTR)GlobalLock(hMem);

    // �G�f�B�b�g�R���g���[���̓��e��lpszBuf�ɕۊ�
    GetWindowText(hEdit, lpszBuf, nLen + 1);

    // OPENFILENAME�\���̂�ݒ�
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hEdit;
    ofn.lpstrFilter =
        TEXT("text(*.txt)\0*.txt\0All files(*.*)\0*.*\0\0");
    ofn.lpstrFile = szFile;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nFilterIndex = 1;
    ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = TEXT("txt");
    ofn.lpstrTitle = TEXT("���O��t���ĕۑ�����");

    if(GetSaveFileName(&ofn) == 0)  // �u�t�@�C����ۑ��v�_�C�A���O
        return -1;

    // �t�@�C����lpszBuf�̓��e����������
    hFile = CreateFile(szFile, GENERIC_WRITE, 0, NULL,
                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hFile, lpszBuf, (DWORD)lstrlen(lpszBuf),
              &dwAccBytes, NULL);

    // �^�C�g���o�[�̐ݒ�
    wsprintf(szTitle, szTitle_org, szFileTitle, nLen);
    SetWindowText(GetParent(hEdit), szTitle);

    if(CloseHandle(hFile) == 0)
        MessageBox(hEdit, TEXT("Error CloseHandle"),
                   TEXT("Error"), MB_OK);

    // �G�f�B�b�g�R���g���[���̕ύX�t���O��FALSE�ɐݒ�
    SendMessage(hEdit, EM_SETMODIFY, FALSE, 0);

    GlobalUnlock(hMem);
    GlobalFree(hMem);

    return 0;
}

int MySave(HWND hEdit)
{
    HANDLE hFile;
    DWORD dwAccBytes;
    int nLen;
    LPTSTR lpszBuf;
    HGLOBAL hMem;

    if (lstrcmp(szFile, TEXT("") ) == 0) {
        MessageBox(hEdit, TEXT("�t�@�C�������t�����Ă��܂���"),
                   TEXT("�L�ł��킩�郁�������ǂ�"), MB_OK);
        MySaveAs(hEdit);
        return -1;
    }

    // �G�f�B�b�g�R���g���[���ɏ������܂�Ă��镶�������擾���A
    // ����Ɍ������������𓮓I�Ɋm��
    nLen = GetWindowTextLength(hEdit);
    hMem = GlobalAlloc(GHND, nLen + sizeof(TCHAR));
    lpszBuf = (LPTSTR)GlobalLock(hMem);

    // �G�f�B�b�g�R���g���[���̓��e��lpszBuf�ɕۊ�
    GetWindowText(hEdit, lpszBuf, nLen + 1);

    // �t�@�C����lpszBuf�̓��e����������
    hFile = CreateFile(szFile, GENERIC_WRITE, 0, NULL,
                TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hFile, lpszBuf, (DWORD)lstrlen(lpszBuf),
              &dwAccBytes, NULL);

    GlobalUnlock(hMem);
    GlobalFree(hMem);

    // �G�f�B�b�g�R���g���[���̕ύX�t���O��FALSE�ɐݒ�
    SendMessage(hEdit, EM_SETMODIFY, FALSE, 0);

    wsprintf(szTitle, szTitle_org, szFileTitle, nLen);
    SetWindowText(GetParent(hEdit), szTitle);
    if (CloseHandle(hFile) == 0) {
        MessageBox(hEdit, TEXT("Error CloseHandle"),
                   TEXT("Error"), MB_OK);
        return -1;
    }

    return 0;
}

int MyConfirm(HWND hEdit)
{
    int id;

    if (SendMessage(hEdit, EM_GETMODIFY, 0, 0) == TRUE) {
        id = MessageBox(hEdit,
            TEXT("�������X�V����Ă��܂��B\n�ύX��ۑ����܂���?"),
            TEXT("�L�ł��킩�郁�������ǂ�"),
            MB_YESNOCANCEL | MB_ICONEXCLAMATION);
        if (id == IDYES) {
            MySave(hEdit);
        } else if (id == IDCANCEL) {
            return IDCANCEL;
        } else if (id ==  IDNO) {
            return IDNO;
        }
    }
    return 0;
}
