#include<windows.h>
#include<d3dx9.h>


LPDIRECT3D9 pD3d;
LPDIRECT3DDEVICE9 pDevice;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3d(HWND);
VOID Draw();

// アプリケーションのエントリー関数
int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInstance, _In_   LPSTR lpCmdLine, _In_ int nCmdShow)
{
    HWND hWnd = NULL;
    MSG msg;

    //ウィンドウの初期化と登録
    const char szAppName[] = "BASE";
    WNDCLASSEX wndclass;
    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInst;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wndclass);

    //ウィンドウの生成と表示・更新
    hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
        0, 0, 640, 480, NULL, NULL, hInst, NULL);
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    //★Direct3D初期化
    if (FAILED(InitD3d(hWnd)))
    {
        return(0);
    }

    //メッセージループ
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //★描画
            Draw();
        }
    }
    return(INT)msg.wParam;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        switch ((CHAR)wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

HRESULT InitD3d(HWND hWnd)
{
    // Direct3D作成
    if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
    {
        MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
        return E_FAIL;
    }
    // Direct3D Device作成
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.BackBufferCount = 1;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.Windowed = TRUE;

    if (FAILED(pD3d->CreateDevice(
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_MIXED_VERTEXPROCESSING,
        &d3dpp, &pDevice)))
    {
        MessageBox(0, "HALモードDIRECT3Dデバイス失敗\nREFモード再試行 ", NULL, MB_OK);
        if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
            D3DCREATE_MIXED_VERTEXPROCESSING,
            &d3dpp, &pDevice)))
        {
            MessageBox(0, "DIRECT3Dデバイス作成に失敗", NULL, MB_OK);
            return E_FAIL;
        }
    }
    return S_OK;
}

//　Draw
VOID Draw()
{
    static UCHAR c = 0;
    c = (c++) % UCHAR_MAX;
    pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(c, c, c), 1.0f, 0);
    if (SUCCEEDED(pDevice->BeginScene()))
    {
        //ここに描画処理
        pDevice->EndScene();
    }
    pDevice->Present(NULL, NULL, NULL, NULL);
}
