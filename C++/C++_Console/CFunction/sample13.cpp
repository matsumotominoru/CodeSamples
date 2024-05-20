#include <stdio.h>

int main(void)
{
	char str1[6] = {'M','A','R','I','O','\0'};
	printf("%s\n",str1);
	
	char str2[] = "MARIO";
	printf("%s\n",str2);
	
	char str[6];
	str[0] = 'M';
	str[1] = 'A';
	str[2] = 'R';
	str[3] = 'I';
	str[4] = 'O';
	str[5] = '\0';
	printf("%s\n",str);
	
	
	return 0;
}