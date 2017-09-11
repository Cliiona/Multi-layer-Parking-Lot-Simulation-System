#include"draw.h"

 void Set_Video_Mode(int mode) //设置显示模式的函数
 {
	 union REGS inregs ,outregs; //定义输入和返回寄存器
	 inregs.h.ah=0; //ah 存放功能号0h 表示进入视频模式设定
     inregs.h.al=(unsigned char) mode ;    //al存放要设定的视频模式
	 int86(0x10,&inregs,&outregs);     //通过10h 中断设定显示模式
 }
//当函数被设定为 VGA256时，屏幕将函数设置为图形模式，当被设定为TEXT_MODE时，回到最初的文本模式

void Plot(int x, int y, char color) /*画点函数*/
{    
     unsigned char far * video_buffer=(char far *)0xA0000000L;
     video_buffer[(y<<8)+(y<<6)+x]=color;
}

int Get_Plot(int x,int y)             /*取点的颜色*/
{ 
    int color;
    unsigned char far * video_buffer=(char far *)0xA0000000L;
    color=video_buffer[(y<<8)+(y<<6)+x];
    return color;
}

void line(int x0,int y0,int x1,int y1,char color)     /*画任意线的函数*/
{   unsigned char far * video_buffer=(char far *)0xA0000000L;
	int dx,dy,x_inc,y_inc,error=0,index;
    unsigned char far *vb_start=video_buffer; //设定起始显存位置
	vb_start=vb_start+((unsigned int )y0<<6)+((unsigned int) y0<<8)+(unsigned int) x0;//以下获得斜线x,y方向上的偏移，同时明确各自偏移方向
	dx=x1-x0;
    dy=y1-y0;
    if(dx>=0) x_inc=1;
    else {x_inc=-1;
		dx=-dx;
         }
    if(dy>=0) y_inc=320;
    else{ y_inc=-320;
         dy=-dy;
    }
    if(dx>dy)
    { //以下如果x长于y的画点循环方法
        for(index=0;index<=dx;index++)
        { *vb_start=color;//设定点的颜色
            error+=dy;
            if(error>dx){//每循环dx/dy次，才满足此条件
                error-=dx;
                vb_start+=y_inc;//y方向增加单位增量，画点
            }
            vb_start+=x_inc;//x方向增加单位增量，画点

        }
    }
    else{//以下如果y长于x的画点循环方法
          for(index=0;index<=dy;index++)
        {
        *vb_start=color;
        error+=dx;
         if(error>0)
        {
            error-=dy;
            vb_start+=x_inc;
        }vb_start+=y_inc;
      
        }      
    }
}

void Rectangle(int x1,int y1,int x2,int y2,char color)
{   
    line(x1,y1,x2,y1,color);
    line(x1,y1,x1,y2,color);
    line(x2,y1,x2,y2,color);
    line(x1,y2,x2,y2,color);
}

//填充就用循环画线或者点
void Set_BMP_Palette_Register(int index,RGB_BMP_ptr color)
{
outp(PALETTE_MASK,0xff);
outp(PALETTE_REGISTER_WR,index);
outp(PALETTE_DATA,color->red);
outp(PALETTE_DATA,color->green);
outp(PALETTE_DATA,color->blue);
}

void Check_Bmp(bmp_picture_ptr bmp_ptr)
{
if(bmp_ptr->file.bfType!=0x4d42)
{
	printf("Not a BMP file!\n");
exit(1);
}
if(bmp_ptr->info.biCompression!=0)
{
printf("Can not display a compressed BMP file!\n");
exit(1);
}
if(bmp_ptr->info.biBitCount!=8)
{
printf("Not a index 16color BMP file!\n");

exit(1);
}
}


void BMP_Load_Screen(char *bmp) 
{unsigned char far * video_buffer=(char far *)0xA0000000L;
 int i,fp;
 bmp_picture bmp256;
 char *file_name;
 if ((fp=open(bmp,O_RDONLY))==1)
	 return;

 read(fp,&bmp256.file,sizeof(bitmapfile));
 read(fp,&bmp256.info,sizeof(bitmapinfo));

 Check_Bmp((bmp_picture_ptr)&bmp256);//u can ingore it
// lseek(fp,54,0);

 for (i=0;i<256;i++)
 {
  read(fp,&bmp256.palette[i].blue,1);
  read(fp,&bmp256.palette[i].green,1);
  read(fp,&bmp256.palette[i].red,1);
  read(fp,&bmp256.palette[i].reserved,1);
  bmp256.palette[i].blue=bmp256.palette[i].blue>>2;
  bmp256.palette[i].green=bmp256.palette[i].green>>2;
  bmp256.palette[i].red=bmp256.palette[i].red>>2;
 }
 for (i=0;i<256;i++)
   Set_BMP_Palette_Register(i,(RGB_BMP_ptr)&bmp256.palette[i]);

 for(i=SCREEN_HEIGHT-1;i>=0;i--)
 {
	lseek(fp,1078+(long)(SCREEN_HEIGHT-i-1)*SCREEN_WIDTH,0);
	read(fp,&video_buffer[i*SCREEN_WIDTH],SCREEN_WIDTH);
 }
 close(fp);

}




