#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//https://www.onlinegdb.com/
char *getConstantString(void)
{
    char *str = (char*)"hello";
    printf("Fn(getConstantString): %s\n", str);
    return str;
}

char *getHeapString(void)
{
    char *str = _strdup("Hello");//strdupはPOSIXのためWindowsでは使えない。
    printf("Fn(getHeapString): %s\n", str);
    return str;
}

char *getStackString(void)
{
    char str[] = "hello";
    printf("Fn(getStackString): %s\n", str);
    return str;//warning C4172: ローカル変数またはテンポラリのアドレスを返します
}

int main(void)
{
    char *constStr = getConstantString();
    char *heapStr = getHeapString();
    char *stackStr = getStackString();

    printf("Main(getConstantString): %s\n", constStr);
    printf("Main(getHeapString): %s\n", heapStr);
    printf("Main(getStackString): %s\n", stackStr);//nullか別の文字列

    free(heapStr);
    return 0;
}