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

#define VGA256 0x13 //图形模式13h
#define TEXT_MODE 0x03 //普通文本模式
#define F1 0x3b00
#define F2 0x3c00
#define F3 0x3d00
#define ENTER 0x1c0d
#define MAX   15

typedef struct Button
{
    int x1;
    int y1;
    int x2;
    int y2;
    char bname[20];
}BUTTON;

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



#endif
