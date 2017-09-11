#include"process.h"

////////////////////显示屏显示函数/////////////////////////
void Load_LED(int x,int y,char *s,int state,int color)
{
    switch(state)
    {
        case 0:  WriteHz16s(s,x,y,color);            // 打印汉字
                 break;
        case 1:  Blit_String(x,y,color,s,1);         // 打印西文
                 break;
    }
}

////////////////////////显示屏擦除函数////////////////////////////////
void wipeout(int x,int y,int state)
{
    switch(state)
    {
        case 0:
               fill_Rectangle(x,y,x+100,y+57,0);
               break;
       case 1:
               fill_Rectangle(x,y,x+159,y+20,0);
               break;
        
       case 2:
               fill_Rectangle(x,y,x+18,y+14,0);
               break;

    }

}
//////////////////////////////将数字转化为字符串////////////////////////////////////
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
void Draw_Arrow(int x,int y,int m)     //////////////////控制引导函数////////////////
{
    int c=2;
    setcolor(c);
    
switch(m)
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

int change(int i,int j,int k)                      //将车位号转换成一个整型
{
    int m;
    m=(i+1)*100+(j+1)*10+k+1;
    return m;

}

void bk()                          //画车库背景
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
 rectangle(x-10,y-10,x+56,y+185);
 rectangle(x+130-10,y-10,x+130+56,y+185);
 rectangle(x+350-10,y-10,x+350+56,y+185);
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
	 rectangle(x+130*i,y,x+46+130*i,y+175);
	 for(j=0;j<6;j++)
	 {
		 line(x+130*i,y+25+j*25,x+46+130*i,y+25+j*25);
	 }
 }
  rectangle(x+350,y,x+350+46,y+175);
	 for(j=0;j<6;j++)
	 {
		 line(x+350,y+25+j*25,x+350+46,y+25+j*25);
	 }

}
void Draw_Car(sp *ob)             //画车
{
   int x=ob->x;
   int y=ob->y;
    switch(ob->frame)
    {
        case 0:
	           setcolor(0);
               setfillstyle(1,3);
	           arc(x,y,0,180,8);
               line(x-7,y,x-7,y+25);
               line(x+7,y,x+7,y+25);
               line(x-8,y+25,x+8,y+25);
	           floodfill(x,y,0);
               //setcolor(15);
             //  setfillstyle(1,15);
               //bar(x-7,y+12,x+7,y+17);
               //floodfill(x,y+16,15);
               break;
         case 1:
                setcolor(0);
                setfillstyle(1,3);
             	arc(x,y,315,135,8);
                line(x-5,y-6,x-23,y+12);
                line(x+5,y+6,x-12,y+23);
                line(x-12,y+23,x-23,y+12);
            	floodfill(x,y,0);
              // setcolor(15);
              // setfillstyle(1,15);
              // bar(x-7,y+12,x+7,y+17);
               //floodfill(x,y+16,15);
               break;
          case 2:  
               setcolor(0);
               setfillstyle(1,3);
	           arc(x,y,270,90,8);
               line(x-25,y-7,x,y-7);
               line(x-25,y+7,x,y+7);
               line(x-25,y-7,x-25,y+8);
	           floodfill(x,y,0);
               //setcolor(15);
             //  setfillstyle(1,15);
               //bar(x-7,y+12,x+7,y+17);
			   //floodfill(x,y+16,15);
               break;
         case 3:
               setcolor(0);
               setfillstyle(1,3);
	           arc(x,y,225,45,8);
               line(x-5,y+6,x-23,y-12);
               line(x+6,y-5,x-12,y-23);
               line(x-23,y-12,x-12,y-23);
	           floodfill(x,y,0);
              // setcolor(15);
              // setfillstyle(1,15);
              // bar(x-7,y+12,x+7,y+17);
               //floodfill(x,y+16,15);
               break;
        case 4:
	           setcolor(0);
               setfillstyle(1,3);
	           arc(x,y,180,360,8);
               line(x-8,y,x-8,y-25);
               line(x+8,y,x+8,y-25);
               line(x-8,y-25,x+8,y-25);
	           floodfill(x,y,0);
               //setcolor(15);
             //  setfillstyle(1,15);
               //bar(x-7,y+12,x+7,y+17);
               //floodfill(x,y+16,15);
               break;
         case 5:
               setcolor(0);
               setfillstyle(1,3);
	           arc(x,y,135,315,8);
               line(x-6,y-5,x+12,y-23);
               line(x+6,y+5,x+23,y-12);
               line(x+12,y-23,x+23,y-12);
	           floodfill(x,y,0);
              // setcolor(15);
              // setfillstyle(1,15);
              // bar(x-7,y+12,x+7,y+17);
               //floodfill(x,y+16,15);
               break;       
          case 6:  
               setcolor(0);
               setfillstyle(1,3);
	           arc(x,y,90,270,8);
               line(x,y-7,x+25,y-7);
               line(x,y+7,x+25,y+7);
               line(x+25,y-7,x+25,y+7);
	           floodfill(x,y,0);
               //setcolor(15);
             //  setfillstyle(1,15);
               //bar(x-7,y+12,x+7,y+17);
               //floodfill(x,y+16,15);
               break;
    
        case 7:
               setcolor(0);
               setfillstyle(1,3);
	           arc(x,y,45,225,8);
               line(x-6,y+5,x+12,y+23);
               line(x+6,y-5,x+23,y+12);
               line(x+12,y+23,x+23,y+12);
	           floodfill(x,y,0);
              // setcolor(15);
              // setfillstyle(1,15);
              // bar(x-7,y+12,x+7,y+17);
               //floodfill(x,y+16,15);
               break;
      
       
  
    
   

    }
}

///////////////小车结构初始化//////////////
void init_car(Car* p)
{   
	char string[12]="parking---";
	int m,n;
    p->i=0;
    p->j=0;
    p->k=0;                       //停车位初始化
    p->time=0;
	strcpy(p->it,string);
	strcpy(p->ot,string);
    for(m=0;m<7;m++)
    { for(n=0;n<2;n++)
		 p->road[m][n]=0;
                                            //路径初始化
    }
	p->carnum=rand_bi();

}
void init_pp(Pp * p,Rec list)                                //初始化车库
{   
    Rec node=NULL;
    int x,i,j,k,h;
    char string[15]="parking---";
   // time_t y;
	//srand((int)time(NULL));//随机种子    
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
                    node=create_node();//创建一个结点
					node->port=change(i,j,k);//将数据放入这个节点
					node->carnum=rand_bi();
                    strcpy(node->it,format_time());  //调用格式化时间函数，把时间字符串
                    strcpy(node->ot,string);
                    node->time=0;
                    node->next=NULL; //给这个结点的指针域赋值
					list=insert_node(list,node);//将节点插入到已有链表中
                 }

                }
                
            }
        }

}

void  init_sp(sp *p,int ax,int ay)            //初始化小车模块
{
    p->x=ax;
    p->y=ay;
    p->frame=0;
    p->pro=0;
    p->fx=0;
    p->state=0;
}

///////////////////////进度条动画//////////////////////////////

void login()
{
    PCX_Load_Screen("s1.pcx",1);
     Delay(14);
     PCX_Load_Screen("s2.pcx",1);
}
int end_page()
{
    int flag;
	sprite small;
	mou curmouse,oldmouse;
    BUTTON a[2];
    BUTTON button_exit={245,80,295,98};
    BUTTON button_back={245,117,295,134};
    a[0]=button_exit;
    a[1]=button_back;

	mouse_all(&curmouse,&oldmouse,&small);
    back("carend.pcx",&small);
	 while(1)
	 {
	   move_mouse(& curmouse,& oldmouse,&small);
        if(curmouse.key)
        {
	    if(mouse_on(a))
            {
                flag=10;
                return flag;
			                                                      //退出系统
            }
           
            else if(mouse_on(a+1))
            {
			
	            flag=0;
                Delay(10);
                PCX_Load_Screen("homepage.pcx",1);
                return flag;         //返回主页
                
            }
        }
     }  
}

///////////////////////////获取车库空余车位//////////////////////////////////////////////
void attain(Pp * p)
{   

	int i,j,k;
	p->a_park=0;
    p->f1=0;
	p->f2=0;
    p->f3=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<7;k++)
            {
                if(p->a[i][j][k]!=1)
                {
                    p->a_park+=1;
					switch(i)
                    { case 0:    p->f1+=1;break;
                      case 1:    p->f2+=1;break;
                      case 2:    p->f3+=1;break;
                    }             
                }
            }
        }
    }

}


///////////////车位分配函数//////////////
void assign(Pp * s,Car * p,Rec list)     
{
	int i,j,k;
    Rec node;
	for(i=2;i>=0;i--)
	{
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
					   strcpy(p->it,format_time());              //系统时间
						   node=create_node();//创建一个结点
						   node->port=change(p->i,p->j,p->k);//将数据放入这个节点
						   node->carnum=p->carnum;
						   strcpy(node->it,p->it);  //调用格式化时间函数，把时间字符串
						   strcpy(node->ot,p->ot);
						   node->time=p->time;
						   node->next=NULL; //给这个结点的指针域赋值
						   list=insert_node(list,node);//将节点插入到已有链表中

						return;
					 }

				 }

		}
	}
}
void assign2(Pp * s,Car * p,Rec list,int n)
{   
  //  printf("%d\n",a[0][0][0]);
    Rec node;
	int i,j,k;
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
					   strcpy(p->it,format_time());              //系统时间
					   node=create_node();//创建一个结点
                         node->port=change(p->i,p->j,p->k);//将数据放入这个节点
                        node->carnum=p->carnum;
                        strcpy(node->it,p->it);  //调用格式化时间函数，把时间字符串
                         strcpy(node->ot,p->ot);
                         node->time=p->time;
                        node->next=NULL; //给这个结点的指针域赋值
                        list=insert_node(list,node);//将节点插入到已有链表中
                        
                       return;
					 }
				
				 }
				 
		}
    }

////////////////制定小车路线/////////////////////

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



/////////////////////小车停车事件函数////////////////////////////////////////////////////////
void car(Pp *state,sp *ob,Car * p,int a,int *h)
{
 int index,m;
 int c=0;
 int x,y;
 if(ob->state==1)
 { 
	 Draw_Car(ob);
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
	   ob->x--;

	 }
	else if ((p->road[ob->pro][0]==ob->x)&&(p->road[ob->pro][1]==ob->y))
	 {

	  if((ob->pro==0&&p->j==0))           //右转
	  {
		  switch(ob->fx)
		  {
		   case 1:
				   ob->frame=2;
				   Draw_Car(ob);   //画小车
				   ob->pro++;
				   ob->fx=0;
				   break;
		   case 0:
				   ob->frame=1;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
		  }


	  }
	 else if((ob->pro==1&&p->j==2))           //右转         BUG
	  {

		   switch(ob->fx)
		  {
			  case 1:
				   ob->frame=0;
				   Draw_Car(ob);   //画小车
				   ob->pro++;
				   ob->fx=0;
				   break;
			  case 0:
				   ob->frame=7;
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
				   ob->frame=6;
				   Draw_Car(ob);   //画小车
				   ob->pro++;
				   ob->fx=0;
				   break;
		  case 0:
				   ob->frame=7;
				   ob->fx=1;
				   Draw_Car(ob);   //画小车
				   break;
		  }

	  }
	  }
	else if(p->road[ob->pro][1]>ob->y)
	 {
	  x=p->road[ob->pro][0];
	  y=p->road[ob->pro][1]+18;

      Draw_Arrow(x,y,ob->frame); 
      Draw_Car(ob);   //画小车
       ob->y++;
   
      //delay(SPEED);    
     }
    else if(p->road[ob->pro][0]>ob->x)
    {
      x=p->road[ob->pro][0]+18;
      y=p->road[ob->pro][1];
     
      Draw_Arrow(x,y,ob->frame);
      Draw_Car(ob);   //画小车
      ob->x++;
     
      //delay(SPEED);
     }
     else if(p->road[ob->pro][1]<ob->y)
     {
       x=p->road[ob->pro][0];
       y=p->road[ob->pro][1]-18;
       Draw_Arrow(x,y,ob->frame);
     
      Draw_Car(ob);   //画小车
      ob->y--;
     //delay(SPEED);
	 }
     c=1;
       }
//限制范围
 m=((ob->x>135)&&(ob->x<216))||((ob->x>265)&&(ob->x<396))||((ob->x>300)&&(ob->x<502));
 if((p->road[ob->pro][0]==0)&&(p->road[ob->pro][1]==0)&&m)              ///////停进车位
 {
	 switch(p->j)
     {
        case 0: 
               
				 Draw_Car(ob);
                 ob->x++;
				//delay(SPEED);
                break;

         case 1:
               
				Draw_Car(ob);
                ob->x--;
                //delay(SPEED);
                break;

         case 2:
              
			   Draw_Car(ob);
               ob->x--;
               //delay(SPEED);
               break;
        
     }
 }
 else if(c==0&&ob->state==0)
   {  ob->state=1;
       state->a[p->i][p->j][p->k]=1;
	  *h+=1;
      
 }
 
 
}
////////////////////////////////小车进库动画//////////////////////////////////////////
void car_in3(int n,Car *cr,Pp *state,Rec list) 
{
    char *s=NULL,*s1=NULL;
	char m;
	int h1,h2,h3;
    Rec node=NULL;
	switch(n)
	{
		case 0:
        
		 	   wipeout(0,0,0);              //系统模式
               Load_LED(0,0,"车位",0,140);
               strcpy(s,transform(cr->i+1));
               Load_LED(12,20,s,1,79);
               Load_LED(30,20,"-",1,79);
               Load_LED(62,20,"-",1,79);
               strcpy(s,transform(cr->j+1));
               Load_LED(42,20,s,1,79);
               strcpy(s,transform(cr->k+1));
               Load_LED(70,20,s,1,79);
               getch();
			   break;
		  case 1:
               while(!kbhit())
               { 
                   Delay(15);
                   wipeout(0,0,0);
                   s="请输入预定";
                   Load_LED(0,0,s,0,140);
                   s="车位";
                   Load_LED(0,18,s,0,140);
                   Delay(15);
                   wipeout(0,0,0);
                   s1="-";
                   Load_LED(30,20,s1,1,79);
                   Load_LED(62,20,s1,1,79);
                   m=bioskey(0);
                   h1=m-'0'; 
                   strcpy(s,transform(h1));
                   delay(2);
                   Load_LED(12,20,s,1,79);
                   m=bioskey(0);
                   h2=m-'0';
                   strcpy(s,transform(h2));
                   delay(2);
                   Load_LED(43,20,s,1,79);
                   m=bioskey(0);
                   h3=m-'0';
                   strcpy(s,transform(h3));
                   delay(2);
                   Load_LED(70,20,s,1,79);
                   Delay(20);
				   if(state->a[h1-1][h2-1][h3-1]==3)
                  {
                    wipeout(0,0,0);
                    cr->i=h1-1;
                    cr->j=h2-1;
                    cr->k=h3-1;
					strcpy(cr->it,format_time());              //系统时间
					node=create_node();//创建一个结点
                    node->port=change(cr->i,cr->j,cr->k);//将数据放入这个节点
                    node->carnum=cr->carnum;
                    strcpy(node->it,cr->it);  //调用格式化时间函数，把时间字符串
                    strcpy(node->ot,cr->ot);
                    node->time=cr->time;
                    node->next=NULL; //给这个结点的指针域赋值
                    list=insert_node(list,node);//将节点插入到已有链表中
	                break;	        
                  }
                     else
                 {
                     while(!kbhit())
                     {      
                     wipeout(0,0,0);
                     s="该车位信息";
                     Load_LED(8,5,s,0,133);
                     s="读取不正确";
                     Load_LED(8,23,s,0,133);
					 Delay(23);
                     wipeout(0,0,0);
                     s="按任意键";
                     Load_LED(8,5,s,0,80);
                     s="重新输入";
                     Load_LED(8,23,s,0,80);
                     Delay(23);
                     } 
                     m=bioskey(0);
                      }
               }

		 break;

    }

}

int car_in2(Car *cr,Pp *state,Rec list)
{
char *s1=NULL;
int m;
int o;
attain(state);
PCX_Load_Screen("charge.pcx",1);
while(!kbhit())
{
    attain(state);
	Load_LED(20,18,"欢迎停车",0,50);
	Delay(20);
	wipeout(0,0,0);
	Load_LED(0,6,"本车库提供自",0,140);
	Load_LED(0,24,"动引导停车",0,140);
	Delay(20);
	wipeout(0,0,0);
	Load_LED(21,10,"Available",1,87);
	strcpy(s1,transform(state->a_park));
	Load_LED(45,30,s1,1,50);
	Delay(20);
	wipeout(0,0,0);
    if(state->a_park==0)
    {
        Load_LED(20,18,"车位已满",0,87);
        break;
            
    }
}
	m=bioskey(0);
    if(state->a_park)
{	
	Load_LED(10,5,"普通用户：",0,63);
	Load_LED(80,14,"F1",1,63);
	Load_LED(10,28,"持卡用户：",0,63);
	Load_LED(80,37,"F2",1,63);
    m=bioskey(0);
if(m==F1)
{
	 assign(state,cr,list);      //系统安排车位
     road_design(cr);             //设置路径
	 car_in3(0,cr,state,list);
  }
else if(m==F2)
  {

	 car_in3(1,cr,state,list);
	 road_design(cr);
  }
return 1;
}
else
{
    getch();
    return 0;
}
}



/////////////////////////////////小车坡道动画//////////////////////////////////////////////
void floor1()
{
    sprite c1;
	pcx_picture background_pcx,o1,objects_pcx;
	PCX_Load1("tiny.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,260,151,0,0,0,0,65,50,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,65,50);//将屏幕内容复制给小图片
    Fill_Screen(0);
	PCX_Load1("floor.pcx",(pcx_picture_ptr)&background_pcx,1);//背景
    Behind_Sprite_Size((sprite_ptr)&c1,65,50);//取图片后内容

while(c1.x>226)
{
	    Erase_Sprite_Size((sprite_ptr)&c1,65,50);
		c1.x-=1;
		Behind_Sprite_Size((sprite_ptr)&c1,65,50);
		Draw_Sprite_Size((sprite_ptr)&c1,65,50);
	    Delay(1);
}
    Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);
    WriteHz16("即将进入第一层",98,98,79);
    Delay(10);

}

void floor2()
{
    sprite c1,c2;
	pcx_picture background_pcx,o1,objects_pcx;
	PCX_Load1("tiny.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,260,165,0,0,0,0,65,50,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,65,50);//将屏幕内容复制给小图片
	PCX_Load1("tiny2.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
    Sprite_Init_Size((sprite_ptr)&c2,13,121,0,0,0,0,65,50,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c2,0,0,0,65,50);//将屏幕内容复制给小图片
    Fill_Screen(0);
	PCX_Load1("floor.pcx",(pcx_picture_ptr)&background_pcx,1);//背景
    Behind_Sprite_Size((sprite_ptr)&c1,65,50);//取图片后内容
  while(c1.x>230)
{
		Erase_Sprite_Size((sprite_ptr)&c1,65,50);
		c1.x-=1;
		Behind_Sprite_Size((sprite_ptr)&c1,65,50);
		Draw_Sprite_Size((sprite_ptr)&c1,65,50);
		Delay(1);
}
while(c1.x<=230&&c1.x>10)
{
		Erase_Sprite_Size((sprite_ptr)&c1,65,50);
		c1.x-=5;
        c1.y-=1;
		Behind_Sprite_Size((sprite_ptr)&c1,65,50);
		Draw_Sprite_Size((sprite_ptr)&c1,65,50);
		Delay(5);
}
    Erase_Sprite_Size((sprite_ptr)&c1,65,50);
    Sprite_Delete_Size(&c1,1);
    Behind_Sprite_Size((sprite_ptr)&c2,65,50);
	
while(c2.y>100)
{
		Erase_Sprite_Size((sprite_ptr)&c2,65,50);
		c2.y-=1;
		Behind_Sprite_Size((sprite_ptr)&c2,65,50);
		Draw_Sprite_Size((sprite_ptr)&c2,65,50);
		Delay(1);
}	
   Sprite_Delete_Size(&c2,1);
    delay(25);
	WriteHz16("即将进入第二层",98,98,79);
	getch();
}




void floor3()
{
    sprite c1,c2,c3;
	pcx_picture o1;
	PCX_Load1("tiny.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,260,165,0,0,0,0,65,50,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,65,50);//将屏幕内容复制给小图片
	PCX_Load1("tiny2.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
    Sprite_Init_Size((sprite_ptr)&c2,13,121,0,0,0,0,65,50,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c2,0,0,0,65,50);//将屏幕内容复制给小图片
    PCX_Load1("tiny3.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
    Sprite_Init_Size((sprite_ptr)&c3,13,105,0,0,0,0,65,50,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c3,0,0,0,65,50);//将屏幕内容复制给小图片
    Fill_Screen(0);
	PCX_Load1("floor.pcx",(pcx_picture_ptr)&o1,1);//背景
    Behind_Sprite_Size((sprite_ptr)&c1,65,50);//取图片后内容
  while(c1.x>230)
{
		Erase_Sprite_Size((sprite_ptr)&c1,65,50);
		c1.x-=1;
		Behind_Sprite_Size((sprite_ptr)&c1,65,50);
		Draw_Sprite_Size((sprite_ptr)&c1,65,50);
		Delay(1);
}
while(c1.x<=230&&c1.x>10)
{
		Erase_Sprite_Size((sprite_ptr)&c1,65,50);
		c1.x-=5;
        c1.y-=1;
		Behind_Sprite_Size((sprite_ptr)&c1,65,50);
		Draw_Sprite_Size((sprite_ptr)&c1,65,50);
		Delay(5);
}
    Erase_Sprite_Size((sprite_ptr)&c1,65,50);
    Behind_Sprite_Size((sprite_ptr)&c2,65,50);
	
while(c2.y>106)
{
		Erase_Sprite_Size((sprite_ptr)&c2,65,50);
		c2.y-=1;
		Behind_Sprite_Size((sprite_ptr)&c2,65,50);
		Draw_Sprite_Size((sprite_ptr)&c2,65,50);
		Delay(1);
}	
   Erase_Sprite_Size((sprite_ptr)&c2,65,50);
   Behind_Sprite_Size((sprite_ptr)&c3,65,50);
	
while(c3.x<180)
{
		Erase_Sprite_Size((sprite_ptr)&c3,65,50);
		c3.x+=1;
		Behind_Sprite_Size((sprite_ptr)&c3,65,50);
		Draw_Sprite_Size((sprite_ptr)&c3,65,50);
		Delay(1);
}	
Erase_Sprite_Size((sprite_ptr)&c3,65,50);
c1.x=180;
c1.y=106;
Behind_Sprite_Size((sprite_ptr)&c1,65,50);
while(c1.x<=180&&c1.x>7)
{
		Erase_Sprite_Size((sprite_ptr)&c1,65,50);
		c1.x-=3;
        c1.y-=1;
		Behind_Sprite_Size((sprite_ptr)&c1,65,50);
		Draw_Sprite_Size((sprite_ptr)&c1,65,50);
		Delay(3);
}
    Erase_Sprite_Size((sprite_ptr)&c1,65,50);
    
c2.x=10;
c2.y=48;
Behind_Sprite_Size((sprite_ptr)&c2,65,50);
while(c2.y>35)
{
		Erase_Sprite_Size((sprite_ptr)&c2,65,50);
		c2.y-=1;
		Behind_Sprite_Size((sprite_ptr)&c2,65,50);
		Draw_Sprite_Size((sprite_ptr)&c2,65,50);
		Delay(1);
}	
Sprite_Delete_Size(&c2,1);
Sprite_Delete_Size(&c2,1);
Sprite_Delete_Size(&c2,1);
    delay(25);
	WriteHz16("即将进入第三层",98,98,79);
	getch();
}

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


//////////////////////////////////界面展示判断函数///////////////////////////////////
void situation(int i)
{
    switch(i)
    {
	case 0: floor1();
		break;
	case 1:  floor2();
		break;
	case 2: floor3();
	       break;
    }
}
void extra_car(Pp *state,Car *p,sp *ob,int a,int k,int *f)
{
	time_t timep;
	int i;
	char *string=NULL,*s2=NULL;
		bk();
		time(&timep);
		sscanf(ctime(&timep),"%*s%*s%*s%s",string);
		setcolor(15);
		settextstyle(0,0,1);
		outtextxy(565,340,string);
		attain(state);
		strcpy(s2,transform(tofloor(state,a)));
		outhzxy(10,321,"本层",2);
		setcolor(2);
		settextstyle(0,0,2);
		if(tofloor(state,a)==0)setcolor(4);
		outtextxy(49,320,s2);


		 for(i=0;i<k;i++)
		{
			car(state,&ob[i],&p[i],i,f);
	   }
}
void pull_over(Pp *state,Car *p,sp *ob,int n,int a)   //停车过程函数
{

	int i,k=1,s,x,y,f=0;
	for(s=0;;s++)
	{

		setactivepage(1);
		cleardevice();
		extra_car(state,p,ob,a,k,&f);
		setvisualpage(1);

	   delay(14);
	   setactivepage(0);
	   cleardevice();
	   extra_car(state,p,ob,a,k,&f);
	   setvisualpage(0);
		if(k<n)
		{ k=1+s/70;}

       delay(14);
	   if(kbhit()) break;
	   if(f==(n)) break;

	}
	Delay(30);
    getch();
	closegraph();
   }
void parkp(Pp *state)    //实况
{
  int index,m=0,i,j,k;
  int gd=VGA;
  int gm=VGAMED;
  Rec list=create_node();
  sp ob[21];
  Car cr[21];
  attain(state);
  init_car(&cr[0]);


  //car_in1();                                   //进入动画
 if( car_in2(cr,state,list))
 {  switch(cr[0].i)
  {
      case 0:  m=state->f1;
	       break;
      case 1:  m=state->f2;          //m是楼层空车位的个数
	       break;
      case 2:  m=state->f3;
	       break;
  }
  road_design(&cr[0]);
  for(i=1;i<m;i++)
  {
      init_car(&cr[i]);
	  assign2(state,&cr[i],list,cr[0].i);     //安排车位，设置路径
      road_design(&cr[i]);
  }

  add_to_today(list);

    for(i=0;i<m;i++)
    {                          //初始化小车模块
       init_sp(&ob[i],X0,Y);
    }

  situation(cr[0].i);
  getch();
 initgraph(&gd,&gm,"bgi");

  pull_over(state,cr,ob,m,cr[0].i);
 // rectangle();
 }
}



//觉得是内存问题，释放键盘缓存以及子画面缓存
