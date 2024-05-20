#include <stdio.h>

int main(void)
{
    int data;
	scanf_s("%d",&data);
	printf("%d\n",data);
	
	double data_;
	scanf_s("%lf",&data_);
	printf("%f\n",data_);
	
	int data1,data2;
	scanf_s("%d%d",&data1,&data2);//区切り文字はスペースやタブ
	printf("%d , %d\n",data1,data2);
	
	int data3,data4;
	scanf_s("%d,%d",&data3,&data4);//区切り記号は,
	printf("%d , %d\n",data3,data4);
	
    return 0;
}