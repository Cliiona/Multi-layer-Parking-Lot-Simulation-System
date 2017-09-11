#include"main.h"
void main()
{
 Pp state;
 Rec list=NULL;
 int a;
 int i;
 randomize();
 init_pp(&state,list);
 Set_Video_Mode(SVGA);
 //readbmp(0,0,"outall.bmp");

//a=Get_Plot(100,100);
// Set_Video_Mode(TEXT_MODE);
// printf("%d",a);
//WriteHz16("ds",600,100,a);

 //getch();
 yes(&state);
}
