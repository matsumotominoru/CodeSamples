//page150
//POSIX Only
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char buff[BUFSIZ];
    printf("FileName>");
    scanf("%s", buff);

    if(access(buff,F_OK) == 0){
        printf("FileExists\n");
    }
    else{
        printf("FileNotExists\n");
    }
}
