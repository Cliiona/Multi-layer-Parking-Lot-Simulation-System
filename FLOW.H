#ifndef FLOW_H
#define FLOW_H

/*INCLUDES*/
#include"common.h"
#include"draw.h"
#include"mouse.h"
#include"manage.h"
#include"process.h"
#include"hanzi.h"

/*FORWARD DECLARATION*/
void yes(Pp*); 
void Init_flow(char *filename);
void Init_park(Pp *state);
int flow_homepage();
int flow_introduction();
int flow_manage_login();
int flow_manage_unlock();
int flow_manage_setting();
int flow_manage_help();
int flow_manage_current(Pp *a);
int flow_manage_record();
int flow_manage_query();
int flow_process(Pp *state,int * show);
int flow_park(Pp *state,int *show,Car *cr);
int flow_outcar(int *show);
int flow_outall(int * show,Pp *state);
int flow_outone(Pp *state,Car* cr,int *show);
int endpage();
void welcome();

#endif
