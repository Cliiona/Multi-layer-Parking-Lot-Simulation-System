#ifndef DRAW_H
#define DRAW_H

#include"common.h"

void Set_Video_Mode(int mode);
void selectpage(int page);
void Plot(int x, int y, char color);
int Get_Plot(int x,int y);
void Line(int x1,int y1,int x2,int y2,int color);
void Rectangle(int x1,int y1,int x2,int y2,int color);
void readbmp(int x,int y,char *filename);
void part_bmp(int x,int y,char *filename);
void Delay(int clicks);
void Behind_image(int x,int y,int x0,int y0,int *buffer[]);

#endif 
