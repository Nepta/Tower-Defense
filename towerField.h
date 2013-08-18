#ifndef __towerField_H__
#define __towerField_H__

#include <SDL/SDL.h>
#include "interfaces.h"

/**
 * TODO: doc
 */
struct fieldInterface{
	SDL_Surface *background;
};

/**
 * create an interface to hang up event in the main field
 * \param mapName path to the field image
 * \return interface to the field
 */
FieldInterface* createFieldInterface(char* mapName);

/**
 * callback function which is called when we click on the main field
 * \param field structure defining the field
 * \param x x position of mouse in the field
 * \param y y position of mouse in the field
 */
void clickOnScreen(Interface* interfaces, int x,int y);

#endif /* __towerField_H__ */

