#ifndef COMMON_H
#define COMMON_H

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<dos.h>
#include<string.h>
#include<bios.h>
#include<alloc.h>
#include<io.h>
#include<stdio.h>
#include<bios.h>
#include<mem.h>
#include<fcntl.h>
#include<process.h>
#include <malloc.h>
#define SVGA 0x117 //ͼ��ģʽ13h
#define TEXT_MODE 0x03 //��ͨ�ı�ģʽ

//-----------����-----------
#define ESC 0x11b
#define BACKSPACE 0xe08
#define ENTER 0x1c0d 

//-----------����---------------
#define N 26
#define X0 396
#define Y  346
#define Y1 318
#define X2 214
#define Y0 284

//-----------��λ����-----------
#define  TODAY   1
#define  HISTORY 2
#define  ALL     3
#define  QUERY   4

//----------���ṹ----------------
typedef struct MOUSE
{
    int x;
    int y;
    int key;
}mou,*Mouse;

//---------��ť�ṹ------------------
typedef struct Button
{
    int x1;
    int y1;
    int x2;
    int y2;
}BUTTON;

//---------С���ṹ---------
typedef struct {
int i;               //��λ����  
int j;               //��λ����
int k;               //��λ��
int carnum;           //���ƺ�
char it[20];              //����ʱ��
char ot[20];              //����ʱ��
int time;            //ͣ��ʱ�䣨�룩
int road[7][2];      //ͣ��·��
}Car,*Cart;

//---------����ṹ---------
typedef struct{
int a[3][3][7];            //��λͣ��״̬����0:�ճ�λ1��ͣ��2��������3����Ԥ��4:��ͣʹ��,5:����ȡ��
int f1;                    //һ��ճ�λ��
int f2;                    //����ճ�λ��
int f3;                    //����ճ�λ��
int m1;                    //����λ��
int m2;
int m3;
int a_park;                //���п��೵λ
}Pp,*PARK_port;

//---------��¼�Ľṹ-------
typedef struct REC{
	int port;             //��λ��
	int carnum;           //���ƺ�
	char it[20];          //����ʱ��
	char ot[20];          //����ʱ��
	int time;             //ͣ��ʱ�䣨�룩
	struct REC *next;
}record,*Rec;//����2���ṹ����

//-----------����Ա��Ϣ�ṹ---------
typedef struct MAN
{
	char n;
	char code[10];
	char username[10];

}man,*Man;

//---------С��ģ��---------
typedef struct SP{
int x;      //��ǰ����
int y;      //��ǰ����
int frame;  //����
int pro;
int fx;
int state;
}sp;

#endif