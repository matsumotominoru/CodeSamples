//fizzbuzz、愚直に printf 呼ぶと40.4秒のところ、最適化したコードだと1.58秒。
//数値は文字列化しておく
//分岐予測あてる
//"2\nfizz\n"とかは64bitストアで書かせる
//https://x.com/kazuho/status/1704699813735108835?s=20
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define inline __attribute__((always_inline))

static char tens[16];
static size_t tenslen = 0;
static int n;

static char outbuf[8000], *outp = outbuf;

static void flush(void)
{
    write(1, outbuf, outp - outbuf);
    outp = outbuf;
}

static void flush_and_exit(void)
{
    flush();
    exit(0);
}

static inline void append(const char *s, size_t l)
{
    while (l-- != 0)
        *outp++ = *s++;
}

static void plus10(void)
{
    if (tenslen == 0)
        tenslen = 1;

    for (size_t i = sizeof(tens) - 1;; i--) {
       if (++tens[i] <= '9')
           return;
       tens[i] = '0';
       if (sizeof(tens) - i == tenslen)
           ++tenslen;
    }
}

static inline void emit30(int maxval)
{
#define INCR() ++n; if (n > maxval) flush_and_exit()
#define NUMBER(ld); INCR(); append(tens + sizeof(tens) - tenslen, tenslen); *outp++ = ld; *outp++ = '\n'
#define FIZZ() INCR(); append("fizz\n", 5)
#define BUZZ() INCR(); append("buzz\n", 5)
#define FIZZBUZZ() INCR(); append("fizzbuzz\n", 9)

    NUMBER('1');
    NUMBER('2');
    FIZZ();
    NUMBER('4');
    BUZZ();
    FIZZ();
    NUMBER('7');
    NUMBER('8');
    FIZZ();
    BUZZ();

    plus10();

    NUMBER('1');
    FIZZ();
    NUMBER('3');
    NUMBER('4');
    FIZZBUZZ();
    NUMBER('6');
    NUMBER('7');
    FIZZ();
    NUMBER('9');
    BUZZ();

    plus10();

    FIZZ();
    NUMBER('2');
    NUMBER('3');
    FIZZ();
    BUZZ();
    NUMBER('6');
    FIZZ();
    NUMBER('8');
    NUMBER('9');
    FIZZBUZZ();

    plus10();
}

int main(int argc, char **argv)
{
    int maxval;

    if (argc < 2 || sscanf(argv[1], "%d", &maxval) != 1) {
        fprintf(stderr, "usage: %s <max-value>\n", argv[0]);
        exit(1);
    }
    memset(tens, '0', sizeof(tens));

    while (n + 30 < maxval) {
        emit30(INT_MAX);
        if (outp - outbuf >= sizeof(outbuf) - 500)
            flush();
    }
    emit30(maxval);

    return 0;
}
