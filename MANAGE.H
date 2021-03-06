#ifndef MANAGE_H
#define MANAGE_H

/* INCLUDES */
#include"common.h"
#include"flow.h"
#include"mouse.h"
#include"hanzi.h"
#include"draw.h"

/* Foward Redeclaration */
char *format_time();
int rand_bi();
char *input(BUTTON *button);
char * codeput(BUTTON *button);
int wrong_times(int,int *);
int match(char u[6],char c[6]);
int print_file(int flag,int sort);
void add_to_file(Rec list,int sort);
Rec create_list(int);
Rec create_node();
void get_query_list(Rec list,int );
int query(int port);
void insert_node(Rec list,record);
void delete_node(Rec list,Rec node);
void destroy_list(Rec list);
void rewrite_file(Rec list,int sort);
void delete_one_all(int,int);//delete_all.txt_record
void delete_one_query(int,int);
void delete_query_in_all(Rec);
void delete_query_in_today(Rec node);
void bling(int i,int j,int k,int status);
void current_state(Pp *);
int * count_port(Pp *p);
Pp * book_pause_port(char *,Pp *,int);
int park_time(char *it,char *ot);
void write_ot();
void add_history_to_all();
void new_all();
void save_new_record();
int super_code();
int inf_modify(char *ou,char *nu,char *oc,char *nc,char *ic);
int modify_file(int num,char *nu,char *oc,char *nc);
int check_ou(char *ou);
void show_avatar(char *u);
void drop_car1(int cn);
void drop_car2(int cn);

#endif
