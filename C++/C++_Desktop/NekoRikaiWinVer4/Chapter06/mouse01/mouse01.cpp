// mouse01.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
void DrawRect(HWND, POINTS, POINTS);

TCHAR szClassName[] = TEXT("mouse01");	//�E�B���h�E�N���X
POINTS start, end, old_end;

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

//�E�B���h�E�E�N���X�̓o�^

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
	wc.lpszClassName = szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//�E�B���h�E�̐���

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			TEXT("�L�ł��킩��}�E�X����"), //�^�C�g���o�[�ɂ��̖��O���\������܂�
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

//�E�B���h�E�v���V�[�W��

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int id;
	TCHAR szBuf[32];
	HDC hdc;
	HBRUSH hBrush;
	static BOOL bDraw;

	switch (msg) {
		case WM_LBUTTONDOWN:
			bDraw = TRUE;
			old_end = start = MAKEPOINTS(lp);
			DrawRect(hWnd, start, old_end);
			break;
		case WM_MOUSEMOVE:
			if(bDraw) {
				end = MAKEPOINTS(lp);
				DrawRect(hWnd, start, old_end);
				DrawRect(hWnd, start, end);
				old_end = end;
			} else {
				return DefWindowProc(hWnd, msg, wp, lp);
			}
			break;
		case WM_LBUTTONUP:
			if(bDraw) {
				DrawRect(hWnd, start, end);
				bDraw = FALSE;

				wsprintf(szBuf, 
					TEXT("(%d, %d) - (%d, %d)"), 
					start.x, start.y, end.x, end.y);
				SetWindowText(hWnd, szBuf);
				hdc = GetDC(hWnd);
				hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
				SelectObject(hdc, hBrush);
				Ellipse(hdc, start.x, start.y, end.x, end.y);
				ReleaseDC(hWnd, hdc);
			} else {
				return DefWindowProc(hWnd, msg, wp, lp);
			}
			break;
		case WM_CLOSE:
			id = MessageBox(hWnd,
				TEXT("�I�����Ă���낵���ł���"),
				TEXT("�m�F"),
				MB_YESNO | MB_ICONQUESTION);
			if (id == IDYES)
				DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}

void DrawRect(HWND hWnd, POINTS beg, POINTS end)
{
	HDC hdc;

	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOT);
	MoveToEx(hdc, beg.x, beg.y, NULL);
	LineTo(hdc, end.x, beg.y);
	LineTo(hdc, end.x, end.y);
	LineTo(hdc, beg.x, end.y);
	LineTo(hdc, beg.x, beg.y);
	LineTo(hdc, end.x, end.y);
	ReleaseDC(hWnd, hdc);
	return;
}
