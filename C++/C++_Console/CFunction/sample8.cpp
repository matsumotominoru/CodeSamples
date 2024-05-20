#include <stdio.h>

int count;	/* グローバル変数 */

int countfunc(void);

int main(void)
{
	countfunc();
	count = 10;	/* ここで変更 */
	countfunc();
	countfunc();
	return 0;
}
int countfunc(void)
{
	count++;
	printf("%d\n",count);
	return count;
}
