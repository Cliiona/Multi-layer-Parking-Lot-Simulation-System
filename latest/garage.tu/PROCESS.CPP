#include"process.h"
/////////////////////提示灯/////////////////////////////////
void lamp()
{  int i,j;
    int c=2;
    for(j=0;j<3;j++)
    {  
        for(i=0;i<9;i++)
    {
		BPlot(8+j*105,143-i*11,c);
    }
   
        for(i=0;i<5;i++)
    {
        BPlot(64+j*105,121-i*11,c);
    }
    
        for(i=0;i<7;i++)
    {
       BPlot(103+j*105,121-i*11,c);
    }
    
        for(i=0;i<4;i++)
    {
		BPlot(40+i*11+j*105,31,c);
	}
	}
}
  void c_lamp(Pp* p,int a)
{
	int i,j,k;
    int c=1;
	for(i=0;i<3;i++)
	{
	   for(j=0;j<4;j++)
   {	switch(j)
	  {	case 0:
			for(k=0;k<9;k++)
			{
				if(p->a[i][j][k]==a)
				{
					BPlot(8+i*105,143-k*11,c);
				}
			}
			break;
		case 1:
		for(k=0;k<5;k++)
		{
			if(p->a[i][j][k]==a)
			{
				BPlot(64+i*105,121-k*11,c);
			}
		}
		break;
		case 2:
		for(k=0;k<7;k++)
		{
			if(p->a[i][j][k]==a)
			{
				 BPlot(103+i*105,121-k*11,c);
			 }
		}
		break;
		case 3:
		for(k=0;k<4;k++)
		{
			if(p->a[i][j][k]==a)
			{
				BPlot(40+k*11+i*105,31,c);
			}
		}
		break;
		}
	}
	}


}


///////////////小车结构初始化//////////////
void init_car(Car* p)
{   
    int x;
    int m,n;
    x=random(10);
    p->number[0]='A'+x;              //车牌号
    p->number[1]=x;
    p->number[2]=x-1;
    p->i=0;
    p->j=0;
    p->k=0;                       //停车位初始化
    p->time=0;
    for(m=0;m<5;m++)
    { for(n=0;n<2;n++)
		{  p->road[m][n]=0;
        }                                  //路径初始化

    }
}

void init_pp(Pp * p)                                //初始化车库
{   
    int x,i,j,k;
    
    p->f1=0;
    p->f2=0;
    p->f3=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            for(k=0;k<9;k++)
            {   
               
                x=random(2);
				if((j==0&&k<9)||(j==1&&k<5)||(j==2&&k<7)||(j==3&&k<4))p->a[i][j][k]=x;
                else 
                {
				   p->a[i][j][k]=1;
                }
            }
        }
    }

}
///////////////////////进度条动画//////////////////////////////
void login()
{
    PCX_Load_Screen("s1.pcx",1);
     Delay(14);
     PCX_Load_Screen("s2.pcx",1);
}
void introduction()
{
   PCX_Load_Screen("in.pcx",1);
   getch();
   PCX_Load_Screen("pstr.pcx",1);
   return;
}

void portfunc()
{
    BUTTON a[3];
    BUTTON button_go={350,120,507,147,"进入"};
    BUTTON button_back={350,150,507,175,"返回"};
    BUTTON button_help={400,180,517,195,"详情"};
    a[0]=button_go;
    a[1]=button_back;
    a[2]=button_help;
    sprite small;
    mou curmouse,oldmouse;
 //    char s1[2],s2[2],s3[2],s4[2],s5[2];
    login();
//     s1[0]=n/10+'0';
  //  s2[0]=n%10+'0';
    //s3[0]='/';
   // s4[0]=7+'0';
    //s5[0]=8+'0';
     Delay(16);
     mouse_all(&curmouse,&oldmouse,&small);
     back("pstr.pcx",&small);
	 while(1)
	 {
	   move_mouse(& curmouse,& oldmouse,& small);
        if(curmouse.key)
        {
            if(mouse_on(a))
            {
               test();
            }
           
            else if(mouse_on(a+1))
            {
                //jiemian_homepage();
            }
              else if(mouse_on(a+2))
		   {
               introduction();
		
		   }  
             

        }
     }
   // Blit_String(X,Y,10,s1,1);
//	Blit_String(X+A,Y,10,s2,1);
//	Blit_String(X+2*A,Y,10,s3,1);
//	Blit_String(X+3*A,Y,10,s4,1);
//	Blit_String(X+4*A,Y,10,s5,1);
    
}
///////////////////////////获取车库空余车位//////////////////////////////////////////////
void attain(Pp * p)
{   
    p->a_park=0;
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            for(k=0;k<9;k++)
            {
                if(p->a[i][j][k]==0)p->a_park+=1;
            }
        }
    }

}


///////////////车位分配函数//////////////
void assign(Pp * s,Car * p)
{   
  //  printf("%d\n",a[0][0][0]);
	int i,j,k;
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<9;k++)
			 {
				if((s->a[i][j][k]==0))
					 {
					  (s->a[i][j][k])=2;
					   p->i=i;
					   p->j=j;         //车结构中关于车位安排
					   p->k=k;
                       return;
					 }
				
				 }
				 
		}
    }
}

//小车拿到分配车位

////////////////制定小车路线/////////////////////
void road_design(Car *p)
{
	int h,l;
	h=p->k;
    l=(p->i)*102;
	p->road[0][0]=INIT_X+l;                    //第一个拐点坐标
	p->road[0][1]=INIT_Y;
    switch(p->j)                         //判断区位
    {
        case 0: p->road[1][0]=INIT_X+l;          //M为第一个车位纵坐标，N为车位宽度.第一区
                p->road[1][1]=M-h*N;
                p->road[2][0]=0;
                p->road[2][1]=0;
                break;
        
        case 1: p->road[1][0]=INIT_X+l;          //第二区   
                p->road[1][1]=INIT_Y-P-h*N;
                p->road[2][0]=0;
                p->road[2][1]=0;
                break;

        case 2: p->road[1][0]=INIT_X+l;         //第三区       
                p->road[1][1]=M;  
                p->road[2][0]=L+l;
                p->road[2][1]=M;
                p->road[3][0]=L+l;
				p->road[3][1]=M-h*N-S;
                p->road[4][0]=0;
                p->road[4][1]=0;
                break;
		case 3:                     //第四区
                p->road[1][0]=INIT_X+l;
                p->road[1][1]=M;
                p->road[2][0]=L+l;
                p->road[2][1]=M;
                p->road[3][0]=L+l;
                p->road[3][1]=H;
                p->road[4][0]=L-F-N*h;
                p->road[4][1]=H;
				break;      
     }
}
//////////////过程函数//////////////////              */



/////////////////////小车事件函数/////////////////////////
void car(Pp *state,sprite * sprite,Car * p,int *j,int * pro)
{
 int index,m,m1,m2,m3,m4,o;
 *j=0;
 o=(p->i)*105;
 if(p->road[*pro][0]!=0&&p->road[*pro][1]!=0)
 {
	 if(p->road[*pro][0]<sprite->x)
	{
	  Erase_Sprite(sprite);
	  sprite->x--;
	  Behind_Sprite(sprite);
	  Draw_Sprite(sprite);   //画小车
	  delay(SPEED);
	 }
	else if ((p->road[*pro][0]==sprite->x)&&(p->road[*pro][1]==sprite->y))
	 {
	  Erase_Sprite(sprite);
	  if((p->j==0&&*pro==1)||(p->j==3&&(*pro==2||*pro==3))||(p->j==2&&*pro==2))
	  {sprite->curr_frame=(sprite->curr_frame-1)%4;}//帧数变化.左
	  else{
		  sprite->curr_frame=(sprite->curr_frame+1)%4;//右
	 }
	  Behind_Sprite(sprite);
	  Draw_Sprite(sprite);   //画小车
	  delay(SPEED);
	  (*pro)++;
	 }
	else if(p->road[*pro][1]>sprite->y)
	 {
	  Erase_Sprite(sprite);
	  sprite->y++;
	  Behind_Sprite(sprite);
	  Draw_Sprite(sprite);   //画小车
	  delay(SPEED);
	 }
	else if(p->road[*pro][0]>sprite->x)
	{
	  Erase_Sprite(sprite);
	  sprite->x++;
	  Behind_Sprite(sprite);
	  Draw_Sprite(sprite);   //画小车
	  delay(SPEED);
	 }
	 else if(p->road[*pro][1]<sprite->y)
	 {
	  Erase_Sprite(sprite);
	  sprite->y--;
	  Behind_Sprite(sprite);
	  Draw_Sprite(sprite);   //画小车
	  delay(SPEED);
	 }
	 *j=2;
   }


 m1=((sprite->x>(9+o))&&(sprite->x<(28+o))&&(sprite->y>30)&&(sprite->y<150));
 m2=((sprite->y>50)&&(sprite->y<120)&&(sprite->x>20+o)&&(sprite->x<46+o));
 m3=((sprite->x>66+o)&&(sprite->x<86+o)&&(sprite->y>30)&&(sprite->y<150));
 m4=((sprite->y>32)&&(sprite->y<50)&&(sprite->x>0+o)&&(sprite->x<100+o));
 m=m1||m2||m3||m4;
 if(m&&p->road[*pro][0]==0&&p->road[*pro][1]==0)              ///////停进车位
 {
	 switch(p->j)
	 {
		case 0: Erase_Sprite(sprite);
				sprite->x--;
				Behind_Sprite(sprite);
				Draw_Sprite(sprite);
				delay(SPEED+2);
				break;

		 case 1:Erase_Sprite(sprite);
				sprite->x++;
				Behind_Sprite(sprite);
				Draw_Sprite(sprite);
				delay(SPEED+2);
				break;

		 case 2:Erase_Sprite(sprite);
			   sprite->x++;
			   Behind_Sprite(sprite);
			   Draw_Sprite(sprite);
			   delay(SPEED+2);
			   break;
		 case 3:Erase_Sprite(sprite);
			   sprite->y--;
			   Behind_Sprite(sprite);
			   Draw_Sprite(sprite);
			   delay(SPEED+2);
			   break;
	 }
 }
 else if(*j!=2)
   {   Sprite_Delete(sprite);
	   state->a[p->i][p->j][p->k]=1;
	   *j=1;

 }
}
/*  void Judge_Sprite(sprite_ptr head)                     //检查子画面
{
sprite_ptr sprite;
sprite=head;
do{
	sprite->car(sprite);                //执行子画面事件函数
	sprite=sprite->next;
}while(sprite!=NULL);
}

void Sprite_Build(sprite_ptr head)                   //建立子画面链表(几辆车)
{
int index;
pcx_picture objects_pcx;
PCX_Init((pcx_picture_ptr)&objects_pcx);
PCX_Load("cart.pcx",(pcx_picture_ptr)&objects_pcx,1);
now=pre=(struct sprite *)malloc(sizeof(struct sprite_type));
head=now;
Sprite_Init(now,50,50,0,0,0,0,car);
for(index=0;index<4;index++)
{
 PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,now,index,index,0);
}
pre->next=NULL;
PCX_Delete((pcx_picture_ptr)&objects_pcx);

}
  */
////////////////////////////停车动画/////////////////////////////////////////

void build_sprite(sprite * spo,Car * cr)
{ int index=0;
  pcx_picture objects_pcx;
  //  pcx_picture o1,o2,o3,o4,o5;
  PCX_Init((pcx_picture_ptr)&objects_pcx);
  PCX_Load("but.pcx",(pcx_picture_ptr)&objects_pcx,1);
  Sprite_Init(&spo[0],OX,INIT_Y,0,0,0,0);
  for(index=0;index<4;index++)
	{
	 PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,&spo[0],index,index,0);
	}
  PCX_Delete((pcx_picture_ptr)&objects_pcx);
  PCX_Load("boo.pcx",(pcx_picture_ptr)&objects_pcx,1);
  Sprite_Init(&spo[1],OX,INIT_Y,0,0,0,0);
  for(index=0;index<4;index++)
	{
	 PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,&spo[1],index,index,0);
	}
  PCX_Delete((pcx_picture_ptr)&objects_pcx);
  PCX_Load("3.pcx",(pcx_picture_ptr)&objects_pcx,1);
  Sprite_Init(&spo[2],OX,INIT_Y,0,0,0,0);
  for(index=0;index<4;index++)
	{
	 PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,&spo[2],index,index,0);
	}
  PCX_Delete((pcx_picture_ptr)&objects_pcx);
  PCX_Load("4.pcx",(pcx_picture_ptr)&objects_pcx,1);
  Sprite_Init(&spo[3],OX,INIT_Y,0,0,0,0);
  for(index=0;index<4;index++)
	{
	 PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,&spo[3],index,index,0);
	}
  PCX_Delete((pcx_picture_ptr)&objects_pcx);
  PCX_Load("5.pcx",(pcx_picture_ptr)&objects_pcx,1);
  Sprite_Init(&spo[4],OX,INIT_Y,0,0,0,0);
  for(index=0;index<4;index++)
	{
	 PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,&spo[4],index,index,0);
	}
  PCX_Delete((pcx_picture_ptr)&objects_pcx);
  Behind_Sprite(&spo[0]);
  Behind_Sprite(&spo[1]);
  Behind_Sprite(&spo[2]);
  Behind_Sprite(&spo[3]);
  Behind_Sprite(&spo[4]);
}

void pull_over(char *filename,Pp *state,Car * cr,Car * boom,sprite * spo,sprite * head ,int f)
{
  BUTTON a[3];
  BUTTON button_back={40,180,55,195,"主页"};
  BUTTON button_stop={58,150,70,175,"暂停"};
  BUTTON button_exit={75,180,80,195,"退出"};
  a[0]=button_back;
  a[1]=button_stop;
  a[2]=button_exit;
  sprite small;
  mou curmouse,oldmouse;  
  int j=0,k=0,s=0,index=0;
  mouse_all(&curmouse,&oldmouse,&small);
  Fill_Screen(0);
  PCX_Load_Screen(filename,1);
  Behind_Sprite_Size(&small,20,20);
  lamp();
  c_lamp(state,1);
  build_sprite(head,cr);
  spo=head;
  cr=boom;
  for(index=0;index<f;index++,spo++,cr++)
  {spo->x=OX+(cr->i)*100;
  }
  
    
      
      for(s=0;;s++)
  {   while(1)
      {
      
          move_mouse(&curmouse,&oldmouse,&small);
          if(curmouse.key&&mouse_on(a+1))
	         {while(!kbhit())
                   {}
             }
      }
      
     spo=head;
	 cr=boom;
		if(k<f)
	   {
		   k=s/100+1;
		   for(index=0;index<k;index++,spo++,cr++)
		  {   
		   car(state,spo,cr,&j,&(spo->pro));
           c_lamp(state,1);
		   delay(2);
			}
	   }
	   else{
			 for(index=0;index<f;index++,spo++,cr++)
			{
               car(state,spo,cr,&j,&(spo->pro));
               c_lamp(state,1);
               delay(2);
			}
		 }
        
       if(j==1)    break;
  }
}

void test()                             //尝试小车转弯
{
  Set_Video_Mode(VGA256);
  int index,num,m=0,i,j,k;
  randomize();
  Pp stu;
  Pp  * state;
  sprite *spo,head[10];
  Car *cr, boom[10];
  pcx_picture objects_pcx;
  //num=random(10)+1;
  num=2;                                  

  state=&stu;
  cr=boom;
  spo=head;    //保存头指针
/////////////// 进入加载过程的（动画）/// 显示空余车位/////////////////////////////////////////////////////////
  init_pp(state);                                          //初始化车库
  attain(state);                                       //获取空余车位
 // login();
       
    for(i=0;i<num;i++,cr++)
{    
    init_car(cr);
    assign(state,cr);
    attain(state);
    road_design(cr);
}

   attain(state);
  /////////////////////////单弄个函数：背景列表格把车位，车牌号什么的展示出来，以及空车位和已停车位/////////////////////////////////////////////////////////
  
  
  pull_over("garage.pcx",state,cr,boom,spo,head,num);//  一层停车动画

 //  if(state->f2)
//{
// Delay(16);
// Fill_Screen(0);
// PCX_Load_Screen("floor2.pcx",1);
 //spo=head;
 //pull_over2(cr,cr,spo,head,state->f2);      //  }// 二层停车动画
 //if(state->f3)
//{  
// delay(8);
 //pull_over("floor3.pcx",cr,cr,spo,head,state->f3); } // 三层停车动画*/
 getch();

}

////////////////////////有待实现的功能：鼠标。3.时间显示。5.边栏的停车状态表示表格。。6.引导箭头///////////////////

