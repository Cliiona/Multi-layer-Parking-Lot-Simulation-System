#include "manage.h"

/* **********************************************************************************************
 * Function:codeput
 * Description:[����Ա��½] ����������ʾ�Ǻ�
 * **********************************************************************************************/
char * codeput(BUTTON *button)
{
    int k;
    int m;
    int i=0;
    int j=0;
    char s[20];
    char c[15]; //��ʾ�Ǻ�
    fill_Rectangle(button->x1,button->y1,button->x2,button->y2,0x5FBF);
    while(1)
    {
        m=0;
        k=bioskey(0);
        switch(k)
        {
            case ENTER: if(i==0) continue;  //��û�������κ��ַ��������ȴ�����
                        else {m=1;break;}  //�������ַ�  �˳�switch  m��1
            case BACKSPACE: if(i>0)       //�˸�
                            {
                                s[--i]='\0';
                                c[--j]='\0';
                                fill_Rectangle(button->x1,button->y1,button->x2,button->y2,0x5FBF);
								Put_String((button->x1)+5,button->y1+5,1,1,0,c); 
                                continue;
                            }
            default: s[i]=k;//�κ�һ���ַ�����������Ӧ��ASCII��ʾ
                     s[i+1]='\0';
                     c[j]=42;
                     c[j+1]='\0';
                      //*��ASCII��42
					 Put_String((button->x1)+5,button->y1+5,1,1,0,c);   
                     i++;
                     j++;
        }
        if(m)  break;   //�˳�while
    }
    return s; //���������ݴ��ص�½����

}

/* **********************************************************************************************
 * Function:match
 * Description:[����Ա��½] �û���������֤
 * **********************************************************************************************/
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

/* **********************************************************************************************
 * Function:wrong_times
 * Description:[����Ա��½]�ۼ��������������5���������������
 * others:*int��Ϊ���ڱ��������ܸı���溯����ģ���̬��flagֵ
 * **********************************************************************************************/
int wrong_times(int count,int *flag)  
{
    (*flag)++;
    count=5-(*flag);
    return count;
}

/* **********************************************************************************************
 * Function:inf_modify
 * Description:[����Ա��½]����Ա��Ϣ�޸ģ������
 * **********************************************************************************************/
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
	if(!strcmp(nc,ic))///��������һ��
    {
        if(!stricmp(manager[0].username,ou))num=0;
        else if(!stricmp(manager[1].username,ou))num=1;
        else if(!stricmp(manager[2].username,ou))num=2;
        else if(!stricmp(manager[3].username,ou))num=3;
        if(modify_file(num,nu,oc,nc))//���ô�ou(old_username),ic(insure_code)��
        {
            readbmp(170,570,"modified.bmp");//�޸ĳɹ�
            Delay(10);
            return 1;//���ص�¼����
        }
        else 
        {
            readbmp(170,570,"oc_wrong.bmp");
            Delay(15);
            readbmp(0,0,"setting.bmp");
            return 0;
        }
            
    }
    else 
    {
        readbmp(170,570,"mismatch.bmp");
        Delay(15);
        readbmp(0,0,"setting.bmp");
        return 0;
    }
}

/* **********************************************************************************************
 * Function:modify_file
 * Description:[����Ա��½]����Ա��Ϣfile�޸�
 * **********************************************************************************************/
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
    if(!stricmp(manager[num].code,oc))//����������ȷ
    {
        strcpy(manager[num].code,nc);//�޸���Ϣ
        strcpy(manager[num].username,nu);
    }
    else return 0;//ԭ�����������

    if((fp=fopen("MANAGER.txt","wt"))==NULL)
    {
        printf("sorry\n");
        getch();
    }    
    for(i=0;i<4;i++)
    {
        fprintf(fp,"%d %s %s\n",i+1,manager[i].code,manager[i].username);//������Ϣ�ļ�
    }
    fclose(fp);
    return 1;

}

/* **********************************************************************************************
 * Function:check_ou
 * Description:[����Ա��½] ����û��Ƿ����
 * **********************************************************************************************/
int check_ou(char *ou)
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
        Delay(16);   
        readbmp(0,0,"setting.bmp");
        return 0;//�û�������
    }  
    else
    {
        return 1;//�û�����
    }
} 

/* **********************************************************************************************
 * Function:show_avatar
 * Description:[����Ա��½]�����û�����ʾͷ��
 * **********************************************************************************************/
void show_avatar(char *u)
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
    if(!stricmp(manager[0].username,u)) 
    {
        readbmp(302,164,"m4.bmp");
    }
    else if(!stricmp(manager[1].username,u)) 
    {
        readbmp(302,164,"m3.bmp");
    }
    else if(!stricmp(manager[2].username,u)) 
    {
        readbmp(302,164,"m1.bmp");
    }
    else if(!stricmp(manager[3].username,u)) 
    {
        readbmp(302,164,"m2.bmp");
    }
    else  
    {
        readbmp(302,164,"navatar.bmp");
    }
}

/* **********************************************************************************************
 * Function:super_code
 * Description:ɾ����¼�Ŀ���
 * **********************************************************************************************/
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

/* [ͣ����¼��غ���] */
/* **********************************************************************************************
 * Function:[��¼-���]print_file();
 * Description:��һ����ʽ���ļ������ݴ�ӡ����Ӧҳ��ı�����
 * Calls:��
 * Called by:flow_manage_record();flow_manage_query();
 * Input:flag--��ǰҳ����-1;sort--���򿪵��ļ���
 * return:����1��δ���ļ�β������2���ѵ��ļ�β
 * others:��
 * **********************************************************************************************/
int print_file(int flag,int sort)
{
	FILE *fp;
	char s[11][70];
    char ch;
    int i=0;
    int r=0; //��Ϊ��������ֵ
    switch(sort)
    {
        case ALL:fp=fopen("all.txt","rt");break;
        case TODAY:fp=fopen("today.txt","rt");break;
    }
	if(fp==NULL)
    {
        printf("sorry");
        getch();
    }
    fseek(fp,flag*660L,SEEK_CUR);//���ݵ�ǰҳ���ƶ�λ��ָ��,flag��0��ʼ
    while(i<10)
    {
	   if((ch=fgetc(fp))!=EOF)//!feof(fp)
        {
            r=1;
            fseek(fp,-1L,SEEK_CUR);
            fgets(s[i],65,fp);  
            fseek(fp,2L,SEEK_CUR);//ת���ַ�\n 2
            Put_String(145,295+i*39,1,1,0x5FBF,s[i]);
            i++;
        }
       else
       {
             r=0;
             i=10;//�˳�while
       }
    }
	fclose(fp);
    return r;
}

/* **********************************************************************************************
 * Function:[��¼-ɾ��]delete_one_all();
 * Description:����ҳ����λ��,ɾ�� ͣ����¼���� ĳһ��ͣ����¼
 * Calls:create_list();delete_node();rewrite_file();destroy_list();
 * Called by:flow_manage_record();
 * Input:flag--��ǰҳ����-1;d--�ڼ���ɾ����ť���������ƫ��
 * return:��
 * others:��
 * **********************************************************************************************/
void delete_one_all(int d,int flag)
{
	int i=0;
	int test;
	Rec list=create_list(ALL);
    Rec node=list;  //ָ��ͷ��� 
    while(i<(d+10*flag) && node!=NULL) //ָ��Ҫɾ�Ľ��
    {
        i++;
        node=node->next;
	}
	delete_node(list,node);
	rewrite_file(list,ALL);
    destroy_list(list);
}

/* **********************************************************************************************
 * Function:[��¼-����]query()
 * Description:��all������������鳵λ����������query�ļ�
 * Calls:create_node();create_list();get_query_list();rewrite_file(); destroy_list();
 * Called by:flow_manage_query();
 * Input:port--��λ��
 * return:0���޸ó�λ��¼��1���м�¼
 * others:
 * **********************************************************************************************/
int query(int port)
{
	FILE *fp;
	Rec list=create_node();
	list=create_list(ALL);  //��ȫ����ʷ�ļ���������´���������
	get_query_list(list,port);  //����������ֻ����������λ�ŵĵĽ��
    if(!list->next)//�޸ó�λ��¼
    {
        return 0;
    }
    else
    {
    	rewrite_file(list,QUERY);    //���浽query�ļ�
        destroy_list(list);
        return 1;
    }

}
/* **********************************************************************************************
 * Function:[��¼-����]get_query_list()
 * Description:����λ�ž�������
 * Calls:delete_node()
 * Called by:query()
 * Input:list--ALL����;num--��λ��
 * return:��
 * others:��
 * **********************************************************************************************/
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

/* **********************************************************************************************
 * Function:[��¼-ɾ��]delete_one_query()
 * Description:����ҳ����λ�� ɾ����ȷ���ҽ���ĳһ��ͣ����¼
 * Calls:create_list();delete_query_in_all();delete_query_in_today();
 *       delete_node();rewrite_file();destroy_list();
 * Called by:flow_manage_query();
 * Input:d--�ڼ���ɾ����ť��flat--ҳ����-1
 * return:��
 * others:��
 * **********************************************************************************************/
void delete_one_query(int d,int flag)
{
	int i=0;
	Rec list=create_list(QUERY);
	Rec node=list;//ָ��ͷ���
	while(i<(10*flag+d) && node!=NULL) //ָ��Ҫɾ�Ľ��
	{
		i++;
		node=node->next;
	}
	delete_query_in_all(node);//���ڲ���ҳ��ɾ���ļ�¼Ҳ��all & history��ɾ��
    delete_query_in_today(node);//��today��Ҳɾ��������¼���򷵻�recordʱ��new_all

	delete_node(list,node);//�������������������destroy_list!���滹Ҫ��
	rewrite_file(list,QUERY);
    destroy_list(list);//��������
    node=NULL;
}
/* **********************************************************************************************
 * Function:[��¼-ɾ��]delete_query_in_all()
 * Description:��ɾ��queryʱҲ��all��ɾ��������¼
 * Calls:create_list();delete_node();rewrite_file();destroy_list();
 * Called by:delete_one_query();
 * Input:node--���鳵λ�ŵĽ��
 * return:��
 * others:��
 * **********************************************************************************************/
void delete_query_in_all(Rec node)
{
	Rec pos=NULL;
	Rec list=create_list(ALL);
	pos=list->next;
	while(((pos->port!=node->port)||(pos->carnum)!=(node->carnum) ) && pos)//�ҵ���Ҫɾ���Ľ��
    {
        pos=pos->next;
    }
	delete_node(list,pos); 
    rewrite_file(list,ALL);
    destroy_list(list);//������������
    pos=NULL;//��Ҫ��node=NULL������delete_qauery_in_today��delete_list�л�Ҫ�����node�ĵ�ַ,ָnull�Ĺ��������ܵ�����delete_one_query
}

/* **********************************************************************************************
 * Function:[��¼-ɾ��]delete_query_in_today()
 * Description:��ɾ��queryʱҲ��today��ɾ��������¼
 * Calls:create_list();delete_node();rewrite_file();destroy_list();
 * Called by:delete_one_query();
 * Input:node--���鳵λ�ŵĽ��
 * return:��
 * others:��
 * **********************************************************************************************/
void delete_query_in_today(Rec node)
{
	Rec list=create_list(TODAY);
	Rec pos=list->next;
	while(((pos->port!=node->port)||(pos->carnum)!=(node->carnum) )&& pos)//�ҵ���Ҫɾ���Ľ��
    {
        pos=pos->next;
    }
	delete_node(list,pos);  
    rewrite_file(list,TODAY);  
    destroy_list(list);//������������
    pos=NULL;    //��Ҫ��node=NULL������delete_query_in_today�л�Ҫ�����node�ĵ�ַ
}

/* **********************************************************************************************
 * Function:[ͣ��ʵ��]current_state()
 * Description:ɨ��p->a[i][j][k],��ʾͣ��״̬�� �� ���೵λ��
 * Calls:bling();fill_Rectangle();Put_String();
 * Called by:delete_one_query();
 * Input:p--����ṹ�����ݸ���λ״̬
 * return:��
 * others:��
 * **********************************************************************************************/
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

	Put_String(298,532,1,1,0x5FBF,itoa(count_port(p)[0],ch,10));  //��ʾ���೵λ����
	Put_String(298,561,1,1,0x5FBF,itoa(count_port(p)[1],ch,10));//parking
	Put_String(298,621,1,1,0x5FBF,itoa(count_port(p)[2],ch,10));//pause
    Put_String(298,591,1,1,0x5FBF,itoa(count_port(p)[3],ch,10));//book
}

/* **********************************************************************************************
 * Function:[ͣ��ʵ��] book_pause_port()
 * Description:Ԥ������ͣ��λ
 * Calls:atoi()
 * Called by:flow_manage_current()
 * Input:p--����ṹ�����ݸ���λ״̬,t--����Ա������ַ����ͳ�λ��,sort--1��Ԥ����2����ͣ
 * Output:p--����ṹ�����ݸ���λ״̬
 * return:p--����ṹ�����ݸ���λ״̬
 * others:��
 * **********************************************************************************************/
Pp * book_pause_port(char *t,Pp *p,int sort)
{
    int a=atoi(t)-111;//�ַ���000����111
    int g,s,b;
    g=a%10; //��λ
    b=a/100;//��λ
	s=(a%100)/10;//ʮλ
	if(p->a[b][s][g]==0 || p->a[b][s][g]==3) //ֻ�ܶԿ�λ����Ԥ���ĳ�λ���в���
    {
        if(sort==2)  //��ͣʹ��
        {
           p->a[b][s][g]=4;
        }
        if(sort==1 && p->a[b][s][g]==0)  //ֻ�ܶԿ�λ����Ԥ������
        {
            p->a[b][s][g]=3;
        }
    }
    return p;   
}

/* **********************************************************************************************
 * Function:[ͣ��ʵ��] count_port()
 * Description:�������״̬�ĳ�λ��
 * Calls:��
 * Called by:flow_manage_current()
 * Input:p--����ṹ�����ݸ���λ״̬
 * return:p--����ṹ�����ݸ���λ״̬
 * others:��
 * **********************************************************************************************/
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
					 case 0:count[0]++;break;  //��λ��
                     case 1:count[1]++;break;  //ͣ����
                     case 3:count[2]++;break;  //��Ԥ��
                     case 4:count[3]++;break;  //��ͣʹ��
                }
            }
    return count;
}

/* **********************************************************************************************
 * Function:[ͣ��ʵ��] bling()
 * Description: ����λ�ֿ���
 * Calls:readbmp();
 * Called by:current_state();
 * Input:i,j,k--��λ�ţ�status--��λ״̬
 * return:��
 * **********************************************************************************************/
void bling(int i,int j,int k,int status)
{
    int x;
	x=277+(214*j)+30*(k); //��������λ��ȷ��������
	switch(status)
	{
		case 0:readbmp(x,326+i*45,"green.bmp");break; //��λ ��
		case 1:readbmp(x,326+i*45,"red.bmp");break; //ͣ�� ��
		case 3:readbmp(x,326+i*45,"yellow.bmp");break; //Ԥ�� ��
		case 4:readbmp(x,326+i*45,"blue.bmp");break; //��ͣʹ�� ��
	}
	return;
}

/* [���ļ���صĺ���] */
/* **********************************************************************************************
 * Function:[��¼-���/�޸�] new_all()
 * Description: ���¼�¼�ŵ���ʷ��¼ǰ�棬�����µ�all�ļ���Ϊ�����׼��
 * Calls:create_list();rewrite_file();destroy_list(list);add_history_to_all();
 * Called by:flow_manage_record();
 * Input:��
 * return:��
 * **********************************************************************************************/
void new_all()
{
	FILE *fp;
	char ch;
	Rec list=NULL;
	Rec list2=NULL;

	list=create_list(TODAY);//���ɽ����¼����
	rewrite_file(list,ALL);//today��д��all,����������
    destroy_list(list);
	
	list2=create_list(HISTORY);
	add_history_to_all(list2);
    destroy_list(list2);
}

/* **********************************************************************************************
 * Function:[��¼-�޸�] rewrite_file()
 * Description: ��ͣ����¼�� ��¼���� �ĸ�ʽ ��д���ļ���
 * Calls:�ļ���غ���
 * Called by:delete_one_query();delete_query_in_all();delete_query_in_today();query();new_all();
 * Input:list--д���ļ���������sort--����д����ļ���
 * return:��
 * **********************************************************************************************/
void rewrite_file(Rec list,int sort)
{
	FILE *fp;
	Rec pos=list->next;
	switch(sort)
	{
		case TODAY:fp=fopen("today.txt","wt"); break;
		//case HISTORY:fp=fopen("history.txt","wt"); break; //��������дhistory�ļ�����Ϊ��historyֻ�ܽ���׷�Ӳ���
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
	//destroy_list(list);//��Ҫ�ٴ�����������������������ܻ��ᱻ����ʹ��
}

/* **********************************************************************************************
 * Function:[��¼-�޸�] add_history_to_all()
 * Description: ��history����׷�ӵ�all�ļ���
 * Calls:�ļ���غ���
 * Called by:new_all();
 * Input:list--д���ļ�������
 * return:��
 * **********************************************************************************************/
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

/* **********************************************************************************************
 * Function:[��¼-�޸�] save_new_record()
 * Description: �˳�ϵͳʱ�����г������⴦���������ͣ��ʱ��д����ʷ
 * Calls:write_ot();create_list();add_to_file();destroy_list();
 * Called by:yes();
 * Input:��
 * return:��
 * **********************************************************************************************/
void save_new_record()
{
	Rec list=NULL;
    write_ot();//��������Ϣ����today
	list=create_list(TODAY);//�õ���Ϣ�걸today������
    add_to_file(list,HISTORY);//����Ϣ�걸��today׷�ӵ�history�ļ���   
    destroy_list(list);
}

/* **********************************************************************************************
 * Function:[��¼-�޸�] write_ot()
 * Description: ���˳�ʱ����Ϊ���쳵�ĳ���ʱ�䣬���ú�����дtoday�ļ�
 * Calls:�ļ���غ���;rewrite_file(); destroy_list();
 * Called by:save_new_record()
 * Input:��
 * return:��
 * **********************************************************************************************/
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
		node.next=NULL;
		fscanf(fp,"%3d%8d%23s%23s%9d\n",&node.port,&node.carnum,node.it,node.ot,&node.time);//ÿ��������ݣ���ȡһ�������ַ������м�����
		strcpy(node.ot,format_time());//���˳�ʱ����Ϊ����ʱ��
		node.time=park_time(node.it,node.ot); //���ú�������ͣ��ʱ��
        insert_node(list,node);
    }
    fclose(fp);
    rewrite_file(list,TODAY);//��дtoday
    destroy_list(list);
}

/* **********************************************************************************************
 * Function:[��¼-�޸�] add_to_file()
 * Description: ����Ϣ׷�ӵ���Ӧ�ļ���
 * Calls:�ļ���غ���;rewrite_file(); destroy_list();
 * Called by:save_new_record()
 * Input:��
 * return:��
 * **********************************************************************************************/
void add_to_file(Rec list,int sort)
{
	FILE *fp;
    Rec pos=list->next;
    switch(sort)
    {
        case HISTORY:fp=fopen("history.txt","at");break;
        case TODAY:fp=fopen("today.txt","at");break;
        //case ALL:fp=fopen("all.txt","at");break;
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
}

/* **********************************************************************************************
 * Function:[��¼-��ȡ] create_list()
 * Description: ���ļ��ж�ȡ��¼��������
 * Calls:�ļ���غ�����create_node();insert_node();
 * Called by:drop_car1(int cn);drop_car2(int cn);save_new_record(); 
 *           new_all();delete_query_in_today();delete_one_query();query();delete_one_all();
 * Input:sort--�ļ���
 * return:list--���ɵ�������ͷ���
 * **********************************************************************************************/
Rec create_list(int sort)
{
    FILE *fp;
	char ch;
	unsigned u;
    Rec list=create_node();
	record node;
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
			 fscanf(fp,"%3d%8d%23s%23s%9d\n",&node.port,&node.carnum,node.it,node.ot,&node.time);//ÿ��������ݣ���ȡһ�������ַ������м�����
			 insert_node(list,node);
    }
	fclose(fp);
	return list;
}


/* **********************************************************************************************
 * Function:[��¼-��ȡ] drop_car1()
 * Description: ȡ��(��todayɾ��ȡ�߳��ļ�¼)
 * Calls:�ļ���غ���;create_node();insert_node()
 * Called by: car_message()
 * Input:cn--����
 * return:��
 * **********************************************************************************************/
void drop_car1(int cn)
{
    Rec list=create_list(TODAY);
    Rec pos=list;
    while(pos->next->port!=cn)
    {
        pos=pos->next;
    }
    delete_node(list,pos->next);
    rewrite_file(list,TODAY);
    destroy_list(list);
    new_all();
    pos=NULL;
}

/* **********************************************************************************************
 * Function:[��¼-��ȡ] drop_car2()
 * Description: ȡ��(��ȡ�ߵĳ�����Ϣд����ʷ��¼)
 * Calls:�ļ���غ���;create_node();insert_node()
 * Called by: car_message()
 * Input:cn--����
 * return:��
 * **********************************************************************************************/
void drop_car2(int cn)
{
    Rec list=create_list(TODAY);
    Rec pos=list;   
    char git[20];//GET IN TIME
    while(pos->next->port!=cn)
    {
        pos=pos->next;
    }
    pos->next->next=NULL;
    strcpy(git,pos->next->it);
    strcpy(pos->next->ot,format_time());//���˳�ʱ����Ϊ����ʱ��
    pos->next->time=park_time(git,pos->next->ot); //���ú�������ͣ��ʱ��
	//pos->time=park_time(pos->next->it,pos->next->ot); //���ú�������ͣ��ʱ��
    add_to_file(pos,HISTORY);//�������������Ӧ��������ͷ���
    destroy_list(list);
    pos=NULL;
}

/* [���õĹ��ܺ���] */
/* **********************************************************************************************
 * Function:create_node
 * Description:����һ�����
 * **********************************************************************************************/
Rec create_node(void)
{
    Rec node=(Rec)malloc(sizeof(record));
    if(node==NULL)
    {
        printf("sorry\n");
        getch();
    }
    node->next=NULL;
    return node;
}

/* **********************************************************************************************
 * Function:delete_node
 * Description:ɾ��һ�����
 * **********************************************************************************************/
void delete_node(Rec list,Rec node)
{
    Rec pos=list;//���ܸ�list���������
    Rec temp=node;//����node��ַ������������޸ģ�����Ҫ�����ĵ�ַ��
    if(pos->next==NULL)
	{return NULL;}
    while(pos->next!=temp && pos->next!=NULL)
    {
        pos=pos->next;
    }
    if(pos->next!=NULL)
    {
		pos->next=temp->next;
		free(temp);
		temp->next=NULL;
    }
    pos=NULL;
	//else return NULL; //û�ҵ���¼
	//return list;
}

/* **********************************************************************************************
 * Function:insert_node
 * Description:����β���������µĽ��
 * **********************************************************************************************/
void insert_node(Rec list,record park)
{
    Rec pos=list;//Ҫ����ͷ���
    Rec node=create_node();
	node->carnum=park.carnum;
	node->port=park.port;
	strcpy(node->it,park.it);
	strcpy(node->ot,park.ot);
	node->time=park.time;
	while(pos->next!=NULL)   //�ҵ�����β
	{
		pos=pos->next;
	}
	node->next=NULL;
	pos->next=node;       //�ٵ���ָ����
}

/* **********************************************************************************************
 * Function:destroy_list
 * Description:��������
 * **********************************************************************************************/
void destroy_list(Rec list)
{
	int i;
    Rec node=list;
	while(list)
	{
        list=list->next;//��list��ָ���һ�����
        free(node);
        node=list;
    }
    node=NULL;
}

/* **********************************************************************************************
 * Function:input
 * Description:���������ʾ�����ַ���
 * **********************************************************************************************/
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
		//if(k==ESC) break; //ǧ���ܰ�esc��break�������ܱ����ܲ�������
        switch(k)
        {
            case ENTER: if(i==0) continue;  //��û�������κ��ַ��������ȴ�����
                        else {m=1;break;}  //�������ַ�  �˳�switch  m��1
            case BACKSPACE: if(i>0)       //�˸�
                            {
                                s[--i]='\0';
                                fill_Rectangle(button->x1,button->y1,button->x2,button->y2,0x5FBF);
								Put_String(button->x1+4,button->y1+3,1,1,0,s); 
                                continue;
                            }
            default: s[i]=k;//�κ�һ���ַ�����������Ӧ��ASCII��ʾ
                     s[i+1]='\0';
					 Put_String((button->x1)+4,button->y1+3,1,1,0,s);   
                     i++;
        }
        if(m)  break;   //�˳�while
    }
    return s; //���������ݴ��ص�½����
}

/* **********************************************************************************************
 * Function:format_time
 * Description:����ͣ��ʱ��ĸ�ʽ
 * **********************************************************************************************/
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

/* **********************************************************************************************
 * Function:rand_bi()
 * Description:����һ����λ�������--����
 * **********************************************************************************************/
int rand_bi()
{
    int d;
    d=rand()%90+10;
    return d;
}

/* **********************************************************************************************
 * Function:park_time
 * Description:����ͣ��ʱ��
 * **********************************************************************************************/
int park_time(char *it,char *ot) 
{
    int it1,it2,ot1,ot2,time;  //1��Сʱ2�Ƿ���
    char ch[20];
    sscanf(ot,"%*[^-]-%d:%d",&ot1,&ot2);  //����
    sscanf(it,"%*[^-]-%d:%d",&it1,&it2);  //����
    time=60*(ot1-it1)+ot2-it2;
    if(time==0) {time=1;}
    return time;
    /*  
    time_ time2=time(NULL);
    int time=difftime(time2,time1);  //��λ��s
    time=(int)ceil(time/60); //ceil������ȡ������ ͣ��ʱ������Ϊ��λ
    return time;*/
}




