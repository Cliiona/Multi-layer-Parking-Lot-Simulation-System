#ifndef CARTOON_H
#define CARTOON_H

#include"common.h"
#include"draw.h"


#define sprite_SPEED 4

#define PARK_OK  0
#define RARK_ING 1
#define PARK_W   2
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 40
#define SCREEN_WIDTH1 320
#define SCREEN_HEIGHT1 200





#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 16

#define MAX_SPRITE_FRAMES 8

#define PALETTE_MASK 0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA 0x3c9
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


typedef struct pcx_picture_typ
	{
	pcx_header header;//pcx头部分
	RGB_color palette[256];//调色板数据部分
	char far *buffer;//数据区指针

	} pcx_picture, *pcx_picture_ptr;



#endif
