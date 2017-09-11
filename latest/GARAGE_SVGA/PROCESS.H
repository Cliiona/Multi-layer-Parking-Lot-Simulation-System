#ifndef PROCESS_H
#define PROCESS_H

#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"hanzi.h"
#include"jiemian.h"



char* transform(int n);
void Draw_Arrow(int x,int y,int m);
int change(int i,int j,int k);
void bk();
void Draw_Car(sp *ob);
void init_car(Car* p);
void init_pp(Pp * p,Rec s);
void init_sp(sp *p,int ax,int ay);
void attain(Pp * p);
void assign2(Pp * s,Car * p,Rec list,int n);
void road_design(Cart p);
int tofloor(Pp *state,int a);  
void car(Pp *state,sp *ob,Car * p,int,int *);
void extra_car(Pp *state,Car *p,sp *ob,int a,int k,int *f);
int pull_over(Pp *state,Car *p,int,int);
void Init_outsp(sp*p,Car *cr);
void car_message(Pp *state,Car *cr,int f);
void carout(Pp *state,sp *ob,Car * p,int a,int *h);
void tick_car(Pp *state,Car *p,sp *ob,int a,int k,int *f);
int drop_off(Pp *state,Car *p,int n,int a,int func);
#endif
