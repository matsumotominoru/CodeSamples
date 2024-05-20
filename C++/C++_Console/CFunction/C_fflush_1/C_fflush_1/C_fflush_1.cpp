/* header files */
#include <stdio.h>
#include <stdlib.h>

/* functions */
void MySleep(int n);

/* main */
int main(void) {
    char buf[BUFSIZ];

    /* 標準出力を完全バッファリングする */
    setvbuf(stdout, buf, _IOFBF,INT_MAX);

    /* Snoopyの出力 */
    printf("Snoopy\n"); /* <-- "Snoopy\n"がバッファリングされる */

    /* 時間稼ぎ */
    MySleep(100000);

    /* バッファのフラッシュ */
    fflush(stdout); /* <-- この時点で"Snoopy\n"が出力される" */

    return EXIT_SUCCESS;
}

/* 時間かせぎ */
void MySleep(int n) {
    int i;
    for (i = 0; i < n * 5000; i++);
}