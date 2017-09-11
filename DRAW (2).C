#include"draw.h"

/* **************************************************************************
 * Function:Set_Video_Mode
 * Description:������ʾģʽ�ĺ���.
 *             ���������趨Ϊ SVGAʱ����Ļ����������Ϊͼ��ģʽ;
 *             �����趨ΪTEXT_MODEʱ���ص�������ı�ģʽ
 * **************************************************************************/
void Set_Video_Mode(int mode)
 {
	 union REGS r;
     r.x.ax=0x4f02;
     r.x.bx=mode;
     int86(0x10,&r,&r);    //ͨ��10h�ж��趨��ʾģʽ
 }

/* **************************************************************************
 * Function:selectpage
 * Description:��ҳ����
 * *************************************************************************/
void selectpage(int page) 
{
  union REGS r;
  r.x.ax=0x4f05;
  r.x.bx=0x00;
  r.x.dx=page;
  int86(0x10,&r,&r);
}

/* **************************************************************************
 * Function:Plot
 * Description:���㺯��
 * **************************************************************************/
void Plot(int x, int y, char color) 
{    
   unsigned short far *video_buffer=(unsigned short far *)0xA0000000L;
   long pos=(y*1024L+x);
   unsigned int page=pos*2/65536L; //һ��λ���ֽ�����64*1024
   selectpage(page);
   *(video_buffer+pos)=color;
}

/* **************************************************************************
 * Function:Get_Plot
 * Description:ȡ�����ɫ
 * *************************************************************************/
int Get_Plot(int x,int y)             
{ 
	char  color;
    long pos=(y*1024L+x);
    unsigned int page=pos*2/65536L;
    unsigned short far *video_buffer=(unsigned short far *)0xA0000000L;
    
    selectpage(page);
	color=*((unsigned short far *)(video_buffer+pos));
    return color;
}

/* **************************************************************************
 * Function:Line
 * Description:���ߺ���
 * **************************************************************************/
void Line(int x1,int y1,int x2,int y2,int color)        
{
   int dx,dy,x_inc=1,y_inc=1,x,y;
   int index,error=0;
   x=x1;y=y1;
   dx=x2-x1;dy=y2-y1;
   if(dx<0)
	{
	 dx=-dx;
	 x_inc=-1;
	}
   if(dy<0)
	{
	 dy=-dy;
	 y_inc=-1;
	}
	if(dx>dy)
	{
		 for(index=0;index<=dx;index++)
		 {
		    Plot(x,y,color);
		    error+=dy;
		    x+=x_inc;
		    Plot(x,y,color);
		    if(error>dx)
		    {
				error-=dx;
				y+=y_inc;
				Plot(x,y,color);
		    }
		 }
	}
	else
		{
		 for(index=0;index<=dy;index++)
			   {
				Plot(x,y,color);
				error+=dx;
				y+=y_inc;
				Plot(x,y,color);
				if(error>dy)
					{
					 error-=dy;
					 x+=x_inc;
					 Plot(x,y,color);
					}
			   }
		}
}

/* **************************************************************************
 * Function:Rectangle
 * Description:�����κ���
 * *************************************************************************/
void Rectangle(int x1,int y1,int x2,int y2,int color)       
{
  Line(x1,y1,x1,y2,color);
  Line(x1,y2,x2,y2,color);
  Line(x2,y2,x2,y1,color);
  Line(x2,y1,x1,y1,color);
}

/* **************************************************************************
 * Function:fill_Rectangle
 * Description:��ʵ�ľ��κ���
 * *************************************************************************/
void fill_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    int i,j;
    for(i=0;i<y2-y1;i++)
    {
        Line(x1,y1+i,x2,y1+i,color);
    }

}

/* **************************************************************************
 * Function:readbmp
 * Description:��BMP�����߼��Դ�
 * *************************************************************************/
void readbmp(int x,int y,char *filename)    
{
    	int i,j;
    	FILE *fp;
    	long Width,Height,oldpage,newpage;
    	unsigned long position;
    	short far *buffer=NULL;
    	short far *video_buffer=(short far *)0xA0000000L;    //��ʼ��ָ��VRAM��ָ��
    	if((fp=fopen(filename,"rb"))==NULL)
    	{
		    printf("Cannot install image\n%s",filename);
        	getch();
        	return;
    	}
    	fseek(fp,18,SEEK_SET);
    	fread(&Width,sizeof(long),1,fp);
    	fread(&Height,sizeof(long),1,fp);
    	buffer=(short *)malloc(Width*2);       //����һ��ͼ��Ĵ洢�ռ䡣ÿ�����ص������ֽ�
    	if(buffer==NULL)
    	{
        	printf("Malloc error!");
        	getch();
        	return;
    	}
    	fseek(fp,70,SEEK_SET);         
    	oldpage=((Height-1+y)*(long)1024+x)*2/65536L;    //��ʼ��ҳ��
    	newpage=oldpage;
    	selectpage(oldpage);
    	for(i=Height-1;i>=0;i--)            //�������϶�ȡ����BMPͼƬ�����й�
   	    {
        	fread(buffer,Width*2,1,fp);   //����һ��ͼ����Ϣ���ڴ�
        	for(j=0;j<Width;j++)
        	{
            		position=((i+y)*(long)1024+j+x);
            		newpage=position*2/65536;
            		if(newpage!=oldpage)            //���û�ҳ���� �Ż�����һ��ҳ��Ͳ���ҳ������һ��ҳ��Ż�ҳ
            		{
                		selectpage(newpage);
                		oldpage=newpage;
            		}
            		*(video_buffer+(i+y)*1024+x+j)=buffer[j];      //���ڴ��е�ͼ����Ϣ������VRAM      
        	}
    	}
    	fclose(fp);
    	free(buffer);
}

/* **************************************************************************
 * Function:part_bmp
 * Description:��ʾ����ͼƬ
 * **************************************************************************/
void part_bmp(int x,int y,char *filename)
{
    	int i,j;
    	FILE *fp;
    	long Width,Height,oldpage,newpage;
    	unsigned long position;
    	short far *buffer;
    	short far *video_buffer=(short far *)0xA0000000L;    //��ʼ��ָ��VRAM��ָ��

    	if((fp=fopen(filename,"rb"))==NULL)
    	{
		printf("Cannot install image\n%s",filename);
        	getch();
        	return;
    	}

    	fseek(fp,18,SEEK_SET);
    	fread(&Width,sizeof(long),1,fp);
    	fread(&Height,sizeof(long),1,fp);

    	buffer=(short *)malloc(Width*2);       //����һ��ͼ��Ĵ洢�ռ䡣ÿ�����ص������ֽ�

    	if(buffer==NULL)
    	{
        	printf("Malloc error!");
        	getch();
        	return;
    	}
    	fseek(fp,70,SEEK_SET);         
    	oldpage=((Height-1+y)*(long)1024+x)*2/65536L;    //��ʼ��ҳ��
    	newpage=oldpage;
    	selectpage(oldpage);
    	for(i=Height-1;i>=0;i--)            //�������϶�ȡ����BMPͼƬ�����й�
   	    {
        	fread(buffer,Width*2,1,fp);   //����һ��ͼ����Ϣ���ڴ�
        	for(j=0;j<Width;j++)
        	{
            		position=((i+y)*(long)1024+j+x);
            		newpage=position*2/65536;
            		if(newpage!=oldpage)            //���û�ҳ���� �Ż�����һ��ҳ��Ͳ���ҳ������һ��ҳ��Ż�ҳ
            		{
                		selectpage(newpage);
                		oldpage=newpage;
            		}
					if(buffer[j])//�����ص㲻�Ǻ�ɫ������ʾ
                    {
            		    *(video_buffer+(i+y)*1024+x+j)=buffer[j];      //���ڴ��е�ͼ����Ϣ������VRAM   
                    }   
        	}
    	}
    	fclose(fp);
    	free(buffer);
}

/* **************************************************************************
 * Function:Delay
 * Description:�ӳٺ���
 * **************************************************************************/
void Delay(int clicks)
{
    unsigned int far *clock=(unsigned int far *)0x0000046CL;
    unsigned int now;
    now=*clock;
    while(abs(*clock-now)<clicks){}
}

/* **************************************************************************
 * Function:Dark
 * Description:������
 * **************************************************************************/
void Dark()                             
{
    int i;
    unsigned long pos;
    short far *video_buffer=(short far *)0xA0000000L;
    char np=0;
    selectpage(np);
    for(i=0;i<37;i++)
    {
        for(pos=0;pos<32768;pos=pos+2)
        {
            video_buffer[pos]=0;
        }
        np++;
        selectpage(np);
    }
    return;
}