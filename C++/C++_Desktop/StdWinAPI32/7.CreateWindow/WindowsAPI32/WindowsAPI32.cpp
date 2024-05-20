#include<windows.h>
/*Windowsプログラミングでは、ウィンドウの生成は二つの作業にわかれる
①ウィンドウクラスの登録
　比較的汎用的な設定を行い、これを登録して使いまわすことができます
②直接的なウィンドウの生成作業
　登録されているウィンドウクラスを基盤に、ウィンドウをCreateWindowなどで生成します
　生成関数は戻り値として HWND型 の値を返す。これはウィンドウハンドルと呼ばれるものだ。ウィンドウオブジェクトへの参照とも言い換えられる。
*/

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR lpCmdLine,int nCmdShow) {
	HWND hwnd;

	//HWND CreateWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName,DWORD dwStyle,int x, int y, int nWidth, int nHeight,HWND hWndParent, HMENU hMenu,HANDLE hInstance, LPVOID lpParam);
	//ウィンドウを生成する。戻り値として HWND型。
	//第一引数は事前に設定したウィンドウクラスの名前。
	//第二引数はウィンドウの名前。
	//第三引数はウィンドウのスタイルを設定。
	//第四第五引数はウィンドウの初期位置。
	//第六第七引数はウィンドウ幅をピクセルで指定する。
	//第八引数は親ウィンドウ、またはオーナーウィンドウとなるハンドルを指定。親ウィンドウを持つ子ウィンドウの表示は、親ウィンドウのクライアントエリアに限定され、オーナーウィンドウを持つ場合オーナーが破棄されるとそのウィンドウも破棄される。
	//第九引数はメニューのハンドル
	//第十引数はインスタンスハンドル
	//第十一引数はメッセージと呼ばれるものに渡されるパラメータを指定するもの。LPVOID 型 は、void*に相当する汎用ポインタ型。
	hwnd = CreateWindow(TEXT("STATIC"), TEXT("Window1"), WS_CAPTION, 100, 100, 200, 200, NULL, NULL, hInstance, NULL);
	//ウィンドウの生成に失敗したとき
	if (hwnd == NULL)
		return 0;
	//デフォルトでは不可視状態のため、次のメソッドでウィンドウを表示する。
	ShowWindow(hwnd, SW_SHOW);

	MessageBox(NULL, TEXT("1です。"), TEXT("Window"), MB_ICONINFORMATION);

	//拡張ウィンドウを生成する。第一引数は拡張されたウィンドウスタイル。第二引数以降はCreateWindow関数と同じ。
	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, TEXT("STATIC"), TEXT("Window2"), WS_OVERLAPPEDWINDOW, 100, 100, 200, 200, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, SW_SHOW);

	MessageBox(NULL, TEXT("2です。"), TEXT("Window"), MB_ICONINFORMATION);

	return 0;
}