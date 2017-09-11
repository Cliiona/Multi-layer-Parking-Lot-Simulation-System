#ifndef JIEMIAN_H
#define JIEMIAN_H

//#include"common.h"
#include"manage.h"
#include"draw.h"
#include"mous.h"
#include"hanzi.h"
#include"process.h"

void begin();
void jiemianstart();
void jiemian_introduction();
//void jiemian_instructions();

void jiemian_homepage();
void jiemian_manage_login();
void jiemian_manage_history(BUTTON *);
void jiemian_manage_current(BUTTON *);
void jiemian_manage_search(BUTTON *);


void jiemian_process();  
//int mouse_on(BUTTON *b);


#endif
