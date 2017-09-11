#ifndef  MOUSE_H
#define  MOUSE_H

#include "common.h"
#include "draw.h"

void mousecheck();
void mousemove();
void mouseread(Mouse m);
void Mouse_cpy(Mouse mouse) ;
void Mouse_reshow(Mouse mouse);
void Mouse_show( Mouse mouse);
void move_mouse(Mouse curmouse,Mouse oldmouse);
#endif