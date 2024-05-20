#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char str[] = "145";
	int suuti = atoi(str);
	printf("%d\n",suuti);
	
	//strcpy(コピー先文字列配列名,コピー元文字列配列名);
	char str2[10];
	strcpy(str2,"MARIO");
	printf("%s\n",str2);
	
	//strncpy(コピー先文字列配列名,コピー元文字列配列名,コピーする文字数);
	char str3[] = "MARIO",str4[10];
	strncpy(str4,str3,3);
	str4[3] = '\0';	/* EOSを付加 */
	printf("%s\n",str4);
	
	char str5[] = "DRAGON" "QUEST";
	printf("%s\n",str5);
	
	//strcat(元の文字列が記憶された配列,追加する文字列の記憶された配列);
	char str6[12] = "DRAGON";
	char str7[] = "QUEST";
	strcat(str6,str7);
	printf("%s\n",str6);
	
	//sprintf(結果を記憶する配列,書式文字列,各種変数・・・);
	char str8[16];
	char str9[12] = "DRAGON";
	char str10[] = "QUEST";
	int i = 3;
	sprintf(str8,"%s%s%d\n",str9,str10,i);
	printf(str8);
	
	char str11[32];
	scanf("%32s",str11);//スペースは区切り文字扱いなので、スペース以降は変数に格納されない。
	printf("%s\n",str11);
	
	i = strlen(str11);
	printf("%d\n",i);
	
	if (strcmp(str11,str5) == 0) {
		printf("同じ\n");
	} else {
		printf("違う\n");
	}
	
	
	return 0;
}