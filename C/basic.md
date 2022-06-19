# Basic

## Standard I/O

### Sample 1

```C
//Input
//n
//x_1 y_1
//x_2 y_2
//...
//x_n y_n

#include <stdio.h>
int main(void){
    int i, n;
    char buf[1000];
    char token1[100], token2[100];

    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d\n", &n);
    for (i=0; i<n; i++) {
        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%s %s\n", token1, token2);
        printf("hello = %s , world = %s\n" ,token1 ,token2);
    }
    return 0;
}
```

## Tokenize

### Sample 1

```C
#include <stdio.h>
#include <string.h>

int main () {
   char s[256];
    strcpy(s, "one two three");
    char* token = strtok(s, " ");
    while (token) {
        printf("token: %s\n", token);
        token = strtok(NULL, " ");
    }

    return 0;
}
```
