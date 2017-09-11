#ifndef PICTURE_H
#define PICTURE_H


#include"common.h"

#define SCREEN_HEIGHT 40
#define SCREEN_WIDTH 320
#define PALETTE_MASK 0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA 0x3c9

typedef struct pcx_header_typ
	{
	char manufacturer;
	char version;
	char encoding;
	char bits_per_pixel;
	int x,y;
	int width,height;
	int horz_res;
	int vert_res;
	char ega_palette[48];
	char reserved;
	char num_color_planes;
	int bytes_per_line;
	int palette_type;
	char padding[58];

	} pcx_header, *pcx_header_ptr;

typedef struct RGB_color_typ
{
unsigned char red;
unsigned char green;
unsigned char blue;
}RGB_color,*RGB_color_ptr;



typedef struct pcx_picture_typ
	{
	pcx_header header;
	RGB_color palette[256];
	char far *buffer;

	} pcx_picture, *pcx_picture_ptr;

void Set_Palette_Register(int index,RGB_color_ptr color);
void PCX_Init(pcx_picture_ptr image);
void PCX_Delete(pcx_picture_ptr image);
void PCX_Load(char *filename, pcx_picture_ptr image,int enable_palette);
void PCX_Show_Buffer(pcx_picture_ptr image);
void readbmp(int x,int y,char *filename)  ;
void selectpage(register char page);
#endif
