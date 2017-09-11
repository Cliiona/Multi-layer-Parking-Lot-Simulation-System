#ifndef DRAW_H
#define DRAW_H

#include"common.h"


void Set_Video_Mode(int);
void Plot(int,int,char);
int Get_Plot(int x,int y);
void Line(int x0,int y0,int x1,int y1,char color) ;
void hLine(int x1,int x2,int y,char color);
void Rectangle(int ,int ,int ,int ,char);
void fill_Rectangle(int,int,int,int,char);
void BPlot(int x,int y,char color);
void Fill_Screen(int value);
void Fill_Screen_Size(int value,int x0,int y0,int x1,int y1);
void Set_Palette_Register(int index,RGB_color_ptr color); 
void PCX_Init(pcx_picture_ptr image);
void PCX_Delete(pcx_picture_ptr image); 
void PCX_Load(char *filename, pcx_picture_ptr image,int enable_palette); 
void PCX_Load_Screen(char *filename,int enable_palette);
void Sprite_Init(sprite_ptr sprite,int x,int y,int ac,int as,int mc,int ms); 
void PCX_Grab_Bitmap(pcx_picture_ptr image, sprite_ptr sprite,int sprite_frame,int grab_x, int grab_y);  
void Behind_Sprite_Size(sprite_ptr sprite,int height,int width); 
void Draw_Sprite_Size(sprite_ptr sprite,int height,int width);
void Erase_Sprite_Size(sprite_ptr sprite,int height,int width); 
void Sprite_Init_Size(sprite_ptr sprite,int x,int y,int ac,int as,int mc,int ms,int height,int width,int frame) ;
void PCX_Grab_Bitmap_Size_Screen(pcx_picture_ptr image,sprite_ptr sprite,int sprite_frame,int grab_x, int grab_y,int height,int width);
void PCX_Load1(char *filename, pcx_picture_ptr image,int enable_palette);
void Sprite_Delete_Size(sprite_ptr sprite,int frame);
void Draw_Sprite(sprite_ptr sprite);  
void Behind_Sprite(sprite_ptr sprite);
void Erase_Sprite(sprite_ptr sprite);   
void Sprite_Delete(sprite_ptr sprite);
void Delay(int clicks);
#endif 
