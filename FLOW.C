#include "flow.h"
/* ****************************************************************
 * Function: yes(Pp *a)
 * Description:���潻�����ؿ��غ���
 * Calls:Init_flow(char *filename);flow_manage_query();
 *      flow_homepage();flow_process(Pp *,int *);flow_manage_login();
 *      flow_introduction();flow_manage_record();
 *      flow_manage_current(Pp *);flow_manage_query();
 *      flow_park(Pp *,int *,Car *);pull_over(Pp *,Car *,int ,int );
 *      endpage();floor_step(int);flow_outcar(int *);
 *      drop_off(Pp *,Car *,int ,int ,int);flow_manage_help();
 *      flow_manage_setting();
 * Called by:mian();
 * Input��Pp *a:����ṹָ��
 * return:��
 * others:��
 * *****************************************************************/
void yes(Pp *a)
{
	int flag=1, p=1, i;//homepage
	int * show=&p;//��ʾ��ʾ������
	Car cr[21];
    
	while(1)
	{   
        attain(a);
		if(flag)
		{
			switch(flag)
			{
				case 1:
					   Init_flow("homepage.bmp");  //��ҳ
					   flag=flow_homepage();
                       break;           

				case 2:
					   Init_flow("carin.bmp");    //����ģ��
					   flag=flow_process(a,show);
					   break;

				case 3:
						Init_flow("login.bmp");//��λ����
						flag=flow_manage_login();
						break;

				case 4:
						flag=flow_introduction(); //ʹ��˵��
						break;
				case 5:
						Init_flow("record.bmp"); //ͣ����¼
						flag=flow_manage_record();
						break;
				case 6:
						Init_flow("current.bmp"); //ͣ���ֿ�
						flag=flow_manage_current(a);
						break;
				case 7:
						Init_flow("query.bmp"); //ͣ������
						flag=flow_manage_query();
						break;
				case 8:
                        save_new_record();        //�˳�ϵͳ
					    Set_Video_Mode(TEXT_MODE);
					    exit(0);
					    break;
				case 9:
					    Init_park(a);                  
					    flag=flow_park(a,show,cr);        // ͣ����Ϣȷ��
					    break;
				case 10:
						 for(i=0;i<=cr[0].i;i++)
						{
							floor_step(0);
						}
					    flag=pull_over(a,cr,a->f1,0);        //ͣ��1¥
					    break;
				case 11:
						for(i=0;i<=cr[0].i;i++)
						{
							floor_step(0);
						}
					    flag=pull_over(a,cr,a->f2,1);    //ͣ��2¥
					    break;
				case 12:                                  //ͣ��3¥
						for(i=0;i<=cr[0].i;i++)
						{
							floor_step(0);
						}
					    flag=pull_over(a,cr,a->f3,2);
					    break;

			   case 13:
					    Set_Video_Mode(SVGA);
					    Init_flow("endpage.bmp");       //������ҳ
					    flag=endpage();
					    break;
			   case 14:
					    flag=flow_outcar(show); //ȡ��
					    break;
			   case 15:
					    flag=flow_outall(show,a);  //ȫȡ
					    break;
			   case 16:
					   flag=drop_off(a,cr,a->m1,0,0); //ȡ��һ��
					   for(i=0;i<=cr[0].i;i++)
						{
							floor_step(1);
						}
					   break;
			   case 17:
					   flag=drop_off(a,cr,a->m2,1,0); //ȡ������
					   for(i=0;i<=cr[0].i;i++)
						{
							floor_step(1);
						}
					   break;
			   case 18:
					   flag=drop_off(a,cr,a->m3,2,0);  //ȡ������
					   for(i=0;i<=cr[0].i;i++)
						{
							floor_step(1);
						}
					   break;
			   case 19:                                
					   flag=flow_outone(a,cr,show);  //ȡ����������
			   case 20:
					   flag=drop_off(a,cr,1,cr[0].i,1);    //ȡ������
						for(i=0;i<=cr[0].i;i++)
						{
							floor_step(1);
						}
					   break;
			   case 21:
						Init_flow("setting.bmp");  //����Ա��Ϣ����
						flag=flow_manage_setting();
						break;
			   case 22:
						for(i=0;i<=cr[0].i;i++)
						{
							floor_step(0);
						}
						flag=pull_over(a,cr,1,cr[0].i);        //Ԥ��ͣ��
						break;

			   case 23:
						Init_flow("help.bmp");     //��λ��������
						flag=flow_manage_help();
						break;

			   default:break;

			}
		}
	}
}

/* *****************************************************************
 * Function:Init_flow
 * Description:�����ʼ��
 * Calls:mousemove();readbmp(int,int,char *filename);
 * Called by:flow_manage_query();
 * Input��char *filename:�ļ���
 * return:��
 * others:��
 * *****************************************************************/
void Init_flow(char *filename)
{
    mousemove();
    readbmp(0,0,filename);
}

/* ***************************************************************
 * Function:Init_park
 * Description:ͣ�����ý����ʼ��
 * Calls:attain(Pp *);strcpy(char*,char*);
 *      Put_String(int,int,int,int,int,char *);
 * Called by:yes(Pp *);
 * Input��Pp *state:����ṹָ��
 * return:��
 * others:��
 * ****************************************************************/
void Init_park(Pp *state)
{
    char s1[3],s2[3],s3[3];
    attain(state);
    strcpy(s1,transform(state->f1));
    strcpy(s2,transform(state->f2));
    strcpy(s3,transform(state->f3));
	Put_String(313,586,2,2,0x17a0,s1);
    Put_String(456,586,2,2,0x17a0,s2);
    Put_String(592,586,2,2,0x17a0,s3);
}

/* ***************************************************************
 * Function:flow_homepage();
 * Description:��ҳ
 * Calls:mousecheck();mousecheck();	Mouse_cpy(Mouse m);
 * Called by:yes(Pp *);
 * Input��Pp *state:����ṹָ��
 * return:2:����ģ�⣬3:��λ������½ 4:˵������ 8:�˳�ϵͳ
 * others:��
 * ***************************************************************/
int flow_homepage()    
{
    mou curmouse,oldmouse; //�������ṹpointer
    mousecheck();
    mousemove();
	Mouse_cpy(&oldmouse);
	while(1)
	{
		move_mouse(&curmouse,&oldmouse); //�ƶ���������ʾ���

        if(curmouse.key)
       {	
           if(curmouse.x<449&&curmouse.x>169&&curmouse.y>270&&curmouse.y<520)
		   {
			   return 2;     //ִ��ģ��
            
		   }
         
           else if(curmouse.x<458&&curmouse.x>347&&curmouse.y>527&&curmouse.y<578)
		   {
			   return 3;       //��λ������½
               
		   }
    
           else if(curmouse.x<645&&curmouse.x>538&&curmouse.y<578&&curmouse.y>535)
		   {
			    return 4;
			                                 //ʹ��˵��
                }
        
           else	if(curmouse.x>716&&curmouse.x<828&&curmouse.y>452&&curmouse.y<525)
		   {
		       return 8;
		   }
		}
}   
}

/* ****************************************************************
 * Function:flow_introduction
 * Description:ʹ��˵��
 * Calls:Mouse_cpy(Mouse m);readbmp(int ,int ,char *filename);
 * Called by:yes(Pp *);
 * Input����
 * return:1��������ҳ
 * others:��
 * ***************************************************************/
int flow_introduction()
{
	mou om,cm;
    Mouse_cpy(&om);
    readbmp(0,0,"intro.bmp");//����
    while(1)
    {
        move_mouse(&cm,&om);
        if(cm.key)
        {
			if(cm.x<1022&&cm.x>868&&cm.y>511&&cm.y<561)
            {
                readbmp(0,0,"intro.bmp");
            }
            else if(cm.x<1022&&cm.x>869&&cm.y>592&&cm.y<631)
            {
                readbmp(0,0,"intro2.bmp");
            }
            else if(cm.x<1022&&cm.x>869&&cm.y>666&&cm.y<711)
            {
                return 1;
            }
        }
    }
}


/*��λ����ģ��*/
/* ****************************************************************
 * Function:flow_manage_login
 * Description:��λ������½����
 * Calls:Mouse_cpy(Mouse m);readbmp(int ,int ,char *filename);
 *      show_avatar(char *);
 * Called by:yes(Pp *);
 * Input����
 * return:1��������ҳ��21�����ù���Ա��Ϣ��3����½���棬6��λ�ֿ�
 * others:��
 * ****************************************************************/
int flow_manage_login()
{
	mou oldmouse,curmouse;
    int w,wrong;
	char u[10],c[10]; //�����û�������
	int count;    //��ӡʣ�����
   	static flag=0;    //����Ƿ��������,���㷵����ҳ�ٻ���Ҳ������ۼƣ�ֱ��������ȷ��������
    BUTTON l[2];
	BUTTON username={293,352,555,378};   //�û��������
	BUTTON code={292,397,555,425};       //���������
	l[0]=username;
	l[1]=code;
    Mouse_cpy(&oldmouse);
	while(1)
	{
		move_mouse(&curmouse,&oldmouse); //�ƶ���������ʾ���
	    if(bioskey(1))
	    {
	        w=bioskey(0);//�����ڵ�������ǰ������ַ�
	    }
		if(curmouse.key)
		{
			if(curmouse.x>293&&curmouse.x<561&&curmouse.y>348&&curmouse.y<381)
			{
		        Mouse_reshow(&curmouse);
				strcpy(u,input(l));// u�Ǵ���û���������,����input���ص���������
                Mouse_cpy(&oldmouse);
                show_avatar(u);
			}
			else if(curmouse.x>292&&curmouse.x<561&&curmouse.y>304&&curmouse.y<427)
			{
				Mouse_reshow(&oldmouse);
				strcpy(c,codeput(l+1));// c�Ǵ�����������
                Mouse_cpy(&oldmouse);

			}
			else if(curmouse.x>377&&curmouse.x<466&&curmouse.y>463&&curmouse.y<486)
            {				
                if(match(u,c)==1)//��֤�ɹ�
				{
					flag=0;     //ֻҪ������ȷ���Ǵ�����
                    readbmp(609,402,"welcome.bmp");
		            Delay(10);
		            return 6;//flow_current
				}
				else
				{
                    wrong=wrong_times(count,&flag);//�����ۼ�����ۼƺ�������ӡʣ�����
                    switch(wrong)
                    {
                        case 1:readbmp(609,402,"1.bmp");break;
                        case 2:readbmp(609,402,"2.bmp");break;
                        case 3:readbmp(609,402,"3.bmp");break;
                        case 4:readbmp(609,402,"4.bmp");break;
                    }	
				}
            }
			else if(curmouse.x>484&&curmouse.x<554&&curmouse.y>462&&curmouse.y<486)
			{
		        return 1;//homepage
			}
			else if(curmouse.x>625&&curmouse.x<720&&curmouse.y>460&&curmouse.y<490)//setting
			{
		        return 21;//setting
			}
		}//if
		else if(flag==5)  //����5���˳�
		{
			 readbmp(609,402,"locked.bmp");
			 sleep(1);
             readbmp(0,0,"unlock.bmp");
             flag=flow_manage_unlock(lock);//flag=0
             return 3;//ֻ����֤�ɹ����ܴ�unlock����,flag=0
		}//else if
	}//while
}

/* ****************************************************************
 * Function:flow_manage_unlock
 * Description:�����������
 * Calls:fill_Rectangle(int,int,int,int,int);
 *      strcpy(char *s,char *s);readbmp(int,int,int,int,int);
 * Called by:yes(Pp *);
 * Input����
 * return:0:��½����
 * others:��
 * ****************************************************************/
int flow_manage_unlock()
{
	char ulock[5]; //unlock code
	BUTTON lock_input={312,315,685,352};
    do
    {
	    fill_Rectangle(312,312,685,352,0x5FBF); 
	    strcpy(ulock,codeput(&lock_input)); 
	    if(strcmp(ulock,"you")==0)
		{
	        readbmp(308,465,"ba_log.bmp");//back login
	        Delay(10);
			break;
	    }
	    else
	    {
	        readbmp(308,465,"un_w.bmp");
	        Delay(8);
            readbmp(0,0,"unlock.bmp");
	    }
	}while(1);
    return 0;//login
}

/* *****************************************************************
 * Function:flow_manage_setting
 * Description:��Ϣ�޸�ҳ�����
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse);
 *      inf_modify(char*,char*,char*,char*,char*);
 * Called by:yes(Pp *);
 * Input:��
 * return:3�����ص�½����
 * others:��
 * *****************************************************************/
int flow_manage_setting()
{
	mou oldmouse,curmouse;
    int w,c=0;//c��������check_ou()
	char ou[10],nu[10],oc[10],nc[10],ic[10]; //�����û�������
	BUTTON old_u={374,261,609,282};   //ԭ�û���
    BUTTON new_u={374,323,609,346};   //���û���
	BUTTON old_c={374,384,609,405};   //ԭ����
	BUTTON new_c={374,442,609,463};       //������
    BUTTON insure_c={373,506,609,526};     //����ȷ��
    Mouse_cpy(&oldmouse);
	while(1)
	{
		move_mouse(&curmouse,&oldmouse); //�ƶ���������ʾ���
	    if(bioskey(1))
	    {
	        w=bioskey(0);//�����ڵ�������ǰ������ַ�
	    }
		if(curmouse.key)
		{ 
			if(curmouse.x>374 && curmouse.x<609 && curmouse.y>261 && curmouse.y<282)
			{			
                Mouse_reshow(&oldmouse);
                strcpy(ou,input(&old_u));// u�Ǵ���û���������,����input���ص���������
                c=check_ou(ou);//����û��Ƿ����      
                Mouse_cpy(&curmouse);
			}
			else if(curmouse.x>374 && curmouse.x<609 && curmouse.y>323 && curmouse.y<346)
			{
                Mouse_reshow(&oldmouse);
                strcpy(nu,input(&new_u));
                Mouse_cpy(&oldmouse);
			}
			else if(curmouse.x>374 && curmouse.x<609 && curmouse.y>384 && curmouse.y<405)
			{
                Mouse_reshow(&oldmouse);
                strcpy(oc,input(&old_c));
                Mouse_cpy(&oldmouse);
			}
			else if(curmouse.x>374 && curmouse.x<609 && curmouse.y>442 && curmouse.y<463)
			{
                Mouse_reshow(&oldmouse);
                strcpy(nc,input(&new_c));
                Mouse_cpy(&oldmouse);
			}
			else if(curmouse.x>374 && curmouse.x<609 && curmouse.y>506 && curmouse.y<526)
			{
                Mouse_reshow(&oldmouse);
                strcpy(ic,input(&insure_c));
                Mouse_cpy(&oldmouse);
			}
            else if(curmouse.x>525 && curmouse.x<613 && curmouse.y>580 && curmouse.y<613)
            {
				if(inf_modify(ou,nu,oc,nc,ic)&&c)
                {
                    return 3;//login
                }
            } 
            else if(curmouse.x>657 && curmouse.x<724 && curmouse.y>124 && curmouse.y<158)
            {
		        return 3;//login
            }
		}//if

	}//while
}

/* ******************************************************************
 * Function:flow_manage_help
 * Description:��������
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse);
 * Called by:yes(Pp *);
 * Input:��
 * return:6����λ�ֿ�
 * others:��
 * *****************************************************************/
int flow_manage_help()
{
    mou oldmouse,curmouse;
    Mouse_cpy(&oldmouse);
    while(1)
    {
        move_mouse(&curmouse,&oldmouse);//�ƶ���������ʾ���
		if(curmouse.x>884 && curmouse.x<950 && curmouse.y>34 && curmouse.y<70&&curmouse.key)
		{			
            return 6;
		}
    }
}

/* *****************************************************************
 * Function:flow_manage_current
 * Description:��λʹ���ֿ�
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse);book_pause_port();current_state(a);
 * Called by:yes(Pp *);
 * Input:Pp *:����ṹָ��
 * return:��1����ҳ��5:ͣ����¼,6����λ�ֿ���23:����
 * others:��
 * *****************************************************************/
int flow_manage_current(Pp *a)
{
    int i;
    int w; //���������Ҵ���ַ�
    char q[3];
    char core[10];
    mou oldmouse,curmouse;
    BUTTON tempclose={694,550,800,570};//��ͣʹ��
	BUTTON book={694,589,800,609};//Ԥ����
	fill_Rectangle(694,550,800,570,0x5fbf);
    fill_Rectangle(694,589,800,609,0x5fbf);
    Put_String(100,100,1,1,0x5fbf,ultoa(coreleft(),core,10));
    current_state(a);//��λ״̬ ����ʾ��ͬ��ɫ��͸��ֳ�λ������
    Mouse_cpy(&oldmouse); 
    while(1)
    {
	    move_mouse(&curmouse,&oldmouse); //�ƶ���������ʾ���
	    if(bioskey(1))  //�����û�������֮ǰ�����룬����w���գ����������������ѻ��۵��ַ�
	    {
	        w=bioskey(0);
	    }
	    if(curmouse.key )
	    {
	        if(curmouse.x>433&&curmouse.x<581&&curmouse.y>117&&curmouse.y<144)
	        {
	            return 5; //flow_manage_record
	        }
	        else if(curmouse.x>587&&curmouse.x<725&&curmouse.y>135&&curmouse.y<163)
	        {
		        return 7;//query
	        }
	        else if(curmouse.x>113&&curmouse.x<283&&curmouse.y>114&&curmouse.y<144)
	        {
	            return 1;      //��ҳ
	        }
	        else if(curmouse.x>733&&curmouse.x<925&&curmouse.y>115&&curmouse.y<145)
	        { 
	            return 23;//����
	        }
	        else if(curmouse.x>694&&curmouse.x<800&&curmouse.y>590&&curmouse.y<620) //book
	        {
		        Mouse_reshow(&oldmouse);
		        strcpy(q,input(&book)); //���복λ��
		        Mouse_cpy(&oldmouse);
		        a=book_pause_port(q,a,1); //book
		        current_state(a);
	        }
	        else if(curmouse.x>694&&curmouse.x<800&&curmouse.y>550&&curmouse.y<580) //pause
	        {
		        Mouse_reshow(&oldmouse);
		        strcpy(q,input(&tempclose));
		        Mouse_cpy(&oldmouse);
		        a=book_pause_port(q,a,2); //pause
		        current_state(a);
	        }
	    }//if
    }//while
}

/* ******************************************************************
 * Function:flow_manage_record
 * Description:ͣ����¼ҳ��
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse);print_file(int);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ,5:ͣ����¼,6����λ�ֿ�,7:����,23:����
 * others:��
 * ******************************************************************/
int flow_manage_record()
{
    mou oldmouse,curmouse;
    int w; //���������Ҵ���ַ�
    int dele;
    int flag=0;
	int r=1;   //���ڽ���print_file����ֵ��Ϊ0˵���ѵ��ļ���β
    char core[10];
    new_all();
	print_file(flag,ALL);//��ʾ��һҳ����ʷ������һ��ȥ��Ҫ�м�¼��
    Put_String(100,100,1,1,0x5fbf,ultoa(coreleft(),core,10));
    Mouse_cpy(&oldmouse);
	while(!bioskey(1))
	{
	    move_mouse(&curmouse,&oldmouse); //�ƶ���������ʾ���
	    if(curmouse.key)
	    {
	        if(curmouse.x>283&&curmouse.x<428&&curmouse.y>144&&curmouse.y<163)
	        {
		        return 6;//current
	        }
	        else if(curmouse.x>587&&curmouse.x<725&&curmouse.y>135&&curmouse.y<163)
		    {
	    	    return 7;//query
		    }
	        else if(curmouse.x>113&&curmouse.x<283&&curmouse.y>114&&curmouse.y<144)
	        {
		        return 1;  //homepage
	        }
	        else if(curmouse.x>473&&curmouse.x<512&&curmouse.y>676&&curmouse.y<700)   //��һҳ
	        {
		         if(flag>0) //�ж��Ƿ������һҳ��������ҳ��
		        {
				    readbmp(0,0,"record.bmp");
				    r=print_file(--flag,ALL);
                    Mouse_cpy(&curmouse);
		        }
	        }
	        else if(curmouse.x>512&&curmouse.x<550&&curmouse.y>676&&curmouse.y<700) //��һҳ
	        {
		        if(r)  //�ж��Ƿ���һҳ������Ϊ�Ƿ��ļ���β
		        {
				    readbmp(0,0,"record.bmp");
				    r=print_file(++flag,ALL);
                    Mouse_cpy(&curmouse);
		        }
	        }
	        else if(curmouse.x>733&&curmouse.x<925&&curmouse.y>115&&curmouse.y<145)
	        { 
	            return 23; //����
	        }
	        else if(curmouse.x>842&&curmouse.x<911&&curmouse.y>285&&curmouse.y<670) //delete
		    {
                readbmp(374,336,"de_cop.bmp");
                dele=((curmouse.y-285)/39)+1;//�жϵ��Ǵ�ʱ��y
                while(1)
                {
                    move_mouse(&curmouse,&oldmouse); //�ƶ���������ʾ���
                    if(curmouse.x>465&&curmouse.x<552&&curmouse.y>425&&curmouse.y<443&&curmouse.key)//����ɾ������
                    {
                        if(super_code())//������ȷ����ɾ
                        {
                            Mouse_reshow(&oldmouse);
                            delete_one_all(dele,flag);//ɾ����¼��
                            readbmp(0,0,"record.bmp");
                            r=print_file(flag,ALL);//��ʾ�µ���ʷ��¼
                            Mouse_cpy(&curmouse);
				            Put_String(100,100,1,1,0x5fbf,ultoa(coreleft(),core,10)); 
                            break;//�˳�while
                        }
                    }
                    else if(curmouse.x>456&&curmouse.x<567&&curmouse.y>467&&curmouse.y<492&&curmouse.key)//����
                    {
                        readbmp(0,0,"record.bmp");
                        r=print_file(flag,ALL);//��ʾ�µ���ʷ��¼
                        Mouse_cpy(&curmouse);
                        break;//�˳�while
                    }

                }
	        }
	    }
	}//while
}

/* *******************************************************************
 * Function:flow_manage_query
 * Description:��λ��ȷ����
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse);
 *      Put_String(int,int,int,int,int,ultoa(coreleft(),char *s,int));
 *      print_file(int);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ,5:ͣ����¼,6:��λ�ֿ�,23:����
 * others:��
 * ******************************************************************/
int flow_manage_query()
{
    FILE * fp;
    mou oldmouse,curmouse;
    char q[4];  //����
    char core[10];
    int flag=0;
    int w,dele; //���������Ҵ���ַ�
	int r=1;//���ڽ���print_file����ֵ��Ϊ0˵���ѵ��ļ���β
    BUTTON frame={644,200,833,217};
    Put_String(100,100,1,1,0x5fbf,ultoa(coreleft(),core,10));
    Mouse_cpy(&oldmouse);
    while(1)
    {
	    move_mouse(&curmouse,&oldmouse);//�ƶ���������ʾ���
	    if(bioskey(1))
	    {
	        w=bioskey(0);
	    }
	    if(curmouse.key )
	    {
	        if(curmouse.x>433&&curmouse.x<581&&curmouse.y>117&&curmouse.y<144)
	        {
	            return 5; //record
	        }
	        else if(curmouse.x>283&&curmouse.x<428&&curmouse.y>144&&curmouse.y<163)
	        {
	            return 6;//current
	        }
	        else if(curmouse.x>113&&curmouse.x<283&&curmouse.y>114&&curmouse.y<144)
	        {
	            return 1;//HOMEPAGE
	        }
	        else if(curmouse.x>733&&curmouse.x<925&&curmouse.y>115&&curmouse.y<145)
	        {  
	            return 23;//help
	        }
	        else if(curmouse.x>473&&curmouse.x<512&&curmouse.y>676&&curmouse.y<700)  //��һҳ
	        {
	            if(flag>0)
	            {
				    readbmp(0,0,"query.bmp");
				    fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
				    r=print_file(--flag,QUERY);
	            }
	        }
	        else if(curmouse.x>512&&curmouse.x<550&&curmouse.y>676&&curmouse.y<700) //��һҳ
	        {
	            if(r)
	            {
				    readbmp(0,0,"query.bmp");
				    fill_Rectangle((frame.x1),frame.y1,(frame.x2),frame.y2,7);
				    r=print_file(++flag,QUERY);
	            }
	        }
	        else if(curmouse.x>644&&curmouse.x<838&&curmouse.y>202&&curmouse.y<217)//�����
	        {
		        Mouse_reshow(&oldmouse);
		        strcpy(q,input(&frame)); //�����Ҫ���ҵĳ�λ��		        
		        Mouse_cpy(&oldmouse); 
	        }
            else if(curmouse.x>580&&curmouse.x<900&&curmouse.y>200&&curmouse.y<220)//����
            {
		        if(query(atoi(q)))//����¼����
                {
                    //Mouse_reshow(&oldmouse);
                    readbmp(0,0,"query.bmp");
                    r=print_file(flag,QUERY); //���ļ� ��ӡ������
                    Put_String(169,195,2,2,0x5FBF,q);
                    //Mouse_cpy(&oldmouse); 
                }
                else//��¼������
                {
                    readbmp(374,336,"no_rec.bmp");
                    Delay(12);
                    readbmp(0,0,"query.bmp");
                    //Mouse_cpy(&oldmouse); 
                }
            }
            else if(curmouse.x>842&&curmouse.x<911&&curmouse.y>285&&curmouse.y<670) //delete
		    {
                readbmp(374,336,"de_coo.bmp");
                dele=((curmouse.y-285)/39)+1;//�жϵ��Ǵ�ʱ��y
                while(1)
                {
                    move_mouse(&curmouse,&oldmouse); //�ƶ���������ʾ���
                    if(curmouse.x>465&&curmouse.x<552&&curmouse.y>425&&curmouse.y<443&&curmouse.key)//����ɾ������
                    {
                        if(super_code())//������ȷ����ɾ
                        {
                            delete_one_query(dele,flag);//ɾ����¼��
                            Mouse_reshow(&oldmouse);
                            readbmp(0,0,"query.bmp");
                            r=print_file(flag,QUERY);//��ʾ�µ���ʷ��¼
                            Put_String(169,195,2,2,0x5FBF,q);
				            Put_String(100,100,1,1,0x5fbf,ultoa(coreleft(),core,10)); 
                            Mouse_cpy(&oldmouse); 
                            break;//�˳�while
                        }
                    }
                    else if(curmouse.x>456&&curmouse.x<567&&curmouse.y>467&&curmouse.y<492&&curmouse.key)//����
                    {
                        Mouse_reshow(&oldmouse);
                        readbmp(0,0,"query.bmp");
                        Put_String(169,195,2,2,0x5FBF,q);
                        r=print_file(flag,QUERY);//��ʾ�µ���ʷ��¼
                        Mouse_cpy(&oldmouse); 
                        break;//�˳�while
                    }
	            }
            }//else if
        }//if
    }//while
}


/*ͣ���Զ�����ģ��*/
/* *******************************************************************
 * Function:flow_process
 * Description:����ģ��
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse); 
 *      Put_String(int,int,int,int,int,ultoa(coreleft(),char *s,int));
 *      print_file(int);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ,9:ģ��ͣ����Ϣ����,14:ģ��ȡ����Ϣ����
 * others:��
 * *****************************************************************/
int flow_process(Pp *state,int * show)
{
    mou cm,om;
    readbmp(708,360,"t1.bmp");  
    getch();
    readbmp(708,360,"t2.bmp");
    Mouse_cpy(&om);
    while(1)
    {
        move_mouse(&cm,&om);
        if(cm.key)
        {
            if(cm.x<119&&cm.x>68&&cm.y<713&&cm.y>659)       //������ҳ
            {
                return 1;
             }
        
            else if(cm.x<731&&cm.x>680&&cm.y<760&&cm.y>680&&show) //�ر���ʾ����
            {
                *show=0;                            
                readbmp(708,360,"white.bmp");
            }
            else if(cm.x<955&&cm.x>790&&cm.y<124&&cm.y>59)//ͣ������
            { 
                if(*show) 
                {
                   readbmp(708,360,"t3.bmp");      
                }
                readbmp(200,512,"parkc.bmp");
				Mouse_reshow(&cm);
                return 9;
            
            }
			else if(cm.x<952&&cm.x>792&&cm.y<230&&cm.y>162)//ȡ������
			{
			  if(*show) 
              {
                  readbmp(708,360,"t4.bmp"); 
              }
              readbmp(196,512,"outc.bmp");
              Mouse_reshow(&cm);
              return 14;
			}


        }
    }


}

/* ********************************************************************
 * Function:flow_park
 * Description:ͣ�����ý���
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse); Put_String(int,int,int,int,int,char *);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ,9:ģ��ͣ����Ϣ����,14:ģ��ȡ����Ϣ����,
 *          10:һ��ͣ��,11:����ͣ��,12:����ͣ��,22:Ԥ��ͣ��
 * others:��
 * *******************************************************************/
int flow_park(Pp *state,int *show,Car *cr)
{
    mou cm,om;
	int fun=0; //���ƹ��ܵ��Ⱥ�ִ��
	int i=0;
	char s1[3],s2[3],s3[3];
    int h1,h2,h3;
    Rec list=create_node();       
    BUTTON floor={441,672,462,693};
    BUTTON area={534,672,552,693};
    BUTTON num={626,672,646,693};
    Mouse_cpy(&om);
	while(1)
	{   
		move_mouse(&cm,&om);
		if(cm.key)
		{
			 if(cm.x<119&&cm.x>68&&cm.y<713&&cm.y>659)           //������ҳ
			{
				return 1;
			 }
			 else if(cm.x<731&&cm.x>680&&cm.y<760&&cm.y>680&&show)
			{
				*show=0;                              //�ر���ʾ����
				readbmp(708,360,"white.bmp");
			}
               else if(cm.x<955&&cm.x>790&&cm.y<124&&cm.y>59)

            { 
                if(*show) readbmp(708,360,"t3.bmp");      //���¼���ͣ������
                readbmp(200,512,"parkc.bmp");
				Mouse_reshow(&cm);
                return 9;
            
            }
			else if(cm.x<952&&cm.x>792&&cm.y<230&&cm.y>162)
			{
			if(*show) readbmp(708,360,"t4.bmp"); //���¼���ȡ������
              readbmp(196,512,"outc.bmp");
              Mouse_reshow(&cm);
              return 14;
			}
	    	 else if(cm.x<365&&cm.x>272&&cm.y>566&&cm.y<628)     //ͣ��һ�㳵λ״̬���
			 {
                 readbmp(383,715,"grey.bmp");
                 if(state->f1)
                 { 
				     fun=1;
                 }
                 else
                 {
                     readbmp(383,715,"warn.bmp");
                 }
			 }
			 else if(cm.x<507&&cm.x>413&&cm.y>566&&cm.y<628)   //ͣ�����㳵λ״̬��� 
			 {  
                 readbmp(383,715,"grey.bmp");
                 if(state->f2)
                 {
				 fun=2;
                 }
                 else
                 {
                      readbmp(383,715,"warn.bmp");

                 }
			 }
			 else if(cm.x<645&&cm.x>552&&cm.y>566&&cm.y<628)   //ͣ�����㳵λ״̬���  
			 {  
                 readbmp(383,715,"grey.bmp");
                 if(state->f3)
                 {
                 fun=3;
                 }
                 else
                 {
                  readbmp(383,715,"warn.bmp");
                 }
			 }
			 else if(cm.x<358&&cm.x>272&&cm.y<726&&cm.y>707&&fun)
			 {
				 
				 switch(fun)
				 {
					 case 1:
                             if(*show) readbmp(708,360,"tend.bmp"); //��һ��ͣ��
                             for(i=0;i<state->f1;i++)
				             {
					             init_car(&cr[i]);
					             assign2(state,&cr[i],list,0);
					             road_design(&cr[i]);
				             }
                             add_to_file(list,TODAY);
							 Delay(20);
							 return 10;     
                             break;
                      case 2:
                             if(*show) readbmp(708,360,"tend.bmp");//�ڶ���ͣ��
                             for(i=0;i<state->f2;i++)
				            {
			           		    init_car(&cr[i]);
					            assign2(state,&cr[i],list,1);
					            road_design(&cr[i]);
				             }
                             add_to_file(list,TODAY);
                             Delay(20);
                             return 11;   
                             break;
                      case 3:
                             if(*show) readbmp(708,360,"tend.bmp");//������ͣ��
                             for(i=0;i<state->f3;i++)
				            {
					           init_car(&cr[i]);
					           assign2(state,&cr[i],list,2);
					           road_design(&cr[i]);
				             }
                             add_to_file(list,TODAY);
                             Delay(20);
                             return 12; 
                             break;
                     case 4:                                     //Ԥ����λ
                             if(state->a[h1][h2][h3]==3)
                            {
                               readbmp(383,715,"ok.bmp");
                               init_car(&cr[0]);
                               cr[0].i=h1;
                               cr[0].j=h2;
                               cr[0].k=h3;
                               road_design(&cr[0]);
                               write_node(cr,list);
				               add_to_file(list,TODAY);
                               if(*show)
                               {
                                   readbmp(708,360,"tend.bmp");
                               }
                              Delay(20);
                              return 22;
                             }
                           else
                          {
                             readbmp(383,715,"error.bmp");
                          }
                          break;
                 }
             }
             else if(cm.x<358&&cm.y>272&&cm.y>677&&cm.y<697)     //��Ԥ����Ϣ�����Լ���λ״̬���
             {
                 Mouse_reshow(&om);
                 readbmp(383,715,"grey.bmp");
				 strcpy(s1,input(&floor));
                 h1=atoi(s1)-1;
				 strcpy(s2,input(&area));
                 h2=atoi(s2)-1;
				 strcpy(s3,input(&num));
                 h3=atoi(s3)-1;
                 fun=4;
             }
        }
	}
}

/* *******************************************************************
 * Function:flow_outcar
 * Description:ȡ��ѡ�����
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);Mouse_reshow(&curmouse);Put_String(int,int,int,int,int,char *);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ,9:ģ��ͣ����Ϣ����,14:ģ��ȡ����Ϣ����,15,ȫȡ��Ϣ�趨,19.����ȡ��
 * others:��
 * *******************************************************************/
int flow_outcar(int *show)   
{
	mou cm,om;
   // mousecheck();,
	//mousemove();
    Mouse_cpy(&om);
	while(1)
	{
		move_mouse(&cm,&om);
		if(cm.key)
		{
			 if(cm.x<119&&cm.x>68&&cm.y<713&&cm.y>659)           //������ҳ
			{
				return 1;
			 }
			 if(cm.x<331&&cm.x>289&&cm.y<618&&cm.y>571)
			 {
				 readbmp(196,512,"outall.bmp");            //ȫȡ��Ϣ�趨
				 return 15;
			 }
			 if(cm.x<331&&cm.x>286&&cm.y<712&&cm.y>673)
			 {
				 readbmp(196,512,"outone.bmp");              //������Ϣ�趨
				 return 19;
			 }
				 else if(cm.x<731&&cm.x>680&&cm.y<760&&cm.y>680&&show)
			{
				*show=0;                              //�ر���ʾ����
				readbmp(708,360,"white.bmp");
			}
				   else if(cm.x<955&&cm.x>790&&cm.y<124&&cm.y>59)

			{
				if(*show) readbmp(708,360,"t3.bmp");      //���¼���ͣ������
				readbmp(200,512,"parkc.bmp");
				Mouse_reshow(&cm);
				return 9;

			}
			else if(cm.x<952&&cm.x>792&&cm.y<230&&cm.y>162)
			{
			if(*show) readbmp(708,360,"t4.bmp"); //���¼���ȡ������
			  readbmp(196,512,"outc.bmp");
			  Mouse_reshow(&cm);
			  return 14;
			}

		}

	}


}

/* ******************************************************************
 * Function:flow_outall
 * Description:ȡ��ȫ�����ý���
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *          Mouse_reshow(&curmouse);
 *          Put_String(int,int,int,int,int,char *);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ,9:ģ��ͣ����Ϣ����,14:ģ��ȡ����Ϣ����,
 *          16һ��ȡ��,17����ȡ��,18����ȡ��
 * others:��
 * *******************************************************************/
int flow_outall(int * show,Pp *state)
{
	mou cm,om;
	int fun=0;
    Mouse_cpy(&om);
	while(1)
	{
		move_mouse(&cm,&om);
		if(cm.key)
		{

			 if(cm.x<119&&cm.x>68&&cm.y<713&&cm.y>659)           //������ҳ
			{
				return 1;
			 }
			 if(cm.x>437&&cm.y>611&&cm.x<598&&cm.y<628)
			 {
                 if(state->m1)
               {
				 fun=1;
               }

			 }
			 if(cm.x>437&&cm.x<598&&cm.y>638&&cm.y<668)
			 {
                 if(state->m2)
                 {
                     fun=2;
                 }
			 }
			 if(cm.x>437&&cm.x<598&&cm.y>678&&cm.y<712)
			 {
                 if(state->m3)
                 {
				 fun=3;
                 }
			 }
			 if(fun&&cm.x>666&&cm.x<686&&cm.y>277&&cm.y<718)
			 {

				if(*show) 
                readbmp(708,360,"tend.bmp");
                printf("%u",coreleft());
				Delay(20);
				switch(fun)
				{
					case 1:
                           return 16;
                           break;
					case 2:
                           return 17;
                           break;
					case 3:
                           return 18;
                           break;

				}
			 }
				 
             else if(cm.x<731&&cm.x>680&&cm.y<760&&cm.y>680&&show)
			{
				*show=0;                              //�ر���ʾ����
				readbmp(708,360,"white.bmp");
			}
             else if(cm.x<955&&cm.x>790&&cm.y<124&&cm.y>59)

			{
				if(*show) 
                readbmp(708,360,"t3.bmp");      //���¼���ͣ������
				readbmp(200,512,"parkc.bmp");
				Mouse_reshow(&cm);
				return 9;

			}
			else if(cm.x<952&&cm.x>792&&cm.y<230&&cm.y>162)
			{
			  if(*show)
              readbmp(708,360,"t4.bmp"); //���¼���ȡ������
			  readbmp(196,512,"outc.bmp");
			  Mouse_reshow(&cm);
			  return 14;
			}


		}

	}
}

/* *******************************************************************
 * Function:flow_outone
 * Description:ȡ���������ý���
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse);Put_String(int,int,int,int,int,char *);
 * Called by:yes(Pp *);
 * Input:��
 * return:1:��ҳ,9:ģ��ͣ����Ϣ����,14:ģ��ȡ����Ϣ����,
 *        16һ��ȡ��,17����ȡ��,18����ȡ��
 * others:��
 * ******************************************************************/
int flow_outone(Pp *state,Car* cr,int *show)
{
    mou cm,om;
	int h1,h2,h3;
	char s1[3],s2[3],s3[3];
	BUTTON floor={492,609,611,631};
	BUTTON area={492,648,611,670};
	BUTTON num={492,686,611,708};
	strcpy(s1,input(&floor));
	h1=atoi(s1)-1;
	strcpy(s2,input(&area));
	h2=atoi(s2)-1;
	strcpy(s3,input(&num));
	h3=atoi(s3)-1;
    Mouse_cpy(&om);
	while(1)
	{
        move_mouse(&cm,&om);
        if(cm.key)
        { 
            if(cm.x<119&&cm.x>68&&cm.y<713&&cm.y>659)           //������ҳ
			{
				return 1;
			 }

	 else if(cm.x<731&&cm.x>680&&cm.y<760&&cm.y>680&&show)
			{
				*show=0;                              //�ر���ʾ����
				readbmp(708,360,"white.bmp");
			}
	 else if(cm.x<955&&cm.x>790&&cm.y<124&&cm.y>59)

			{
				if(*show) readbmp(708,360,"t3.bmp");      //���¼���ͣ������
				readbmp(200,512,"parkc.bmp");
				Mouse_reshow(&cm);
				return 9;

			}
	 else if(cm.x<952&&cm.x>792&&cm.y<230&&cm.y>162)
			{
			if(*show) readbmp(708,360,"t4.bmp"); //���¼���ȡ������
			  readbmp(196,512,"outc.bmp");
			  Mouse_reshow(&cm);
			  return 14;
			}
	 else if(cm.x<683&&cm.x>662&&cm.y<733&&cm.y>593)
	   {  
           Mouse_reshow(&cm);
		   if(state->a[h1][h2][h3]==1)
		   {
			   readbmp(708,360,"tend.bmp");
			   cr[0].i=h1;
			   cr[0].j=h2;
			   cr[0].k=h3;
               road_design(&cr[0]);
               drop_car2(change(h1,h2,h3));
			   drop_car1(change(h1,h2,h3));
               Delay(20);
			   return 20;
           }
           else
           {
                readbmp(356,535,"onewrong.bmp");
                getch();
                readbmp(356,535,"onegrey.bmp");
                strcpy(s1,input(&floor));
                h1=atoi(s1)-1;
	            strcpy(s2,input(&area));
                h2=atoi(s2)-1;
	            strcpy(s3,input(&num));
                h3=atoi(s3)-1;

            }
         }
      }
   }
}

/* *******************************************************************
 * Function:endpage
 * Description:����ģ�ⷵ�ؽ���
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);
 *      Mouse_reshow(&curmouse);Put_String(int,int,int,int,int,char *);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ
 * others:��
 * *******************************************************************/
int endpage()
{
     mou cm,om;
     Mouse_cpy(&om);
     while(1)
     {
         move_mouse(&cm,&om);
         if(cm.key)
         {
             if(cm.x<602&&cm.x>436&&cm.y<501&&cm.y>445)
             {
                 return 1;
             }
         }
     }
}

/* *******************************************************************
 * Function:endpage
 * Description:�������ض���
 * Calls:move_mouse(Mouse ,Mouse);Mouse_cpy(&curmouse);Mouse_reshow(&curmouse);Put_String(int,int,int,int,int,char *);
 * Called by:yes(Pp *);
 * Input:��
 * return:��1:��ҳ
 * others:��
 * ********************************************************************/
void welcome()
{
    int i,j,k;
    readbmp(0,0,"load.bmp");
	for(i=0;i<2;i++)
 {
		readbmp(386,270,"l1.bmp");
        Delay(3);
        readbmp(386,270,"l2.bmp");
        Delay(3);
        readbmp(386,270,"l3.bmp");
        Delay(3);
        readbmp(386,270,"l4.bmp");
        Delay(3);
        readbmp(386,270,"l5.bmp");
        Delay(3);
        readbmp(386,270,"l6.bmp");
        Delay(3);
        readbmp(386,270,"l7.bmp");
        Delay(3);
        readbmp(386,270,"l8.bmp");
        Delay(3);
        readbmp(386,270,"l9.bmp");
        Delay(3);
        readbmp(386,270,"l10.bmp");
        Delay(3);
        readbmp(386,270,"l11.bmp");
        Delay(3);
        readbmp(386,270,"l12.bmp");
        Delay(3);
    }

   Delay(3);
}