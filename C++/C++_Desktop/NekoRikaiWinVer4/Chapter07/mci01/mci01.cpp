// mci01.cpp

#define ID_PLAY 100            // PLAY�{�^���̎��ʎq
#define ID_STOP 101            // STOP�{�^���̎��ʎq

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

LPCTSTR lpszClassName = TEXT("mci01");    // �E�B���h�E�N���X
HINSTANCE hInst;                          // �C���X�^���X�n���h��

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;

    hInst = hCurInst;  // �O���[�o���ϐ�hInst�ɃC���X�^���X�n���h����ۊ�

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
            TEXT("�L�ł��킩��Windows�v���O���~���O"),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            128, 128,                     // ���ƍ����𐔒l�Ŏw��
            NULL, NULL, hInst,NULL);
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
    static MCI_OPEN_PARMS op;
    MCI_STATUS_PARMS sp;
    static HWND hPlay, hStop;
    static BOOL bPlay = FALSE;
    MCIERROR err;
    TCHAR szErr[1024];

    switch (msg) {
        case WM_CREATE:
            // CD�I�[�f�B�I�f�o�C�X���I�[�v��
            op.lpstrDeviceType = TEXT("cdaudio");
            err = mciSendCommand(NULL,
                MCI_OPEN, MCI_OPEN_TYPE | MCI_WAIT, (DWORD_PTR)&op);

            // �G���[����
            if (err != 0) {
                mciGetErrorString(err, szErr, (UINT)sizeof(szErr));
                MessageBox(hWnd, szErr, TEXT("�G���["), MB_OK);
                break;
            }

            hPlay = CreateWindow(TEXT("BUTTON"),  // PLAY�{�^�����쐬
                TEXT("PLAY"), WS_CHILD | WS_VISIBLE,
                10, 10, 100, 30, hWnd, (HMENU)ID_PLAY, hInst, NULL);
            hStop = CreateWindow(TEXT("BUTTON"),  // STOP�{�^�����쐬
                TEXT("STOP"), WS_CHILD | WS_VISIBLE,
                10, 50, 100, 30, hWnd, (HMENU)ID_STOP, hInst, NULL);
            EnableWindow(hStop, FALSE);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case ID_PLAY:        // PLAY�{�^���������ꂽ�Ƃ��̏���
                    // CD�̗L�����`�F�b�N
                    sp.dwItem = MCI_STATUS_MEDIA_PRESENT;
                    err = mciSendCommand(op.wDeviceID,
                        MCI_STATUS, MCI_STATUS_ITEM | MCI_WAIT,
                        (DWORD_PTR)&sp);

                    if (err != 0) {
                        mciGetErrorString(
                            err, szErr, (UINT)sizeof(szErr));
                        MessageBox(hWnd, szErr, TEXT("�G���["), MB_OK);
                        break;
                    }
                    if (!sp.dwReturn) {
                        MessageBox(hWnd,
                            TEXT("CD���Z�b�g����Ă��܂���"),
                            TEXT("�G���["), MB_OK);
                        break;
                    }

                    // CD���Đ�
                    err = mciSendCommand(op.wDeviceID, MCI_PLAY, 0, 0);
                    if (err != 0) {
                        mciGetErrorString(
                            err, szErr, (UINT)sizeof(szErr));
                        MessageBox(hWnd, szErr, TEXT("�G���["), MB_OK);
                        break;
                    }

                    EnableWindow(hPlay, FALSE);
                    EnableWindow(hStop, TRUE);
                    bPlay = TRUE;
                    break;
                case ID_STOP:        // STOP�{�^���������ꂽ�Ƃ��̏���
                    // CD�̍Đ����~
                    err = mciSendCommand(op.wDeviceID, MCI_STOP, 0, 0);
                    if (err != 0) {
                        mciGetErrorString(
                            err, szErr, (UINT)sizeof(szErr));
                        MessageBox(hWnd, szErr, TEXT("�G���["), MB_OK);
                        break;
                    }

                    EnableWindow(hPlay, TRUE);
                    EnableWindow(hStop, FALSE);
                    bPlay = FALSE;
                    break;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                TEXT("�I���m�F"), MB_YESNO);
            if (id == IDYES) {
                if (bPlay) {
                    // CD�̍Đ����~
                    mciSendCommand(op.wDeviceID, MCI_STOP, 0, 0);
                }
                // �f�o�C�X���N���[�Y
                mciSendCommand(op.wDeviceID, MCI_CLOSE, 0, 0);

                DestroyWindow(hPlay);    // PLAY�{�^����j��
                DestroyWindow(hStop);    // STOP�{�^����j��
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
