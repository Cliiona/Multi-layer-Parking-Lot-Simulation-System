#include <stdio.h>
#include<time.h>
#include<conio.h>
#include<bios.h>
void main()
{
	time(&timep);
	time_t timep;
	printf("%s",ctime(&timep));
}