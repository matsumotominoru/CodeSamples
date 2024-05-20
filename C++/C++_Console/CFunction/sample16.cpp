#include <stdio.h>

void func(int *pvalue);
int getaverage(int data[10]);

int main(void)
{
	int value = 10;
	printf("&value = %p\n",&value);
	func(&value);	/* アドレスを渡す */
	printf("value = %d\n",value);
	
	int average;
	int array[10] = {15,78,98,15,98,85,17,35,42,15};
	average = getaverage(array);
	printf("%d\n",array[3]);//変わっている
	printf("%d\n",average);
	
	int array2[5] = {15,98,98,17,42};/* 要素数が5 */
	average = getaverage(array2);//強引に10個の要素の足し算を行う。
	printf("%d\n",average);
	return 0;
}

void func(int *pvalue)
{
	printf("pvalue = %p\n",pvalue);
	*pvalue = 100;	/* 通常変数モードに切り替えて代入 */
	return;
}

int getaverage(int data[10])//配列の引数はアドレスを渡す。int data[]やint *dataもこれと同じ
{
	int i,average = 0;
	for (i = 0;i < 10;i++) {
		average += data[i];
	}
	data[3]=1500;
	return average / 10;
}