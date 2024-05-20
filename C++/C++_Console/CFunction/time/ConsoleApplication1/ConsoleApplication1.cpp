#include<stdio.h>
#include<time.h>

#define SIZE 26

void main()
{
	//日付と時間を格納する変数
	time_t tm;

	//現在日時と時刻を取得
	time(&tm);

	char buff[SIZE];
	ctime_s(buff, SIZE,&tm);

	printf("現在時刻は%s\n", buff);
}
