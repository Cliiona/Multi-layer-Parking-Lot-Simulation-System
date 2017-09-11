#include "jiemian.h"

/******被主函数调用的start*******/
void jiemianstart() // 主函数只调用这个子函数//
{
	jiemian_homepage();
    getch();
    exit(1);
}

/* ********成员信息********* */
void jiemian_introduction()
{
    Set_Video_Mode(VGA256);
    PCX_Load_Screen("intro.pcx",1);//背景
    getch();
}

/* ********主页********* */
void jiemian_homepage()
{   
    BUTTON a[4];
    BUTTON button_process={60,100,175,180};//进入模拟
    BUTTON button_manage_login={200,130,320,220};//车位管理
    BUTTON button_help={330,130,410,220};//使用说明
    BUTTON button_exit={415,100,520,180};//退出

    a[0]=button_process;
    a[1]=button_manage_login;
    a[2]=button_help;
    a[3]=button_exit;

    Set_Video_Mode(VGA256);
	mou curmouse,oldmouse; //定义鼠标结构pointer
	sprite small;

	mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
	back("homepage.pcx",&small);
	while(kbhit()==0)
	{
		move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标

		if(curmouse.key)
		{

	     if(mouse_on(a))
		   {
              // Set_Video_Mode(TEXT_MODE);
			  test();
				//curmouse->key=0;
		   }
		   else if(mouse_on(a+1))
		   {
			   jiemian_manage_login();
               curmouse.key=0;
		   }
		   else if(mouse_on(a+2))
		   {
			    Set_Video_Mode(TEXT_MODE);
				//jiemian_instructions(); //说明界面 给我做出来！！！！！
				curmouse.key=0;
		   }
		   else if(mouse_on(a+3))
		   {
			 	exit(1);
            }
		}

	}
}

/* ********车位管理登陆界面****** */
void jiemian_manage_login()
{
    mou oldmouse,curmouse;
    sprite small;
    char u[20],c[20]; //输入用户名密码
    Set_Video_Mode(VGA256);
    mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
    back("login.pcx",&small);
  
    BUTTON l[2];
    BUTTON button_username={320,180,380,195};//用户名
    BUTTON button_code={320,210,380,215};//密码
    l[0]=button_username;
    l[1]=button_code;

//管理界面的按钮结构—-----------------------------------------
    BUTTON m[7];
    BUTTON button_history={250,30,290,60};//车位使用历史
    BUTTON button_current={300,30,350,60};//车位使用现况
    BUTTON button_search={395,40,440,55};//车位精确查找
    BUTTON button_homepage={460,30,525,60};//返回主页
    BUTTON button_exit={520,30,600,60};//退出系统
    BUTTON button_lastpage={285,170,325,190};//上一页
    BUTTON button_nextpage={326,170,366,190};//下一页

    m[0]=button_history;
    m[1]=button_current;
    m[2]=button_search;
    m[3]=button_homepage;
    m[4]=button_exit;
    m[5]=button_lastpage;
    m[6]=button_nextpage;

    while(kbhit()==0)
    {   
         move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
		 if(curmouse.key)
        {
           if(mouse_on(l))
           {
                Erase_Sprite_Size(&small,20,20);
			    input(l,u);// u是存放用户名的数组
                Behind_Sprite_Size(&small,20,20);

           }
           else if(mouse_on(l+1))
           {
                Erase_Sprite_Size(&small,20,20);
			    input(l+1,c);// c是存放密码的数组
                Behind_Sprite_Size(&small,20,20);

           }
           else if(mouse_on(m+3))
           { 
                jiemian_manage_search(m);
                curmouse.key=0;
           } 
            
        }  
    }
    
}

/* **********车位使用历史********** */
void jiemian_manage_history(BUTTON *m)
{
    mou oldmouse,curmouse;
    sprite small;
    int flag=0;
    Set_Video_Mode(VGA256);
    mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
	back("history.pcx",&small);
       
    BUTTON button_file={0,0,100,70};//文件

    while(!kbhit())
    {   
        move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
		
        if(curmouse.key)
        {
          if(mouse_on(m+1))
           {
                jiemian_manage_current(m);
				curmouse.key=0;
           }
           else if(mouse_on(m+2))
		   {
                jiemian_manage_search(m);
                curmouse.key=0;
		   }
           else if(mouse_on(m+3))
           {
                jiemian_homepage(); 
                curmouse.key=0;
           }
           else if(mouse_on(&button_file))
            {                
                readfile(50);
                curmouse.key=0;
            }
           else if(mouse_on(m+4))
            {                
                exit(1);
                curmouse.key=0;
            }
           else if(mouse_on(m+5))   
           {
               //lastpage
                //curmouse.key=0; 
           }
           else if(mouse_on(m+6))
           {
               //nextpage
                //curmouse.key=0; 
           }

       }
    } 
}
/* **********车位使用现况********** */
void jiemian_manage_current(BUTTON *m)
{   
    mou oldmouse,curmouse;
    sprite small;
    Set_Video_Mode(VGA256);
    mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
    back("current.pcx",&small);

    while(!kbhit())
    {   
        move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
        if(curmouse.key )
        {
          if(mouse_on(m))
           {
                jiemian_manage_history(m);
                curmouse.key=0;
           }
          else if(mouse_on(m+2))
           {
                jiemian_manage_search(m);   
                curmouse.key=0; 
           }
          else if(mouse_on(m+3))
           {
                jiemian_homepage();   
                curmouse.key=0; 
           }
        }
    }  
}
 
/* **********车位精确查找********** */
void jiemian_manage_search(BUTTON *m)
{   
    mou oldmouse,curmouse;
    sprite small;
    char q[20];  //输入车号
    Set_Video_Mode(VGA256);
    mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
    back("search.pcx",&small);
       
    BUTTON frame={130,47,170,59};//输入框
    fill_Rectangle((frame.x1)/2+5,frame.y1,(frame.x2),frame.y2,7);
    while(!kbhit())
    {   
        move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
        if(curmouse.key )
        {
          if(mouse_on(m))
           {
                jiemian_manage_history(m);
                curmouse.key=0;
           }
          else if(mouse_on(m+1))
           {
                jiemian_manage_current(m);   
                curmouse.key=0; 
           }
          else if(mouse_on(m+3))
           {
                jiemian_homepage();   
                curmouse.key=0; 
           }
          else if(mouse_on(m+4))
           {
                exit(1);   
                //curmouse.key=0; 
           }
          else if(mouse_on(m+5))   
           {
               //lastpage
                //curmouse.key=0; 
           }
          else if(mouse_on(m+6))
           {
               //nextpage
                //curmouse.key=0; 
           }
          else if(mouse_on(&frame))
           {
                Erase_Sprite_Size(&small,20,20);
			    input(&frame,q);
                Behind_Sprite_Size(&small,20,20);
                //curmouse.key=0; 
           }
        }
    }
}

/* *******模拟泊车***** */
void jiemian_process(void)
{
  test(0,0);
}

/* *******开始动画******* */
/*
void begin()
{  	
    BUTTON button_start={200,177,430,198,"start"};
    mou oldmouse,curmouse;
	oldmouse.x=0;oldmouse.y=0;oldmouse.key=0;
	curmouse.x=0;curmouse.y=0;curmouse.key=0;

	sprite c1,small;
	pcx_picture background_pcx,o1,objects_pcx;
	Set_Video_Mode(VGA256);
	PCX_Load1("C1.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,120,-5,0,0,0,0,65,55,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,65,55);//将屏幕内容复制给小图片
    
    PCX_Load1("mouse.pcx",(pcx_picture_ptr)&objects_pcx,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&small,0,0,0,0,0,0,65,55,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&objects_pcx,(sprite_ptr)&small,0,0,0,65,55);//将屏幕内容复制给小图片
    
    
	Fill_Screen(0);
	PCX_Load1("sur.pcx",(pcx_picture_ptr)&background_pcx,1);//背景
	Behind_Sprite_Size((sprite_ptr)&small,65,55);
    Behind_Sprite_Size((sprite_ptr)&c1,65,55);//取图片后内容
    mousecheck();//初始化鼠标
	mousemove();//设置鼠标范围
    small.x=curmouse.x/2;
	small.y=curmouse.y;
	Behind_Sprite_Size((sprite_ptr)&small,65,55);//保存小图片后背景内容
	Draw_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片于鼠标位置
		while(!kbhit())
         { 
			if(curmouse.key && mouse_on(&button_start))
             { 
                     
                  while(1)
                {
		   Erase_Sprite_Size((sprite_ptr)&c1,65,55);
		   if(c1.y<140)c1.y++;
		   Behind_Sprite_Size((sprite_ptr)&c1,65,55);
		   Draw_Sprite_Size((sprite_ptr)&c1,65,55);
			   if(c1.y==138)
                        {
                              
                              while(c1.x<210)
            
                               {   
				  Erase_Sprite_Size((sprite_ptr)&c1,65,55);
                                  c1.x++;
		                  Behind_Sprite_Size((sprite_ptr)&c1,65,55);
				  Draw_Sprite_Size((sprite_ptr)&c1,65,55);
								  delay(10);
                
                               }
                             delay(20);
                             while(c1.x>53)
                              {
              	                  Erase_Sprite_Size((sprite_ptr)&c1,65,55);
                                  c1.x--;
		                  Behind_Sprite_Size((sprite_ptr)&c1,65,55);
				  Draw_Sprite_Size((sprite_ptr)&c1,65,55);
                                  delay(10);
                             }
                             Sprite_Delete_Size((sprite_ptr)&c1,1);
                             break;
                        }
					  delay(9);
               }
              PCX_Load_Screen("op.pcx",1);///////////////切换到下一个界面            
              break;
                
           }
       
        else 
       {   
            mouseread(&curmouse);
    	    if(curmouse.x!=oldmouse.x||curmouse.y!=oldmouse.y)//判断是否移动过鼠标
	      {
		    Erase_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片后背景内容
                    small.x=curmouse.x/2;
	            small.y=curmouse.y;
		    Behind_Sprite_Size((sprite_ptr)&small,65,55);//保存小图片后背景内容
	    	    Draw_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片于鼠标位置
	    	    oldmouse.x=curmouse.x;
		    oldmouse.y=curmouse.y;
    	 }
      }
 
    }  
      getch();
          
}	*/
