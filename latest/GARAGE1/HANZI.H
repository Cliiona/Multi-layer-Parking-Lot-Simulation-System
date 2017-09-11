#ifndef HANZI_H
#define HANZI_H 

#include"common.h"
#include"draw.h"

void GetHz16(char ch0,char ch1,char *bitdata);
void Write_Hz16(char ch0,char ch1,int x,int y,char color);
void WriteHz16(char *str ,int x,int y,char color);//¿¬Ìå

void GetHz16s(char ch0,char ch1,char *bitdata);
void Write_Hz16s(char ch0,char ch1,int x,int y,char color);
void WriteHz16s(char *str ,int x,int y,char color);//ËÎÌå

void ShowHz(int left,int top,unsigned char byte1,unsigned  char byte2,int color);
void outhzxy(int x,int y,char *str,int color);

void Blit_Char(int xc,int yc,char c,int color,int trans_flag);
void Blit_String(int x,int y,int color,char *string,int trans_flag);
#endif