#ifndef PROCESS_H
#define PROCESS_H



#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"hanzi.h"

#define SPEED   18
#define PI (float)3.14159
#define N  11           //车的宽度
#define OX 97
#define INIT_Y 147      //第一个拐点横纵坐标
#define INIT_X  27
#define M       134        //第一个车位纵坐标
#define L       68      // 第三区拐点横坐标
#define H       44       //第四区拐点纵坐标
#define F       2        //微调量
#define P       34      //微调量
#define S       22        //微调量
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
void car(Pp *state,sprite * sprite,Car * p,int *j,int * pro);
void pull_over(Cart cr,Cart boom,sprite_ptr sprite,sprite_ptr head ,int f);
void test();
void login();
void portfunc();
#endif
