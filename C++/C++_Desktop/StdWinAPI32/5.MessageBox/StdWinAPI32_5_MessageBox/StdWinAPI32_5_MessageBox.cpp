#include<windows.h>
//Unicodeだと上手くいかないため、マルチバイト文字で実行

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	int on_button;//戻り値の押されたボタン
	TCHAR chStr[128];
	//右の文字列はconst char*扱いになるため、キャストした。
	TCHAR *str1 = (TCHAR *)TEXT("Kitty on your lap");
	TCHAR str2[32];


	//第二引数が本文、第三引数がタイトル
	MessageBox(NULL, TEXT("Kitty on your lap"), TEXT("メッセージボックス"), MB_OK);

	//メッセージボックスにiのアイコンがつく。
	MessageBox(NULL, TEXT("Kitty on your lap"), TEXT("メッセージボックス"), MB_OK | MB_ICONINFORMATION);

	//疑問符のアイコンがつく
	on_button = MessageBox(NULL, TEXT("Do you like Nekomimi?"), TEXT("質問しています"), MB_YESNO | MB_ICONQUESTION);
	//はいのとき
	if (on_button == IDYES)
		MessageBox(NULL, TEXT("You are nice!"), TEXT("メッセージボックス"), MB_OK);
	else MessageBox(NULL, TEXT("Be Killed!"), TEXT("メッセージボックス"), MB_OK);

	//wsprintfは文字列フォーマット関数。フォーマットした文字列は第一引数に入れる。
	//第一引数はフォーマットする文字列を格納するバッファ、
	//第二引数はNULL で終わる書式制御文字列へのポインタを指定
	//関数が成功するとバッファに格納された終端の NULL を含まない文字数が返り、
	//関数が失敗すると書式制御文字列の長さよりも小さな値が返る
	//deprecated(Because of security risk)
	wsprintf(chStr, TEXT("インスタンスハンドル : %d"), (int) hInstance);//C言語のsprintf関数と同じ
	MessageBox(NULL, chStr, TEXT("Kitty on your lap"), MB_OK);

	//文字を第一引数のバッファにコピーする。
	//deprecated
	lstrcpy(str2, str1);
	MessageBox(NULL, str1, str2, MB_OK);

	return 0;
}
