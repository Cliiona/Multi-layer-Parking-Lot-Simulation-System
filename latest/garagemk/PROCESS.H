#ifndef PROCESS_H
#define PROCESS_H

#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"hanzi.h"

#define SPEED   20
#define PI (float)3.14159
#define N  20           //车的宽度
#define OX 250
#define INIT_Y 174      //第一个拐点横纵坐标
#define INIT_X  50
#define M       153        //第一个车位纵坐标
#define L       235      // 第三区拐点横坐标
#define H       40       //第四区拐点纵坐标
#define Q       126      //第四区右半部拐点横坐标
#define I       5        //微调量
#define F       3        //微调量
#define X       250     
#define Y        60
#define A        7

void floor();
void _cspeed(int x,int y);
void cspeed(int x,int y);
void yline();
void freearea();  
void init_car(Cart p);
void init_PP(PARK_port p);
void assign(int **a[],Cart p);
void road_design(Cart p);
void attain(PARK_port p);
void setlist(Cart ,PARK_port ,int n);
void car(sprite_type * sprite,Car * p,int *j,int *);
void pull_over(char *filename,Cart cr,Cart boom,sprite_ptr sprite,sprite_ptr head ,int f);
void test();
void login();
#endif
