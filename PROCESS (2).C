#include"process.h"
/*功能准备模块*/
/* **********************************************************************************************
 * Function: transform
 * Description:将int转化为"02"格式的char型
 * Calls:无
 * Called by: extra_car(Pp *state,Car *p,sp *ob,int a,int k,int *f);flow_park();
 * Input:n:int型
 * return:char型
 * others:无
 * **********************************************************************************************/
char* transform(int n)
{
    char m1,m2;
    char *s=NULL;
    m1=n/10+'0';
    m2=n%10+'0';
    s[0]=m1;
    s[1]=m2;
    s[2]='\0';
    return s;
}

/* **********************************************************************************************
 * Function: change
 * Description:将车位号转换成一个整型
 * Calls:无
 * Called by: extra_car(Pp *state,Car *p,sp *ob,int a,int k,int
 * *f);flow_park();Car_massage();flow_outone();
 * Input:n:int型
 * return:int型
 * others:无
 * **********************************************************************************************/
int change(int i,int j,int k)                     
{
    int m;
    m=(i+1)*100+(j+1)*10+k+1;
    return m;
}

/* **********************************************************************************************
 * Function: write_node
 * Description:将小车信息写入链表
 * Calls:无
 * Called by: init_pp();assign2();
 * Input:n:Car *p,Rec list
 * return:无
 * others:无
 * **********************************************************************************************/
void write_node(Car *p,Rec list)
{
     record node;
     strcpy(p->it,format_time());              //系统时间
     node.port=change(p->i,p->j,p->k);//将数据放入这个节点
     node.carnum=p->carnum;
     strcpy(node.it,p->it);  //调用格式化时间函数，把时间字符串
     strcpy(node.ot,p->ot);
     node.time=p->time;
     node.next=NULL; //给这个结点的指针域赋值
	 insert_node(list,node);//将节点插入到已有链表中
}

/* **********************************************************************************************
 * Function:tofloor(Pp *state,int a)
 * Description:得到任意楼层空余车位
 * Calls:无
 * Called by: extra_car();tick_car();
 * Input:Pp *state,int a
 * return:int：a层空余车位数目
 * others:无
 * **********************************************************************************************/
int tofloor(Pp *state,int a)
{
    int floor;
     switch(a)
    {
        case 0:
               floor=state->f1;
               break;
        case 1:
               floor=state->f2;
               break;
        case 2:floor=state->f3;
               break;
    }

     return floor;
}
/*图形准备模块*/
/* **********************************************************************************************
 * Function: Draw_Arrow
 * Description:控制引导函数
 * Calls:库函数
 * Called by:car();carout();
 * Input:n:x:引导屏横坐标，y:引导屏纵坐标,m:引导状态量
 * return:无
 * others:无
 * **********************************************************************************************/
void Draw_Arrow(int x,int y,int m)    
{
    int c=2;
    setcolor(c);
    switch(m)        //判断引导状态
    {
        
        case 0:line(x+1,y+6,x+6,y+1);
               line(x+6,y+1,x+11,y+6);
               line(x+1,y+9,x+6,y+4);
               line(x+6,y+4,x+11,y+9);
               break;
        case 2:line(x+3,y+1,x+8,y+6);
               line(x+3,y+11,x+8,y+6);
               line(x+6,y+1,x+11,y+6);
               line(x+6,y+11,x+11,y+6);
               break;
       
        case 4:line(x+1,y+1,x+6,y+6);
               line(x+6,y+6,x+11,y+1);
               line(x+1,y+6,x+6,y+11);
               line(x+6,y+11,x+11,y+6);
               break;    
        case 6:line(x+1,y+6,x+6,y+1);
               line(x+1,y+6,x+6,y+11);
               line(x+4,y+6,x+9,y+1);
               line(x+4,y+6,x+9,y+11);
               break;        
    }

}

/* **********************************************************************************************
 * Function: bk
 * Description:画车库背景
 * Calls:库函数
 * Called by:pull_over();drop_off();
 * **********************************************************************************************/
void bk()                         
{
int i,j,x=120,y=120;
 setfillstyle(11,9);
 setbkcolor(0);
 setcolor(9);
 line(0,0,640,0);
 line(0,0,0,62);
 line(9,61,53,2);
 line(53,1,579,1);
 line(9,62,23,62);
 line(24,62,34,48);
 line(18,47,34,47);
 line(0,65,21,65);
 line(22,65,22,215);
 line(0,216,22,216);
 line(8,217,24,217);
 line(24,217,37,197);
 line(37,92,37,197);
 line(37,91,43,83);
 line(37,46,37,78);
 line(25,62,35,51);
 line(25,63,25,211);
 line(36,51,36,193);
 line(25,211,36,193);
 line(7,217,7,349);
 line(0,349,7,349);
 line(0,215,0,349);
 line(37,78,42,71);
 line(19,46,37,46);
 line(42,14,42,71);
 line(43,13,60,13);
 line(60,17,60,81);
 line(44,81,60,81);
 line(44,82,61,82);
 line(61,82,73,70);
 line(639,0,639,349);
 line(0,350,640,350);
 rectangle(43,14,60,82);
 line(73,0,60,14);
 line(73,0,73,70);
 line(72,1,72,70);
 rectangle(73,1,579,70);
 line(639,0,639,75);
 line(579,1,639,75);
 line(579,70,639,140);
 rectangle(632,141,639,349);
 line(632,141,579,78);
 line(579,78,65,78);
 line(0,0,0,349);
 floodfill(633,142,9);
 floodfill(600,5,9);
 floodfill(24,194,9);
 floodfill(1,1,9);
 floodfill(2,348,9);
 floodfill(575,77,9);
 setfillstyle(1,8);
 floodfill(630,170,9);
 setcolor(15);
 setfillstyle(1,7);
 rectangle(x-10,y-8,x+56,y+186);
 rectangle(x+130-10,y-8,x+130+56,y+186);
 rectangle(x+350-10,y-8,x+350+56,y+186);
 floodfill(x,y,15);
 floodfill(x+130,y+130,15);
 floodfill(480,y,15);
 setfillstyle(4,14);
 setcolor(0);
 bar(340,337,440,349);//进出口
 floodfill(400,348,0); 


 setcolor(15);
 for(i=0;i<2;i++)
 {
	 rectangle(x+130*i,y-4,x+46+130*i,y+178);
	 for(j=0;j<6;j++)
	 {
		 line(x+130*i,y+22+j*26,x+46+130*i,y+22+j*26);
	 }
 }
  rectangle(x+350,y-4,x+350+46,y+178);
	 for(j=0;j<6;j++)
	 {
		 line(x+350,y+22+j*26,x+350+46,y+22+j*26);
	 }
}

/* **********************************************************************************************
 * Function: bk_car(Pp *state,int f)
 * Description:分析数据后画出车库已经停放的车
 * Calls:库函数
 * Called by:pull_over();drop_off();
 * Input:Pp *state,int f
 * return:无
 * others:无
 * **********************************************************************************************/
void bk_car(Pp *state,int f)
{
    int  j, k;
    int  x, y;

    for(j=0;j<3;j++)
    {
	for(k=0;k<7;k++)
	{
	    if(state->a[f][j][k]==1)
	    {
		 y=283-N*k;
				switch(j)
		{
		    case 0:  x=502;
			      setcolor(0);
		  setfillstyle(1,15);
	       line(x+3,y-10,x+3,y+10);
	       line(x-28,y-10,x+3,y-10);
	       line(x-28,y+10,x+3,y+10);
	       line(x-28,y-10,x-28,y+10);
	       floodfill(x-1,y,0);
	       setfillstyle(1,3);
		  // arc(x,y,270,90,8);
	       line(x,y-7,x,y+7);
	       line(x-25,y-7,x,y-7);
	       line(x-25,y+7,x,y+7);
	       line(x-25,y-7,x-25,y+7);
	       floodfill(x-1,y,0);
		line(x+3,y-10,x,y-7);
	       line(x+3,y+10,x,y+7);
	       line(x-28,y+10,x-25,y+7);
	       line(x-28,y-10,x-25,y-7);
	       break;
		    case 1:
			     x=266;

				setcolor(0);
		  setfillstyle(1,15);
		 line(x-3,y-10,x-3,y+10);
	       line(x-3,y-10,x+28,y-10);
	       line(x-3,y+10,x+28,y+10);
	       line(x+28,y-10,x+28,y+10);
	       floodfill(x+1,y,0);
	       setfillstyle(1,3);
		  // arc(x,y,90,270,8);
		  line(x,y-7,x,y+7);
	       line(x,y-7,x+25,y-7);
	       line(x,y+7,x+25,y+7);
	       line(x+25,y-7,x+25,y+7);
		floodfill(x+1,y,0);

		line(x-3,y-10,x,y-7);
		line(x-3,y+10,x,y+7);
		line(x+28,y-10,x+25,y-7);
		line(x+28,y+10,x+25,y+7);
		break;
		    case 2:
			     x=136;
				setcolor(0);
		  setfillstyle(1,15);
		 line(x-3,y-10,x-3,y+10);
	       line(x-3,y-10,x+28,y-10);
	       line(x-3,y+10,x+28,y+10);
	       line(x+28,y-10,x+28,y+10);
	       floodfill(x+1,y,0);
	       setfillstyle(1,3);
		  // arc(x,y,90,270,8);
		  line(x,y-7,x,y+7);
	       line(x,y-7,x+25,y-7);
	       line(x,y+7,x+25,y+7);
	       line(x+25,y-7,x+25,y+7);
		floodfill(x+1,y,0);
				floodfill(x+1,y,0);
		line(x-3,y-10,x,y-7);
		line(x-3,y+10,x,y+7);
		line(x+28,y-10,x+25,y-7);
		line(x+28,y+10,x+25,y+7);
		break;
	       }
	    }
	}
    }

}

/* **********************************************************************************************
 * Function: step_car
 * Description:画坡道小车
 * **********************************************************************************************/
void step_car(int x,int y)
{
    setcolor(9);
    line(x-36,y-15,x-36,y+33);
    line(x-36,y+33,x+36,y+15);
    line(x+36,y-33,x+36,y+15);
    line(x-36,y-15,x+36,y-33);

    line(x-36,y+33,x-36,y+36);
    line(x+36,y+15,x+36,y+18);
    line(x-36,y+36,x+36,y+18);
    setfillstyle(1,11);
	floodfill(x,y,9);
	setfillstyle(1,8);
	floodfill(x,y+26,9);
 }

/* **********************************************************************************************
 * Function:step
 * Description:画坡道
 * Calls:库函数
 * Called by:pull_over();drop_off();
 * **********************************************************************************************/
void step()
{
    int i=0;
    setcolor(15);
    line(0,159,0,349);
    line(0,349,639,189);
    line(639,0,639,349);
    line(0,159,639,0);
    line(0,349,639,349);
    setfillstyle(11,8);
    floodfill(620,345,15);
    setfillstyle(1,7);
    floodfill(638,5,15);
    setcolor(14);
    for(i=0;i<10;i++)
    {
	line(0,253+i,639,73+i);
    }
}

/* **********************************************************************************************
 * Function:Draw_Car(sp *ob)
 * Description:分析数据后画出小车
 * Calls:库函数
 * Called by:extra_car();tick_car();
 * Input:sp *ob
 * return:无
 * others:无
 * **********************************************************************************************/
void Draw_Car(sp *ob)
{
   int x=ob->x;
   int y=ob->y;
    switch(ob->frame)
    {
	case 0:
		   setcolor(0);
		    setfillstyle(1,15);
			   //arc(x,y,0,180,8);
	       line(x-10,y-3,x+10,y-3);
	       line(x-10,y-3,x-10,y+28);
	       line(x+10,y-3,x+10,y+28);
	       line(x-10,y+28,x+10,y+28);
	       floodfill(x+1,y+1,0);
	       setfillstyle(1,3);
		   //arc(x,y,0,180,8);
	       line(x-7,y,x+7,y);
	       line(x-7,y,x-7,y+25);
	       line(x+7,y,x+7,y+25);
	       line(x-8,y+25,x+8,y+25);
		   floodfill(x+1,y+1,0);
		   line(x-10,y-3,x-7,y);
		   line(x+10,y-3,x+7,y);
		   line(x-10,y+28,x-8,y+25);
		   line(x+10,y+28,x+8,y+25);
	       break;
  /*	 case 1:
		setcolor(0);
		   setfillstyle(1,7);
		line(x-8,y-9,x+8,y+9);
		line(x-8,y-9,x-26,y+15);
		line(x+8,y+9,x-15,y+26);
		line(x-15,y+26,x-26,y+15);
		floodfill(x-1,y+1,0);
		setfillstyle(1,3);

	       //	floodfill(x+1,y+1,0);
	       //	arc(x,y,315,135,8);
		line(x-5,y-6,x+5,y+6);
		line(x-5,y-6,x-23,y+12);
		line(x+5,y+6,x-12,y+23);
		line(x-12,y+23,x-23,y+12);
		floodfill(x-1,y+1,0);   */
	       break;
	  case 2:
	       setcolor(0);
		  setfillstyle(1,15);
	       line(x+3,y-10,x+3,y+10);
	       line(x-28,y-10,x+3,y-10);
	       line(x-28,y+10,x+3,y+10);
	       line(x-28,y-10,x-28,y+10);
	       floodfill(x-1,y,0);
	       setfillstyle(1,3);
		  // arc(x,y,270,90,8);
	       line(x,y-7,x,y+7);
	       line(x-25,y-7,x,y-7);
	       line(x-25,y+7,x,y+7);
	       line(x-25,y-7,x-25,y+7);
	       floodfill(x-1,y,0);
	       line(x+3,y-10,x,y-7);
	       line(x+3,y+10,x,y+7);
	       line(x-28,y+10,x-25,y+7);
	       line(x-28,y-10,x-25,y-7);
	       break;
    /*	 case 3:
	       setcolor(0);
		  setfillstyle(1,7);
	       line(x-8,y+9,x+9,y-8);
	       line(x-8,y+9,x-26,y-15);
	       line(x+9,y-8,x-15,y-26);
	       line(x-26,y-15,x-15,y-26);
	       floodfill(x-1,y-1,0);
	       setfillstyle(1,3);
		 //  arc(x,y,225,45,8);
		 line(x-5,y+6,x+6,y-5);
	       line(x-5,y+6,x-23,y-12);
	       line(x+6,y-5,x-12,y-23);
	       line(x-23,y-12,x-12,y-23);
	       floodfill(x-1,y-1,0);
	       break;
	       */
	case 4:
		   setcolor(0);
		      setfillstyle(1,15);
	       line(x-11,y+3,x+11,y-3);
	       line(x-11,y+3,x-11,y-28);
	       line(x+11,y+3,x+11,y-28);
	       line(x-11,y-28,x+11,y-28);
	       floodfill(x,y-1,0);
	       setfillstyle(1,3);
		  // arc(x,y,180,360,8);
		  line(x-8,y,x+8,y);
	       line(x-8,y,x-8,y-25);
	       line(x+8,y,x+8,y-25);
	       line(x-8,y-25,x+8,y-25);
	       floodfill(x,y-1,0);
	       line(x-11,y+3,x-8,y);
	       line(x+11,y-3,x+8,y);
	       line(x-11,y-28,x-8,y-25);
	       line(x+11,y-28,x+8,y-25);
	       break;
 /*	 case 5:
	       setcolor(0);
		  setfillstyle(1,7);
		 line(x-9,y-8,x+9,y+8);
	       line(x-9,y-8,x+15,y-26);
	       line(x+9,y+8,x+26,y-15);
	       line(x+15,y-26,x+26,y-15);
	       floodfill(x+1,y-1,0);
	       setfillstyle(1,3);
		 //  arc(x,y,135,315,8);
		 line(x-6,y-5,x+6,y+5);
	       line(x-6,y-5,x+12,y-23);
	       line(x+6,y+5,x+23,y-12);
	       line(x+12,y-23,x+23,y-12);
		floodfill(x+1,y-1,0);
	       break;
	      */
	  case 6:
	       setcolor(0);
		  setfillstyle(1,15);
		 line(x-3,y-10,x-3,y+10);
	       line(x-3,y-10,x+28,y-10);
	       line(x-3,y+10,x+28,y+10);
	       line(x+28,y-10,x+28,y+10);
	       floodfill(x+1,y,0);
	       setfillstyle(1,3);
		  // arc(x,y,90,270,8);
		  line(x,y-7,x,y+7);
	       line(x,y-7,x+25,y-7);
	       line(x,y+7,x+25,y+7);
	       line(x+25,y-7,x+25,y+7);
		floodfill(x+1,y,0);
		line(x-3,y-10,x,y-7);
		line(x-3,y+10,x,y+7);
		line(x+28,y-10,x+25,y-7);
		line(x+28,y+10,x+25,y+7);
	       break;

       /*	case 7:
	       setcolor(0);
		  setfillstyle(1,7);
	       line(x-9,y+8,x+9,y-8);
	       line(x-9,y+8,x+15,y+26);
	       line(x+9,y-8,x+26,y+15);
	       line(x+15,y+26,x+26,y+15);
		floodfill(x+1,y+1,0);
	       setfillstyle(1,3);
		  // arc(x,y,45,225,8);
	       line(x-6,y+5,x+6,y-5);
	       line(x-6,y+5,x+12,y+23);
	       line(x+6,y-5,x+23,y+12);
	       line(x+12,y+23,x+23,y+12);
		floodfill(x+1,y+1,0);
	       break;
	       */
      }
}


/*数据准备模块*/
/* **********************************************************************************************
 * Function:init_car(Car* p)
 * Description:小车结构初始化,随机生成小车车牌号。
 * Calls:无
 * Called by:extra_car();tick_car();
 * Input:Car* p：小车结构
 * return:无
 * others:无
 * **********************************************************************************************/
void init_car(Car* p)
{
	char string[20]="-----parking----";
	int m,n;
    p->i=0;
    p->j=0;
    p->k=0;                       //停车位初始化
    p->time=0;
	strcpy(p->it,string);
	strcpy(p->ot,string);
    for(m=0;m<7;m++)
    { 
        for(n=0;n<2;n++)
		 p->road[m][n]=0;
                                            //路径初始化
    }
	p->carnum=rand_bi();

}

/* **********************************************************************************************
 * Function:init_pp(Pp * p,Rec list) 
 * Description:车库结构初始化。随机生成车库空余与满车位
 * Calls:无
 * Called by:main();
 * Input:Pp * p:车库结构,Rec list:链表头结点
 * return:无
 * others:无
 * **********************************************************************************************/
void init_pp(Pp * p,Rec list)                               
{   
    record node;
    int x,i,j,k,h;
    char string[20]="-----parking----";
    p->f1=0;
    p->f2=0;
    p->f3=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<7;k++)
            {   
               
                x=random(2);
				p->a[i][j][k]=x;
                 if(p->a[i][j][k]==1)
                 {
					node.port=change(i,j,k);//将数据放入这个节点
					node.carnum=rand_bi();
                    strcpy(node.it,format_time());  //调用格式化时间函数，把时间字符串
                    strcpy(node.ot,string);
                    node.time=0;
                    node.next=NULL; //给这个结点的指针域赋值
					insert_node(list,node);//将节点插入到已有链表中
                    
                 }

                }
                
            }
        }

}

/* **********************************************************************************************
 * Function: init_sp(sp *p,int ax,int ay)
 * Description:初始化小车模块
 * Calls:
 * Called by:pull_over,drop_off
 * Input:sp *p,int ax,int ay:小车模块结构成员项
 * return:无
 * others:无
 * **********************************************************************************************/
void  init_sp(sp *p,int ax,int ay)            
{
    p->x=ax;
    p->y=ay;
    p->frame=0;
    p->pro=0;
    p->fx=0;
    p->state=0;
}

/* **********************************************************************************************
 * Function: init_sp(sp *p,int ax,int ay)
 * Description:获取车库车位信息，并将信息放入车位结构
 * Calls:无
 * Called by:yes();以及若干显示空余车位的函数
 * Input:Pp * p：车库结构指针
 * return:无
 * others:无
 * **********************************************************************************************/
void attain(Pp * p)
{   
    int  i, j, k;
	p->a_park=0;
    p->f1=0;
	p->f2=0;
    p->f3=0;
    p->m1=0;
    p->m2=0;
    p->m3=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<7;k++)
            {
                if(p->a[i][j][k]==0||p->a[i][j][k]==2)
                {
                    p->a_park+=1;
					switch(i)
                    { case 0:    p->f1+=1;
                                 break;
                      case 1:    p->f2+=1;
                                 break;
                      case 2:    p->f3+=1;
                                 break;
                    }             
                }
                else if(p->a[i][j][k]==1)
                {
                    switch(i)
                    {
                        case 0:p->m1+=1;
                               break;
                        case 1:p->m2+=1;
                               break;
                        case 2:p->m3+=1;
                               break;
                    }
                }
            }
        }
    }

}

/* **********************************************************************************************
 * Function:assign2(Pp * s,Car * p,Rec list,int n)
 * Description:根据车库规则，将空闲车位分配给小车
 * Calls:无
 * Called by:flow.c中有关停车的函数
 * Input:Pp * p：车库结构指针,Car * p：小车结构Rec list：链表头结点,n:层数
 * return:无
 * others:无
 * **********************************************************************************************/
void assign2(Pp * s,Car * p,Rec list,int n)
{   
	int  i, j, k;
    i=n;
		for(j=0;j<3;j++)
		{
			for(k=0;k<7;k++)
			 {
				if((s->a[i][j][k]==0))
					 {
					  (s->a[i][j][k])=2;//车位被分配后的状态
                       p->i=i;
					   p->j=j;         //车结构中关于车位安排
					   p->k=k;
					   write_node(p,list);
                       return;
					 }
				
				 }
				 
		}
    }

/* **********************************************************************************************
 * Function: road_design(Car* p)
 * Description:根据车位号，为小车设定沿途引导信息。并将控制小车动画的关键值放入小车结构
 * Calls:无
 * Called by:flow.c中有关停车的函数
 * Input:Car * p：小车结构
 * return:无
 * others:无
 * **********************************************************************************************/
void road_design(Car* p)
{
	int k;
	k=p->k;
    switch(p->j)                         //判断区位
    {
        case 0: p->road[0][0]=X0;          //M为第一个车位纵坐标，N为车位宽度.第一区
                p->road[0][1]=Y0-N*k;
                break;
        
        case 1: p->road[0][0]=X0;          //第二区   
                p->road[0][1]=Y0-N*k;
                break;

        case 2: p->road[0][0]=X0;         //第三区       
                p->road[0][1]=Y1;           
                p->road[1][0]=X2;
                p->road[1][1]=Y1;
                p->road[2][0]=X2;
				p->road[2][1]=Y0-N*k;
                break;
     
     }
}

/*小车运动计算模块*/
/*停车*/
/* **********************************************************************************************
 * Function:car(Pp *state,sp *ob,Car * p,int a,int *h)
 * Description:小车停车事件函数。判断并实现小车每一帧的运动
 * Calls:Draw_Arrow;Draw_Car;
 * Called by:flow.c中有关停车的函数
 * Input:Car * p：小车结构
 * return:无
 * others:无
 * **********************************************************************************************/
void car(Pp *state,sp *ob,Car * p,int a,int *h)
{
 int  index, m;
 int c=0;
 int x,y;
  if(ob->state==1)
 { 
	 //Draw_Car(ob);
     outhzxy(80+(a%6)*80,13+(a/6)*18,"停车成功",2);   
 }
 if(p->road[ob->pro][0]!=0&&p->road[ob->pro][1]!=0)
 {
	 if(p->road[ob->pro][0]<ob->x)
	{
	   x=p->road[ob->pro][0]-18;
	   y=p->road[ob->pro][1];
	   Draw_Arrow(x,y,ob->frame);
	   Draw_Car(ob);
	   ob->x-=2;

	 }
	else if ((p->road[ob->pro][0]==ob->x)&&(p->road[ob->pro][1]==ob->y))
	 {

	  if((ob->pro==0&&p->j==0))           //右转
	  {
		  //switch(ob->fx)
		 // {
		  // case 1:
				   ob->frame=2;
				   Draw_Car(ob);   //画小车
				   ob->pro++;
				   ob->fx=0;
				   //break;
		 /*  case 0:
				   ob->frame=1;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
		  }*/


	  }
	 else if((ob->pro==1&&p->j==2))           //右转         BUG
	  {

		 //  switch(ob->fx)
		  //{
			//  case 1:
				   ob->frame=0;
				   Draw_Car(ob);   //画小车
				   ob->pro++;
				   ob->fx=0;
			/*	   break;
			  case 0:
				   ob->frame=7;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
		  }*/


	  }

	  else if((ob->pro==0&&p->j==1)||(ob->pro==0&&p->j==2)||(ob->pro==2&&p->j==2))      //左转
	  {
		   //switch(ob->fx)
		  //{
		  //case 1:
				   ob->frame=6;
				   Draw_Car(ob);   //画小车
		       		   ob->pro++;
				   ob->fx=0;
			//	   break;
		/*  case 0:
				   ob->frame=7;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
*/		  

	  }
	  }
	else if(p->road[ob->pro][1]>ob->y)
	 {
	  x=p->road[ob->pro][0];
	  y=p->road[ob->pro][1]+18;

      Draw_Arrow(x,y,ob->frame); 
      Draw_Car(ob);   //画小车
      ob->y+=2;
    
     }
    else if(p->road[ob->pro][0]>ob->x)
    {
      x=p->road[ob->pro][0]+18;
      y=p->road[ob->pro][1];
     
      Draw_Arrow(x,y,ob->frame);
      Draw_Car(ob);   //画小车
      ob->x+=2;
     
     }
     else if(p->road[ob->pro][1]<ob->y)
     {
       x=p->road[ob->pro][0];
       y=p->road[ob->pro][1]-18;
       Draw_Arrow(x,y,ob->frame);
     
      Draw_Car(ob);   //画小车
      ob->y-=2;
	 }
     c=1;
       }
                                                                                       //限制范围
 m=((ob->x>135)&&(ob->x<216))||((ob->x>265)&&(ob->x<396))||((ob->x>300)&&(ob->x<502));
 if((p->road[ob->pro][0]==0)&&(p->road[ob->pro][1]==0)&&m)              //停进车位
 {
	 switch(p->j)
     {
        case 0: 
               
				 Draw_Car(ob);
                 ob->x+=2;
				//delay(SPEED);
                break;

         case 1:
               
				Draw_Car(ob);
                ob->x-=2;
                //delay(SPEED);
                break;

         case 2:
              
			   Draw_Car(ob);
               ob->x-=2;
               //delay(SPEED);
               break;
        
     }
 }
 else if(c==0&&ob->state==0)
   {  ob->state=1;
      state->a[p->i][p->j][p->k]=1;
      attain(state);
	  *h+=1;
      }

 
 
}

/* **********************************************************************************************
 * Function:extra_car(Pp *state,Car *p,sp *ob,int a,int k,int *f)
 * Description:实现多辆小车的运动，以及动画页面其余变量的改变
 * Calls:bk();,bk_car();
 * Called by:pull_over();
 * Input:Pp *state:车库结构，Car *p：小车结构指针,sp *ob：小车模块结构指针,int a：楼层数,int k：小车数量,int *f：记录停车成功小车数目的指针
 * return:无
 * others:无
 * **********************************************************************************************/
void extra_car(Pp *state,Car *p,sp *ob,int a,int k,int *f)
{
	time_t timep;
	int i;
	char string[9],s2[3],s1[3];
	bk();
    bk_car(state,a);
	time(&timep);
	sscanf(ctime(&timep),"%*s%*s%*s%s",string);
	setcolor(15);
	settextstyle(0,0,1);
	outtextxy(565,340,string);
	for(i=0;i<k;i++)
	{
	 car(state,&ob[i],&p[i],i,f);
	}
    attain(state);
    strcpy(s1,transform(a+1));
	strcpy(s2,transform(tofloor(state,a)));
	setcolor(6);
    outhzxy(10,321,"第",6);
    outhzxy(53,321,"层",6);
    settextstyle(4,0,2);
    outtextxy(28,313,s1);
    setcolor(2);
	settextstyle(0,0,2);
    if(tofloor(state,a)==0)setcolor(4);
    outtextxy(74,320,s2);
}

/* **********************************************************************************************
 * Function: pull_over(Pp *state,Car *p,int n,int a) 
 * Description:停车过程函数，实现整个停车过程
 * Calls:init_sp();extra_car(state,p,ob,a,k,f);
 * Called by:flow.c中有关停车的函数
 * Input:Pp *state:车库结构，Car *p：小车结构指针,sp *ob：小车模块结构指针,int a：楼层数,int k：小车数量,int *f：记录停车成功小车数目的指针
 * return:13:endpage
 * others:无
 * **********************************************************************************************/
int pull_over(Pp *state,Car *p,int n,int a)
{
    int gd=VGA;
    int gm=VGAMED;
	int i,k=1,s,x,y,d=0;
	int *f=&d;
	sp ob[21];
	for(i=0;i<n;i++)
	{                          //初始化小车模块
	   init_sp(&ob[i],X0,Y);
	}
	initgraph(&gd,&gm,"bgi");
	for(s=0;;s++)
	{

		setactivepage(1);
		cleardevice();
        extra_car(state,p,ob,a,k,f);
        setvisualpage(1);
        delay(14);
	    setactivepage(0);
	    cleardevice();
        extra_car(state,p,ob,a,k,f);
        setvisualpage(0);
		if(k<n)
		{ k=1+s/60;}
        delay(14);
	   if(kbhit()) 
       {
           break;
       }
	   if(f==(n)) 
       {
           break;
       }

	}
	getch();
        for(x=0;x<n;x++)
{
state->a[p[x].i][p[x].j][p[x].k]=1;
}
	closegraph();
	return 13;    //选择页
   }

/*取车*/
/* **********************************************************************************************
 * Function:Init_outsp(sp*p,Car *cr)
 * Description:针对取车初始化小车模块
 * Calls:
 * Called by:drop_off
 * Input:sp*p:小车模块,Car *cr:小车模块
 * return:无
 * others:无
 * **********************************************************************************************/
void Init_outsp(sp*p,Car *cr)      
{
    switch(cr->j)
    {
	   case 0: p->frame=2;
			   p->x=502;
			   p->pro=0;
			   break;
	   case 1: p->frame=6;
			   p->x=266;
			   p->pro=0;
			   break;
	   case 2: p->frame=6;
			   p->x=136;
			   p->pro=2;
			   break;

	}
	 p->y=Y0-N*(cr->k);
	 p->state=0;
	 p->fx=0;
}

/* **********************************************************************************************
 * Function:car_message(Pp *state,Car *cr,int f)
 * Description:录入被取小车信息到小车结构
 * Calls:
 * Called by:drop_off
 * Input:sp*p:小车模块,Car *cr:小车模块，f：楼层 
 * return:无
 * others:无
 * **********************************************************************************************/
void car_message(Pp *state,Car *cr,int f)       
{
	int  j, k;
	int i=0;
	for(j=0;j<3;j++)
	{
        switch(j)
        {
            case 0:
            case 2:
         for(k=0;k<7;k++)
		{
           if (state->a[f][j][k]==1)
           {
               init_car(&cr[i]);
               cr[i].i=f;
               cr[i].j=j;
               cr[i].k=k;
               road_design(&cr[i]);
               drop_car2(change(f,j,k));
               drop_car1(change(f,j,k));
               i++;
              }
        }
                      
         break;
            case 1:
            	for(k=6;k>=0;k--)
		{
           if (state->a[f][j][k]==1)
           {
               init_car(&cr[i]);
               cr[i].i=f;
               cr[i].j=j;
               cr[i].k=k;
               road_design(&cr[i]);
               drop_car2(change(f,j,k));
               drop_car1(change(f,j,k));
               i++;
              }
        }
                break;
           
        
        }
    }
    
} 

/* **********************************************************************************************
 * Function:car(Pp *state,sp *ob,Car * p,int a,int *h)
 * Description:小车取车事件函数。判断并实现小车每一帧的运动
 * Calls:Draw_Arrow;Draw_Car;
 * Called by:flow.c中有关停车的函数
 * Input:Car * p：小车结构
 * return:无
 * others:无
 * **********************************************************************************************/
void carout(Pp *state,sp *ob,Car * p,int a,int *h)
{
 int index,m;
 int c=0, frame=0;
 int x,y;

 if(ob->pro>=0)
 {
	 if(p->road[ob->pro][0]<ob->x)
	{
	   x=p->road[ob->pro][0]-15;
	   y=p->road[ob->pro][1];
	   Draw_Car(ob);
	   if(((p->j==0||p->j==1)&&ob->pro==0)||(p->j==2&&ob->pro==2))
	   {
		   frame=(ob->frame+4)%8;
	   }
	   else
	   {
		   frame=ob->frame;
	   }
	   Draw_Arrow(x,y,frame);
	   ob->x-=2;

	 }

	else if(p->road[ob->pro][1]>ob->y)
	 {
	  x=p->road[ob->pro][0];
	  y=p->road[ob->pro][1]+15;
	  Draw_Car(ob);   //画小车
	  Draw_Arrow(x,y,ob->frame);
	  ob->y+=2;
	 }
	else if(p->road[ob->pro][0]>ob->x)
	{
	  x=p->road[ob->pro][0]+15;
	  y=p->road[ob->pro][1];
	  if(((p->j==0||p->j==1)&&ob->pro==0)||(p->j==2&&ob->pro==2))
	   {
		   frame=(ob->frame+4)%8;
	   }
	   else
	   {
		   frame=ob->frame;
	   }
	   Draw_Arrow(x,y,frame);
	   Draw_Car(ob);   //画小车
	   ob->x+=2;

	 }
	 else if(p->road[ob->pro][1]<ob->y)
	 {
	   x=p->road[ob->pro][0];
	   y=p->road[ob->pro][1]-15;
	   Draw_Car(ob);   //画小车
	   Draw_Arrow(x,y,ob->frame);
	   ob->y-=2;
	 }
		else if ((p->road[ob->pro][0]==ob->x)&&(p->road[ob->pro][1]==ob->y))
	 {

	  if((ob->pro==0&&p->j==0))
	  {
		  switch(ob->fx)
		  {
		   case 1:
				   ob->frame=4;
				   Draw_Car(ob);   //画小车
				   ob->pro--;
				   ob->fx=0;
				   break;
		   case 0:
				   ob->frame=3;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
		  }


	  }
	 else if((ob->pro==1&&p->j==2))
	  {

		   switch(ob->fx)
		  {
			  case 1:
				   ob->frame=2;
				   Draw_Car(ob);   //画小车
				   ob->pro--;
				   ob->fx=0;
				   break;
			  case 0:
				   ob->frame=3;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
		  }
 }
else if((ob->pro==0&&p->j==1)||(ob->pro==0&&p->j==2)||(ob->pro==2&&p->j==2))      //左转
	  {
		   switch(ob->fx)
		  {
		  case 1:
				   ob->frame=4;
				   Draw_Car(ob);   //画小车
				   ob->pro--;
				   ob->fx=0;
				   break;
		  case 0:
				   ob->frame=5;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
		  }

	  }
	  }
     c=1;
       }
 else if(ob->y<348)              ///////停进车位
 {
     Draw_Car(ob);
	 ob->y+=2;
 }
 else if(ob->state==0)
{  
       ob->state=1;
       *h+=1;
      
}
 else if(ob->state==1)
 { 
     
     state->a[p->i][p->j][p->k]=0;
     attain(state);
     outhzxy(80+(a%6)*80,13+(a/6)*18,"取车成功",2);
    
 }

 }

/* **********************************************************************************************
 * Function:extra_car(Pp *state,Car *p,sp *ob,int a,int k,int *f)
 * Description:实现多辆小车的运动，以及动画页面其余变量的改变
 * Calls:bk();,bk_car();
 * Called by:pull_over();
 * Input:Pp *state:车库结构，Car *p：小车结构指针,sp *ob：小车模块结构指针,int a：楼层数,int k：小车数量,int *f：记录停车成功小车数目的指针
 * return:无
 * others:无
 * **********************************************************************************************/
void tick_car(Pp *state,Car *p,sp *ob,int a,int k,int *f)
{
	time_t timep;
	int i;
	char  string[9], s2[3], s1[3];
	bk();            //画背景
    bk_car(state,a);//画停车
	time(&timep); //调用系统时间
	sscanf(ctime(&timep),"%*s%*s%*s%s",string); //将系统时间按格式打出来
	setcolor(15);
	settextstyle(0,0,1);
	outtextxy(565,340,string);  //显示时间
	
    for(i=0;i<k;i++)
	{        
		state->a[p[k-1].i][p[k-1].j][p[k-1].k]=5;
        carout(state,&ob[i],&p[i],i,f);
	   }
    attain(state);
    strcpy(s1,transform(a+1));
	strcpy(s2,transform(tofloor(state,a)));
    setcolor(6);
    outhzxy(10,321,"第",6);
    outhzxy(53,321,"层",6);
    settextstyle(4,0,2);
    outtextxy(28,313,s1);
    setcolor(2);
	settextstyle(0,0,2);
    if(tofloor(state,a)==0)setcolor(4);
    outtextxy(74,320,s2);
}

/* **********************************************************************************************
 * Function: pull_over(Pp *state,Car *p,int n,int a) 
 * Description:停车过程函数，实现整个停车过程
 * Calls:init_sp();extra_car(state,p,ob,a,k,f);
 * Called by:flow.c中有关停车的函数
 * Input:Pp *state:车库结构，Car *p：小车结构指针,int a：楼层数,int n：小车数量,func=0全层取车，func=1，单辆取车
 * return:13:endpage
 * others:无
 * **********************************************************************************************/
int drop_off(Pp *state,Car *p,int n,int a,int func)  
{
    int gd=VGA;
    int gm=VGAMED;
	int i, k=1, d=0, s=0, x=0;
    int *f=&d;
    sp ob[21];
	if(!func) 
    {
        car_message(state,p,a);               //设置小车信息,单辆小车在外部设置好
    } 	
    for(i=0;i<n;i++)
    {                          //初始化小车模块
	   Init_outsp(&ob[i],&p[i]);
	}
	initgraph(&gd,&gm,"bgi");
	for(s=0;;s++)
	{

	  setactivepage(1);
      cleardevice();
      tick_car(state,p,ob,a,k,f);
      setvisualpage(1);
      delay(14);
	  setactivepage(0);
	  cleardevice();
      tick_car(state,p,ob,a,k,f);
      setvisualpage(0);
	  if(k<n)
		{ k=1+s/60;}
      delay(14);
	 if(kbhit()) break;
	 if(d==(n+1)) break;

	}
	Delay(30);
    getch();
        for(x=0;x<n;x++)
{
state->a[p[x].i][p[x].j][p[x].k]=0;
}
	closegraph();
    return 13;    //选择页
   }

/* ****坡道动画***** */
void floor_step( int state)       
{
    
    int gd=VGA;
    int gm=VGAMED;
    int s, i=0;
	initgraph(&gd,&gm,"bgi");
	for(s=0;s<85;s++)
	{

		setactivepage(1);
		cleardevice();

		step();
        switch(state)
        {
            
           case 0 :step_car(0+i*4,286-i);
                   break;
           case 1:step_car(660-4*i,28+i);  
                  break;
        }
        i++;
       setvisualpage(1);
        delay(14);
	   setactivepage(0);
	   cleardevice();

	   	step();
          switch(state)
        {
            
           case 0 :step_car(0+i*4,286-i);
                   break;
           case 1:step_car(660-4*i,28+i);  
                  break;
        }
        i++;

       setvisualpage(0);
      delay(14);

	}
    closegraph();
}



