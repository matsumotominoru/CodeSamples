#include<stdio.h>
#include <wchar.h>
#include <windows.h>
//ユニコード
//文字化けが起こる。
int main()
{
	wchar_t str1[100] = L"あいまい１";
	WCHAR str2[100] = L"寺田２";

	fwprintf(stderr, L"%s\n", str1);
	fwprintf(stderr, L"%s\n", str2);

	return 0;
}
