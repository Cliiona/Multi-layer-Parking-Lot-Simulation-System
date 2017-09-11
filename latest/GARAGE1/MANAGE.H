#ifndef MANAGE_H
#define MANAGE_H

#include"common.h"
#include"jiemian.h"
#include"mouse.h"
#include"hanzi.h"
#include"draw.h"

char *format_time();
int rand_bi();
char *input(BUTTON *button,char *s);
char * codeput(BUTTON *button,char *s);

char *wrong_times(char *,int *);
int match(char u[6],char c[6]);

void add_to_history(Rec list);
void add_to_today(Rec list);

Rec create_list(int);
Rec create_node();

Rec get_query_list(Rec list,int );
Rec query_car_node(Rec list,int);//没什么用
void query(int port);

Rec insert_node(Rec list,Rec node);
Rec delete_node(Rec list,Rec node);
void destory_list(Rec list);

void rewrite_file(Rec list,int sort);

void delete_one_all(int,int);//delete_all.txt_record
void delete_one_query(int,int);
void delete_query_in_all(Rec);

int print_all(FILE * fp,int flag);
int print_query(int);

void bling(int i,int j,int k,int status);
void current_state(Pp *);
int * count_port(Pp *p);
Pp * book_pause_port(char *,Pp *,int);

int park_time(char *it,char *ot);
void write_ot();
void add_history_to_all();
void new_all();//每次初始化车库后新的all

void save_new_record();

#endif
