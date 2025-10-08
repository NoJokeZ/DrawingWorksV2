#include "Menu.h"


int main()
{
	Menu* _menu = new Menu();
	_menu->Initialize();
	delete _menu;
	_menu = nullptr;
	return 0;
}