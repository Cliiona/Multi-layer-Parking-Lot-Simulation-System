#ifndef JIEMIAN_H
#define JIEMIAN_H

#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"manage.h"
#include"process.h"
#include"hanzi.h"

void begin();
void jiemianstart(Pp*);  //1
void jiemian_introduction();
//void jiemian_instructions();

void jiemian_homepage(Pp*);//2
int jiemian_manage_login(Pp*);//3
int jiemian_manage_unlock(int *flag,Pp *);
int jiemian_manage_history(Pp*);
int jiemian_manage_current(Pp*);//4
int jiemian_manage_query(Pp*);


int jiemian_process(Pp*);  
//int mouse_on(BUTTON *b);

int automation(int flag,Pp *state);
#endif
