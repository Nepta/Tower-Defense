#include "menu.h"

Menu* createMenu(){
	Menu *menu = malloc(sizeof (Menu));
	menu->currentDescription = Tower1;
	menu->isUpdated = 1;
 return menu;
}

void updateMenu(Menu *menu){
	menu->isUpdated = 1;
}

