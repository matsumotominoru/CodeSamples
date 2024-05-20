// controls01.cpp

#include <windows.h>
#include <windowsx.h>        // �R���g���[���֘A�̃}�N�����g������
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("controls01");  // �E�B���h�E�N���X
HINSTANCE hInst;
TCHAR szText[6][64];
int nSex, nNation, n20, nPet, nAddress, nPos = 50;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;      // �C���X�^���X�n���h�����O���[�o���ϐ��ɕۊ�
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

    hWnd = CreateWindow(szClassName, TEXT("�L�ł��킩��R���g���[��"),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            270, 200, NULL, NULL, hInst, NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int n;
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            for (n = 0; n < 6; n++)
                TextOut(hdc, 10, 20 * n + 10, szText[n],
                        lstrlen(szText[n]));
            EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_DLG:
                    // �_�C�A���O�{�b�N�X��\������
                    DialogBox(hInst, TEXT("MYDLG"), hWnd,
                              (DLGPROC)MyDlgProc);
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

//�_�C�A���O�{�b�N�X�̃v���V�[�W��
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND hRadio1, hRadio2, hRadio3, hRadio4;
    static HWND hCheck1, hCombo1, hList1, hEdit1, hScrol1;
    TCHAR szBuf[64];
    TCHAR szList[5][16] = { TEXT("�����Ă��Ȃ�"), TEXT("��"),
                            TEXT("�L"), TEXT("�˂���"), TEXT("�n")};
    TCHAR szCombo[6][16] = { TEXT("�k�C��"), TEXT("�{�B"), TEXT("�l��"),
                             TEXT("��B"), TEXT("����"), TEXT("���̑�") };
    static HWND hMain;
    int id, n;
    BOOL bSuccess;

    switch (msg) {
        case WM_HSCROLL:        // �X�N���[���C�x���g�̏���
            if (lp != (LPARAM)hScrol1)
                return FALSE;
            switch (LOWORD(wp)) {
                case SB_LEFT:
                    nPos = 0;
                    break;
                case SB_RIGHT:
                    nPos = 100;
                    break;
                case SB_LINELEFT:
                    nPos--;
                    if (nPos < 0)   nPos = 0;
                    break;
                case SB_LINERIGHT:
                    nPos++;
                    if (nPos > 100) nPos = 100;
                    break;
                case SB_PAGELEFT:
                    nPos -= 10;
                    if (nPos > 100) nPos = 100;
                    break;
                case SB_PAGERIGHT:
                    nPos += 10;
                    if (nPos < 0)   nPos = 0;
                    break;
                case SB_THUMBTRACK:
                case SB_THUMBPOSITION:
                    nPos = HIWORD(wp);
                    break;
                
            }

            // �X�N���[���܂݂��ړ�������
            ScrollBar_SetPos(hScrol1, nPos, TRUE);

            wsprintf(szBuf, TEXT("%03d"), nPos);
            Edit_SetText(hEdit1, szBuf);
            wsprintf(szText[5],
                TEXT("�X�N���[���o�[�̈ʒu=%03d"), nPos);
            InvalidateRect(hMain, NULL, TRUE);
            return TRUE;
        case WM_INITDIALOG:
            //�e�E�B���h�E�̃n���h���擾
            hMain = GetParent(hDlg);
            //�e�R���g���[���̃n���h�����擾
            hRadio1 = GetDlgItem(hDlg, IDC_RADIO1);
            hRadio2 = GetDlgItem(hDlg, IDC_RADIO2);
            hRadio3 = GetDlgItem(hDlg, IDC_RADIO3);
            hRadio4 = GetDlgItem(hDlg, IDC_RADIO4);
            hCheck1 = GetDlgItem(hDlg, IDC_CHECK1);
            hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
            hList1 = GetDlgItem(hDlg, IDC_LIST1);
            hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
            hScrol1 = GetDlgItem(hDlg, IDC_SCROLLBAR1);
            //�X�N���[���o�[�̏����ݒ�
            ScrollBar_SetRange(hScrol1, 0, 100, TRUE);
            ScrollBar_SetPos(hScrol1, nPos, TRUE);
            //���W�I�O���[�v�̏����ݒ�
            if (nSex == 0)
                Button_SetCheck(hRadio1, BST_CHECKED);
            else
                Button_SetCheck(hRadio2, BST_CHECKED);
            if (nNation == 0)
                Button_SetCheck(hRadio3, BST_CHECKED);
            else
                Button_SetCheck(hRadio4, BST_CHECKED);
            //�`�F�b�N�{�b�N�X�̐ݒ�
            if (n20 == 1)
                Button_SetCheck(hCheck1, BST_CHECKED);
            else
                Button_SetCheck(hCheck1, BST_UNCHECKED);
            //�R���{�{�b�N�X�ɕ������������
            for (n = 0; n < 6; n++)
                ComboBox_AddString(hCombo1, szCombo[n]);
            //���X�g�{�b�N�X�ɕ������������
            for (n = 0; n < 5; n++)
                ListBox_AddString(hList1, szList[n]);
            //�R���{�{�b�N�X�̏����l
            ComboBox_SetCurSel(hCombo1, nAddress);
            ListBox_SetCurSel(hList1, nPet);
            wsprintf(szBuf, TEXT("%03d"), nPos);
            Edit_SetText(hEdit1, szBuf);
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDCANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
                case IDOK:
                    if (nSex == 0)
                        lstrcpy(szText[0], TEXT("�j���I������܂���"));
                    else
                        lstrcpy(szText[0], TEXT("�����I������܂���"));
                    if (nNation == 0)
                        lstrcpy(szText[1], TEXT("���{���I������܂���"));
                    else
                        lstrcpy(szText[1], 
                        TEXT("���{�ȊO���I������܂���"));
                    if (n20 == 0)
                        lstrcpy(szText[2], TEXT("20�Ζ����ł�"));
                    else
                        lstrcpy(szText[2], TEXT("20�Έȏ�ł�"));
                    wsprintf(szText[3], TEXT("%s���I������܂���"),
                             szCombo[nAddress]);
                    wsprintf(szText[4], TEXT("%s���I������܂���"),
                             szList[nPet]);
                    wsprintf(szText[5],
                             TEXT("�X�N���[���o�[�̈ʒu=%03d"), nPos);
                    InvalidateRect(hMain, NULL, TRUE);
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                case IDC_RADIO1:
                    nSex = 0;
                    lstrcpy(szText[0], TEXT("�j���I������܂���"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_RADIO2:
                    nSex = 1;
                    lstrcpy(szText[0], TEXT("�����I������܂���"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_RADIO3:
                    nNation = 0;
                    lstrcpy(szText[1], TEXT("���{���I������܂���"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_RADIO4:
                    nNation = 1;
                    lstrcpy(szText[1], TEXT("���{�ȊO���I������܂���"));
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_CHECK1:
                    if (Button_GetCheck(hCheck1) == BST_CHECKED) {
                        n20 = 1;
                        lstrcpy(szText[2], TEXT("20�Έȏ�ł�"));
                    } else {
                        n20 = 0;
                        lstrcpy(szText[2], TEXT("20�Ζ����ł�"));
                    }
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
                case IDC_COMBO1:
                    id = ComboBox_GetCurSel(hCombo1);
                    wsprintf(szText[3],
                             TEXT("%s���I������܂���"), szCombo[id]);
                    InvalidateRect(hMain, NULL, TRUE);
                    nAddress = id;
                    return TRUE;
                case IDC_LIST1:
                    id = ListBox_GetCurSel(hList1);
                    wsprintf(szText[4],
                             TEXT("%s���I������܂���"), szList[id]);
                    InvalidateRect(hMain, NULL, TRUE);
                    nPet = id;
                    return TRUE;
                case IDC_EDIT1:
                    nPos = GetDlgItemInt(
                        hDlg, IDC_EDIT1, &bSuccess, FALSE);
                    if (nPos > 100)
                        nPos = 100;
                    if (nPos < 0)
                        nPos = 0;
                    ScrollBar_SetPos(hScrol1, nPos, TRUE);
                    wsprintf(szText[5],
                             TEXT("�X�N���[���o�[�̈ʒu=%03d"), nPos);
                    InvalidateRect(hMain, NULL, TRUE);
                    return TRUE;
            }
            return FALSE;
    }
    return FALSE;
}
