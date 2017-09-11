#include"main.h"

void main()
{
  Pp state;
  Rec list;//链表的头结点
  randomize();
  srand((int)time(NULL));//随机种子  
  list=create_node();//分配内存，指针域赋值
  init_pp(&state,list); //初始化车库，每生成一结构，创建一个结点，插入一个结点
  rewrite_file(list,TODAY); //将记录保存today到文件中
 // new_all();
  jiemianstart(&state);
}
