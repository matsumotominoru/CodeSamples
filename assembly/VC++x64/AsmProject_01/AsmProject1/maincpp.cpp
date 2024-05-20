#include<stdio.h>

//asm function
extern "C" void asmSample(int* a);

int main(void) {
	int a = 0;

	asmSample(&a);
	printf("a = %d\n", a);

	return 0;
}