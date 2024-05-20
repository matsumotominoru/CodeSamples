// toolbar01.cpp

#define ID_TOOLBAR 100

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HWND MyCreateToolbar(HWND);

TCHAR szClassName[] = TEXT("toolbar01");  // �E�B���h�E�N���X
int nType = 0;    // 0:���^�C�v 1:�t���b�g�^�C�v 2:�����^�C�v

// ���̂悤�ɏ���������Ƃ���
// �o�[�W�����ɂ��TBBUTTON�\���̂̑傫���ɒ���
TBBUTTON tbb[] = {
    { 0, IDM_MARU,    TBSTATE_ENABLED, BTNS_BUTTON },
    { 1, IDM_SANKAKU, TBSTATE_ENABLED, BTNS_BUTTON },
    { 2, IDM_SHIKAKU, TBSTATE_ENABLED, BTNS_BUTTON },
};

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

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩��c�[���o�["),
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
    INITCOMMONCONTROLSEX cc;
    static HWND hTool;
    LONG lStyle;
    MENUITEMINFO mi;
    static HMENU hMenu;

    switch (msg) {
        case WM_CREATE:
            hMenu = GetMenu(hWnd);          // ���j���[�n���h�����擾
            cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
            cc.dwICC = ICC_BAR_CLASSES;
            InitCommonControlsEx(&cc);      // �R�����R���g���[����������
            hTool = MyCreateToolbar(hWnd);  // �c�[���o�[���쐬
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_MARU:
                    MessageBox(hWnd, TEXT("�ۂ��I������܂���"),
                               TEXT("�I�v�V����"), MB_OK);
                    break;
                case IDM_SANKAKU:
                    MessageBox(hWnd, TEXT("�O�p���I������܂���"),
                               TEXT("�I�v�V����"), MB_OK);
                    break;
                case IDM_SHIKAKU:
                    MessageBox(hWnd, TEXT("�l�p���I������܂���"),
                               TEXT("�I�v�V����"), MB_OK);
                    break;
                case IDM_OLD:
                    // �u���^�C�v�v�̃c�[���o�[�ɕύX
                    lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
                    lStyle = lStyle & ~TBSTYLE_FLAT &
                             ~TBSTYLE_TRANSPARENT;
                    SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
                    InvalidateRect(hTool, NULL, TRUE);
                    nType = 0;
                    break;
                case IDM_FLAT:
                    // �u�t���b�g�^�C�v�v�̃c�[���o�[�ɕύX
                    lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
                    lStyle = (lStyle | TBSTYLE_FLAT) &
                             ~TBSTYLE_TRANSPARENT;
                    SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
                    InvalidateRect(hTool, NULL, TRUE);
                    nType = 1;
                    break;
                case IDM_TRANSPARENT:
                    // �u�����^�C�v�v�̃c�[���o�[�ɕύX
                    lStyle = GetWindowLongPtr(hTool, GWL_STYLE);
                    lStyle = lStyle | TBSTYLE_FLAT |
                             TBSTYLE_TRANSPARENT;
                    SetWindowLongPtr(hTool, GWL_STYLE, lStyle);
                    InvalidateRect(hTool, NULL, TRUE);
                    nType = 2;
            }
            break;
        case WM_SIZE:
            // SendMessage(hTool, msg, wp, lp);�𑗂��Ă��悢
            SendMessage(hTool, TB_AUTOSIZE, 0, 0);
            break;
        case WM_INITMENU:
            mi.cbSize = sizeof(MENUITEMINFO);
            mi.fMask = MIIM_STATE;
            switch (nType) {
                case 0:
                    mi.fState = MFS_CHECKED;
                    SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
                    mi.fState = MFS_UNCHECKED;
                    SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
                    SetMenuItemInfo(hMenu, IDM_TRANSPARENT,
                                    FALSE, &mi);
                    break;
                case 1:
                    mi.fState = MFS_CHECKED;
                    SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
                    mi.fState = MFS_UNCHECKED;
                    SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
                    SetMenuItemInfo(hMenu, IDM_TRANSPARENT,
                                    FALSE, &mi);
                    break;
                case 2:
                    mi.fState = MFS_CHECKED;
                    SetMenuItemInfo(hMenu, IDM_TRANSPARENT,
                                    FALSE, &mi);
                    mi.fState = MFS_UNCHECKED;
                    SetMenuItemInfo(hMenu, IDM_OLD, FALSE, &mi);
                    SetMenuItemInfo(hMenu, IDM_FLAT, FALSE, &mi);
                    break;
            }
            DrawMenuBar(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

HWND MyCreateToolbar(HWND hWnd)
{
    HINSTANCE hInst;
    HWND hTool;

    // �C���X�^���X�n���h�����擾
    hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);

    hTool = CreateToolbarEx(
        hWnd,                   // �e�E�B���h�E
        WS_CHILD | WS_VISIBLE,  // �E�B���h�E�X�^�C��
        ID_TOOLBAR,             // �R���g���[��ID
        3,                      // �C���[�W�̐�
        hInst,                  // �C���X�^���X�n���h��
        IDR_TOOLBAR1,           // �c�[���o�[��ID
        tbb,                    // TBBUTTON�\����
        3,                      // �{�^���̐�
        0,                      // �{�^���̕�
        0,                      // �{�^���̍���
        0,                      // �C���[�W�̕�
        0,                      // �C���[�W�̍���
        sizeof(TBBUTTON));
    return hTool;
}