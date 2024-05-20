#include <stdio.h>

int main(void)
{
    printf_s("HelloWorld\nこんにちは！\nマック\tMac\n");
	printf("%d\n",100);
	printf("%d\n",100+200);
	printf("%d\n",10 - 3);
	printf("%d\n",10 * 3);
	printf("%d\n",10 / 3);
	printf("%d\n",10 % 3);
	printf("%f\n",10.0 + 3.0);
	printf("%f\n",10.0 - 3.0);
	printf("%f\n",10.0 * 3.0);
	printf("%f\n",10.0 / 3.0);
	
	int value;
	value = 10+40;
	printf("%d\n",value);
	
	double left,right;
	left = 10;
	right = 3;
	printf("%f\n",left + right);
	printf("%f\n",left - right);
	printf("%f\n",left * right);
	printf("%f\n",left / right);
	
	printf("%d\n",(int)(1.05 * 360));
	
	int a = 10000,b = 500,c = 3;
	printf("Aは %5d です。\n",a);
	printf("Bは %5d です。\n",b);
	printf("Cは %5d です。\n",c);
	printf("Aは %05d です。\n",a);
	printf("Bは %05d です。\n",b);
	printf("Cは %05d です。\n",c);
	
	double pi = 3.14159;
	printf("%6.2f\n",pi);
	printf("123456\n");
	
    return 0;
}