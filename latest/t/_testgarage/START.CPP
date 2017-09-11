#include"start.h"
////////////原创开始动画////////////

void begin()
{  	
    mou oldmouse,curmouse;
	oldmouse.x=0;oldmouse.y=0;oldmouse.key=0;
	curmouse.x=0;curmouse.y=0;curmouse.key=0;
    
	sprite c1,small;
	pcx_picture background_pcx,o1,objects_pcx;
	Set_Video_Mode(VGA256);
	PCX_Load1("C1.pcx",(pcx_picture_ptr)&o1,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&c1,120,-5,0,0,0,0,65,55,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&o1,(sprite_ptr)&c1,0,0,0,65,55);//将屏幕内容复制给小图片
    
    PCX_Load1("mouse.pcx",(pcx_picture_ptr)&objects_pcx,1);//调用图片文件
	Sprite_Init_Size((sprite_ptr)&small,0,0,0,0,0,0,65,55,1);//初始化小图片
	PCX_Grab_Bitmap_Size_Screen((pcx_picture_ptr)&objects_pcx,(sprite_ptr)&small,0,0,0,65,55);//将屏幕内容复制给小图片
    
    
	Fill_Screen(0);
	PCX_Load1("sur.pcx",(pcx_picture_ptr)&background_pcx,1);//背景
	Behind_Sprite_Size((sprite_ptr)&small,65,55);
    Behind_Sprite_Size((sprite_ptr)&c1,65,55);//取图片后内容
    mousecheck();//初始化鼠标
	mousemove();//设置鼠标范围
    small.x=curmouse.x/2;
	small.y=curmouse.y;
	Behind_Sprite_Size((sprite_ptr)&small,65,55);//保存小图片后背景内容
	Draw_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片于鼠标位置*/
		while(!kbhit())
         { 
            if(curmouse.key && curmouse.x>200&& curmouse.x<430 && curmouse.y>177 && curmouse.y<198)
             { 
                     
                  while(1)
                {
		   Erase_Sprite_Size((sprite_ptr)&c1,65,55);
		   if(c1.y<140)c1.y++;
		   Behind_Sprite_Size((sprite_ptr)&c1,65,55);
		   Draw_Sprite_Size((sprite_ptr)&c1,65,55);
			   if(c1.y==138)
                        {
                              
                              while(c1.x<210)
            
                               {   
				  Erase_Sprite_Size((sprite_ptr)&c1,65,55);
                                  c1.x++;
		                  Behind_Sprite_Size((sprite_ptr)&c1,65,55);
				  Draw_Sprite_Size((sprite_ptr)&c1,65,55);
								  delay(10);
                
                               }
                             delay(20);
                             while(c1.x>53)
                              {
              	                  Erase_Sprite_Size((sprite_ptr)&c1,65,55);
                                  c1.x--;
		                  Behind_Sprite_Size((sprite_ptr)&c1,65,55);
				  Draw_Sprite_Size((sprite_ptr)&c1,65,55);
                                  delay(10);
                             }
                           //  Sprite_Delete_Size((sprite_ptr)&c1,1);
                             break;
                        }
					  delay(9);
               }
              PCX_Load_Screen("op.pcx",1);///////////////切换到下一个界面            
              break;
                
           }
       
        else 
       {   
            mouseread(&curmouse);
    	    if(curmouse.x!=oldmouse.x||curmouse.y!=oldmouse.y)//判断是否移动过鼠标
	      {
		    Erase_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片后背景内容
                    small.x=curmouse.x/2;
	            small.y=curmouse.y;
		    Behind_Sprite_Size((sprite_ptr)&small,65,55);//保存小图片后背景内容
	    	    Draw_Sprite_Size((sprite_ptr)&small,65,55);//显示小图片于鼠标位置
	    	    oldmouse.x=curmouse.x;
		    oldmouse.y=curmouse.y;
    	 }
      }
 
    }  
      getch();
      Set_Video_Mode(TEXT_MODE);
}	
