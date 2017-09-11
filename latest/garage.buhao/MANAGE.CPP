#include "manage.h"



 
/* ***********车位使用历史界面**********/

void jiemian_manage_history()
{
   mou oldmouse,curmouse;
   back_mouse(history);	  //1=search
   
   mouseread(&curmouse);//取鼠标位置
      
    if(curmouse.x>20 && curmouse.x<250 && curmouse.y>66 && curmouse.y<80 && curmouse.key)//判断范围
    {
        Set_Video_Mode(TEXT_MODE); 
	  //  process();
	}

}

/* ***********车位使现况 界面**********/

void jiemian_manage_current()
{   
    //mou oldmouse,curmouse;
    back_mouse(current);
    //mouseread(&curmouse);//取鼠标位置
    /*  
    if(curmouse.x>20 && curmouse.x<250 && curmouse.y>66 && curmouse.y<80 && curmouse.key)//判断范围
    {
        Set_Video_Mode(TEXT_MODE); 
        jiemian_manage_history();
    
    }
    */

}


