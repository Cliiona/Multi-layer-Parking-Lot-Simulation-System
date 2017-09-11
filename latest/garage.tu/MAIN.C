#include"main.h"

void main()
{
	Set_Video_Mode(VGA256);
	Rectangle(100,100,200,190,WHITE);
	WriteHz16("我",101,101,WHITE);
	hz24_k("华中科技大学",0,0,WHITE);

	getch();
	Set_Video_Mode(TEXT_MODE);

}
