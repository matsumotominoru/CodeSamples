#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char c = 'A';
	printf("%c\n",c);
	
	char d = 'A' + 9;/* 最初は0なので9を足す */
	printf("%c\n",d);
	
	char e = '8';	/* 数字 */
	int suuti = e - '0';	/* 数値に変換 */
	printf("%d\n",suuti);
	
	if (c >= '0' && c <= '9') {	/* 判定部分 */
		suuti = c - '0';	/* 数値に変換 */
	} else {
		suuti = 0;
	}
	printf("%d\n",suuti);
	
	if (isdigit(c)) {	/* 判定部分 */
		suuti = c - '0';
	} else {
		suuti = 0;
	}
	printf("%d\n",suuti);
	
	
	return 0;
}