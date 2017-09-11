#ifndef  MOUSE_H
#define  MOUSE_H

#include "common.h"
#include"draw.h"

typedef struct Mouse{
int x;
int y;
int key;
}mou,*mouse;
void mousecheck();
void mousemove();
void mouseread(mouse m);

void back(char *FILENAME,sprite_ptr small);
void mouse_all(mouse curmouse,mouse oldmouse,sprite_ptr small);
void move_mouse(mouse curmouse,mouse oldmouse,sprite_ptr small);

int mouse_on(BUTTON *b);
#endif
