#ifndef HANZI_H
#define HANZI_H 

#include"common.h"
#include"draw.h"

void GetHz16(char ch0,char ch1,char *bitdata) ;
void Write_Hz16(char ch0,char ch1,int x,int y,char color);
void WriteHz16(char *str ,int x,int y,char color);//¿¬Ìå

void GetHz16s(char ch0,char ch1,char *bitdata) ;
void Write_Hz16s(char ch0,char ch1,int x,int y,char color);
void WriteHz16s(char *str ,int x,int y,char color);//ËÎÌå
int test(unsigned int a,int k) ;
void hz24_k(char *zw,int x,int y,char color)  ;
void hz24_h(char *zw,int x, int y,char color);
void hz24_s(char *zw,int x, int  y,char color);
void hz24_f(char *zw,int x,int y,char color);
void Blit_Char(int xc,int yc,char c,int color,int trans_flag);
void Blit_String(int x,int y,int color,char *string,int trans_flag);
#endif