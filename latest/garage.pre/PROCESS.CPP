
#include"process.h"
/////////////////////提示灯/////////////////////////////////
void lamp()
{  int i,j;
    int c=50;
    for(j=0;j<3;j++)
    {  
        for(i=0;i<9;i++)
    {
		BPlot(8+j*105,139-i*11,c);
    }
   
        for(i=0;i<5;i++)
    {
        BPlot(64+j*105,117-i*11,c);
    }
    
        for(i=0;i<7;i++)
    {
       BPlot(103+j*105,117-i*11,c);
    }
    
        for(i=0;i<4;i++)
    {
		BPlot(39+i*11+j*105,27,c);
	}
	}
}
void c_lamp(Pp* p,int a) /////////////控制车位灯的函数
{
	int i,j,k;
    int c=78;
	for(i=0;i<3;i++)
	{
	   for(j=0;j<4;j++)
   {	if(j==0)
       {	for(k=0;k<9;k++)
			{
				if(p->a[i][j][k]==a)
				{
					BPlot(8+i*105,139-k*11,c);
				}
			}
			
   }
       if(j==1)
       {
		for(k=0;k<5;k++)
		{
			if(p->a[i][j][k]==a)
			{
				BPlot(64+i*105,117-k*11,c);
			}
		}
       }
		if(j==3)
        {
		for(k=0;k<7;k++)
		{
			if(p->a[i][j][k]==a)
			{
				 BPlot(103+i*105,51+k*11,c);
			 }
		}
        }
		if(j==2)
        {
		for(k=0;k<4;k++)
		{
			if(p->a[i][j][k]==a)
			{
				BPlot(39+k*11+i*105,27,c);
            }
		}
		
		}
	}
	}


}
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
               fill_Rectangle(x,y,x+100,y+50,0);
               break;
        case 1:
               fill_Rectangle(x,y,x+159,y+20,0);
               break;

    }

}
//////////////////////////////将数字转化为字符串////////////////////////////////////
char* transform(int n)
{
    char m1,m2;
    char *s;
    m1=n/10+'0';
    m2=n%10+'0';
    s[0]=m1;
    s[1]=m2;
    s[2]='\0';
    return s;

}

void base2(int n,Car *cr) ////////////////////////////////显示屏显示第二屏
{
	char *s;
	char m;
    int h;
	switch(n)
    {
        case 0:
               s="车位：";                  //系统模式
               Load_LED(150,178,s,0,140);
               s=transform(cr->i+1);
               Load_LED(192,185,s,1,79);
			   s="-";
               Load_LED(208,185,s,1,79);
               Load_LED(231,185,s,1,79);
               s=transform(cr->j+1);
               Load_LED(215,185,s,1,79);
               s=transform(cr->k+1);
               Load_LED(238,185,s,1,79);
               break;
		case 1:s="请选择指示灯为绿色的";
               Load_LED(150,178,s,0,140);
               Delay(15);
               wipeout(150,178,1);
               s="车位";
               Load_LED(150,178,s,0,140);
               wipeout(150,178,1);
               s="-";
               Load_LED(213,185,s,1,79);
               Load_LED(236,185,s,1,79);
               s="层数：";
               Load_LED(150,178,s,0,140);
               m=bioskey(0);
               h=m-'0';
               cr->i=h-1;
               wipeout(150,178,1);
               s="-";
               Load_LED(213,185,s,1,79);
               Load_LED(236,185,s,1,79);
               s=transform(cr->i+1);
               Load_LED(194,185,s,1,79);
               s="区域：";
               Load_LED(150,178,s,0,140);
               m=bioskey(0);
               h=m-'0';
               cr->j=h-1;
               wipeout(150,178,1);
               s="-";
               Load_LED(213,185,s,1,79);
               Load_LED(236,185,s,1,79);
               s=transform(cr->i+1);
               Load_LED(194,185,s,1,79);
               s=transform(cr->j+1);
               Load_LED(217,185,s,1,79);
               s="号码：";
               Load_LED(150,178,s,0,140);
               m=bioskey(0);
               h=m-'0';
               cr->k=h-1;
               wipeout(150,178,1);
               delay(2);
               s="车位：";
               Load_LED(150,178,s,0,140);
               s=transform(cr->k+1);
               Load_LED(239,185,s,1,79);
               s="-";
               Load_LED(213,185,s,1,79);
               Load_LED(236,185,s,1,79);
               s=transform(cr->i+1);
               Load_LED(194,185,s,1,79);
               s=transform(cr->j+1);
               Load_LED(217,185,s,1,79);
    }
}

void base1(Pp *state,Car *cr)     ////////////////////显示屏第一屏/////////////////////////
{
  char *s1,*s2,*s3,*s4,*s5,*s;
  int m;
  s1="floor 1:  floor 2:";
  s2="floor 3:" ;
  s3="系统设定：";
  s4="自定义：";
  //s3="再来一次";
//  s4="返回主页";
  s5="空车位";
  	while(!kbhit())
  {                                                      //获取空余车位并显示
  attain(state);
  Load_LED(199,178,s5,0,123);
  Delay(20);
  wipeout(150,178,1);
  Load_LED(150,178,s1,1,140);//紫色
  Load_LED(150,187,s2,1,140);
  s=transform(state->f1);
  Load_LED(211,178,s,1,123);
  s=transform(state->f2);
  Load_LED(293,178,s,1,123);
  s=transform(state->f3);
  Load_LED(211,187,s,1,123);//绿色
  Delay(20);
  wipeout(150,178,1);
  }
  m=bioskey(0);
  Load_LED(150,178,s3,0,63);
  Load_LED(235,178,s4,0,63);
  s="F1";
  Load_LED(220,185,s,1,63);
  s="F2";
  Load_LED(288,185,s,1,63);
  m=bioskey(0);
   if(m==F1) 
  {
    
   // printf("%d",state->a[0][0][2]);
    assign(state,cr);      //系统安排车位
    //printf("%d%d%d",cr->i,cr->j,cr->k);
    wipeout(150,178,1);
  // PCX_Load_Screen("in.pcx",1);
    base2(0,cr);
  }                   
  if(m==F2)            //自定义模式返回1
  {
       wipeout(150,178,1);
       base2(1,cr);
  }

}
/*int base3()                    ///////////////////////显示屏第三屏////////////////////////
{
	char*s,m;
	wipeout(150,178,1);
	s="返回：";
	Load_LED(150,178,s,0,63);         //黄色
	s="Esc";
	Load_LED(189,185,s,1,63);
	s="再来一次：";
	Load_LED(218,178,s,0,63);
	s="F3";
	Load_LED(290,185,s,1,63);
	m=bioskey(0);
	if(m==F3) return 1;
} */
void arrow(Arrow p)     //////////////////控制引导函数////////////////
{
    int c=50;
    int x=p->x,y=p->y;
switch(p->des)
    {
        case 0:
               fill_Rectangle(x,y,x+12,y+12,0);
        case 1:line(x+1,y+6,x+6,y+1,c);
               line(x+6,y+1,x+11,y+6,c);
               line(x+1,y+9,x+6,y+4,c);
               line(x+6,y+4,x+11,y+9,c);
               break;
        case 2:line(x+3,y+1,x+8,y+6,c);
               line(x+3,y+11,x+8,y+6,c);
               line(x+6,y+1,x+11,y+6,c);
               line(x+6,y+11,x+11,y+6,c);
               break;
        case 3:line(x+1,y+6,x+6,y+1,c);
               line(x+1,y+6,x+6,y+11,c);
               line(x+4,y+6,x+9,y+1,c);
               line(x+4,y+6,x+9,y+11,c);
               break;
        case 4:line(x+1,y+3,x+6,y+6,c);
               line(x+6,y+6,x+11,y+1,c);
               line(x+1,y+6,x+6,y+11,c);
               line(x+6,y+11,x+11,y+6,c);
               break;       
    }

}
/*void draw_sp(int x,int y,int i)
{switch(i)
	{

	  case 0:   fill_Rectangle_Xor(x,y,x+6,y+10,180);
				Plot_Xor(x,y,60);
				Plot_Xor(x+1,y+1,60);
				Plot_Xor(x+6,y,60);
				Plot_Xor(x+5,y+1,60);
				fill_Rectangle_Xor(x+1,y+5,x+5,y+6,7);
				hline_Xor(x,x+6,y+10,56);
				break;
	  case 2:   fill_Rectangle_Xor(x,y+2,x+10,y+8,180);
			    Plot_Xor(x,y+2,60);
				Plot_Xor(x+1,y+3,60);
				Plot_Xor(x,y+8,60);
				Plot_Xor(x+1,y+7,60);
				fill_Rectangle_Xor(x+5,y+3,x+6,y+7,7);
				vline_Xor(x+10,y+2,y+8,56);
				break;
	  case 1:   fill_Rectangle_Xor(x-10,y+2,x,y+8,180);
				Plot_Xor(x,y+2,60);
				Plot_Xor(x-1,y+3,60);
				Plot_Xor(x,y+8,60);
				Plot_Xor(x-1,y+7,60);
				fill_Rectangle_Xor(x-6,y+3,x-5,y+7,7);
				vline_Xor(x-10,y+2,y+8,56);
				break;
	  case 3:   fill_Rectangle_Xor(x,y,x+6,y+10,180);
				Plot_Xor(x,y+10,60);
				Plot_Xor(x+1,y+9,60);
				Plot_Xor(x+6,y+10,60);
				Plot_Xor(x+5,y+9,60);
				fill_Rectangle_Xor(x+1,y+4,x+5,y+5,7);
				hline_Xor(x,x+6,y,56);
				break;

	}
}
*/


///////////////周日需要建立结构sp,仿照子画面结构将，x,y,方向存入。修改分配。路径函数。将箭头加在关键结点/。////////////////////////////////


///////////////小车结构初始化//////////////
void init_car(Car* p)
{   
    int m,n;
    p->i=0;
    p->j=0;
    p->k=0;                       //停车位初始化
    p->time=0;
    for(m=0;m<7;m++)
    { for(n=0;n<2;n++)
		 p->road[m][n]=0;
                                            //路径初始化

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
				if((j==0&&k<9)||(j==1&&k<5)||(j==2&&k<4)||(j==3&&k<7))p->a[i][j][k]=x;
                else 
                {
				   p->a[i][j][k]=1;
                }
            }
        }
    }

}
/////////////////////初始化引导系统/////////////////////////
void init_arrow(Arrow p)
{
    int i;
    for(i=0;i<3;i++)
    {   
        p[i*5].y=149;
        p[i*5].x=31+i*105;
        p[i*5+2].y=51;
        p[i*5+2].x=29;
        p[i*5+3].y=51;
        p[i*5+3].x=68;
        p[i*5+1].y=93;
        p[i*5+1].x=29;
        p[i*5+4].y=93;
        p[i*5+4].x=68;
    }
    for(i=0;i<15;i++)
    {
        p[i].des=0;
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
    p->f1=0;
    p->f2=0;
    p->f3=0;
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            for(k=0;k<9;k++)
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
					  (s->a[i][j][k])=2;//车位被分配后的状态
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

void road_design(Cart p)
{
	int k;
	k=p->k;
	p->road[0][0]=INIT_X;                    //第一个拐点坐标
	p->road[0][1]=INIT_Y;
    switch(p->j)                         //判断区位
    {
        case 0: p->road[1][0]=INIT_X;          //M为第一个车位纵坐标，N为车位宽度.第一区
                p->road[1][1]=M-k*N;
                break;
        
        case 1: p->road[1][0]=INIT_X;          //第二区   
                p->road[1][1]=M;
                p->road[2][0]=INIT_X+k*N;
                p->road[2][1]=M;
                break;

        case 2: p->road[1][0]=INIT_X;         //第三区       
                p->road[1][1]=M;  
                p->road[2][0]=L;
                p->road[2][1]=M;
                p->road[3][0]=L;
				p->road[3][1]=M-k*N;
                break;
        case 3: if(k<5)                     //第四区
               {
                   p->road[1][0]=INIT_X;
                   p->road[1][1]=H;
				   p->road[2][0]=INIT_X+k*N+I;   //I为微调量
				   p->road[2][1]=H;
               }
                else
               { 
                   p->road[1][0]=INIT_X;
                   p->road[1][1]=M; 
                   p->road[2][0]=Q;
                   p->road[2][1]=M;
                   p->road[3][0]=Q;
                   p->road[3][1]=H;
                   p->road[4][0]=Q+F+(k-5)*N; //F为微调量
                   p->road[4][1]=H;
              }
              return;      
     }
}

//////////////过程函数//////////////////              */



















/*  
/////////////////////小车停车事件函数/////////////////////////
void car(Pp *state,sprite*ob,Car * p,Arrow ar,int *j,int * pro)
{
 int index,m;
 static int pro;
 *j=0;
 if(p->road[pro][0]!=0&&p->road[pro][1]!=0)
 {
     if(p->road[pro][0]<sprite->x)
    {
      Erase_Sprite(sprite);
      sprite->x--;
      Behind_Sprite(sprite);
      Draw_Sprite(sprite);   //画小车
	  delay(SPEED);
     }
    else if ((p->road[pro][0]==sprite->x)&&(p->road[pro][1]==sprite->y))
     {
      Erase_Sprite(sprite);
      if((p->road[pro+1][0]==0)&&(p->road[pro+1][1]==0)&&(p->j==0||p->j==3))
      {sprite->curr_frame=(sprite->curr_frame-1)%4;}//帧数变化
      else{sprite->curr_frame=(sprite->curr_frame+1)%4;}
      Behind_Sprite(sprite);
      Draw_Sprite(sprite);   //画小车
      delay(SPEED);
      pro++;
     }
    else if(p->road[pro][1]>sprite->y)
     {
      Erase_Sprite(sprite);
      sprite->y--;
      Behind_Sprite(sprite);
      Draw_Sprite(sprite);   //画小车
      delay(SPEED);    
     }
    else if(p->road[pro][0]>sprite->x)
    {
      Erase_Sprite(sprite);
      sprite->x++;
      Behind_Sprite(sprite);
      Draw_Sprite(sprite);   //画小车
      delay(SPEED);
     }
     else if(p->road[pro][1]<sprite->y)
     {
      Erase_Sprite(sprite);
      sprite->y++;
      Behind_Sprite(sprite);
      Draw_Sprite(sprite);   //画小车
      delay(SPEED);    
	 }
	 *j=2;
   }
 m=((sprite->x>5)&&(sprite->x<55))||((sprite->y>5)&&(sprite->y<55))||((sprite->x>220)&&(sprite->x<245))||((sprite->y>140)&&(sprite->y<194));
 if((p->road[pro][0]==0)&&(p->road[pro][1]==0)&&m)              ///////停进车位
 {
	 switch(p->j)
     {
        case 0: Erase_Sprite(sprite);
                sprite->x--;
                Behind_Sprite(sprite);
				Draw_Sprite(sprite);
				delay(SPEED);
                break;

         case 1:Erase_Sprite(sprite);
                sprite->y++;
                Behind_Sprite(sprite);
				Draw_Sprite(sprite);
                delay(SPEED);
                Sprite_Delete(sprite);
                break;

         case 2:Erase_Sprite(sprite);
               sprite->x++;
               Behind_Sprite(sprite);
			   Draw_Sprite(sprite);
               delay(SPEED);
               Sprite_Delete(sprite);
               break;
         case 3:Erase_Sprite(sprite);
               sprite->y--;
               Behind_Sprite(sprite);
               Draw_Sprite(sprite);
               delay(SPEED+2);
               Sprite_Delete(sprite);
               break;
     }
 }
 else if(*j!=2)
   {  *j=1;
	 return;
 }
 
}
//////////////////////引导小车事件函数//////////////////////////////
void ar_design(Car *cr,Arrow p)
{
int s;
s=5*cr->i;
switch(cr->i):
    { 
        case 0:       p[0].des=1;
                      break;
        case 1:   
                      p[0].des=2;
                      break;
        case  2:      p[0].des=2;
                      p[5].des=2;
                      break;
    }                   
            


    p[0+s].des=1;
    switch(cr->j):
    { 
        case 0:
            if(cr->k<4)
           {
               p[1+s].des=4;
           }
            else{
                p[1+s].des=1;
                p[2+s].des=4;
            }
            break;
               
        case 1:if(cr->k<2)
           {
               p[1+s].des=2;
           }
               else{
                   p[1+s].des=1;
                   p[2+s].des=2;
               }
               break;
        case 2:
               p[1+s].des=1;
               p[2+s].des=2;
               p[3+s].des=1;
               break;
        case 3:
               p[1+s].des=1;
               p[2+s].des=2;
               p[3+s].des=3;
               p[4+s].des=2;
               break;
    }
        

           




}




////////////////////////////停车动画/////////////////////////////////////////
void build_sprite(sprite * spo,Car * cr)
{ int index=0;
  pcx_picture objects_pcx;
  //  pcx_picture o1,o2,o3,o4,o5;
  PCX_Init((pcx_picture_ptr)&objects_pcx);
  PCX_Load("boo.pcx",(pcx_picture_ptr)&objects_pcx,1);
  Sprite_Init(&spo[0],OX,INIT_Y,0,0,0,0);
  for(index=0;index<4;index++)
	{
	 PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,&spo[0],index,index,0);
	}
  PCX_Delete((pcx_picture_ptr)&objects_pcx);

  Behind_Sprite(spo);
}

void pull_over(Pp *state,Car * cr,sprite * spo,Arrow ar)
{
   

  //s5=state->a_park;
      
  int s;int j,m=0;
  char *s1;

       build_sprite(spo,cr); 
       ar_design(cr,ar);       
       
     while(1)
	  {
		  
           
           attain(state);
           if(m!=state->a_park)
           {
               m=state->a_park;
              wipeout(5,167,0);
	          s1=transform(m);
	          Load_LED(8,172,s1,1,50);
           }
		  car(state,spo,cr,&j,&(spo->pro));
		  
          c_lamp(state,1);
          delay(2);
		
        
          if(j==1) 
          {     attain(state);
           if(m!=state->a_park)
           {
               m=state->a_park;
              wipeout(5,167,0);
	          s1=transform(m);
	          Load_LED(8,172,s1,1,50);
           }
          
              break;}
      }
  
// if( !base3())  return;
  //getch();
   //}
}

*/



void car_in1()
{
    sprite c1;
	pcx_picture background_pcx,o1,objects_pcx;
	PCX_Load1("cars.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,148,170,0,0,0,0,105,65,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,105,65);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("bd.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

    Behind_Sprite_Size((sprite_ptr)&c1,105,65);//取图片后内容

while(c1.y>144)
{
           Erase_Sprite_Size((sprite_ptr)&c1,105,65);
		   c1.y-=1;c1.x+=4; 
		   Behind_Sprite_Size((sprite_ptr)&c1,105,65);
		   Draw_Sprite_Size((sprite_ptr)&c1,105,65);
           Delay(1);
}
    Sprite_Delete_Size((sprite_ptr)&c1,1);
    Delay(2);
}

void car_in3(int n,Car *cr,Pp *state) ////////////////////////////////显示屏显示第二屏
{
   char *s,*s4,*s5,*s6,*s7;
   char	*s1="111",*s2="222",*s3="333";
	char m;
	int h;
	switch(n)
	{
		case 0:
              // printf("%d",cr->i);
		 	   wipeout(0,0,0); 
               s="车位：";                  //系统模式
               Load_LED(0,0,s,0,140);
               s=transform(cr->i+1);
               Load_LED(10,20,s,1,79);
			   s="-";
               Load_LED(35,20,s,1,79);
               Load_LED(75,20,s,1,79);
               s=transform(cr->j+1);
               Load_LED(42,20,s,1,79);
               s=transform(cr->k+1);
               Load_LED(82,20,s,1,79);
               getch();
			   break;
		  case 1:Delay(15);
               wipeout(0,0,0);
               s="请输入预定";
               Load_LED(0,0,s,0,140);
               s="车位";
               Load_LED(0,18,s,0,140);
               Delay(15);
               wipeout(0,0,0);
               s="-";
               Load_LED(35,20,s,1,79);
               Load_LED(75,20,s,1,79);
               s="层数：";
               Load_LED(0,0,s,0,140);
               m=bioskey(0);
               h=m-'0';
               cr->i=h-1;
               wipeout(0,0,0);
               s="-";
               Load_LED(35,20,s,1,79);
               Load_LED(75,20,s,1,79);
               s=transform(cr->i+1);
               Load_LED(10,20,s,1,79);
               s="区域：";
               Load_LED(0,0,s,0,140);
               m=bioskey(0);
               h=m-'0';
               cr->j=h-1;
               wipeout(0,0,0);
               s="-";
               Load_LED(35,20,s,1,79);
               Load_LED(75,20,s,1,79);
               s=transform(cr->i+1);
               Load_LED(10,20,s,1,79);
               s=transform(cr->j+1);
               Load_LED(42,20,s,1,79);
               s="号码：";
               Load_LED(0,0,s,0,140);
               m=bioskey(0);
               h=m-'0';
               cr->k=h-1;
               wipeout(0,0,0);
               delay(2);
               s="车位：";
               Load_LED(0,0,s,0,140);
               s=transform(cr->k+1);
               Load_LED(82,20,s,1,79);
               s="-";
               Load_LED(35,20,s,1,79);
               Load_LED(75,20,s,1,79);
               s=transform(cr->i+1);
               Load_LED(10,20,s,1,79);
               s=transform(cr->j+1);
               Load_LED(42,20,s,1,79);
               getch();
               break;
            
    }

}

void car_in2(Car *cr,Pp *state)
{
char *s,*s1,*s2,*s3,*s4,*s5,*s6,*s7,*s8;
int m;
int o;
attain(state);
while(!kbhit())
{

	PCX_Load_Screen("charge.pcx",1);
	s6="欢迎停车";
	Load_LED(20,18,s6,0,50);
	Delay(20);
	s7="本车库提供自";
	wipeout(0,0,0);
	Load_LED(0,6,s7,0,140);
	s="动引导停车";
	Load_LED(0,24,s,0,140);
	Delay(20);
	wipeout(0,0,0);
	s5="Available";
	Load_LED(21,10,s5,1,87);
	s1=transform(state->a_park);
	Load_LED(45,30,s1,1,50);
	Delay(20);
	wipeout(0,0,0);
}
	m=bioskey(0);
	s8="普通用户：";
	Load_LED(0,0,s8,0,63);
	s2="F1";
	Load_LED(70,9,s2,1,63);
	s3="持卡用户：";
	Load_LED(0,18,s3,0,63);
	s4="F2";
	Load_LED(70,27,s4,1,63);
	
    m=bioskey(0);
if(m==F1) 
  {
    
   // printf("%d",state->a[0][0][2]);
     assign(state,cr);      //系统安排车位
  //   printf("%d",cr->i);
    //printf("%d%d%d",cr->i,cr->j,cr->k);
  // wipeout(0,0,0);
  // PCX_Load_Screen("in.pcx",1);
	car_in3(0,cr,state);
  }
  if(m==F2)            //自定义模式返回1
  {

	   car_in3(1,cr,state);
  }

}

void floor1()
{
    sprite c1;
	pcx_picture background_pcx,o1,objects_pcx;
	PCX_Load1("carf.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,80,77,0,0,0,0,110,95,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,110,95);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("floor1.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

    Behind_Sprite_Size((sprite_ptr)&c1,110,95);//取图片后内容

while(c1.y<102)
{
           Erase_Sprite_Size((sprite_ptr)&c1,110,95);
		   c1.y+=1;c1.x+=6; 
		   Behind_Sprite_Size((sprite_ptr)&c1,110,95);
		   Draw_Sprite_Size((sprite_ptr)&c1,110,95);
           Delay(1);
}
    Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);

}
void floor2()
{
    sprite c1;
	pcx_picture background_pcx,o1,objects_pcx;
	PCX_Load1("carf2.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,160,137,0,0,0,0,100,85,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,100,85);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("floor2.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

    Behind_Sprite_Size((sprite_ptr)&c1,100,85);//取图片后内容

while(c1.y>55)
{
           Erase_Sprite_Size((sprite_ptr)&c1,100,85);
		   c1.y-=3;c1.x-=1; 
		   Behind_Sprite_Size((sprite_ptr)&c1,100,85);
		   Draw_Sprite_Size((sprite_ptr)&c1,100,85);
           Delay(1);
}

    Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);

	PCX_Load1("carf22.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,125,137,0,0,0,0,95,85,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,95,85);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("floor22.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

    Behind_Sprite_Size((sprite_ptr)&c1,95,85);//取图片后内容

while(c1.y>35)
{
           Erase_Sprite_Size((sprite_ptr)&c1,95,85);
		   if(c1.y>120)
           { c1.y-=3;
                  }
           else
           {
               c1.y-=4;
               c1.x+=2;
           }
		   Behind_Sprite_Size((sprite_ptr)&c1,95,85);
		   Draw_Sprite_Size((sprite_ptr)&c1,95,85);
           Delay(2);
}

    Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);

    
}
void floor3()
{
    sprite c1;
	pcx_picture background_pcx,o1,objects_pcx;
	PCX_Load1("carf2.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,160,137,0,0,0,0,100,85,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,100,85);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("floor2.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

    Behind_Sprite_Size((sprite_ptr)&c1,100,85);//取图片后内容

while(c1.y>55)
{
           Erase_Sprite_Size((sprite_ptr)&c1,100,85);
		   c1.y-=3;c1.x-=1; 
		   Behind_Sprite_Size((sprite_ptr)&c1,100,85);
		   Draw_Sprite_Size((sprite_ptr)&c1,100,85);
           Delay(1);
}

    Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);

	PCX_Load1("carf22.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,125,137,0,0,0,0,95,85,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,95,85);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("floor31.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

    Behind_Sprite_Size((sprite_ptr)&c1,95,85);//取图片后内容

while(c1.y>35)
{
           Erase_Sprite_Size((sprite_ptr)&c1,95,85);
		   if(c1.y>120)
           { c1.y-=3;
                  }
           else
           {
               c1.y-=4;
               c1.x+=2;
           }
		   Behind_Sprite_Size((sprite_ptr)&c1,95,85);
		   Draw_Sprite_Size((sprite_ptr)&c1,95,85);
           Delay(2);
}

    Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);
	PCX_Load1("carf22.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,125,137,0,0,0,0,95,85,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,95,85);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("floor32.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

    Behind_Sprite_Size((sprite_ptr)&c1,95,85);//取图片后内容

while(c1.y>35)
{
           Erase_Sprite_Size((sprite_ptr)&c1,95,85);
		   if(c1.y>120)
           { c1.y-=3;
                  }
           else
           {
               c1.y-=4;
               c1.x+=2;
           }
		   Behind_Sprite_Size((sprite_ptr)&c1,95,85);
		   Draw_Sprite_Size((sprite_ptr)&c1,95,85);
           Delay(2);
}

    Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);


    getch();
/*  
	PCX_Load1("carf22.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,125,137,0,0,0,0,95,85,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,95,85);//将屏幕内容复制给小图片

    Fill_Screen(0);
	PCX_Load1("floor22.pcx",(pcx_picture_ptr)&background_pcx,1);//背景

   Behind_Sprite_Size((sprite_ptr)&c1,95,85);//取图片后内容
    while(c1.y>35)
{
           Erase_Sprite_Size((sprite_ptr)&c1,95,85);
		   if(c1.y>120)
           { c1.y-=3;
                  }
           else
           {
               c1.y-=4;
               c1.x+=2;
           }
		   Behind_Sprite_Size((sprite_ptr)&c1,95,85);
		   Draw_Sprite_Size((sprite_ptr)&c1,95,85);
           Delay(2);
}
  Sprite_Delete_Size((sprite_ptr)&c1,1);
    delay(25);*/

}
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
 setfillstyle(1,10);
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
  void ss()
{
    int gd=VGA;
    int gm=VGAMED;
    initgraph(&gd,&gm,"bgi");
    cleardevice();
   // setcolor(10);
    bk();

  /*  for(i=0;;i++)
    {
        setvisualpage(0);
        setactivepage(1);
        cleardevice();
        //先画背景，再画箭头，最后画小车。
        setvisualpage(1);
        setactivepage(0);
        cleardevice();
         //先画背景，再画箭头，最后画小车。画小车用循环函数。每个小车都依次画一遍
    }*/
    getch();
}


void test()                             //尝试小车转弯
{
  Set_Video_Mode(VGA256);
  int index,m=0,i,j,k;
  int y=180;
  randomize();
  Arrow ar;
  Pp state;
  sprite spo;
  Car cr[10];
  //num=random(10)+1;

  //保存头指针
/////////////// 进入加载过程的（动画）/// 显示空余车位/////////////////////////////////////////////////////////
      

     init_pp(&state); //初始化车库
       for(i=0;i<10;i++)  //初始化车
	   { init_car(&cr[i]);
       }
     //  assign(&state,cr);
   //  car_in3(0,cr,&state);
car_in1();                                   //进入动画
car_in2(cr,&state);
//car_in3(car_in2(&state),boom,&state);
//第一辆车信息被确定
//接下来确定同层其他车辆

                                              //斜坡动画
//base1(&state,cr);                                              //
delay(20);   ////车位动画
situation(cr[0].i);
ss();

	 //  init_arrow(ar);
     //  PCX_Load_Screen("garage.pcx",1);
       //lamp();
	   //c_lamp(&state,1);
   // while(1) 
   //{   
    
       
       //wipeout(150,178,1);
	//  
	//   road_design(&cr);
                                        

 //Set_Video_Mode(TEXT_MODE);
 

//car_in1();
  /////////////////////////单弄个函数：背景列表格把车位，车牌号什么的展示出来，以及空车位和已停车位/////////////////////////////////////////////////////////
//car_in3(car_in2(&state),cr,&state);

    
//PCX_Load_Screen("garage.pcx",1);
//draw_sp(190,175,0);
//fill_Rectangle(190,175,196,185,29);
//ccc();




//pull_over(&state,&cr,&spo,ar);//  一层停车动画

 getch();

}

////////////////////////有待实现的功能：指示灯有问题。3.时间显示。5.边栏的停车状态表示表格。。6.引导箭头//////////////////
