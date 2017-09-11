#include"svga.h"
void SET_SVGA_MODE(int mode)
{
	union REGS r;
	r.x.ax=0x4f02;
	r.x.bx=mode;
	int86(0x10,&r,&r);
}

void selectpage(register char page) /*换页函数*/
{
	union REGS r;
	r.x.ax=0x4f05;
	r.x.bx=0;
	r.x.dx=page; /*选择页面*/
	int86(0x10,&r,&r);
}

void readbmp(int x,int y,char *filename)    //将BMP放入逻辑显存
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

		buffer=(short *)malloc(Width*2);       //分配一行图像的存储空间

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

		for(i=Height-1;i>=0;i--)
	{
			fread(buffer,Width*2,1,fp);   //读入一行图像信息到内存

			for(j=0;j<Width;j++)
			{
					position=((i+y)*(long)1024+j+x);
					newpage=position*2/65536;
					if(newpage!=oldpage)            //调用换页函数
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
void HZ24_Show(int x,int y,char *h,unsigned short int color,unsigned char *p,char *type)      /*单个汉字显示*/
{
	FILE *hzk;
	int i,j;
	char a[72],mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	unsigned char qh,wh,np,op;
	unsigned long pos,offset;
	short far *video_buffer=(short far *)0xA0000000L;
	qh=h[0]-0xa0;
	wh=h[1]-0xa0;
	offset=(94*(qh-1)+(wh-1))*72L;  /*偏移量确定*/
	op=*p;
	if((hzk=fopen(type,"rb"))==NULL)
	{
		printf("ERROE!The HZ_lib cannot be init!\n");
		getch();
		exit(1);
	}
	fseek(hzk,offset,SEEK_SET);
	fread(a,72,1,hzk);
	for(i=0;i<24;i++)/*显示汉字*/
	{
		for(j=0;j<24;j++)
		{
			pos=(x+j+(y+i)*800l);
			np=pos/32768;
			if(op!=np)
			{
				selectpage(np);
				op=np;
			}
			if((mask[j%8]&a[i*3+j/8])!=NULL) video_buffer[pos%32768]=color;
		}
	}
	fclose(hzk);
	return;
}
