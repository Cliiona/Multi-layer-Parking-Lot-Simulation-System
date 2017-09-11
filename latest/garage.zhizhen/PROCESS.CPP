#include"process.h"
////////////////画车库/////////////////// 
void floor()
 { 
	 //Fill_Screen(81);
	 fill_Rectangle(1,1,278,198,9);
//	 fill_Rectangle(280,1,318,198,78);
}

void _cspeed(int x,int y)
{   
    int i;
    for(i=0;i<4;i++)
    {
        fill_Rectangle(x+i*4,y,x+1+i*4,y+1,0);
    }
    for(i=0;i<3;i++)
    {
    fill_Rectangle(x+2+i*4,y,x+3+i*4,y+1,43);
    }
}

void cspeed(int x,int y)
{
    int i;
     for(i=0;i<4;i++)
    {        fill_Rectangle(x,y+i*4,x+1,y+1+i*4,18);
    }
    for(i=0;i<3;i++)
    {
    fill_Rectangle(x,y+2+i*4,x+1,y+3+i*4,43);
    }

}

void yline()
{
   int i;
   for(i=0;i<7;i++)
   {
       fill_Rectangle(0,31+N*i,30,32+N*i,31);
   }
   for(i=0;i<7;i++)
   {
       fill_Rectangle(250,31+N*i,279,32+N*i,31);
   }
   for(i=0;i<10;i++)
   {
       fill_Rectangle(51+N*i,0,52+N*i,30,31);
   }
   for(i=0;i<4;i++)
   {
       fill_Rectangle(189+N*i,171,190+N*i,200,31);
   }
   fill_Rectangle(31,31,250,170,2);
   fill_Rectangle(34,34,247,168,31);
   fill_Rectangle(36,36,245,166,26);
   fill_Rectangle(66,61,120,135,2);
   fill_Rectangle(146,61,215,135,2);
   fill_Rectangle(69,64,117,132,31);
   fill_Rectangle(149,64,212,132,31);
   fill_Rectangle(151,66,210,130,224);
   fill_Rectangle(71,66,115,130,224);
   
}
void freearea()                  
{   
    int i,j;
    fill_Rectangle(1,171,40,198,0);
    fill_Rectangle(1,173,38,197,224);
    fill_Rectangle(39,188,40,194,6);
    fill_Rectangle(81,171,168,172,0);
    fill_Rectangle(167,171,168,198,0);
    for(i=0;i<12;i++)
    {
        line(41,173+i,166,173+i,19+i);
    }
    for(i=0;i<2;i++)
    {
        line(41,185+i,166,185+i,30);
    }
    for(i=0;i<12;i++)
    {
        line(41,187+i,166,187+i,30-i);
    }
    fill_Rectangle(41,173,166,198,26);
    fill_Rectangle(41,185,166,188,89); 
    _cspeed(41,171);
    _cspeed(50,171);
    _cspeed(61,171);
    _cspeed(68,171);
    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
        { fill_Rectangle(96+55*j,111-45*i,115+55*j,130-45*i,19);
           line(96+55*j,111-45*i,115+55*j,130-45*i,21);
           line(115+55*j,111-45*i,96+55*j,130-45*i,21);
        }
    for(i=0;i<7;i++)
    {
     cspeed(4,35+N*i);  
    }
    for(i=0;i<6;i++)
    {
        cspeed(274,35+N*i);
    }
    for(i=0;i<9;i++)
    {
        _cspeed(56+N*i,4);
    }
    for(i=0;i<4;i++)
    {
        _cspeed(172+N*i,194);
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
				if((j==0&&k<7)||(j==1&&k<4)||(j==2&&k<6)||(j==3&&k<9))p->a[i][j][k]=x;
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
 //    char s1[2],s2[2],s3[2],s4[2],s5[2];
	 PCX_Load_Screen("s1.pcx",1);
     Delay(14);
     PCX_Load_Screen("s2.pcx",1);
//     s1[0]=n/10+'0';
  //  s2[0]=n%10+'0';
    //s3[0]='/';
   // s4[0]=7+'0';
    //s5[0]=8+'0';
     Delay(16);
     PCX_Load_Screen("pstr.pcx",1);
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
					  (s->a[i][j][k])=1;
					   p->i=i;
					   p->j=j;         //车结构中关于  ，车位安排
					   p->k=k;
                       //printf("%d\n",a[0][0][0]);
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
	int h;
	h=p->k;
	p->road[0][0]=INIT_X;                    //第一个拐点坐标
	p->road[0][1]=INIT_Y;
    switch(p->j)                         //判断区位
    {
        case 0: p->road[1][0]=INIT_X;          //M为第一个车位纵坐标，N为车位宽度.第一区
                p->road[1][1]=M-h*N;
                break;
        
        case 1: p->road[1][0]=INIT_X;          //第二区   
                p->road[1][1]=M;
                p->road[2][0]=INIT_X+h*N;
                p->road[2][1]=M;
                break;

        case 2: p->road[1][0]=INIT_X;         //第三区       
                p->road[1][1]=M;  
                p->road[2][0]=L;
                p->road[2][1]=M;
                p->road[3][0]=L;
				p->road[3][1]=M-h*N;
                break;
		case 3: if(h<5)                     //第四区
               {
                   p->road[1][0]=INIT_X;
                   p->road[1][1]=H;
				   p->road[2][0]=INIT_X+h*N+I;   //I为微调量
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
                   p->road[4][0]=Q+F+(h-5)*N; //F为微调量
                   p->road[4][1]=H;
              }
              return;      
     }
}
//////////////过程函数//////////////////              */


/////////////根据小车楼层进行分类///////////////////////
void setlist(Car * cr,Pp * p,int n)
{   
    int i;
    for(i=0;i<n;i++,cr++)
    {
		if(cr->i==0)(p->f1)+=1;
		else if(cr->i==1)p->f2+=1;
		else if(cr->i==2)p->f3+=1;

    }
    
}
/////////////////////小车事件函数/////////////////////////
void car(sprite * sprite,Car * p,int *j,int * pro)
{
 int index,m,m1,m2,m3,m4;
 *j=0;
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
	  if((p->road[*pro+1][0]==0)&&(p->road[*pro+1][1]==0)&&(p->j==0||p->j==3))
      {sprite->curr_frame=(sprite->curr_frame-1)%4;}//帧数变化
      else{sprite->curr_frame=(sprite->curr_frame+1)%4;}
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
m1=((sprite->x>9)&&(sprite->x<55)&&(sprite->y>35)&&(sprite->y<170));
m2=((sprite->y>5)&&(sprite->y<55)&&(sprite->x>50)&&(sprite->x<230));
m3=((sprite->x>220)&&(sprite->x<245)&&(sprite->y>35)&&(sprite->y<170));
m4=((sprite->y>140)&&(sprite->y<194)&&(sprite->x>170)&&(sprite->x<230));
m=m1||m2||m3||m4;
//||((sprite->y>5)&&(sprite->y<55))||((sprite->x>220)&&(sprite->x<245))||((sprite->y>140)&&(sprite->y<194));
 if(m&&p->road[*pro][0]==0&&p->road[*pro][1]==0)              ///////停进车位
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
               delay(SPEED);
               Sprite_Delete(sprite);
               break;
     }
 }
 else if(*j!=2)
   {  *j=1;

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
void pull_over(char *filename,Car * cr,Car * boom,sprite * spo,sprite * head ,int f)
{
  int j=0,k=0,s=0,index=0,pro=0;
  PCX_Load_Screen(filename,1);//背景什么的图还要做  1层
  pcx_picture background_pcx,objects_pcx;
  PCX_Init((pcx_picture_ptr)&objects_pcx);
  PCX_Load("car0.pcx",(pcx_picture_ptr)&objects_pcx,1);
 // for(k=0;k<256;k++)

  //{  
   //  line(10+k,0,10+k,187,k);
 // }
  //  floor();
  //  yline();
  //  freearea();
  for(index=0;index<f;index++,spo++)                    ////////////////////////////把子画面都存入内存
  {
	  Sprite_Init(spo,OX,INIT_Y,0,0,0,0);
	  for(index=0;index<4;index++)
		{
		  PCX_Grab_Bitmap((pcx_picture_ptr)&objects_pcx,spo,index,index,0);
		}

  }
   spo=head;
   for(index=0;index<f;index++,spo++)                      //////保存子画面背后的内容
	{
	   Behind_Sprite(spo);
	}
  PCX_Delete((pcx_picture_ptr)&objects_pcx);

  spo=head;
  cr=boom;
  
  for(s=0;;s++)
  {
	   spo=head;
	   cr=boom;
	  if(k<f)
	 {
		k=s/100+1;

		for(index=0;index<k;index++,spo++,cr++)
		{
		  car(spo,cr,&j,&pro);
		  delay(2);
		 }
	 }
	 else{
		   for(index=0;index<f;index++,spo++,cr++)
		   {
			  car(spo,cr,&j,&pro);
			  delay(2);
		   }
	 }
	 if(j==1) break;;
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
  num=random(10)+1;
                                    

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
  cr=boom;
  setlist(cr,state,num);
  //cr->i=0;cr->j=0;cr->j=0;
  //road_design(cr);
  /////////////////////////单弄个函数：背景列表格把车位，车牌号什么的展示出来，以及空车位和已停车位/////////////////////////////////////////////////////////

 // PCX_Load_Screen("car.pcx",1);
 pull_over("floor1.pcx",cr,boom,spo,head,1/*  state->f1 */);//  一层停车动画
 for(index=0;index<state->f1;index++,spo++,cr++) {}
 delay(8);
 pull_over("floor2.pcx",cr,cr,spo,spo,state->f2);  // 二层停车动画
 for(index=0;index<state->f2;index++,spo++,cr++) {}
 delay(8);
 pull_over("floor3.pcx",cr,cr,spo,spo,state->f3);  // 三层停车动画

  getch();

}

////////////////////////有待实现的功能：鼠标1.绿灯红灯。2.层数显示。3.时间显示。4.边栏的返回。5.边栏的停车状态表示表格。。6.引导箭头///////////////////

