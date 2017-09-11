#include"draw.h"

/* **************************************************************************
 * Function:Set_Video_Mode
 * Description:设置显示模式的函数.
 *             当函数被设定为 SVGA时，屏幕将函数设置为图形模式;
 *             当被设定为TEXT_MODE时，回到最初的文本模式
 * **************************************************************************/
void Set_Video_Mode(int mode)
 {
	 union REGS r;
     r.x.ax=0x4f02;
     r.x.bx=mode;
     int86(0x10,&r,&r);    //通过10h中断设定显示模式
 }

/* **************************************************************************
 * Function:selectpage
 * Description:换页函数
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
 * Description:画点函数
 * **************************************************************************/
void Plot(int x, int y, char color) 
{    
   unsigned short far *video_buffer=(unsigned short far *)0xA0000000L;
   long pos=(y*1024L+x);
   unsigned int page=pos*2/65536L; //一个位面字节数：64*1024
   selectpage(page);
   *(video_buffer+pos)=color;
}

/* **************************************************************************
 * Function:Get_Plot
 * Description:取点的颜色
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
 * Description:画线函数
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
 * Description:画矩形函数
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
 * Description:画实心矩形函数
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
 * Description:将BMP放入逻辑显存
 * *************************************************************************/
void readbmp(int x,int y,char *filename)    
{
    	int i,j;
    	FILE *fp;
    	long Width,Height,oldpage,newpage;
    	unsigned long position;
    	short far *buffer=NULL;
    	short far *video_buffer=(short far *)0xA0000000L;    //初始化指向VRAM的指针
    	if((fp=fopen(filename,"rb"))==NULL)
    	{
		    printf("Cannot install image\n%s",filename);
        	getch();
        	return;
    	}
    	fseek(fp,18,SEEK_SET);
    	fread(&Width,sizeof(long),1,fp);
    	fread(&Height,sizeof(long),1,fp);
    	buffer=(short *)malloc(Width*2);       //分配一行图像的存储空间。每个像素点两个字节
    	if(buffer==NULL)
    	{
        	printf("Malloc error!");
        	getch();
        	return;
    	}
    	fseek(fp,70,SEEK_SET);         
    	oldpage=((Height-1+y)*(long)1024+x)*2/65536L;    //初始化页码
    	newpage=oldpage;
    	selectpage(oldpage);
    	for(i=Height-1;i>=0;i--)            //从下往上读取，与BMP图片构造有关
   	    {
        	fread(buffer,Width*2,1,fp);   //读入一行图像信息到内存
        	for(j=0;j<Width;j++)
        	{
            		position=((i+y)*(long)1024+j+x);
            		newpage=position*2/65536;
            		if(newpage!=oldpage)            //调用换页函数 优化：在一个页面就不换页，不在一个页面才换页
            		{
                		selectpage(newpage);
                		oldpage=newpage;
            		}
            		*(video_buffer+(i+y)*1024+x+j)=buffer[j];      //将内存中的图像信息逐点读入VRAM      
        	}
    	}
    	fclose(fp);
    	free(buffer);
}

/* **************************************************************************
 * Function:part_bmp
 * Description:显示部分图片
 * **************************************************************************/
void part_bmp(int x,int y,char *filename)
{
    	int i,j;
    	FILE *fp;
    	long Width,Height,oldpage,newpage;
    	unsigned long position;
    	short far *buffer;
    	short far *video_buffer=(short far *)0xA0000000L;    //初始化指向VRAM的指针

    	if((fp=fopen(filename,"rb"))==NULL)
    	{
		printf("Cannot install image\n%s",filename);
        	getch();
        	return;
    	}

    	fseek(fp,18,SEEK_SET);
    	fread(&Width,sizeof(long),1,fp);
    	fread(&Height,sizeof(long),1,fp);

    	buffer=(short *)malloc(Width*2);       //分配一行图像的存储空间。每个像素点两个字节

    	if(buffer==NULL)
    	{
        	printf("Malloc error!");
        	getch();
        	return;
    	}
    	fseek(fp,70,SEEK_SET);         
    	oldpage=((Height-1+y)*(long)1024+x)*2/65536L;    //初始化页码
    	newpage=oldpage;
    	selectpage(oldpage);
    	for(i=Height-1;i>=0;i--)            //从下往上读取，与BMP图片构造有关
   	    {
        	fread(buffer,Width*2,1,fp);   //读入一行图像信息到内存
        	for(j=0;j<Width;j++)
        	{
            		position=((i+y)*(long)1024+j+x);
            		newpage=position*2/65536;
            		if(newpage!=oldpage)            //调用换页函数 优化：在一个页面就不换页，不在一个页面才换页
            		{
                		selectpage(newpage);
                		oldpage=newpage;
            		}
					if(buffer[j])//该像素点不是黑色，则显示
                    {
            		    *(video_buffer+(i+y)*1024+x+j)=buffer[j];      //将内存中的图像信息逐点读入VRAM   
                    }   
        	}
    	}
    	fclose(fp);
    	free(buffer);
}

/* **************************************************************************
 * Function:Delay
 * Description:延迟函数
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
 * Description:暗处理
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
