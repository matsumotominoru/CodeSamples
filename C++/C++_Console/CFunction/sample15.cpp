#include <stdio.h>

int main(void)
{
	int in;
	printf("%p\n",&in);
	
	int i1,i2,i3;
	printf("i1(%p)\n",&i1);
	printf("i2(%p)\n",&i2);
	printf("i3(%p)\n",&i3);
	
	int array[10];
	printf("array(%p)\n",array);
	printf("array0(%p)\n",&array[0]);
	printf("array1(%p)\n",&array[1]);
	printf("array2(%p)\n",&array[2]);
	
	char str[256] = "DRAGON";
	scanf("%s",&str[6]); /* 6番の要素のアドレス */
	printf("%s\n",str);
	
	int *p;
	int i;
	p = &i;
	*p = 10; /* 通常変数モードに切り替えたポインタ変数に代入 */
	printf("p = %d\n",*p);
	printf("i = %d\n",i);//iも変わる。変数は指定したアドレスの値をとってくる。
	
	return 0;
}