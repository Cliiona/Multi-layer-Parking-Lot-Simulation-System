#ifndef HANZI_H
#define HANZI_H 

#include"common.h"
#include"draw.h"

void ShowHz(int left,int top,unsigned char byte1,unsigned  char byte2,int color);
void outhzxy(int x,int y,char *str,int color);

void Read_eng(char key,unsigned char *buf);
void Put_eng(int cx,int cy,char key,int fcolor);
void Put_eng_Size(int cx,int cy,int xsize,int ysize,char key,int fcolor);
void Put_String(int x,int y,int x0,int y0,int color,char *str);

#endif