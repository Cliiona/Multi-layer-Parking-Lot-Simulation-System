#ifndef  MOUS_H
#define  MOUS_H

#include "common.h"
#include "draw.h"

void mousecheck();
void mousemove();
void mouseread(mouse m);

void back(char *FILENAME,sprite_ptr small);
void mouse_all(mouse curmouse,mouse oldmouse,sprite_ptr small);
void move_mouse(mouse curmouse,mouse oldmouse,sprite_ptr small);

int mouse_on(BUTTON *b);
#endif