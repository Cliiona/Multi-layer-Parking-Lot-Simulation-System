#ifndef  MOUSE_H
#define  MOUSE_H

#include "common.h"
#include "draw.h"

void mousecheck();
void mousemove();
void mouseread(Mouse m);

void back(char *FILENAME,sprite_ptr small);
void mouse_all(Mouse curmouse,Mouse oldmouse,sprite_ptr small);
void move_mouse(Mouse curmouse,Mouse oldmouse,sprite_ptr small);

int mouse_on(BUTTON *b);
#endif