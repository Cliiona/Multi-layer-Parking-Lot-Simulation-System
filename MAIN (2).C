#include"main.h"
void main()
{
 Pp state;
 Rec list=create_node();
 //unsigned u=coreleft();
 randomize();
 srand((int)time(NULL));//�������
 init_pp(&state,list);
 rewrite_file(list,TODAY);
 Set_Video_Mode(SVGA);
 welcome();
 yes(&state);
}
