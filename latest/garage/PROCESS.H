#ifndef PROCESS_H
#define PROCESS_H



#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"hanzi.h"





#define SPEED  10
#define N 25
#define X0 396
#define Y  345
#define Y1 320
#define X2 200
#define Y0 283







/*
#define N  20           //车的宽度
#define OX 319
#define INIT_Y 174      //第一个拐点横纵坐标
#define INIT_X  50
#define M       157        //第一个车位纵坐标
#define L       235      // 第三区拐点横坐标
#define H       40       //第四区拐点纵坐标
#define Q       126      //第四区右半部拐点横坐标
#define I       5        //微调量
#define F       3        //微调量*/

/*
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
*/
void Load_LED(int x,int y,char *s,int state,int color);
void wipeout(int x,int y,int state);
char* transform(int n);
void Draw_Arrow(int x,int y,int m);
int change(int i,int j,int k);
void  writedown(Car *p,Rec  L);
void Draw_Car(sp *ob);
void init_car(Car* p);
void init_pp(Pp * p,Rec s);
void  init_sp(sp *p,int ax,int ay);
void attain(Pp * p);
void assign(Pp * s,Car * p,Rec list);
void assign2(Pp * s,Car * p,Rec list,int n);
void road_design(Cart p);
void car(Pp *state,sp *ob,Car * p);
void pull_over(Pp *state,Car *p);
void parkp();

#endif
