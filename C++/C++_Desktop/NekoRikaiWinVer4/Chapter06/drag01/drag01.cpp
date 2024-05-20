// drag01.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
BOOL MyAdjustWindow(HWND, int, int);

LPCTSTR lpszClassName = TEXT("drag01");    // �E�B���h�E�N���X
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
	wc.lpfnWndProc = WndProc;	//�v���V�[�W����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//�C���X�^���X
	wc.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;	//���j���[��
	wc.lpszClassName = lpszClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(lpszClassName,
			TEXT("�L�ł��킩��Windows�v���O���~���O"), //�^�C�g���o�[�ɕ\������܂�
			WS_OVERLAPPEDWINDOW, //�E�B���h�E�̎��
			CW_USEDEFAULT,	//�w���W
			CW_USEDEFAULT,	//�x���W
			CW_USEDEFAULT,	//��
			CW_USEDEFAULT,	//����
			NULL, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
			NULL, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
			hInst, //�C���X�^���X�n���h��
			NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id, rcw = 80, rch = 40, mousex, mousey;
    static int catw, cath;
    static HDC hdc_mem, hdc_cat;
    HBITMAP hBmp;
    static HBITMAP hCat;
    HDC hdc;
    static RECT rc1, rc2;
    PAINTSTRUCT ps;
    static BOOL bDrag, bDragCat;
    static POINT ptStart;
    BITMAP bmp_info;

    switch (msg) {
        case WM_CREATE:
            MyAdjustWindow(hWnd, 600, 400);

            hdc_mem = CreateCompatibleDC(NULL);
            hdc = GetDC(hWnd);
            hBmp = CreateCompatibleBitmap(hdc, 600, 400);
            SelectObject(hdc_mem, hBmp);
            PatBlt(hdc_mem, 0, 0, 600, 400, WHITENESS);
            rc1.left = 10;
            rc1.top = 10;
            rc1.right = rc1.left + rcw;
            rc1.bottom = rc1.top + rch;
            Rectangle(hdc_mem, rc1.left, rc1.top, rc1.right, rc1.bottom);

            // �r�b�g�}�b�v��ǂݍ��݁A�������f�o�C�X�R���e�L�X�g�ɓ]������
            hCat = (HBITMAP)LoadImage(hInst,
                TEXT("MYBMP"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
            GetObject(hCat, (int)sizeof(bmp_info), &bmp_info);
            catw = bmp_info.bmWidth;
            cath = bmp_info.bmHeight;
            hdc_cat = CreateCompatibleDC(NULL);
            SelectObject(hdc_cat, hCat);
            rc2.left = 100;
            rc2.top = 100;
            rc2.right = rc2.left + catw;
            rc2.bottom = rc2.top + cath;
            BitBlt(hdc_mem,
                rc2.left, rc2.top, catw, cath, hdc_cat, 0, 0, SRCCOPY);

            DeleteObject(hBmp);
            ReleaseDC(hWnd, hdc);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            BitBlt(hdc, 0, 0, 600, 400, hdc_mem, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
            break;
        case WM_LBUTTONDOWN:
            mousex = LOWORD(lp);   // �}�E�X�ʒu��x���W
            mousey = HIWORD(lp);   // �}�E�X�ʒu��y���W

            // �}�E�X�̈ʒu���A�����`�̓����ɂ���ꍇ
            if (mousex > rc1.left && mousex < rc1.right &&
                mousey > rc1.top && mousey < rc1.bottom) {
                bDrag = TRUE;
            }

            // �}�E�X�̈ʒu���A�r�b�g�}�b�v�̓����ɂ���ꍇ
            if (mousex > rc2.left && mousex < rc2.right &&
                mousey > rc2.top && mousey < rc2.bottom) {
                bDragCat = TRUE;
            }

            // �����`�ƃr�b�g�}�b�v�̂ǂ�����h���b�O����Ă��Ȃ��ꍇ
            if (!bDrag && !bDragCat)
                return DefWindowProc(hWnd, msg, wp, lp);

            ptStart.x = mousex;
            ptStart.y = mousey;
            SetCapture(hWnd);        // �L���v�`���J�n
            break;
        case WM_MOUSEMOVE:
            if (!bDrag && !bDragCat)
                return DefWindowProc(hWnd, msg, wp, lp);

            mousex = LOWORD(lp);     // �}�E�X�ʒu��x���W
            mousey = HIWORD(lp);     // �}�E�X�ʒu��y���W
            if (bDrag) {             // �����`���h���b�O���̏ꍇ
                rc1.left += mousex - ptStart.x;
                rc1.top += mousey - ptStart.y;
                rc1.right = rc1.left + rcw;
                rc1.bottom = rc1.top + rch;
            }
            if (bDragCat) {          // �r�b�g�}�b�v���h���b�O���̏ꍇ
                rc2.left += mousex - ptStart.x;
                rc2.top += mousey - ptStart.y;
                rc2.right = rc2.left + catw;
                rc2.bottom = rc2.top + cath;
            }
            PatBlt(hdc_mem, 0, 0, 600, 400, WHITENESS);
            Rectangle(hdc_mem, rc1.left, rc1.top, rc1.right, rc1.bottom);
            BitBlt(hdc_mem,
                rc2.left, rc2.top, catw, cath, hdc_cat, 0, 0, SRCCOPY);
            InvalidateRect(hWnd, NULL, FALSE);
            ptStart.x = mousex;
            ptStart.y = mousey;
            break;
        case WM_LBUTTONUP:
            if (!bDrag && !bDragCat)
                return DefWindowProc(hWnd, msg, wp, lp);
            ReleaseCapture();        // �L���v�`���I��
            if (bDrag)
                bDrag = FALSE;
            if (bDragCat)
                bDragCat = FALSE;
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd, TEXT("�I�����Ă���낵���ł���"),
                TEXT("�m�F"), MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES)
                DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            if (bDrag || bDragCat)   // �h���b�O���Ȃ�
                ReleaseCapture();    // �L���v�`���I��
            DeleteObject(hCat);
            DeleteDC(hdc_mem);
            DeleteDC(hdc_cat);

            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

BOOL MyAdjustWindow(HWND hWnd, int bmpw, int bmph)
{
    RECT rc;
    int x, y, w, h, winx, winy;

    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    rc.left = 0;
    rc.right = bmpw;
    rc.top = 0;
    rc.bottom = bmph;
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    winx = rc.right - rc.left;
    winy = rc.bottom - rc.top;
    x = (w - winx) / 2;
    y = (h - winy) / 2;
    MoveWindow(hWnd, x, y, winx, winy, FALSE);
    return TRUE;
}
