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
    int x;//x坐标
    int y;//y坐标
    }point;
typedef struct windows{
    int kind;  //界面对象类型
    point top;//界面对象坐标起点
    point move;//界面对象坐标偏移
    char *word;//名称，标注
    int color;//文字颜色
    int bk_color;//背景颜色
    int status;//界面对象当前形态状态
    char *hotkey;//热键
    void (far *windows)(struct windows *win);//指向界面对象事件函数的指针
    char far *background; //指向保存背景图像内存的指针
    int bk_flag;//是否要保存背景
    struct windows *next;//指向下一个界面对象
    struct windows *farther;//链表，指向父指针（如弹出菜单选项）
    int active;//界面对象是否激活
    } windows,*windows_ptr;

typedef struct RGB_color_typ
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}RGB_color,*RGB_color_ptr;
#endif
