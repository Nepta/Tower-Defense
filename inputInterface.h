#ifndef __inputInterface_H__
#define __inputInterface_H__

#include "menu.h"

/**
 * Container for interface in the game (menu, hud ...)
 */
typedef struct{
	Menu *menu;	//!< the main menu on the right (for now)
}Interface;

/**
 * get mouse position and give it to an interface
 * \param interfaces container that contain all the interface
 */
int pollMouseClick(Interface interfaces);

#endif /* __inputInterface_H__ */

