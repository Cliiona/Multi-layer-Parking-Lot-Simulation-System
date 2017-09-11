#include"draw.h"

void Set_Video_Mode(int mode) //设置显示模式的函数
 {
	  union REGS r;
         r.x.ax=0x4f02;
         r.x.bx=mode;
         int86(0x10,&r,&r);    //通过10h 中断设定显示模式
 }
//当函数被设定为 SVGA时，屏幕将函数设置为图形模式，当被设定为TEXT_MODE时，回到最初的文本模式

void selectpage(int page) //换页函数
{
  union REGS r;
  r.x.ax=0x4f05;
  r.x.bx=0x00;
  r.x.dx=page;
  int86(0x10,&r,&r);
}

void Plot(int x, int y, char color) /*画点函数*/
{    
   unsigned short far *video_buffer=(unsigned short far *)0xA0000000L;
   long pos=(y*1024L+x);
   unsigned int page=pos*2/65536L; //一个页面字节数：64*1024
   selectpage(page);
   *(video_buffer+pos)=color;
}
int Get_Plot(int x,int y)             /*取点的颜色*/
{ 
	char  color;
    long pos=(y*1024L+x);
    unsigned int page=pos*2/65536L;
    unsigned short far *video_buffer=(unsigned short far *)0xA0000000L;
    
    selectpage(page);
	color=*((unsigned short far *)(video_buffer+pos));
    return color;
}
void Line(int x1,int y1,int x2,int y2,int color)        //画线函数，待优化
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

void Rectangle(int x1,int y1,int x2,int y2,int color)       //画矩形函数待优化
{
  Line(x1,y1,x1,y2,color);
  Line(x1,y2,x2,y2,color);
  Line(x2,y2,x2,y1,color);
  Line(x2,y1,x1,y1,color);
}

void fill_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    int i,j;
    for(i=0;i<y2-y1;i++)
    {
        Line(x1,y1+i,x2,y1+i,color);
    }

}
void readbmp(int x,int y,char *filename)    //将BMP放入逻辑显存
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

void Delay(int clicks)
{
unsigned int far *clock=(unsigned int far *)0x0000046CL;
unsigned int now;
now=*clock;
while(abs(*clock-now)<clicks){}
}
void Behind_image(int x,int y,int x0,int y0,int *buffer[])        //x,y为左上角坐标，x0,y0为需要保存的画面大小,buffer用来存各个像素点的数组
{
    int i,j;
    unsigned long pos;
    char oldpage,newpage;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=(y*1024L+x)/32768;
    newpage=oldpage;
    selectpage(newpage);
    for(i=0;i<y0;i++)
    {
        for(j=0;j<x0;j++)
        {
            pos=(i+y)*(1024L)+j+x;
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            buffer[i][j]=video_buffer[pos%65536];
        }
    }
    return;
   
    
}						  
void Draw_image(int x,int y,int x0,int y0,int *buffer[]) //x,y为左上角坐标，x0,y0为需要显示的画面大小,buffer用来存各个像素点的数组
{   
    int i,j;
    char oldpage,newpage;
    unsigned long pos;
    short far *video_buffer=(short far *)0xA0000000L;
    oldpage=(y*(1024L)+x)/32768;//页面初始化
    newpage=oldpage;
    selectpage(oldpage);
    for(i=0;i<y0;i++)
    {
        for(j=0;j<x0;j++)
        {
            pos=(i+y)*(1024L)+j+x;
            newpage=pos/32768;
            if(oldpage!=newpage)
            {
                selectpage(newpage);
                oldpage=newpage;
            }
            video_buffer[pos%65536]=buffer[i][j];
        }
    }
    return;
   

}
/*屏幕操作*/
void Dark()                              /*暗*/
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
