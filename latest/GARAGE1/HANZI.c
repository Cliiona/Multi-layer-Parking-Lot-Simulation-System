#include"hanzi.h"
void GetHz16(char ch0,char ch1,char *bitdata)       /*中文字符读取*/     //楷体
{
    FILE *stream;
    long fpos;
    fpos=32L*(((unsigned char)ch0-161)*94+((unsigned char)ch1-161)); //取中文在文件中的偏移
    if((stream=fopen("hzk16k","rb"))==NULL)
    {
        printf("Open hzk16 error!\n");
        exit (0);
    }
	fseek(stream,fpos,SEEK_SET);//到该中文便宜位置
    fread(bitdata,32,1,stream); //读取32个字节
    fclose(stream); //关闭字库文件
}

void Write_Hz16(char ch0,char ch1,int x,int y,char color)//中文字符显示 楷体
{   
    unsigned char bit[8]={128,64,32,16,8,4,2,1};
    register int i,j,k;
    unsigned vpos;
    char bitdata[32];
	GetHz16(ch0,ch1,bitdata);//调用文字读取函数
    for(i=0;i<16;i++)
        for(j=0;j<8;j++)
        {
            if(bitdata[2*i]&bit[j])//判断当前为是否为1
                Plot(x+j,i+y,color);//向屏幕写入一个点
            if(bitdata[2*i+1]&bit[j])
				Plot(x+8+j,i+y,color);
        }
}
void WriteHz16(char *str ,int x,int y,char color) // ！显示楷体汉字的函数 楷体 
{
    int num,i,j,xx;
	unsigned char s0,s1;
    num=strlen(str);
    xx=x;
    for(i=0;i<num;i+=2)
    {
		Write_Hz16(str[i],str[i+1],xx,y,color);
        xx+=16;
    }

}
void GetHz16s(char ch0,char ch1,char *bitdata)       /*中文字符读取*/  //宋体
{
    FILE *stream;
    long fpos;
    fpos=32L*(((unsigned char)ch0-161)*94+((unsigned char)ch1-161)); //取中文在文件中的偏移
    if((stream=fopen("hzk16c","rb"))==NULL)
    {
        printf("Open hzk16c error!\n");
        exit (0);
    }
	fseek(stream,fpos,SEEK_SET);//到该中文便宜位置
    fread(bitdata,32,1,stream); //读取32个字节
    fclose(stream); //关闭字库文件
}
void Write_Hz16s(char ch0,char ch1,int x,int y,char color)//中文字符显示 宋体
{   
    unsigned char bit[8]={128,64,32,16,8,4,2,1};
    register int i,j,k;
    unsigned vpos;
    char bitdata[32];
	GetHz16s(ch0,ch1,bitdata);//调用文字读取函数
    for(i=0;i<16;i++)
        for(j=0;j<8;j++)
        {
            if(bitdata[2*i]&bit[j])//判断当前为是否为1
                Plot(x+j,i+y,color);//向屏幕写入一个点
            if(bitdata[2*i+1]&bit[j])
				Plot(x+8+j,i+y,color);
        }
}
void WriteHz16s(char *str ,int x,int y,char color) // ！显示汉字的函数 宋体
{
    int num,i,j,xx;
	unsigned char s0,s1;
    num=strlen(str);
    xx=x;
    for(i=0;i<num;i+=2)
    {
		Write_Hz16s(str[i],str[i+1],xx,y,color);
        xx+=16;
    }

}

void ShowHz(int left,int top,unsigned char byte1,unsigned  char byte2,int color)
{
   FILE *hzk;
   unsigned char buf[32];
   unsigned char mark;
   long p;
   int i,j,y;
   int quma,weima;
   hzk=fopen("hzk16k","rb");
   if((hzk==NULL))
   {
			outtextxy(10,10,"Cannot open hzk file!Press any key to quit...");
			exit(1);     
   }
   if((byte1>=0xa1&&byte1<=0xfe)&&(byte2>=0xa1&&byte2<=0xfe))
  {                             
		quma=byte1-0xa0;
		weima=byte2-0xa0;
		p=(quma-1)*94+weima-1;
		p*=32;
		fseek(hzk,(long)p,SEEK_SET);
		fread(buf,sizeof(unsigned char),32,hzk);
		fclose(hzk);
		for(i=0,y=top;i<31;i+=2,y++)
		{
			for(mark=0x80,j=0;mark>0;mark=mark>>1,j++)
			{
				if((buf[i]&mark)!=0)putpixel(left+j,y,color);
				if((buf[i+1]&mark)!=0)putpixel(left+j+8,y,color);
			}
		}
  } 
  fclose(hzk);
}
void outhzxy(int x,int y,char *str,int color)
{
    int oldcolor;
    oldcolor=getcolor();
    setcolor(color);
    while(*str)
   {
			if(((unsigned char)*str>=0xa1&&(unsigned char)*str<=0xfe)&&((unsigned char)*(str+1)>=0xa1&&(unsigned char)*(str+1)<=0xfe))
			{
				ShowHz(x,y,*str,*(str+1),color);
				str+=2;
				x+=16+2;
				moveto(x,y);
			}
		else
		{
			char enstr[2];
			moveto(x,y);
			*enstr=*str;
			*(enstr+1)='\0';
			settextstyle(0,0,1);
			outtextxy(x,y+4,enstr);
			x+=8+1;
			str++;
		}
   }
   setcolor(oldcolor);
}


void Blit_Char(int xc,int yc,char c,int color,int trans_flag)
{
    unsigned char far *video_buffer=(char far *)0xA0000000L;
    unsigned char far *rom_char_set=(char far *)0xF000FA6EL;
    int offset,x,y;
    char far *work_char;
    unsigned char bit_mask=0x80;
    work_char=rom_char_set+c*CHAR_HEIGHT;
    offset=(yc<<8)+(yc<<6)+xc;
    for(y=0;y<CHAR_HEIGHT;y++)
    {
        bit_mask=0x80;
        for(x=0;x<CHAR_WIDTH;x++)
        {
            if((*work_char&bit_mask))
            video_buffer[offset+x]=color;
            else if(!trans_flag)
                video_buffer[offset+x]=0;
            bit_mask=(bit_mask>>1);
        }
        offset+=SCREEN_WIDTH;
        work_char++;
    }
}

void Blit_String(int x,int y,int color,char *string,int trans_flag)          /*打出字符串，trans_flag 不明内涵，先填1*/
{
    int index;
    for(index=0;string[index]!=0;index++)
    {
        Blit_Char(x+(index<<3),y,string[index],color,trans_flag);
    }
}


