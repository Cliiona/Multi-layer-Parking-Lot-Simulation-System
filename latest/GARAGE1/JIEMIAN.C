#include "jiemian.h"

/******被主函数调用的start*******/
void jiemianstart(Pp *a) // 主函数只调用这个子函数//
{
Set_Video_Mode(VGA256);
	jiemian_homepage(a); //a是已初始化的车库 携带着是否停车的信息
    getch();
    exit(1);
}

/* ********成员信息********* */
void jiemian_introduction()
{
	//
    PCX_Load_Screen("intro.pcx",1);//背景
    getch();
}

/* ********主页********* */
void jiemian_homepage(Pp *aa)
{   
    //Set_Video_Mode(VGA256);
    int flag=0;
    mou curmouse,oldmouse; //定义鼠标结构pointer
	sprite small;

	BUTTON a[4];
	BUTTON button_process={25,100,75,180};//进入模拟
	BUTTON button_manage_login={100,130,160,220};//车位管理
	BUTTON button_help={165,130,240,220};//使用说明
	BUTTON button_exit={250,100,360,180};//退出

	a[0]=button_process;
	a[1]=button_manage_login;
	a[2]=button_help;
	a[3]=button_exit;

	mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
	back("homepage.pcx",&small);
	while(1)
	{
		if(flag==0)
	{
		move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
	}
		if(curmouse.key)
		{

		 if(mouse_on(a))
		   {
			   flag=1;       //1:执行模拟
			   //PCX_Load_Screen("carm.pcx",1);
				//jiemian_process(aa);
				//curmouse->key=0;
		   }
		   else if(mouse_on(a+1))
		   {
			   flag=4;       //4.车位管理登陆
			 //  jiemian_manage_login(aa);
			   //curmouse.key=0;
		   }
		   else if(mouse_on(a+2))
		   {
				Set_Video_Mode(TEXT_MODE);
				//jiemian_instructions(); //说明界面 给我做出来！！！！！
		   }
		   else if(mouse_on(a+3))
		   {
				//write_ot(); //写入出库时间
				//add_today_to_history();
				//exit(0);
		flag=10;
		   }
		}
		if(flag!=0)                   //flag=0,返回主页
		{
			flag=automation(flag,aa); //执行功能函数的同时返回flag
	    curmouse.key=0;

		}
	   //
     }

}

/* ********车位管理登陆界面****** */
int jiemian_manage_login(Pp *a)
{
	mou oldmouse,curmouse;
	sprite small;
    int fun;
    int w;
	static flag=0;//标记是否输入错误,即便返回主页再回来也会继续累计，直至输入正确或解除锁定
	char u[20],c[20]; //输入用户名密码
	char count[2];//打印剩余次数
	BUTTON l[3];
	BUTTON username={70,138,155,148};//用户名输入框
	BUTTON code={70,157,155,167};//密码输入框
	BUTTON home={294,177,310,191};

    mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
    back("log.pcx",&small);



	l[0]=username;
	l[1]=code;
	l[2]=home;

	fill_Rectangle(username.x1,username.y1,username.x2,username.y2,7);
	fill_Rectangle(code.x1,code.y1,code.x2,code.y2,7);



	while(1)
	{

		move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
	if(bioskey(1))
	{
	    w=bioskey(0);
	}
		if(curmouse.key)
		{
			if(mouse_on(l))
			{
		fill_Rectangle(193,130,315,170,1);
				Erase_Sprite_Size(&small,20,20);
				strcpy(u,input(l,u));// u是存放用户名的数组,接收input返回的输入内容
				Behind_Sprite_Size(&small,20,20);
			}
			else if(mouse_on(l+1))
			{
				fill_Rectangle(193,130,315,170,1);
				Erase_Sprite_Size(&small,20,20);
				Behind_Sprite_Size(&small,20,20);
				strcpy(c,codeput(l+1,c));// c是存放密码的数组
				if(match(u,c)==1)//验证成功
				{
					flag=0;//只要输入正确，记错清零
					WriteHz16s("欢迎进入",215,130,20);
					WriteHz16s("车位管理系统！",195,150,20);
		    Delay(15);
					fun=5;
		    return fun;

				//	jiemian_manage_current(m,a);
				}
				else
				{
					WriteHz16s("对不起，请重试",193,130,20);
					WriteHz16s("您还有",193,150,20);
					WriteHz16s("次机会",251,150,20);
					Blit_String(242,155,20,wrong_times(count,&flag),1); //调用累计输错累计函数并打印剩余次数
				}

			}
			else if(mouse_on(l+2))
			{
				Delay(2);
		PCX_Load_Screen("homepage.pcx",1);
		fun=0;
		return fun;
			//	curmouse.key=0;
			}
		  }

		else if(flag==5)  //输入5次退出
		{
			 fill_Rectangle(193,130,315,170,1);//盖住错误提示
			 WriteHz16s("即将锁定管理系统",190,140,16);
			 sleep(2);
			 Erase_Sprite_Size(&small,20,20);//锁定鼠标
			 return fun=jiemian_manage_unlock(&flag,a);
		}
	}

}

/* **********解除锁定界面********** */
int jiemian_manage_unlock(int *flag,Pp *a)
{
    int fun;
	char *ulock; //unlock code
	BUTTON lock_input={86,80,215,95};
    PCX_Load_Screen("unlock.pcx",1);

    do
    {
	fill_Rectangle(70,97,300,150,0); //用黑色盖住上次提示
	strcpy(ulock,codeput(&lock_input,ulock)); //画输入框并显示
	if(strcmp(ulock,"you")==0)
	{
	    *flag=0;
	    WriteHz16s("解锁成功！正在返回登录界面",77,110,20);
	    Delay(18);
	    fun=4;
	    return fun;
		    //jiemian_manage_login(a);
	}
	else
	{
	    WriteHz16s("输入有误，请重新输入",80,110,20);
	    Delay(1);
	}
    }while(*flag);
}

/* **********车位使用现况********** */
int jiemian_manage_current(Pp *a)
{
    int i;
    int w; //用来吸收乱打的字符
    int flag;
    char q[3];
    mou oldmouse,curmouse;
	sprite small;
    BUTTON m[7];
	BUTTON button_history={125,30,153,63};//车位使用历史
	BUTTON button_current={155,30,175,63};//车位使用现况
	BUTTON button_query={190,30,220,63};//车位精确查找
	BUTTON button_homepage={230,30,262,63};//返回主页
	BUTTON button_exit={260,30,300,63};//退出系统
	BUTTON button_lastpage={143,170,163,190};//上一页
	BUTTON button_nextpage={164,170,183,190};//下一页
	BUTTON book={75,47,115,59};//预定框
    BUTTON fresh={20,47,35,59};//刷新
	BUTTON tempclose={243,173,288,183};//暂停使用
    m[0]=button_history;
	m[1]=button_current;
	m[2]=button_query;
	m[3]=button_homepage;
	m[4]=button_exit;
	m[5]=button_lastpage;
	m[6]=button_nextpage;


    mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
    back("current.pcx",&small);

    current_state(a);//车位状态 会显示不同颜色点和各种车位的数量


    fill_Rectangle(book.x1,book.y1,book.x2,book.y2,1);
    fill_Rectangle(tempclose.x1,tempclose.y1,tempclose.x2,tempclose.y2,1);

    while(1)
    {
	move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
	if(bioskey(1))  //如果在没点输入框之前有输入，先用w吸收，以免点进输入框后有已积累的字符
	{
	    w=bioskey(0);
	}
	if(curmouse.key )
	{
	  if(mouse_on(m))
	   {
	       flag=6;   //历史
	       return flag;
	       //jiemian_manage_history(m,a);
	   }
	  else if(mouse_on(m+2))
	   {
		flag=7;         //查找
		return flag;
		//jiemian_manage_query(m,a);
	   }
	  else if(mouse_on(m+3))
	   {
	       Delay(2);
	       PCX_Load_Screen("homepage.pcx",1);
	       flag=0;
	       return flag;      //主页
	       // jiemian_homepage(a);
	   }
	  else if(mouse_on(m+4))
	   {
	       flag=10;      //退出
	       return flag;
	       //write_ot(); //写入出库时间
		//add_today_to_history();
		//exit(0);
	   }
	  else if(mouse_on(&book))
	   {
		Erase_Sprite_Size(&small,20,20);
			    strcpy(q,input(&book,q)); //这就是要的车位号
		Behind_Sprite_Size(&small,20,20);
		a=book_pause_port(q,a,1); //调用预定车库子函数
		current_state(a);
	   }
	   else if(mouse_on(&tempclose))
	   {
		Erase_Sprite_Size(&small,20,20);
			    strcpy(q,input(&tempclose,q));
		Behind_Sprite_Size(&small,20,20);
		a=book_pause_port(q,a,2); //调用预定车库子函数
		current_state(a);
	   }
	  else if(mouse_on(&fresh))
	  {
	       current_state(a);
	  }

	}
    }
}

/* **********车位使用历史********** */
int jiemian_manage_history(Pp *a)
{
    FILE * fp;
	int w; //用来吸收乱打的字符
 //	int test=0;
    mou oldmouse,curmouse;
    sprite small;
    int flag=0;
    int fun;   //功能输出

    int r=1;//用于接收print_all返回值，为0说明已到文件结尾
	//Set_Video_Mode(VGA256);
    BUTTON m[7];
	BUTTON button_history={125,30,153,63};//车位使用历史
	BUTTON button_current={155,30,175,63};//车位使用现况
	BUTTON button_query={190,30,220,63};//车位精确查找
	BUTTON button_homepage={230,30,262,63};//返回主页             主按钮
	BUTTON button_exit={260,30,300,63};//退出系统
	BUTTON button_lastpage={143,170,163,190};//上一页
	BUTTON button_nextpage={164,170,183,190};//下一页
	BUTTON d[5];
    BUTTON delete1={290,88,303,100};
    BUTTON delete2={290,105,303,120};
    BUTTON delete3={290,122,303,136};
    BUTTON delete4={290,140,303,153};
	BUTTON delete5={290,155,303,170};
    m[0]=button_history;
	m[1]=button_current;
	m[2]=button_query;
	m[3]=button_homepage;
	m[4]=button_exit;
	m[5]=button_lastpage;
	m[6]=button_nextpage;
    new_all();
    mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标
	back("history.pcx",&small);
    //add_today_to_history();
	print_all(fp,flag);//显示第一页，历史界面是一进去就要有记录的，所以要在当前定义文件指针，精确查找则不同

    d[0]=delete1;
    d[1]=delete2;
    d[2]=delete3;
    d[3]=delete4;
    d[4]=delete5;

    while(1)
    {
	move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
	if(bioskey(1))
	{
	    w=bioskey(0);
	}
	if(curmouse.key)
	{
	  if(mouse_on(m+1))
	   {
			   fun=5;
	       return fun;
	       //PCX_Load_Screen("current",1);
	       // jiemian_manage_current(m,a);
	   }
	   else if(mouse_on(m+2))
		   {
		fun=7;
		return fun;
	       //jiemian_manage_query(m,a);

		   }
	   else if(mouse_on(m+3))
	   {
		Delay(2);
		PCX_Load_Screen("homepage.pcx",1);
		fun=0;
		return fun;
		//jiemian_homepage(a);
	  }
	   else if(mouse_on(m+5))   //上一页
	   {
	       if(flag>0) //判断是否可以上一页的依据是页码
	       {
		 PCX_Load_Screen("history.pcx",1);
		 r=print_all(fp,--flag);
	       }
	   }
		   else if(mouse_on(m+6)) //下一页
	   {
	       if(r)  //判断是否下一页的依据为是否到文件结尾
	       {
		 PCX_Load_Screen("history.pcx",1);
		 r=print_all(fp,++flag);
	       }
	   }
		   else if(mouse_on(d))
		   {
				//密钥

				delete_one_all(1,flag);//删除当页第一条记录后
				PCX_Load_Screen("history.pcx",1);
				r=print_all(fp,flag);//显示新的历史记录

	   }
	   else if(mouse_on(d+1))
	   {
		//密钥
		delete_one_all(2,flag);//在文件中删除当页第一条记录后
		PCX_Load_Screen("history.pcx",1);
		r=print_all(fp,flag);//显示新的历史记录
	   }
	   else if(mouse_on(d+2))
	   {
		//密钥
		delete_one_all(3,flag);//删除当页第一条记录后
		PCX_Load_Screen("history.pcx",1);
		r=print_all(fp,flag);//显示新的历史记录
	   }
	   else if(mouse_on(d+3))
	   {
		//密钥
		delete_one_all(4,flag);//删除当页第一条记录后
		PCX_Load_Screen("history.pcx",1);
		r=print_all(fp,flag);//显示新的历史记录
	   }
	   else if(mouse_on(d+4))
	   {
		//密钥
		delete_one_all(5,flag);//删除当页第一条记录后
		PCX_Load_Screen("history.pcx",1);
		r=print_all(fp,flag);//显示新的历史记录
	   }
	   else if(mouse_on(m+4))
	   {
	       fun=10;
	       return fun;
	      //  write_ot(); //写入出库时间
		//add_today_to_history();
		//exit(0);
	   }
	}
	fclose(fp);
    }
}

 /* **********车位精确查找********** */
int jiemian_manage_query(Pp *a)
{
    FILE * fp;
    mou oldmouse,curmouse;
    sprite small;
    char q[4];  //车号
    int flag=0;
    int fun;  //功能输出
    int w; //用来吸收乱打的字符
    int r=1;//用于接收print_query返回值，为0说明已到文件结尾

	BUTTON m[7];
	BUTTON button_history={125,30,153,63};//车位使用历史
	BUTTON button_current={155,30,175,63};//车位使用现况
	BUTTON button_query={190,30,220,63};//车位精确查找
	BUTTON button_homepage={230,30,262,63};//返回主页             主按钮
	BUTTON button_exit={260,30,300,63};//退出系统
	BUTTON button_lastpage={143,170,163,190};//上一页
	BUTTON button_nextpage={164,170,183,190};//下一页
    BUTTON frame={75,48,114,59};//输入框
	BUTTON d[4];
    BUTTON delete1={273,111,295,123};
    BUTTON delete2={273,127,295,140};
    BUTTON delete3={273,144,295,155};
    BUTTON delete4={273,158,295,170};
    d[0]=delete1;
    d[1]=delete2;
    d[2]=delete3;
	d[3]=delete4;
    m[0]=button_history;
	m[1]=button_current;
	m[2]=button_query;
	m[3]=button_homepage;
	m[4]=button_exit;
	m[5]=button_lastpage;
	m[6]=button_nextpage;

	mouse_all(&curmouse,&oldmouse,&small); //初始化鼠标结构  显示鼠标

    back("query.pcx",&small);//查找界面图片

	fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);

    while(1)
    {
	move_mouse(&curmouse,&oldmouse,&small); //移动过程中显示鼠标
	if(bioskey(1))
	{
	    w=bioskey(0);
	}
	if(curmouse.key )
	{
	  if(mouse_on(m))
	   {
	       fun=6;
	       return fun;
	       // jiemian_manage_history(m,a);
	   }
	  else if(mouse_on(m+1))
	   {
	       fun=5;
	       return fun;
		//jiemian_manage_current(m,a);
	   }
	  else if(mouse_on(m+3))
	   {
	       Delay(2);
	       PCX_Load_Screen("homepage.pcx",1);
	       fun=0;
	       return fun;

	   }
	  else if(mouse_on(m+4))
	   {
	       fun=10;
	       return fun;
	   }
	  else if(mouse_on(m+5))   //上一页
	   {
	       if(flag>0)
	       {
		 PCX_Load_Screen("query.pcx",1);
		 fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
				 r=print_query(--flag);
	       }
	   }
	   else if(mouse_on(m+6)) //下一页
	   {
	       if(r)
	       {
		 PCX_Load_Screen("query.pcx",1);
		 fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
				 r=print_query(++flag);
	       }
	   }
	   else if(mouse_on(&frame))
	   {
		Erase_Sprite_Size(&small,20,20);
			    strcpy(q,input(&frame,q)); //这就是要查找的车位号
		PCX_Load_Screen("query.pcx",1);
		Behind_Sprite_Size(&small,20,20);
		Blit_String(92,78,0,q,1);
		query(atoi(q));
		r=print_query(flag); //读文件 打印到界面
	   }
	   else if(mouse_on(d))
	   {
		//密钥
		delete_one_query(1,flag); //删除当页第一条记录后
		PCX_Load_Screen("query.pcx",1);
		fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
		r=print_query(flag); //显示新的历史记录
		Blit_String(92,78,0,q,1);
	   }
	   else if(mouse_on(d+1))
	   {
		//密钥
		delete_one_query(2,flag);//删除当页第一条记录后
		PCX_Load_Screen("query.pcx",1);
		fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
		r=print_query(flag);//显示新的历史记录
		Blit_String(92,78,0,q,1);
	   }
	   else if(mouse_on(d+2))
	   {
		//密钥
		delete_one_query(3,flag);//删除当页第一条记录后
		PCX_Load_Screen("query.pcx",1);
		fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
		r=print_query(flag);//显示新的历史记录
		Blit_String(92,78,0,q,1);
	   }
	   else if(mouse_on(d+3))
	   {
		//密钥
		delete_one_query(4,flag);//删除当页第一条记录后
		PCX_Load_Screen("query.pcx",1);
		fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
		r=print_query(flag);//显示新的历史记录
		Blit_String(92,78,0,q,1);
	   }
	}
    }
}

/* *******模拟泊车***** */
int jiemian_process(Pp *state)
{
    int flag;

    parkp(state);        //实况
    flag=end_page();
	return flag=0;

}

/////////////////////界面调控开关函数///////////////////////
int automation(int flag,Pp *state)
{
    switch(flag)
    {
	case 1:
		   login();
		   Delay(10);
	       flag=jiemian_process(state);
	       break;

	case 4:
		flag=jiemian_manage_login(state); //车位管理登陆
		break;

	case 5:

		flag=jiemian_manage_current(state);
		break;

	case 6:
		flag=jiemian_manage_history(state);
		break;
	case 7:

		flag=jiemian_manage_query(state);
		break;

	case 10:
		save_new_record();
		exit(0);
		break;
    }
    return flag;
}

