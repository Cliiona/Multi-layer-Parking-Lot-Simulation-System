#include "mouse.h"
int arrowMousePixSave[16][16];    /*用于保存鼠标即将覆盖的区域*/
int arrowMouseDraw[16][10]={    /*设计鼠标的形状,其中1:表示鼠标的边界,2:表示鼠标边界所包围的区域,3:表示鼠标以外的区域*/
    {1,1,3,3,3,3,3,3,3,3},
    {1,2,1,3,3,3,3,3,3,3},
    {1,2,2,1,3,3,3,3,3,3},
    {1,2,2,2,1,3,3,3,3,3},
    {1,2,2,2,2,1,3,3,3,3},
    {1,2,2,2,2,2,1,3,3,3},
    {1,2,2,2,2,2,2,1,3,3},
    {1,2,2,2,2,2,2,2,1,3},
      {1,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,2,1,3,3},
    {1,2,2,2,2,2,1,3,3,3},
    {1,2,1,3,1,2,2,1,3,3},
    {1,1,3,3,1,2,2,1,3,3},
    {3,3,3,3,3,1,2,2,1,3},
    {3,3,3,3,3,1,2,2,1,3},
    {3,3,3,3,3,3,1,2,2,1} };
void mousecheck()
{
    int check;

    asm mov AX,0
    asm int 33h
    asm mov check,AX
}
void mousemove() //设置移动范围
{
    asm mov AX,7
    asm mov CX,0
    asm mov DX,1023
    asm int 33h
    asm mov AX,8
    asm mov CX,0
    asm mov DX,767
    asm int 33h
}
void mouseread(Mouse m)
{
    _AX=3;
    asm int 33h
    (m->x)=_CX;
    (m->y)=_DX;
    _AX=5;
    asm int 33h;
    (m->key)=_BX;
  //  (m->key)=_BX;
}
void Mouse_cpy(Mouse mouse)     /*鼠标区域背景扣取*/
{
    int i,j;
    unsigned long pos;
    char oldpage,newpage;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=((mouse->y)*1024L+(mouse->x))/32768;
    newpage=oldpage;
    selectpage(newpage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            pos=(i+(mouse->y))*(1024L)+j+(mouse->x);
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            arrowMousePixSave[i][j]=video_buffer[pos%65536];
        }
    }
    return;
}
void Mouse_reshow(Mouse mouse)       /*鼠标区域背景扣取后重新显示*/
{
    int i,j;
    char oldpage,newpage;
    unsigned long pos;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=((mouse->y)*(1024L)+(mouse->x))/32768;
    newpage=oldpage;
    selectpage(oldpage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            pos=(i+(mouse->y))*(1024L)+j+(mouse->x);
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            video_buffer[pos%65536]=arrowMousePixSave[i][j];
        }
    }
    return;
}
void Mouse_show( Mouse mouse)     /*鼠标显示*/
{
    int i,j;
    unsigned long pos;
	unsigned long oldpage,newpage;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=((mouse->y)*(1024L)+(mouse->x))/32768;
    newpage=oldpage;
    selectpage(oldpage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<10;j++)
        {
            pos=(i+(mouse->y))*1024L+j+(mouse->x);
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            if(arrowMouseDraw[i][j]==1)
                video_buffer[pos%65536]=0;
            else if(arrowMouseDraw[i][j]==2)    /* 画鼠标*/
                video_buffer[pos%65536]=0xffff;
        }
    }
    delay(15);
    return;
}
void move_mouse(Mouse curmouse,Mouse oldmouse)//移动中显示鼠标
{       

        mouseread(curmouse);
    	if((curmouse->x)!=(oldmouse->x)||(curmouse->y)!=(oldmouse->y))//判断是否移动过鼠标
	   {
                Mouse_reshow(oldmouse);//显示鼠标移动前被框住的内容
				Mouse_cpy(curmouse);//保存鼠标后背景内容（再框）
	    	    Mouse_show(curmouse);
	    	    oldmouse->x=curmouse->x;
		        oldmouse->y=curmouse->y;
                    
    	  }

}
 /********按下按钮*********/
int mouse_on(BUTTON *button)
{

	mou m;
	mouseread(&m);
    if(m.x>(button->x1)&& m.x<(button->x2) && m.y>button->y1 && m.y<button->y2 )
        return 1;
    else return 0;
}

