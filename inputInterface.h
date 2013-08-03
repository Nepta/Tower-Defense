#ifndef __inputInterface_H__
#define __inputInterface_H__

#include "menu.h"

extern const int mapWidth;
extern const int menuWidth;

typedef struct{
	Menu *menu;
}Interface;

int pollMouseClick(Interface interfaces);

#endif /* __inputInterface_H__ */

