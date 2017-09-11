#include "mouse.h"

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
    asm mov DX,629
    asm int 33h
    asm mov AX,8
    asm mov CX,0
    asm mov DX,183
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

void back(char *FILENAME,sprite_ptr small)
{
//	pcx_picture background_pcx; //定义成结构指针
    Fill_Screen(0);//将屏幕涂黑
    PCX_Load_Screen(FILENAME,1);
    Behind_Sprite_Size(small,20,20);//根据鼠标当前位置存储给定大小的背景于小图片结构中（框住一部分图)
}

void mouse_all(Mouse curmouse,Mouse oldmouse,sprite_ptr small) //调用背景图片以及调用鼠标
{
    pcx_picture objects_pcx;
	oldmouse->x=0;oldmouse->y=0;oldmouse->key=0;
    curmouse->x=0;curmouse->y=0;curmouse->key=0;
	//pcx_picture background_pcx,objects_pcx;
	//Set_Video_Mode(VGA256);
	PCX_Load1("mouse.pcx",(pcx_picture_ptr)&objects_pcx,1);//将鼠标图片转化为点阵数组存入obj的结构体中
	Sprite_Init_Size(small,0,0,0,0,0,0,20,20,1);//给小图片的结构成员赋值
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&objects_pcx,small,0,0,0,20,20);//按照用户规定大小将obj中的小图的部分内容转化为点阵放到small结构中
	//Fill_Screen(0);//将屏幕涂黑
	//PCX_Load1(FILENAME,background_pcx,1);  //显示背景图片，并将其点阵存入back结构中
	//Behind_Sprite_Size(small,20,20);      //根据鼠标当前位置存储给定大小的背景于小图片结构中（框住一部分图)
	mousecheck();//初始化鼠标
	mousemove();//设置鼠标移动范围
}

void move_mouse(Mouse curmouse,Mouse oldmouse,sprite_ptr small)//移动中显示鼠标
{
        mouseread(curmouse);
    	if((curmouse->x)!=(oldmouse->x)||(curmouse->y)!=(oldmouse->y))//判断是否移动过鼠标
	      {
		    Erase_Sprite_Size(small,20,20);//显示鼠标移动前被框住的内容
            small->x=curmouse->x/2;
	        small->y=curmouse->y;
		    Behind_Sprite_Size(small,20,20);//保存小图片后背景内容（再框）
	    	Draw_Sprite_Size(small,20,20);//显示小图片于鼠标位置
	    	oldmouse->x=curmouse->x;
		    oldmouse->y=curmouse->y;
    	  }
}

 /********按下按钮*********/
int mouse_on(BUTTON *button)
{
	mou m;
	mouseread(&m);
    if(m.x>(button->x1)*2 && m.x<(button->x2)*2 && m.y>button->y1 && m.y<button->y2 )
        return 1;
    else return 0;
}

