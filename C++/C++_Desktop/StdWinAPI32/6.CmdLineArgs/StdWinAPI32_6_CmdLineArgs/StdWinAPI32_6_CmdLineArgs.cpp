#include<windows.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR lpCmdLine,int nCmdShow) {
	//WinMain() の第三引数は、配列ではない。トークンの分解はしていなく、スペースも含めた一つの文字列として格納している。実行ファイルの名前なし。
	
	//char * からwchar_t *にキャスト。しかしCode Page依存なので、文字化けが発生する。
	size_t newsize = strlen(lpCmdLine) + 1;
	wchar_t* wlpCmdLine = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wlpCmdLine, newsize, lpCmdLine, _TRUNCATE);
	MessageBox(NULL, wlpCmdLine, TEXT("FirstKitty"), MB_ICONINFORMATION);

	//起動時のコマンドライン引数を返す。トークンの分解はしていなく、スペースも含めた一つの文字列として格納している。実行ファイルの名前あり。
	//GetCommandLineの戻り値はユニコード。文字化けしない。
	MessageBox(NULL, GetCommandLine(),TEXT("SecondKitty"), MB_ICONINFORMATION);

	return 0;
}