#include "Menu.h"


int main()
{
	Menu* menu = new Menu();
	menu->Initialize();
	delete menu;
	menu = nullptr;
	return 0;
}