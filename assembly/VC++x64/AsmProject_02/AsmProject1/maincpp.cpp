#include<stdio.h>

//asm function
extern "C" void asmSample(int* a, int b);

int main(void) {
	int a = 0;
	int b = 5;
	
	//a=b
	asmSample(&a, b);
	printf("a = %d\n", a);
	printf("b = %d\n", b);

	return 0;
}