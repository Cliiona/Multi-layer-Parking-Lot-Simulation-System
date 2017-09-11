#include "manage.h"
/* **********************************************************************************************
 *                                [管理登陆界面] 相关功能及其函数                               *
 *                     1. 进行用户验证 2.输错三次锁定页面 3.验证解锁密码                        *
 *                     调用主要子函数有2：codeput(), match(),wrong_times().                     *
 * **********************************************************************************************/

/* ******** [管理员登陆] 输入密码显示星号******** */
char * codeput(BUTTON *button)
{
    int k;
    int m;
    int i=0;
    int j=0;
    char s[20];
    char c[15]; //显示星号
    fill_Rectangle(button->x1,button->y1,button->x2,button->y2,0x5FBF);
    while(1)
    {
        m=0;
        k=bioskey(0);
        switch(k)
        {
            case ENTER: if(i==0) continue;  //若没有输入任何字符，继续等待输入
                        else {m=1;break;}  //有输入字符  退出switch  m置1
            case BACKSPACE: if(i>0)       //退格
                            {
                                s[--i]='\0';
                                c[--j]='\0';
                                fill_Rectangle(button->x1,button->y1,button->x2,button->y2,0x5FBF);
								Put_String((button->x1)+5,button->y1+5,1,1,0,c); 
                                continue;
                            }
            default: s[i]=k;//任何一个字符都可以用相应的ASCII表示
                     s[i+1]='\0';
                     c[j]=42;
                     c[j+1]='\0';
                      //*的ASCII是42
					 Put_String((button->x1)+5,button->y1+5,1,1,0,c);   
                     i++;
                     j++;
        }
        if(m)  break;   //退出while
    }
    return s; //将输入内容传回登陆界面

}

/* ******** [管理员登陆] 用户名密码验证****** */
int match(char u[9],char c[9])
{
    man manager[4];
    FILE *fp;
    int i,num;
    if((fp=fopen("MANAGER.txt","rt"))==NULL)
    {
        printf("sorry\n");
        getch();
    }
    for(i=0;i<4;i++)
    {
        fscanf(fp,"%1c%s%s\n",&manager[i].n,manager[i].code,manager[i].username);
        if(!stricmp(manager[i].username,u))
        { num=i;}
    }
    fclose(fp);    
    if(!stricmp(manager[num].code,c))
    {
             return 1;
    }
    else return 0;
}

/* ******** [管理员登陆] 累计输错次数，超过5次需输入解锁密码******/
int wrong_times(int count,int *flag)  //int *是为了在本函数中能改变界面函数里的（静态）flag值
{
    (*flag)++;
    count=5-(*flag);
    return count;
}

/* **********************************************************************************************
 *                                [停车记录界面] 相关功能及其函数                               *
 *                             1. 按行显示全部停车记录 2.删除操作                               *
 *                       调用的主要子函数有2：print_all(), delete_one_all().                    *
 * **********************************************************************************************/

/* ********* [停车记录] 根据页数和位置 删除停车记录界面某一条停车记录******* */
void delete_one_all(int d,int flag)
{
	int i=0;
	int test;
	Rec list=create_list(ALL);
    Rec node=list;  //指向头结点 
    while(i<(d+10*flag) && node!=NULL) //指向要删的结点
    {
        i++;
        node=node->next;
	}
	delete_node(list,node);
	rewrite_file(list,ALL);
    destroy_list(list);
}

/* ********* [停车记录] 浏览 所找车位 历史记录********* */
int print_all(int flag)
{
	FILE *fp;
	char s[30][100];
    char ch;
    int i;
    int r=0; //作为函数返回值
    i=0;
	if((fp=fopen("all.txt","rt"))==NULL)
    {
        printf("sorry");
        getch();
    }
    fseek(fp,flag*660L,SEEK_CUR);//根据当前页数移动位置指针,flag从0开始
    while(i<10)
    {
	   if((ch=fgetc(fp))!=EOF)//!feof(fp)
        {
            r=1;
            fseek(fp,-1L,SEEK_CUR);
            fgets(s[i],65,fp);  
            fseek(fp,2L,SEEK_CUR);//转义字符\n 2
            Put_String(145,295+i*39,1,1,0x5FBF,s[i]);
            i++;
        }
       else
       {
             r=0;
             i=10;//退出while
       }
    }
	fclose(fp);
    return r;
}

/* **********************************************************************************************
 *                               [精确查找界面] 相关功能及其函数                                *
 *                          1.搜索某一车位号 2.显示 3.删除某条记录                              *
 *               调用的主要子函数有3： query(),print_query(),delete_one_query().                *
 * **********************************************************************************************/

/* ********* [精确查找] 将all文件精简生成query文件,port是车位号,调用query_port_node() & save_query_list()********/
void query(int port)
{
	FILE *fp;
	Rec list=create_node();
	list=create_list(ALL);  //将全部历史文件导入这个新创建的链表
	get_query_list(list,port);  //将链表精简，只保留是所求车位号的的结点
	rewrite_file(list,QUERY);    //保存到query文件
    destroy_list(list);
}

/* ********* [精确查找] 按车位号精简链表***********/
void get_query_list(Rec list,int num)
{
	Rec temp=NULL;
	Rec pos=list;
	while(pos->next!=NULL)
	{
		if(pos->next->port!=num)
		{
			temp=(pos->next)->next;
			delete_node(list,pos->next);
			pos->next=temp;
		}
		else
		{ 
            pos=pos->next;
        }
	}
    temp=NULL;
    pos=NULL;
}

/* ********* [精确查找] 浏览 所找车位 历史记录********* */
int print_query(int flag)
{
	FILE *fp;
	char s[30][100];
    char ch;
    int i;
    int r=0; //作为函数返回值
    i=0;
	if((fp=fopen("query.txt","rt"))==NULL)
    {
        printf("sorry");
        getch();
    }
    fseek(fp,flag*660L,SEEK_CUR);//根据当前页数移动位置指针,flag从0开始
    while(i<10)
    {
	   if((ch=fgetc(fp))!=EOF)//!feof(fp)
        {
            r=1;
            fseek(fp,-1L,SEEK_CUR);
            fgets(s[i],65,fp);  
            fseek(fp,2L,SEEK_CUR);//转义字符\n 2
            Put_String(145,295+i*39,1,1,0x5FBF,s[i]);
            i++;
        }
       else
       {
             r=0;
             i=10;//退出while
       }
    }
	fclose(fp);
    return r;
}

/* ********* [精确查找] 根据页数和位置 删除精确查找界面某一条停车记录******* */
void delete_one_query(int d,int flag)
{
	int i=0;
	Rec list=create_list(QUERY);
	Rec node=list;//指向头结点
	while(i<(10*flag+d) && node!=NULL) //指向要删的结点
	{
		i++;
		node=node->next;
	}
	delete_query_in_all(node);//将在查找页面删除的记录也在all & history中删除
    delete_query_in_today(node);//在today中也删除这条记录，因返回record时会new_all

	delete_node(list,node);//决不能在这个函数里面destroy_list!下面还要用
	rewrite_file(list,QUERY);
    destroy_list(list);//销毁链表
    node=NULL;
}

/* ********* [精确查找] 在删除query时也在all中删除这条记录********** */
void delete_query_in_all(Rec node)
{
	Rec pos=NULL;
	Rec list=create_list(ALL);
	pos=list->next;
	while(((pos->port!=node->port)||(pos->carnum)!=(node->carnum) ) && pos)//找到想要删除的结点
    {
        pos=pos->next;
    }
	delete_node(list,pos); 
    rewrite_file(list,ALL);
    destroy_list(list);//可以销毁链表
    pos=NULL;//不要让node=NULL，因在delete_qauery_in_today和delete_list中还要用这个node的地址,指null的工作交给总调函数delete_one_query
}
/* ********* [精确查找] 在删除query时也在today中删除这条记录********** */
void delete_query_in_today(Rec node)
{
	Rec list=create_list(TODAY);
	Rec pos=list->next;
	while(((pos->port!=node->port)||(pos->carnum)!=(node->carnum) )&& pos)//找到想要删除的结点
    {
        pos=pos->next;
    }
	delete_node(list,pos);  
    rewrite_file(list,TODAY);  
    destroy_list(list);//可以销毁链表
    pos=NULL;    //不要让node=NULL，因在delete_query_in_today中还要用这个node的地址
}

/* **********************************************************************************************
 *                             [车位现况界面] 相关功能及其函数                                  *
 *                      1.显示现况彩色点 及各类车位数目 2.预定车位 3.暂停车位                   *
 *       调用的主要子函数有4： current_state(),book_pause_port()|| count_port(),bling().        *
 * **********************************************************************************************/

/* ******** [车位现况] 扫描p->a[i][j][k],显示停车状态点 和 各类车位数目****** */
void current_state(Pp *p)
{
	int i,j,k,x;
	char ch[3];
	for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            for(k=0;k<7;k++)
            {
                x=p->a[i][j][k];            
                bling(i,j,k,x);
            }
    fill_Rectangle(290,530,320,550,1);
    fill_Rectangle(290,560,320,579,1);
    fill_Rectangle(290,590,320,609,1);
    fill_Rectangle(290,620,320,639,1);

	Put_String(298,532,1,1,0x5FBF,itoa(count_port(p)[0],ch,10));  //显示各类车位数量
	Put_String(298,561,1,1,0x5FBF,itoa(count_port(p)[1],ch,10));//parking
	Put_String(298,621,1,1,0x5FBF,itoa(count_port(p)[2],ch,10));//pause
    Put_String(298,591,1,1,0x5FBF,itoa(count_port(p)[3],ch,10));//book
}

/* ******** [车位现况] 预定车位******* */
Pp * book_pause_port(char *t,Pp *p,int sort)
{
    int a=atoi(t)-111;//字符串000即是111
    int g,s,b;
    g=a%10; //个位
    b=a/100;//百位
	s=(a%100)/10;//十位
	if(p->a[b][s][g]==0 || p->a[b][s][g]==3) //只能对空位和已预订的车位进行操作
    {
        if(sort==2)  //暂停使用
        {
           p->a[b][s][g]=4;
        }
        if(sort==1 && p->a[b][s][g]==0)  //只能对空位进行预定操作
        {
            p->a[b][s][g]=3;
        }
    }
    return p;   
}

/* ******** [车位现况] 计算各种状态的车位数******** */
int * count_port(Pp *p)
{
    int count[4]={0,0,0,0};
    int i,j,k;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            for(k=0;k<7;k++)
            {
                switch(p->a[i][j][k])
                {
					 case 0:count[0]++;break;  //空位数
                     case 1:count[1]++;break;  //停车中
                     case 3:count[2]++;break;  //已预订
                     case 4:count[3]++;break;  //暂停使用
                }
            }
    return count;
}

/* ******** [车位现况] 画车位现况点************ */  
void bling(int i,int j,int k,int status)
{
    int x;
	//int color;
	x=277+(214*j)+30*(k); //根据区和位号确定横坐标
	switch(status)
	{
		case 0:readbmp(x,326+i*45,"green.bmp");break; //空位 绿
		case 1:readbmp(x,326+i*45,"red.bmp");break; //停车 红
		case 3:readbmp(x,326+i*45,"yellow.bmp");break; //预定 黄
		case 4:readbmp(x,326+i*45,"blue.bmp");break; //暂停使用 蓝
	}
	//fill_Rectangle(x,111+i*17,x+4,115+i*17,color); //不同层 不同纵坐标
	return;
}

/* **********************************************************************************************
 *                                       [与文件相关的函数]                                     *
 * **********************************************************************************************/

/* *********** 打开today放入链表，重写入all,再打开history放入链表,追加到all文件中  <调用3个子函数>******** */
void new_all()
{
	FILE *fp;
	char ch;
	unsigned u=coreleft();
	Rec list=NULL;
	Rec list2=NULL;

	list=create_list(TODAY);//生成今天记录链表
	rewrite_file(list,ALL);//today重写入all,并销毁链表
    destroy_list(list);
	
	list2=create_list(HISTORY);
	add_history_to_all(list2);
    destroy_list(list2);
}

/* *********** 将停车记录按 记录界面 的格式 重写入文件中,sort是即将写入的文件名（整型）*********** */
void rewrite_file(Rec list,int sort)
{
	FILE *fp;
	Rec pos=list->next;
	switch(sort)
	{
		case TODAY:fp=fopen("today.txt","wt"); break;
		//case HISTORY:fp=fopen("history.txt","wt"); break; //不会有重写history文件，因为对history只能进行追加操作
		case ALL:fp=fopen("all.txt","wt"); break;
		case QUERY:fp=fopen("query.txt","wt"); break;
	}
	if(fp==NULL)
	{
		printf("sorry");
	}
	while(pos!=NULL)
	{
			fprintf(fp,"%3d%8d%23s%21s%9d\n",pos->port,pos->carnum,pos->it,pos->ot,pos->time);
			pos=pos->next;
	}
	fclose(fp);
    pos=NULL;
	//destroy_list(list);//不要再次销毁链表，因这个链表可能还会被继续使用
}

/* *********** 将history链表追加到all文件中************** */
void add_history_to_all(Rec list)
{
	FILE *fp;
    Rec pos=list->next;
    fp=fopen("all.txt","at"); 
    while(pos!=NULL)
    {
		fprintf(fp,"%3d%8d%23s%21s%9d\n",pos->port,pos->carnum,pos->it,pos->ot,pos->time);
        pos=pos->next;
    }
    fclose(fp);
    pos=NULL;
    //destroy_list(list);
}

/* *********** 退出时将新的停车记录写入历史(调用以下3个函数)****************** */
void save_new_record()
{
	Rec list=NULL;
    write_ot();//将出库信息加入today
	list=create_list(TODAY);//得到信息完备today的链表
    add_to_history(list);//将信息完备的today追加到history文件中   
    destroy_list(list);
}

/* *********** 从today中读取，将退出时间作为今天车的出库时间，调用函数重写today文件********* */
void write_ot()
{
    FILE *fp;
    record node;
    Rec list=create_node();
    if((fp=fopen("today.txt","rt"))==NULL)
    {
        printf("sorry");
        getch();
    }
	while(fgetc(fp)!=EOF)
    {
        fseek(fp,-1L,SEEK_CUR);
        //node=create_node();
		node.next=NULL;
		fscanf(fp,"%3d%8d%23s%23s%9d\n",&node.port,&node.carnum,node.it,node.ot,&node.time);//每读五个数据，读取一个换行字符，换行继续读
		strcpy(node.ot,format_time());//将退出时间作为出库时间
		node.time=park_time(node.it,node.ot); //调用函数计算停车时间
        insert_node(list,node);
    }
    fclose(fp);
    rewrite_file(list,TODAY);//重写today
    destroy_list(list);
}

/* *********** 将信息完备的today追加到history文件中*********** */
void add_to_history(Rec list)
{
	FILE *fp;
    Rec pos=list->next;
    if((fp=fopen("history.txt","at"))==NULL)
    {
        printf("sorry");
    }//追加
    while(pos!=NULL)
    {
		fprintf(fp,"%3d%8d%23s%21s%9d\n",pos->port,pos->carnum,pos->it,pos->ot,pos->time);
        pos=pos->next;
    }
    fclose(fp);
    pos=NULL;
    //destroy_list(list);
}
/* *********** 将信息追加到today文件中*********** */
void add_to_today(Rec list)
{
	FILE *fp;
    Rec pos=list->next;
    if((fp=fopen("today.txt","at"))==NULL)
    {
        printf("sorry");
    }//追加
    while(pos!=NULL)
    {
		fprintf(fp,"%3d%8d%23s%21s%9d\n",pos->port,pos->carnum,pos->it,pos->ot,pos->time);
        pos=pos->next;
    }
    fclose(fp);
    pos=NULL;
    //destroy_list(list);
}

/************* 从文件中读取记录放入链表,sort是文件名（整型）****************** */ 
Rec create_list(int sort)
{
    FILE *fp;
	char ch;
	unsigned u;
    Rec list=create_node();
	record node;
	//printf("%u\n",coreleft());
	switch(sort)
    {
		case TODAY:fp=fopen("today.txt","rt"); break;
		case HISTORY:fp=fopen("history.txt","rt"); break;
		case ALL:fp=fopen("all.txt","rt"); break;
        case QUERY:fp=fopen("query.txt","rt"); break;
	}

	while(ch=fgetc(fp)!=EOF)
	{
			 fseek(fp,-1L,SEEK_CUR);
			 //node=create_node();
			 node.next=NULL;
			 fscanf(fp,"%3d%8d%23s%23s%9d\n",&node.port,&node.carnum,node.it,node.ot,&node.time);//每读五个数据，读取一个换行字符，换行继续读
			 insert_node(list,node);
    }
	fclose(fp);
	return list;
}

/* **********************************************************************************************
 *                                         [共用的功能函数]                                     *
 * **********************************************************************************************/

/* **********创建一个结点***************/  
Rec create_node(void)
{
    Rec node=(Rec)malloc(sizeof(record));
    if(node==NULL)
    {
        printf("sorry\n");
        //printf("%u",coreleft());
        getch();
    }
    node->next=NULL;
    return node;
}

/* **********删除一个结点********** */ 
void delete_node(Rec list,Rec node)
{
    Rec pos=list;//不能改list，后面会用
    if(pos->next==NULL)
	{return NULL;}
    while(pos->next!=node && pos->next!=NULL)
    {
        pos=pos->next;
    }
    if(pos->next!=NULL)
    {
		pos->next=node->next;
		free(node);
		node->next=NULL;
    }
    pos=NULL;
	//else return NULL; //没找到记录
	//return list;
}

/* ********（在尾部）插入新的结点********** */  
void insert_node(Rec list,record park)
{
    Rec pos=list;//要保留头结点
    Rec node=create_node();
	node->carnum=park.carnum;
	node->port=park.port;
	strcpy(node->it,park.it);
	strcpy(node->ot,park.ot);
	node->time=park.time;
	while(pos->next!=NULL)   //找到链表尾
	{
		pos=pos->next;
	}
	node->next=NULL;
	pos->next=node;       //再调整指针域
}

/* ******** 销毁链表 ******** */
void destroy_list(Rec list)
{
	int i;
    Rec node=list;
	while(list)
	{
        list=list->next;//让list先指向后一个结点
        free(node);
        node=list;
    }
    node=NULL;
}
/* ******** 画输入框并且显示输入******* */
char * input(BUTTON *button)
{
    char s[20];
    int k;
    int m;
    int i=0;
    fill_Rectangle(button->x1,button->y1,button->x2,button->y2,0x5FBF);
    while(1)
    {
        m=0;
        k=bioskey(0);
		//if(k==ESC) break; //千万不能按esc来break，否则密保功能不攻自破
        switch(k)
        {
            case ENTER: if(i==0) continue;  //若没有输入任何字符，继续等待输入
                        else {m=1;break;}  //有输入字符  退出switch  m置1
            case BACKSPACE: if(i>0)       //退格
                            {
                                s[--i]='\0';
                                fill_Rectangle(button->x1,button->y1,button->x2,button->y2,0x5FBF);
								Put_String(button->x1+4,button->y1+3,1,1,0,s); 
                                continue;
                            }
            default: s[i]=k;//任何一个字符都可以用相应的ASCII表示
                     s[i+1]='\0';
					 Put_String((button->x1)+4,button->y1+3,1,1,0,s);   
                     i++;
        }
        if(m)  break;   //退出while
    }
    return s; //将输入内容传回登陆界面
}

/* ******** 处理时间格式************ */
char * format_time()
{
	struct tm *ptr;
    time_t y;
    char str[22];
	y=time(NULL);
	ptr=localtime(&y);
	strftime(str,sizeof(str),"%Y/%m/%d-%H:%M",ptr);
	return str;
}

/* ******** 生成一个两位的随机数,车号******** */
int rand_bi()
{
    int d;
    d=rand()%90+10;
    return d;
}

/* ******** 计算停车时间************ */
int park_time(char *it,char *ot)  //传进来的是入库时间
{
    int it1,it2,ot1,ot2,time;  //1是小时2是分钟
    char ch[20];
    sscanf(ot,"%*[^-]-%d:%d",&ot1,&ot2);  //出库
    sscanf(it,"%*[^-]-%d:%d",&it1,&it2);  //进库
    time=60*(ot1-it1)+ot2-it2;
    if(time==0) {time=1;}
    return time;
    /*  
    time_ time2=time(NULL);
    int time=difftime(time2,time1);  //单位是s
    time=(int)ceil(time/60); //ceil是向上取整函数 停车时间以秒为单位
    return time;*/
}

/* ************删除口令*********** */
int super_code()
{
    char code[10];
	BUTTON super={465,425,552,443};
    strcpy(code,codeput(&super));
    if(stricmp("super",code)==0)
    {
        return 1;
    }
    else return 0;

}

/* ************管理员信息修改*********** */
int inf_modify(char *ou,char *nu,char *oc,char *nc,char *ic)
{
    int num;
    man manager[4];
    FILE *fp;
    int i;
    if((fp=fopen("MANAGER.txt","rt"))==NULL)
    {
        printf("sorry\n");
        getch();
    }
    for(i=0;i<4;i++)
    {
        fscanf(fp,"%1c%s%s\n",&manager[i].n,manager[i].code,manager[i].username);
    }
    fclose(fp);
	if(!strcmp(nc,ic))///两次新密一致
    {
        if(!stricmp(manager[0].username,ou))num=0;
        else if(!stricmp(manager[1].username,ou))num=1;
        else if(!stricmp(manager[2].username,ou))num=2;
        else if(!stricmp(manager[3].username,ou))num=3;
        if(modify_file(num,nu,oc,nc))//不用传ou(old_username),ic(insure_code)了
        {
            readbmp(170,570,"modified.bmp");//修改成功
            Delay(10);
            return 1;//返回登录界面
        }
        else 
        {
            readbmp(170,570,"oc_wrong.bmp");
            Delay(10);
            readbmp(0,0,"setting.bmp");
            return 0;
        }
            
    }
    else 
    {
        readbmp(170,570,"mismatch.bmp");
        Delay(10);
        readbmp(0,0,"setting.bmp");
        return 0;
    }
}

/* ************管理员信息file修改*********** */
int modify_file(int num,char *nu,char *oc,char *nc)
{
    man manager[4];
    FILE *fp;
    int i;
    if((fp=fopen("MANAGER.txt","rt"))==NULL)
    {
        printf("sorry\n");
        getch();
    }
    for(i=0;i<4;i++)
    {
        fscanf(fp,"%1c%s%s\n",&manager[i].n,manager[i].code,manager[i].username);
    }
    fclose(fp);
    if(!stricmp(manager[num].code,oc))//密码输入正确
    {
        strcpy(manager[num].code,nc);//修改信息
        strcpy(manager[num].username,nu);
    }
    else return 0;//原密码密码错误

    if((fp=fopen("MANAGER.txt","wt"))==NULL)
    {
        printf("sorry\n");
        getch();
    }    
    for(i=0;i<4;i++)
    {
        fprintf(fp,"%d %s %s\n",i+1,manager[i].code,manager[i].username);//放入信息文件
    }
    fclose(fp);
    return 1;

}

/* ************管理员信息file修改************/
void check_ou(char *ou)
{
    man manager[4];
    FILE *fp;
    int i;
    if((fp=fopen("MANAGER.txt","rt"))==NULL)
    {
        printf("sorry\n");
        getch();
    }
    for(i=0;i<4;i++)
    {
        fscanf(fp,"%1c%s%s\n",&manager[i].n,manager[i].code,manager[i].username);
    }
    fclose(fp);    
    if(stricmp(ou,manager[0].username)&&stricmp(ou,manager[1].username)
            &&stricmp(ou,manager[2].username)&&stricmp(ou,manager[3].username))
    {
        readbmp(170,570,"no_user.bmp");
        Delay(10);   
        readbmp(0,0,"setting.bmp");
    }  
} 
