#include "mouse.h"

int arrowMousePixSave[16][16];    /*���ڱ�����꼴�����ǵ�����*/
int arrowMouseDraw[16][10]={    /*���������״,����1:��ʾ���ı߽�,2:��ʾ���߽�����Χ������,3:��ʾ������������*/
    {1,1,3,3,3,3,3,3,3,3},
    {1,2,1,3,3,3,3,3,3,3},
    {1,2,2,1,3,3,3,3,3,3},
    {1,2,2,2,1,3,3,3,3,3},
    {1,2,2,2,2,1,3,3,3,3},
    {1,2,2,2,2,2,1,3,3,3},
    {1,2,2,2,2,2,2,1,3,3},
    {1,2,2,2,2,2,2,2,1,3},
    {1,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,2,1,3,3},
    {1,2,2,2,2,2,1,3,3,3},
    {1,2,1,3,1,2,2,1,3,3},
    {1,1,3,3,1,2,2,1,3,3},
    {3,3,3,3,3,1,2,2,1,3},
    {3,3,3,3,3,1,2,2,1,3},
    {3,3,3,3,3,3,1,2,2,1} };
void mousecheck()
{
    int check;
    asm mov AX,0
    asm int 33h
    asm mov check,AX
}
void mousemove() //�����ƶ���Χ
{
    asm mov AX,7
    asm mov CX,0
    asm mov DX,1023
    asm int 33h
    asm mov AX,8
    asm mov CX,0
    asm mov DX,767
    asm int 33h
}
void mouseread(Mouse m)
{
    _AX=3;
    asm int 33h
    (m->x)=_CX;
    (m->y)=_DX;
    _AX=5;
    asm int 33h;
    (m->key)=_BX;
}

/* ***************************************************************
 * Function:Mouse_cpy
 * Description:������򱳾���ȡ
 * ***************************************************************/
void Mouse_cpy(Mouse mouse)     
{
    int i,j;
    unsigned long pos;
    char oldpage,newpage;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=((mouse->y)*1024L+(mouse->x))/32768;
    newpage=oldpage;
    selectpage(newpage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            pos=(i+(mouse->y))*(1024L)+j+(mouse->x);
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            arrowMousePixSave[i][j]=video_buffer[pos%65536];
        }
    }
    return;
}

/* ***************************************************************
 * Function:Mouse_reshow
 * Description:������򱳾���ȡ��������ʾ
 * ***************************************************************/
void Mouse_reshow(Mouse mouse)       
{
    int i,j;
    char oldpage,newpage;
    unsigned long pos;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=((mouse->y)*(1024L)+(mouse->x))/32768;
    newpage=oldpage;
    selectpage(oldpage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            pos=(i+(mouse->y))*(1024L)+j+(mouse->x);
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            video_buffer[pos%65536]=arrowMousePixSave[i][j];
        }
    }
    return;
}

/* ***************************************************************
 * Function:Mouse_show
 * Description:�����ʾ
 * ***************************************************************/
void Mouse_show( Mouse mouse)     
{
    int i,j;
    unsigned long pos;
	unsigned long oldpage,newpage;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=((mouse->y)*(1024L)+(mouse->x))/32768;
    newpage=oldpage;
    selectpage(oldpage);
    for(i=0;i<16;i++)
    {
        for(j=0;j<10;j++)
        {
            pos=(i+(mouse->y))*1024L+j+(mouse->x);
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            if(arrowMouseDraw[i][j]==1)
                video_buffer[pos%65536]=0;
            else if(arrowMouseDraw[i][j]==2)    /* �����*/
                video_buffer[pos%65536]=0xffff;
        }
    }
    delay(15);
    return;
}

/* ***************************************************************
 * Function:move_mouse(Mouse curmouse,Mouse oldmouse)
 * Description:�ƶ�����������ʾ���
 * Calls:mouseread��Mouse_reshow��Mouse_cpy��Mouse_show
 * Called by:flow���ֺ���
 * Input:Mouse curmouse--��ǰ���ṹ��Mouse oldmouse--ԭ�����ṹ
 * return��
 * others:��
 * ***************************************************************/
void move_mouse(Mouse curmouse,Mouse oldmouse)
{       
        mouseread(curmouse);
    	if((curmouse->x)!=(oldmouse->x)||(curmouse->y)!=(oldmouse->y))//�ж��Ƿ��ƶ������
	   {
                Mouse_reshow(oldmouse);//��ʾ����ƶ�ǰ����ס������
				Mouse_cpy(curmouse);//�������󱳾����ݣ��ٿ�
	    	    Mouse_show(curmouse);
	    	    oldmouse->x=curmouse->x;
		        oldmouse->y=curmouse->y;        
       }
}


