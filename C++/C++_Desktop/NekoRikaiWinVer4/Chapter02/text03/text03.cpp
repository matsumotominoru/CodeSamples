 // text03.cpp

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("text03");	// �E�B���h�E�N���X


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
	wc.lpfnWndProc = WndProc;	// �v���V�[�W����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst; // �C���X�^���X
	wc.hIcon = NULL;
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;	 // ���j���[��
	wc.lpszClassName = szClassName;
	wc.hIconSm = NULL;

	return (RegisterClassEx(&wc));
}

//�E�B���h�E�̐���

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;

	hWnd = CreateWindow(szClassName,
			TEXT("�������\������"), //�^�C�g���o�[�ɂ��̖��O���\������܂�
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
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rc;
	LPTSTR lpszStr = TEXT("�L�ł��킩��\nWindows\t�v���O���~���O\n\t");
	DRAWTEXTPARAMS dtp;

	switch (msg) {
		case WM_PAINT:
			GetClientRect(hWnd, &rc);
			dtp.cbSize = sizeof(DRAWTEXTPARAMS);
			dtp.iLeftMargin = 20;
			dtp.iRightMargin = 20;
			dtp.iTabLength = 5;

			hdc = BeginPaint(hWnd, &ps);
			SetTextColor(hdc, RGB(255, 0, 255));
			DrawTextEx(hdc, 
				lpszStr, 
				-1, 
				&rc, 
				DT_WORDBREAK | DT_EXPANDTABS | DT_TABSTOP, 
				&dtp);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}

