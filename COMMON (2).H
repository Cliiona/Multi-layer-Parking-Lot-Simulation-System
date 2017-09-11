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
#include <malloc.h>
#define SVGA 0x117 //图形模式13h
#define TEXT_MODE 0x03 //普通文本模式

//-----------按键-----------
#define ESC 0x11b
#define BACKSPACE 0xe08
#define ENTER 0x1c0d 

//-----------动画---------------
#define N 26
#define X0 396
#define Y  346
#define Y1 318
#define X2 214
#define Y0 284

//-----------车位管理-----------
#define  TODAY   1
#define  HISTORY 2
#define  ALL     3
#define  QUERY   4

//----------鼠标结构----------------
typedef struct MOUSE
{
    int x;
    int y;
    int key;
}mou,*Mouse;

//---------按钮结构------------------
typedef struct Button
{
    int x1;
    int y1;
    int x2;
    int y2;
}BUTTON;

//---------小车结构---------
typedef struct {
int i;               //车位层数  
int j;               //车位区域
int k;               //车位号
int carnum;           //车牌号
char it[20];              //进库时间
char ot[20];              //出库时间
int time;            //停车时间（秒）
int road[7][2];      //停车路径
}Car,*Cart;

//---------车库结构---------
typedef struct{
int a[3][3][7];            //车位停车状态数组0:空车位1：停车2：被分配3：被预定4:暂停使用,5:即将取车
int f1;                    //一层空车位数
int f2;                    //二层空车位数
int f3;                    //三层空车位数
int m1;                    //满车位数
int m2;
int m3;
int a_park;                //所有空余车位
}Pp,*PARK_port;

//---------记录的结构-------
typedef struct REC{
	int port;             //车位号
	int carnum;           //车牌号
	char it[20];          //进库时间
	char ot[20];          //出库时间
	int time;             //停车时间（秒）
	struct REC *next;
}record,*Rec;//定义2个结构变量

//-----------管理员信息结构---------
typedef struct MAN
{
	char n;
	char code[10];
	char username[10];

}man,*Man;

//---------小车模块---------
typedef struct SP{
int x;      //当前坐标
int y;      //当前坐标
int frame;  //方向
int pro;
int fx;
int state;
}sp;

#endif
