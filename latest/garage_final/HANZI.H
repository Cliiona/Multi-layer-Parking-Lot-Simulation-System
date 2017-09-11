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

void Read_eng(char key,unsigned char *buf);
void Put_eng(int cx,int cy,char key,int fcolor);
void Put_eng_Size(int cx,int cy,int xsize,int ysize,char key,int fcolor);
void Put_String(int x,int y,int x0,int y0,int color,char *str);

#endif