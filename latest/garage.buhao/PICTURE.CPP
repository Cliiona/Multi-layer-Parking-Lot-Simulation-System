#include"picture.h"


void Set_Palette_Register(int index,RGB_color_ptr color)
{
outp(PALETTE_MASK,0xff);
outp(PALETTE_REGISTER_WR,index);
outp(PALETTE_DATA,color->red);
outp(PALETTE_DATA,color->green);
outp(PALETTE_DATA,color->blue);
}


void PCX_Init(pcx_picture_ptr image)
//申请图像大小的内存空间,pcx
{
unsigned int a=(unsigned int)(SCREEN_WIDTH * SCREEN_HEIGHT + 1);
if((image->buffer = (char *)malloc(a))==NULL)
{
   printf("\ncouldn't allocate screen buffer");
 exit(1);
 }
}


void PCX_Delete(pcx_picture_ptr image)
{
free(image->buffer);
}


void PCX_Load(char *filename, pcx_picture_ptr image,int enable_palette)
//将文件中的图像压缩数据解压到内存,pcx
{

FILE *fp;
int num_bytes,index;
unsigned int count;
unsigned char data;
char far *temp_buffer;

fp = fopen(filename,"rb");

temp_buffer = (char far *)image;

for (index=0; index<128; index++)
    {
    temp_buffer[index] = getc(fp);
    } 

count=0;


while(count<=(unsigned int)SCREEN_WIDTH * SCREEN_HEIGHT)
	 {

	 data = getc(fp);


     if (data>=192 && data<=255)
	{

	num_bytes = data-192;

	data  = getc(fp);

	while(num_bytes-->0)
	     {
	     image->buffer[count++] = data;

	     }
	 }
     else
	{

	image->buffer[count++] = data;

	}

     }

fseek(fp,-768L,SEEK_END);


for (index=0; index<256; index++)
    {

    image->palette[index].red   = (getc(fp) >> 2);


    image->palette[index].green = (getc(fp) >> 2);


    image->palette[index].blue  = (getc(fp) >> 2);

    }

fclose(fp);


if (enable_palette)
   {

   for (index=0; index<256; index++)
       {

       Set_Palette_Register(index,(RGB_color_ptr)&image->palette[index]);

       }

   }

}


void PCX_Show_Buffer(pcx_picture_ptr image)
//将内存中的图像显示,pcx
{unsigned char far *video_buffer=(char far *)0xA0000000L;

char far *data;
data=image->buffer;


asm	push ds;
asm	les di,video_buffer;
asm	lds si,data;
asm 	mov cx,SCREEN_HEIGHT*SCREEN_WIDTH/2;
asm 	cld;
asm	rep movsw;
asm	pop ds;

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
    	char buffer[480];
    	unsigned char far *video_buffer=(char far *)0xA0000000L;  //初始化指向VRAM的指针

    	if((fp=fopen(filename,"rb"))==NULL)
    	{
		printf("Cannot install image\n%s",filename);
        	getch();
        	return;
    	}

    	fseek(fp,18,SEEK_SET);
    	fread(&Width,sizeof(long),1,fp);
    	fread(&Height,sizeof(long),1,fp);

    	buffer=(char *)malloc(Width*2);       //分配一行图像的存储空间

    	if(buffer==NULL)
    	{
        	printf("Malloc error!");
        	getch();
        	return;
    	}

    	fseek(fp,70,SEEK_SET);         
    	oldpage=((Height-1+y)*(long)320+x)*2/65536L;    //初始化页码
    	newpage=oldpage;
    	selectpage(oldpage);

    	for(i=Height-1;i>=0;i--)
   	{
        	fread(buffer,Width*2,1,fp);   //读入一行图像信息到内存

        	for(j=0;j<Width;j++)
        	{
            		position=((i+y)*(long)320+j+x);
            		newpage=position*2/65536;
            		if(newpage!=oldpage)            //调用换页函数
            		{
                		selectpage(newpage);
                		oldpage=newpage;
            		}
            		*(video_buffer+(i+y)*320+x+j)=buffer[j];      //将内存中的图像信息逐点读入VRAM      
        	}
    	}

    	fclose(fp);
    	free(buffer);
}

