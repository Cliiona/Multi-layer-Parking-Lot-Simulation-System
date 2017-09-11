#include "mouse.h"

void mousecheck()
{
    int check;

    asm mov AX,0
    asm int 33h
    asm mov check,AX
}

void mousemove()
{
    asm mov AX,7
    asm mov CX,0
    asm mov DX,630
    asm int 33h
    asm mov AX,3
    asm mov CX,0
    asm mov DX,140
    asm int 33h
}
void mouseread(mou *mouse)
{
    _AX=3;
    asm int 33h
    (mouse->x)=_CX;
    (mouse->y)=_DX;
    (mouse->key)=_BX;
}

void back_mouse(char *FILENAME) //调用背景图片以及调用鼠标
{
    mou oldmouse,curmouse;
	oldmouse.x=0;oldmouse.y=0;oldmouse.key=0;
    curmouse.x=0;curmouse.y=0;curmouse.key=0;
	sprite small;
	pcx_picture background_pcx,objects_pcx;
	Set_Video_Mode(VGA256);
	PCX_Load1("mouse.pcx",(pcx_picture_ptr)&objects_pcx,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&small,0,0,0,0,0,0,65,55,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&objects_pcx,(sprite_ptr)&small,0,0,0,65,55);//将屏幕内容复制给小图片
	Fill_Screen(0);
	PCX_Load1(FILENAME,(pcx_picture_ptr)&background_pcx,1);//背景
	Behind_Sprite_Size((sprite_ptr)&small,65,55);//取图片后内容
	mousecheck();//初始化鼠标
	mousemove();//设置鼠标范围
	while(!kbhit())
{
	mouseread(&curmouse)  ;//取鼠标位置
	if(curmouse.x!=oldmouse.x||curmouse.y!=oldmouse.y)//判断是否移动过鼠标
	{
		Erase_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片后背景内容
		small.x=curmouse.x/2;
		small.y=curmouse.y;
		Behind_Sprite_Size((sprite_ptr)&small,65,55);//保存小图片后背景内容
		Draw_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片于鼠标位置
		oldmouse.x=curmouse.x;
		oldmouse.y=curmouse.y;
	}
}
Sprite_Delete_Size((sprite_ptr)&small,1);
}
