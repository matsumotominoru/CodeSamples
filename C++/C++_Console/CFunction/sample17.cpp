#include <stdio.h>

int main(void)
{
	int *data;
	int i,average = 0;
	int array[10] = {15,78,98,15,98,85,17,35,42,15};
	
	data = array;	/* ポインタ変数に配列のアドレスを代入 */
	
	for (i = 0;i < 10;i++) {
		average += data[i];	/* 配列みたいに使える */
	}
	printf("%d\n",average / 10);
	
	average = 0;
	for (i = 0;i < 10;i++) {
		average += *(data + i);	/* ポインタ演算1 */
	}
	printf("%d\n",average / 10);
	
	average = 0;
	for (data = array;data != &array[10];data++) {	/*ポインタ演算2*/
		average += *data;
	}
	printf("%d\n",average / 10);
	
	return 0;
}