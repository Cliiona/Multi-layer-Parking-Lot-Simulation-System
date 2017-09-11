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
typedef struct RGB_color_typ  //��ɫ��ɫ�ʽṹ��
{
unsigned char red;
unsigned char green;
unsigned char blue;
}RGB_color,*RGB_color_ptr;

typedef struct pcx_header_typ          //pcxͼƬͷ�ļ�
	{
	char manufacturer; //���쳧
	char version;//�汾
	char encoding;//���뷽ʽ
	char bits_per_pixel;
	int x,y;
	int width,height;  //ͼ���Ⱥ͸߶�
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
	pcx_header header;//pcxͷ����
	RGB_color palette[256];//��ɫ�����ݲ���
	char far *buffer;//������ָ��

	} pcx_picture, *pcx_picture_ptr;



#endif
