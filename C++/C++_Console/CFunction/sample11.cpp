#include <stdio.h>
#include <memory.h>

int main(void)
{
	int array[10] = {42,79,13};
	
	printf("array[0] = %d\n",array[0]);
	printf("array[1] = %d\n",array[1]);
	printf("array[2] = %d\n",array[2]);
	printf("array[3] = %d\n",array[3]);
	printf("array[4] = %d\n",array[4]);
	
	int array2[] = {1,2,3,4,5};	/* 要素数が省略されている */
	
	for (int i = 0;i < sizeof(array2) / sizeof(array2[0]);i++) {
		printf("array2[%d] = %d\n",i,array2[i]);//sizeof関数
	}
	
	int array1[] = {42,79,13,19,41};
	
	//memcpy(コピー先配列名､コピー元配列名、配列全体のサイズ)
	memcpy(array2,array1,sizeof(array1)); /* array1 の全要素を array2 にコピー */
	
	for (int i = 0;i < sizeof(array2) / sizeof(array2[0]);i++) {
		printf("array1[%d] = %d\n",i,array2[i]);
	}
	return 0;
}