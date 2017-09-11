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

typedef struct Button
{
    int x1;
    int y1;
    int x2;
    int y2;
    char bname[20];
}BUTTON;

typedef struct {
char *number;          //车牌号
int i;               //车位层数  
int j;               //车位区域
int k;               //车位号
int time;            //停车时间（秒）
int road[5][2];      //停车路径
}Car,*Cart;

typedef struct{
int a[3][4][9];            //车位停车状态数组
int f1;                    //一层即将停车数
int f2;                    //二层即将停车数
int f3;                    //三层即将停车数
int a_park;                //所有空余车位
}Pp,*PARK_port;


#endif
