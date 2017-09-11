#include "manage.h"

void input(BUTTON *button,char *s)
{
    fill_Rectangle((button->x1)/2+5,button->y1,(button->x2)/2,button->y2,7);
    int k;
    int m;
    int i=0;
    while(1)
    {
        m=0;
        k=bioskey(0);
		if(k==ESC) break;
        switch(k)
        {
            case ENTER: if(i==0) continue;  //若还没有输入任何东西，继续输入
                        else {m=1;break;}  //退出switch  m置1
            case BACKSPACE: if(i>0)       //退格
                            {
                                s[--i]='\0';
                                fill_Rectangle((button->x1)/2+55,button->y1,(button->x2)/2,button->y2,7);
								Blit_String((button->x1)/2,button->y1,0,s,1);//---------------x 2倍
                                continue;
                            }
            default: s[i]=k;
                     s[i+1]='\0';
					 Blit_String((button->x1)/2,button->y1,0,s,1);  //---------------x 2倍
                     i++;
        }
        if(m)  break;   //退出while
    }

}

void readfile(int m)
{
	FILE *fp;
	char *s,*v,*u;
    char ch;
    //int i;
    fp=fopen("myfile.txt","at");
    fputs("\n",fp);
    fputs("1-3-3      02      2h",fp);
    fclose(fp);

    fp=fopen("myfile.txt","rt");
    fgets(s,22,fp); //实际读取的字符数是16-1
    fseek(fp,2,SEEK_CUR);//转义字符\n占两字节
    fgets(v,22,fp);
    fseek(fp,2,SEEK_CUR);
    fgets(u,22,fp);
    fclose(fp);
 
    Blit_String(25,92,0,s,1);
    Blit_String(25,107,0,v,1);
    Blit_String(25,122,0,u,1);
	fclose(fp);
    return;

}

void park()
{
    /*  
    time_t t;
    RECORD port[75];  //定义实时记录 结构体
    port.pout_num=3;
    time(&timep);
    strcpy(port[port.pout_num].check_in_time,ctime(&t));
    strcpy(port[port.pout_num].p_num,);
    */
}
