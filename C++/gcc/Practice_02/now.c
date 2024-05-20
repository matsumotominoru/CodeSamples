//page203
#include<stdio.h>
#include<time.h>

int main(){
    time_t now;
    now = time(NULL);

    printf("now %ld\n",now);

    return 0;
}