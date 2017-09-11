#include "mouse.h"

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
    asm mov DX,629
    asm int 33h
    asm mov AX,8
    asm mov CX,0
    asm mov DX,183
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
  //  (m->key)=_BX;
}

void back(char *FILENAME,sprite_ptr small)
{
//	pcx_picture background_pcx; //����ɽṹָ��
    Fill_Screen(0);//����ĻͿ��
    PCX_Load_Screen(FILENAME,1);
    Behind_Sprite_Size(small,20,20);//������굱ǰλ�ô洢������С�ı�����СͼƬ�ṹ�У���סһ����ͼ)
}

void mouse_all(Mouse curmouse,Mouse oldmouse,sprite_ptr small) //���ñ���ͼƬ�Լ��������
{
    pcx_picture objects_pcx;
	oldmouse->x=0;oldmouse->y=0;oldmouse->key=0;
    curmouse->x=0;curmouse->y=0;curmouse->key=0;
	//pcx_picture background_pcx,objects_pcx;
	//Set_Video_Mode(VGA256);
	PCX_Load1("mouse.pcx",(pcx_picture_ptr)&objects_pcx,1);//�����ͼƬת��Ϊ�����������obj�Ľṹ����
	Sprite_Init_Size(small,0,0,0,0,0,0,20,20,1);//��СͼƬ�Ľṹ��Ա��ֵ
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&objects_pcx,small,0,0,0,20,20);//�����û��涨��С��obj�е�Сͼ�Ĳ�������ת��Ϊ����ŵ�small�ṹ��
	//Fill_Screen(0);//����ĻͿ��
	//PCX_Load1(FILENAME,background_pcx,1);  //��ʾ����ͼƬ��������������back�ṹ��
	//Behind_Sprite_Size(small,20,20);      //������굱ǰλ�ô洢������С�ı�����СͼƬ�ṹ�У���סһ����ͼ)
	mousecheck();//��ʼ�����
	mousemove();//��������ƶ���Χ
}

void move_mouse(Mouse curmouse,Mouse oldmouse,sprite_ptr small)//�ƶ�����ʾ���
{
        mouseread(curmouse);
    	if((curmouse->x)!=(oldmouse->x)||(curmouse->y)!=(oldmouse->y))//�ж��Ƿ��ƶ������
	      {
		    Erase_Sprite_Size(small,20,20);//��ʾ����ƶ�ǰ����ס������
            small->x=curmouse->x/2;
	        small->y=curmouse->y;
		    Behind_Sprite_Size(small,20,20);//����СͼƬ�󱳾����ݣ��ٿ�
	    	Draw_Sprite_Size(small,20,20);//��ʾСͼƬ�����λ��
	    	oldmouse->x=curmouse->x;
		    oldmouse->y=curmouse->y;
    	  }
}

 /********���°�ť*********/
int mouse_on(BUTTON *button)
{
	mou m;
	mouseread(&m);
    if(m.x>(button->x1)*2 && m.x<(button->x2)*2 && m.y>button->y1 && m.y<button->y2 )
        return 1;
    else return 0;
}
