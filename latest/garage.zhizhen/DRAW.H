#ifndef DRAW_H
#define DRAW_H

#include"common.h"

#define CHAR_HEIGHT 8  //点阵有8列
#define CHAR_WIDTH  8  //点阵有8行
#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT1 40
#define SCREEN_WIDTH1 320
#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 16


#define PALETTE_MASK 0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA 0x3c9
#define MAX_SPRITE_FRAMES 4
#define VGA256 0x13
#define TEXT_MODE 0x03

typedef struct RGB_color_typ  //调色板色彩结构体
{
unsigned char red;
unsigned char green;
unsigned char blue;
}RGB_color,*RGB_color_ptr;

typedef struct pcx_header_typ          //pcx图片头文件
	{
	char manufacturer; //制造厂
	char version;//版本
	char encoding;//编码方式
	char bits_per_pixel;
	int x,y;
	int width,height;  //图像宽度和高度
	int horz_res;
	int vert_res;
	char ega_palette[48];
	char reserved;
	char num_color_planes;
	int bytes_per_line;
	int palette_type;
	char padding[58];

} pcx_header, *pcx_header_ptr;

typedef struct pcx_picture_typ            //pcx图片结构
	{
	pcx_header header;//pcx头部分
	RGB_color palette[256];//调色板数据部分
	char far *buffer;//数据区指针

	} pcx_picture, *pcx_picture_ptr;

typedef struct sprite_type  //子画面结构体
{
int x,y; //当前位置
int x_old,y_old; //先前位置
int width,height; //宽度和高度
int anim_clock;//子画面时钟
int anim_speed;//子画面速度
int motion_clock;//运动时钟
int motion_speed;//运动速度
char far *frames[MAX_SPRITE_FRAMES];//存放子画面点阵的数组时针
int curr_frame;//当前子画面帧号码
int num_frames;//子画面总帧数
int state;//当前状态
char far *background;//存放子画面背景的指针
}sprite,*sprite_ptr;

void Set_Video_Mode(int);
void Plot(int,int,char);
int Get_Plot(int x,int y);
void line(int x0,int y0,int x1,int y1,char color) ;
void hline(int x1,int x2,int y,char color);
void Rectangle(int ,int ,int ,int ,char);
void fill_Rectangle(int,int,int,int,char);
void BPlot(int x,int y,char color);
void Fill_Screen(int value);
void Fill_Screen_Size(int value,int x0,int y0,int x1,int y1);
void Plot_Xor(int x,int y,char color);
void fill_Rectangle_Xor(int,int,int,int,char);
void hline_Xor(int x1,int x2,int y,char color);
void vline_Xor(int x,int y1,int y2,char color);
void Rectangle_Xor(int x1,int x2,int y1,int y2,char color);
void Set_Palette_Register(int index,RGB_color_ptr color); 
void PCX_Init(pcx_picture_ptr image);
void PCX_Delete(pcx_picture_ptr image); 
void PCX_Load(char *filename, pcx_picture_ptr image,int enable_palette); 
void PCX_Load_Screen(char *filename,int enable_palette);
void Sprite_Init(sprite_ptr sprite,int x,int y,int ac,int as,int mc,int ms); 
void PCX_Grab_Bitmap(pcx_picture_ptr image, sprite_ptr sprite,int sprite_frame,int grab_x, int grab_y);  
void Behind_Sprite_Size(sprite_ptr sprite,int height,int width); 
void Draw_Sprite_Size(sprite_ptr sprite,int height,int width);
void Erase_Sprite_Size(sprite_ptr sprite,int height,int width); 
void Sprite_Init_Size(sprite_ptr sprite,int x,int y,int ac,int as,int mc,int ms,int height,int width,int frame) ;
void PCX_Grab_Bitmap_Size_Screen(pcx_picture_ptr image,sprite_ptr sprite,int sprite_frame,int grab_x, int grab_y,int height,int width);
void PCX_Load1(char *filename, pcx_picture_ptr image,int enable_palette);
void Sprite_Delete_Size(sprite_ptr sprite,int frame);
void Draw_Sprite(sprite_ptr sprite);  
void Behind_Sprite(sprite_ptr sprite);
void Erase_Sprite(sprite_ptr sprite);   
void Sprite_Delete(sprite_ptr sprite);
void Delay(int clicks);
#endif 
