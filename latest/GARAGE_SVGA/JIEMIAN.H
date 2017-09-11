#ifndef JIEMIAN_H
#define JIEMIAN_H

#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"manage.h"
#include"process.h"
#include"hanzi.h"


void yes(Pp*); 
int jiemian_introduction();
void Init_jiemian(char *filename);
int jiemian_homepage();
int jiemian_manage_login();
int jiemian_manage_setting();
int jiemian_manage_unlock();
int jiemian_manage_record();
int jiemian_manage_current(Pp*);
int jiemian_manage_query();

int jiemian_process(Pp*,int *);  
void Init_park(Pp *state);
int jiemian_park(Pp *state,int *show,Car *cr);
int jiemian_outcar(int *show);
int jiemian_outall(int * show);
int jiemian_outone(Pp *state,Car* cr,int *show);
int endpage();
void welcome();

#endif
