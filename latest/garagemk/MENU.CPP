#include"menu.h"
windows_ptr head;
windows_ptr now;
windows_ptr pre;
windows_ptr win_now;
windows_ptr last;
void Object_Init(windows_ptr ptr,int kind,int x,int y,int move_y,char *word,int color ,int bk_color,int status, char *hotkey,int bk_flag,void (far *windows),int active)
{
    ptr->kind=kind;//初始化界面对象类型
    ptr->top.x=x;//初始化界面对象起始横坐标
    ptr->top.y=y;//初始化界面对象起始纵坐标
    ptr->move.x=move_x;//初始化界面对象偏移横坐标
    ptr->move.y=move_y;//初始化界面对象偏移纵坐标
    ptr->word=word;//初始化界面对象文字标注
    ptr->color=color;//初始化界面对象文字颜色
    ptr->bk_color=bk_color;//初始化界面对象背景颜色
    ptr->status=status;//初始化界面形态状态
    ptr->hotkey=hotkey;//初始化界面对象热键
    ptr->windows=windows;//初始化界面对象是否要保存背景
    if(bk_flag==1)//如果要保存背景，初始化界面对象背景图像内存空间
    {
        ptr->background=(char far *)malloc((move_x+1)*(move_y+1)+1);

    }ptr->active=active;//初始化界面对象的激活状态
}mscurstype arrow={0x3fff,0x1fff,0x0fff,0x07ff,
 0x03ff,0x01ff,0x00ff,0x007f,
 0x003f,0x00ff,0x01ff,0x10ff,
 0x30ff,0xf87f,0xf87f,0xfc3f,
 0x0000,0x4000,0x6000,0x7000,
 0x7800,0x7c00,0x7e00,0x7f00,
 0x7f80,0x7e00,0x7c00,0x4600,
 0x0600,0x0300,0x0300,0x0180,0,0};

mscurstype lin={0xe3e3,0xe3e3,0xe3e3,0xe3e3,
0x8080, 0x8080,0x8080,0xe3e3,
0xc1c1, 0x8080,0x0000,0x2323,
0xe3e3,0xe3e3,0xe3e3, 0xe3e3,
 0x0000,0x0808,0x0808,0x0808,
 0x0808,0x3e3e,0x0808,0x0808,
 0x1c1c,0x2a2a,0x4848,0x0808,
 0x0808,0x0808,0x0808,0x0000,2,0};

mscurstype qi={0xff89,0xff88,0xff8e,0x8001,
0x8001,0x8001,0x8d8f,0x8c8c,
0x8d8c,0x8d88,0x8009,0x8983,
0x9542,0x1540,0x39b0,0x7d79,
0x0000,0x0020,0x0020,0x0020,
0x3ffc,0x2020,0x2020,0x2020,
0x2020,0x2020,0x2020,0x2020,
0x0000,0x4008,0x0004,0x0000,16,0};

mscurstype arrowcurs={16383,8191,4095,2047,1023,511,225,127,63,
		       31,511,4351,12543,-1921,-1921,-961,0,16348,
		       24576,28672,30720,31744,32256,32512,32640,
		       32704,31744,17920,17920,768,384,192,-1,-1};



unsigned char far *rom_char_set=(char far *)0xF000FA6EL;



void Delay(int clicks)  //延迟函数
{
unsigned int far *clock=(unsigned int far *)0x0000046CL;
unsigned int now;
now=*clock;
while(abs(*clock-now)<clicks){}
}



void Set_Palette_Register(int index,RGB_color_ptr color)
{
	outp(PALETTE_MASK,0xff);
	outp(PALETTE_REGISTER_WR,index);
	outp(PALETTE_DATA,color->red);
	outp(PALETTE_DATA,color->green);
	outp(PALETTE_DATA,color->blue);
}
void Get_Palette_Register(int index,RGB_color_ptr color)
{
	outp(PALETTE_MASK,0xff);
	outp(PALETTE_REGISTER_RD,index);
	color->red=inp(PALETTE_DATA);
	color->green=inp(PALETTE_DATA);
	color->blue=inp(PALETTE_DATA);

}



void Blit_Char(int xc,int yc,char c,int color,int trans_flag)
{unsigned char far *video_buffer=(char far *)0xA0000000L;
int offset,x,y;
char far *work_char;
unsigned char bit_mask=0x80;
work_char=rom_char_set+c*CHAR_HEIGHT;
offset=(yc<<8)+(yc<<6)+xc;
for(y=0;y<CHAR_HEIGHT;y++)
{
bit_mask=0x80;
for(x=0;x<CHAR_WIDTH;x++)
{
if((*work_char&bit_mask))
video_buffer[offset+x]=color;
else if(!trans_flag)
video_buffer[offset+x]=0;
bit_mask=(bit_mask>>1);
}
offset+=SCREEN_WIDTH;
work_char++;
}
}


void Blit_String(int x,int y,int color,char *string,int trans_flag)
{
int index;
for(index=0;string[index]!=0;index++)
{
Blit_Char(x+(index<<3),y,string[index],color,trans_flag);
}
}

void Draw_Windows(windows_ptr win)
{
	switch(win->kind)
	{
		case WINDOWS:
		{
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x,win->top.y+win->move.y,WINDOWS_COLOR_DARK);
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x-1,win->top.y+win->move.y-1,WINDOWS_COLOR_LIGHT);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+win->move.y-1,WINDOWS_COLOR_OUT);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+10,WINDOWS_COLOR_TITLE);
			if(win->active==ACTIVE)
				Blit_String(win->top.x+2,win->top.y+2,win->color,win->word,1);
			else
				Blit_String(win->top.x+2,win->top.y+2,NOACTIVE_COLOR,win->word,1);
			Fill_Rectangle(win->top.x+2,win->top.y+22,win->top.x+win->move.x-2,win->top.y+win->move.y-2,WINDOWS_COLOR_LIGHT);
			Fill_Rectangle(win->top.x+2,win->top.y+22,win->top.x+win->move.x-3,win->top.y+win->move.y-3,WINDOWS_COLOR_DARK);
			Fill_Rectangle(win->top.x+3,win->top.y+23,win->top.x+win->move.x-3,win->top.y+win->move.y-3,WINDOWS_COLOR_IN);

			break;
		}
		case BUTTON_MENU:
		{
			if(win->active==ACTIVE)
				Blit_String(win->top.x+2,win->top.y+1,win->color,win->word,1);
			else
				Blit_String(win->top.x+2,win->top.y+1,NOACTIVE_COLOR,win->word,1);
			break;
		}
		case BUTTON:
		{
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x,win->top.y+win->move.y,BUTTON_COLOR_DARK);
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR_LIGHT);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR);
			if(win->active==ACTIVE)
				Blit_String(win->top.x+2,win->top.y+1,win->color,win->word,1);
			else
				Blit_String(win->top.x+2,win->top.y+1,NOACTIVE_COLOR,win->word,1);
			break;
		}
		case BUTTON_PRESS:
		{
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x,win->top.y+win->move.y,BUTTON_COLOR_LIGHT);
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR_DARK);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR);
			Blit_String(win->top.x+2,win->top.y+1,win->color,win->word,1);
			break;
		}
		case BUTTON_CLOSE:
		{
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x,win->top.y+win->move.y,BUTTON_COLOR_DARK);
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR_LIGHT);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR);
			if(win->active==ACTIVE)
			{
				Bline(win->top.x+2,win->top.y+2,win->top.x+win->move.x-2,win->top.y+win->move.y-2,win->color);
				Bline(win->top.x+win->move.x-2,win->top.y+2,win->top.x+2,win->top.y+win->move.y-2,win->color);
			}
			else
			{
				Bline(win->top.x+2,win->top.y+2,win->top.x+win->move.x-2,win->top.y+win->move.y-2,NOACTIVE_COLOR);
				Bline(win->top.x+win->move.x-2,win->top.y+2,win->top.x+2,win->top.y+win->move.y-2,NOACTIVE_COLOR);
			}
			break;
		}
		case BUTTON_CLOSE_PRESS:
		{
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x,win->top.y+win->move.y,BUTTON_COLOR_LIGHT);
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR_DARK);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR);
			Bline(win->top.x+2,win->top.y+2,win->top.x+win->move.x-2,win->top.y+win->move.y-2,win->color);
			Bline(win->top.x+win->move.x-2,win->top.y+2,win->top.x+2,win->top.y+win->move.y-2,win->color);
			break;
		}
		case BUTTON_SMALL:
		{
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x,win->top.y+win->move.y,BUTTON_COLOR_DARK);
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR_LIGHT);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR);
			if(win->active==ACTIVE)
				H_Line(win->top.x+2,win->top.x+win->move.x-2,win->top.y+win->move.y-2,win->color);
			else
				H_Line(win->top.x+2,win->top.x+win->move.x-2,win->top.y+win->move.y-2,NOACTIVE_COLOR);
			break;
		}
		case BUTTON_SMALL_PRESS:
		{
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x,win->top.y+win->move.y,BUTTON_COLOR_LIGHT);
			Fill_Rectangle(win->top.x,win->top.y,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR_DARK);
			Fill_Rectangle(win->top.x+1,win->top.y+1,win->top.x+win->move.x-1,win->top.y+win->move.y-1,BUTTON_COLOR);
			H_Line(win->top.x+2,win->top.x+win->move.x-2,win->top.y+win->move.y-2,win->color);
			break;
		}
		default:break;
	}
}
void Behind_Button(windows_ptr win)
{

char far *work_back;
int work_offset=0,offset,y;


work_back = win->background;


offset = (win->top.y << 8) + (win->top.y << 6) + win->top.x;

for (y=0; y<BUTTON_Y; y++)
    {

    _fmemmove((void far *)&work_back[work_offset],
	     (void far *)&video_buffer[offset],
	     BUTTON_X);


    offset      += SCREEN_WIDTH;
    work_offset += BUTTON_X;

    }

}

void Erase_Button(windows_ptr win)
{

char far *work_back;
int work_offset=0,offset,y;


work_back = win->background;


offset = (win->top.y << 8) + (win->top.y << 6) + win->top.x;

for (y=0; y<BUTTON_Y; y++)
    {

    _fmemmove((void far *)&video_buffer[offset],
	     (void far *)&work_back[work_offset],
	     BUTTON_X);


    offset      += SCREEN_WIDTH;
    work_offset += BUTTON_X;

    }

}

void Object_Delete(windows_ptr win)
{

	int index;

	if(win->bk_flag==1)
		free(win->background);
	free(&win);
}


void win(windows_ptr win)
{
//	printf("\n\n\n\n\nwindows fuction is in use\n");
}

void clo(windows_ptr win)
{
	win->kind=BUTTON_CLOSE_PRESS;
	Draw_Windows(win);
	Delay(5);
	win->kind=BUTTON_CLOSE;
	Draw_Windows(win);
	Delay(5);
	Set_Video_Mode(TEXT_MODE);
	exit(1);
}

void bt1(windows_ptr win)
{
	int x,y,fcolor;
	long i;
	win->kind=BUTTON_PRESS;
	Draw_Windows(win);
	Delay(5);
	win->kind=BUTTON;
	Draw_Windows(win);
	men(win->father);
	for(i=0;i<1000000;i++)
	{
		x=rand()%(WINDOWS_X_MOVE-20);
		y=rand()%(WINDOWS_Y_MOVE-40);
		fcolor=rand()%(256)+1;
		Plot_Pixel_Fast(WINDOWS_X+10+x,WINDOWS_Y+30+y,fcolor);
	}

}

void bt2(windows_ptr win)
{
	win->kind=BUTTON_PRESS;
	Draw_Windows(win);
	Delay(5);
	win->kind=BUTTON;
	Draw_Windows(win);
	Delay(5);
	Set_Video_Mode(TEXT_MODE);
	exit(1);
}

void sma(windows_ptr win)
{
	win->kind=BUTTON_SMALL_PRESS;
	Draw_Windows(win);
	Delay(5);
	win->kind=BUTTON_SMALL;
	Draw_Windows(win);
	Blit_String(WINDOWS_X+10,WINDOWS_Y+30,0,"small button is in use",1);
/*	if(win->status==MAX)
	{
		Fill_Screen_Size(0,win_now.top.x,win_now.top.y,win_now.top.x+win_now.move.x,win_now.top.y+win_now.move.y);
		win->status=MIN;
	}
	else(win->status==MIN);
*/
}

void men(windows_ptr win)
{
	windows *restore;
	if(win->status==MIN)
	{
		now=(struct windows *)malloc(sizeof(struct windows));
		Object_Init(now,BUTTON,WINDOWS_X+4,WINDOWS_Y+BUTTON_Y+13,BUTTON_X-1,BUTTON_Y-1,"game",0,24,0,"",1,bt1,ACTIVE);
		now->father=win;
		Behind_Button(now);
		Draw_Windows(now);
		last->next=now;
		pre=now;
		now=(struct windows *)malloc(sizeof(struct windows));
		Object_Init(now,BUTTON,WINDOWS_X+4,WINDOWS_Y+BUTTON_Y*2+13,BUTTON_X-1,BUTTON_Y-1,"exit",0,24,0,"",1,bt2,ACTIVE);
		now->father=win;
		Behind_Button(now);
		Draw_Windows(now);
//		getch();
//		Erase_Button(*now);
//		getch();
		pre->next=now;
		pre=now;
		pre->next=NULL;

		win->status=MAX;

	}
	else if(win->status==MAX)
	{
		restore=head;
		if(restore->bk_flag==1)
		{
			Erase_Button(restore);
			Object_Delete(restore);
		}
		do{
			restore=restore->next;
			if(restore->bk_flag==1)
			{
				Erase_Button(restore);
				Object_Delete(restore);
			}
		}while(restore->next!=NULL);
		last->next=NULL;
		win->status=MIN;
	}
}

void Judge_Object(void)  //检测函数
{
	int xmouse,ymouse,btnmouse;
	static int btn=-1;
	windows_ptr test;
	Squeeze_Mouse(MOUSE_BUTT_POS,&xmouse,&ymouse,&btnmouse);
	if(btnmouse==btn)
		return;
	else
		btn=btnmouse;
	xmouse=xmouse/2;
	ymouse=ymouse;
	if(btnmouse==1)
	{
		test=head;
		if((xmouse>=test->top.x&&xmouse<=test->top.x+test->move.x)&&
		(ymouse>=test->top.y&&ymouse<=test->top.y+test->move.y))
		{
			Squeeze_Mouse(MOUSE_HIDE,0,0,0);
			if(test->active==ACTIVE)
				test->windows(test);
			Squeeze_Mouse(MOUSE_SHOW,0,0,0);
		}
		do{
			test=test->next;
			if((xmouse>=test->top.x&&xmouse<=test->top.x+test->move.x)&&
			(ymouse>=test->top.y&&ymouse<=test->top.y+test->move.y))
			{
				Squeeze_Mouse(MOUSE_HIDE,0,0,0);
				if(test->active==ACTIVE)
					test->windows(test);
				Squeeze_Mouse(MOUSE_SHOW,0,0,0);
			}
		}while(test->next!=NULL);

	}
}

void menu(void)
{
	windows_ptr test;
	Set_Video_Mode(VGA256);
	now=pre=(struct windows *)malloc(sizeof(struct windows));
	Object_Init(now,WINDOWS,WINDOWS_X,WINDOWS_Y,WINDOWS_X_MOVE,WINDOWS_Y_MOVE,"gerage system",0,24,0,"",0,win,ACTIVE);
	win_now=now;
	Draw_Windows(now);
	head=now;
	now=(struct windows *)malloc(sizeof(struct windows));
	Object_Init(now,BUTTON_MENU,WINDOWS_X+2,WINDOWS_Y+11,BUTTON_X-1,BUTTON_Y-1,"menu",0,24,MIN,"",0,men,ACTIVE);
	Draw_Windows(now);
	pre->next=now;
	pre=now;
	now=(struct windows *)malloc(sizeof(struct windows));
	Object_Init(now,BUTTON_SMALL,WINDOWS_X+WINDOWS_X_MOVE-(BUTTON_XY+2)*2,WINDOWS_Y+2,BUTTON_XY-1,BUTTON_XY-1,"",0,24,MAX,"",0,sma,NOACTIVE);
	Draw_Windows(now);
	pre->next=now;
	pre=now;
	now=(struct windows *)malloc(sizeof(struct windows));
	Object_Init(now,BUTTON_CLOSE,WINDOWS_X+WINDOWS_X_MOVE-BUTTON_XY-2,WINDOWS_Y+2,BUTTON_XY-1,BUTTON_XY-1,"",0,24,0,"",0,clo,ACTIVE);
	Draw_Windows(now);
	pre->nextnow;
	pre=now;
	pre->next=NULL;
	last=pre;
/*
	getch();
	test=head;
	test->windows(*test);
	getch();

	do{
		test=test->next;
		test->windows(*test);
		getch();
	}while(test->next!=NULL);
*/
	Squeeze_Mouse(MOUSE_RESET,0,0,0);
	mscurson(handcurs);

	while(1){
		Judge_Object();
	}
}
