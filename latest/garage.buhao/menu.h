#ifndef MENU_H 
#define MENU_H 


#include"common.h"
#include"draw.h"

#define MAX 0
#define MIN 1

#define ACTIVE 1
#define NOACTIVE 0

#define ACTIVE_COLOR 1
#define NOACTIVE_COLOR 8

#define VGA256 0x13
#define TEXT_MODE 0x03
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PALETTE_MASK 0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA 0x3c9

#define CHAR_HEIGHT 8
#define CHAR_WIDTH 8

typedef struct point {
    int x;//x����
    int y;//y����
    }point;
typedef struct windows{
    int kind;  //�����������
    point top;//��������������
    point move;//�����������ƫ��
    char *word;//���ƣ���ע
    int color;//������ɫ
    int bk_color;//������ɫ
    int status;//�������ǰ��̬״̬
    char *hotkey;//�ȼ�
    void (far *windows)(struct windows *win);//ָ���������¼�������ָ��
    char far *background; //ָ�򱣴汳��ͼ���ڴ��ָ��
    int bk_flag;//�Ƿ�Ҫ���汳��
    struct windows *next;//ָ����һ���������
    struct windows *farther;//����ָ��ָ�루�絯���˵�ѡ�
    int active;//��������Ƿ񼤻�
    } windows,*windows_ptr;

typedef struct RGB_color_typ
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}RGB_color,*RGB_color_ptr;
#endif
