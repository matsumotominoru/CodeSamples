#include <stdio.h>
#include <string.h>
//Saved UTF-8 without BOM

int main(void){

    printf("こんにちは℘ℙ!\n");

    //以下は無効のコード。setlocaleが必要か。
    char* str1 ;
    strncpy(str1,"test",strlen("test"));
    printf("%s1\n",str1);

    strncpy(str1, "やあ!",strlen("やあ"));
    printf("%s2\n",str1);

    wchar_t* wstr1;
    wcsncpy(wstr1,L"test",strlen("test"));
    printf("%ls3\n",wstr1);

    char* str2 = (char*) "hello";
    printf("%s4\n",str2);

    wchar_t* wstr2 = (wchar_t*) "hello";
    printf("%ls5\n",wstr2);

    char mbsz[] = "Multibyte String";
    wchar_t wsz[] = L"Wide String";

    printf("%s", mbsz);  // マルチバイト文字列をそのまま出力
    printf("%ls", wsz);  // wcrtomb関数で変換後に出力
    // または
    wprintf(L"%s", mbsz);  // mbrtowc関数で変換後に出力
    wprintf(L"%ls", wsz);  // ワイド文字列をそのまま出力

    return 0;
}