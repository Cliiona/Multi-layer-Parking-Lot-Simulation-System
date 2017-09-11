#ifndef MANAGE_H
#define MANAGE_H

#include"common.h"
#include"jiemian.h"
#include"mouse.h"
#include"hanzi.h"
#include"draw.h"

char *format_time();
int rand_bi();
char *input(BUTTON *button);
char * codeput(BUTTON *button);

int wrong_times(int,int *);
int match(char u[6],char c[6]);

void add_to_history(Rec list);
void add_to_today(Rec list);

Rec create_list(int);
Rec create_node();

void get_query_list(Rec list,int );

void query(int port);

void insert_node(Rec list,record);
void delete_node(Rec list,Rec node);
void destroy_list(Rec list);

void rewrite_file(Rec list,int sort);

void delete_one_all(int,int);//delete_all.txt_record
void delete_one_query(int,int);
void delete_query_in_all(Rec);
void delete_query_in_today(Rec node);

int print_all(int flag);
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
int super_code();
int inf_modify(char *ou,char *nu,char *oc,char *nc,char *ic);
int modify_file(int num,char *nu,char *oc,char *nc);
void check_ou(char *ou);

#endif
