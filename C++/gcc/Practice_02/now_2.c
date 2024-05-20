//page206
#include<stdio.h>
#include<time.h>

int main(){
    time_t now;
    now = time(NULL);

    printf("now %s",ctime(&now));

    return 0;
}