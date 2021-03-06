#include"hanzi.h"
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

void Read_eng(char key,unsigned char *buf)
{
int handle;
long address;
handle=open("Asc16",O_RDONLY|O_BINARY);
address=key*16l;
lseek(handle,address,SEEK_SET);
read(handle,buf,16);
close(handle);
}

void Put_eng_Size(int cx,int cy,int xsize,int ysize,char key,int fcolor)
{
	int a,b,o,k;
	unsigned char buf[16];
	Read_eng(key,buf);
	for(a=0;a<16;a++)
		for(o=1;o<=ysize;o++)
			for(b=0;b<8;b++)
				for(k=1;k<=xsize;k++)
					if((buf[a]>>7-b)&1)
				   //		video_buffer[(((cy+o+a*ysize)<<8)+((cy+o+a*ysize)<<6))+cx+xsize*b+k]=fcolor;
				   Plot(cx+b*xsize+k,cy+o+a*ysize,fcolor);
}

void Put_String(int x,int y,int x0,int y0,int color,char *str)
{
    int i;
    for(i=0;str[i]!='\0';i++)
    {
		Put_eng_Size(x+(i*10*x0),y,x0,y0,str[i],color);
    }
}
