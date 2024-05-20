#include<stdio.h>
#include <wchar.h>
#include <windows.h>
#include <locale.h>

//ユニコード
//文字化けが起きないように、以下を追加
//#include <locale.h>
//setlocale(LC_ALL, "japanese");

int main()
{
	//code page: 932でないと文字化け
	setlocale(LC_ALL, "japanese");

	wchar_t str1[100] = L"あいまい１";
	WCHAR str2[100] = L"寺田２";

	fwprintf(stderr, L"%s\n", str1);
	fwprintf(stderr, L"%s\n", str2);

	return 0;
}
