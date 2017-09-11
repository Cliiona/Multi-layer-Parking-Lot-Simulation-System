#ifndef JIEMIAN_H
#define JIEMIAN_H

#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"manage.h"
#include"process.h"
#include"hanzi.h"


void yes(Pp *);
int jiemian_introduction();

int jiemian_homepage();
int jiemian_manage_login();
int jiemian_manage_unlock();
int jiemian_manage_record();
int jiemian_manage_current(Pp*);
int jiemian_manage_query();
int jiemian_process(Pp*,int *);

void Init_park(Pp *);
void Init_jiemian(char *filename);
int jiemian_park(Pp *,int *show,Car *);

#endif
