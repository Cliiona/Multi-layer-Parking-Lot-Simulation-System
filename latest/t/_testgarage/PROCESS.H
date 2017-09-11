#ifndef PROCESS_H
#define PROCESS_H



#include"common.h"
#include"draw.h"
#include"mous.h"
#include"hanzi.h"

#define SPEED   20
#define N  11           //车的宽度
#define OX 120
#define INIT_Y 167      //第一个拐点横纵坐标
#define INIT_X  29
#define M       131        //第一个车位纵坐标
#define L       68      // 第三区拐点横坐标
#define H       44       //第四区拐点纵坐标
#define F       2        //微调量
#define P       58      //微调量
#define S       0        //微调量
#define X       250     
#define Y        60
#define A        7
#define G        105
#define V        105
#define D        146

void floor();
void _cspeed(int x,int y);
void cspeed(int x,int y);
void yline();
void freearea();  
void init_car(Cart p);
void init_PP(PARK_port p);
void assign(Pp*,Car*p);
void road_design(Car* p);
void attain(PARK_port p);
void setlist(Cart ,PARK_port ,int n);
void car(Pp *state,sprite * sprite,Car * p,int *j,int * pro);
void pull_over(Cart cr,Cart boom,sprite_ptr sprite,sprite_ptr head ,int f);
void test(void);
void login();
void portfunc();
#endif
