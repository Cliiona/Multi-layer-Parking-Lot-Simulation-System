#ifndef COMMON_H
#define COMMON_H


#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<dos.h>
#include<string.h>
#include<bios.h>
#include<alloc.h>
#include<io.h>
#include<stdio.h>
#include<bios.h>
#include<mem.h>
#include<fcntl.h>
#include<process.h>
#include<malloc.h>

////////////draw////////////
#define ESC 0x11b
#define BACKSPACE 0xe08
#define ENTER 0x1c0d
#define F1 0x3b00
#define F2 0x3c00
#define F3 0x3d00
#define F4 0x3e00
#define LEFT 0x4b00
#define UP 0x4800
#define RIGHT 0x4d00
#define DOWN  0x5000   

#define MAX   15

#define CHAR_HEIGHT 8  //点阵有8列
#define CHAR_WIDTH  8  //点阵有8行
#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT1 40
#define SCREEN_WIDTH1 320
#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 16

#define PARK_OK  0
#define RARK_ING 1
#define PARK_W   2
#define PALETTE_MASK 0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA 0x3c9
#define MAX_SPRITE_FRAMES 4
#define VGA256 0x13 //图形模式13h
#define TEXT_MODE 0x03 //普通文本模式

////////////jiemian///////////

#define process "process.pcx"

//---------按钮结构------------------
typedef struct Button
{
    int x1;
    int y1;
    int x2;
    int y2;
    char bname[20];
}BUTTON;

//----------鼠标结构----------------
typedef struct Mouse
{
    int x;
    int y;
    int key;
}mou,*mouse;
//----------车位信息的结构体-------------
typedef struct Carport
{
    int number;//用101-125 201-225 301-325表示不同层数车位号
    int status; //是否停车 0或1
}PORT;

//------------存放车与车位关系信息的结构体（实时记录）-----
typedef struct CarAndPort
{
	int p_num;//车辆停入的车位
    int c_num;//车牌号
    char check_in_time[30]; //进库时间
    char check_out_time[30];//出库时间
}CARANDPORT;

//-------------查找表结构-----------------
typedef struct Table
{
    int *record;
    int length;
    int park; //每次刷新的进入的车辆数
    int leave;//每次刷新的离开的车辆数
}TABLE;

typedef struct {
int i;               //车位层数  
int j;               //车位区域
int k;               //车位号
int time;            //停车时间（秒）
int road[7][2];      //停车路径
int back[6][2];       //取车路径
}Car,*Cart;

typedef struct{
int a[3][4][9];            //车位停车状态数组
int f1;                    //一层空车位数
int f2;                    //二层空车位数
int f3;                    //三层空车位数
int a_park;                //所有空余车位
}Pp,*PARK_port;

typedef struct{ //引导箭头的结构
                   
int x;               //左上角横坐标
int y;              //左上角纵坐标
int des;            //控制参数（方向，熄灭）1:up,2:right,3:dowm,4:left.0:熄灭
            
}Arrow[MAX];

//------------调色板色彩结构体-------------------
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
int pro;          //行驶结点
}sprite,*sprite_ptr;

#endif
