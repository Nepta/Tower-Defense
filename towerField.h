#ifndef __towerField_H__
#define __towerField_H__

/**
 * TODO: doc
 */
typedef struct{
//	SDL_Surface *background;
}FieldInterface;

/**
 * create an interface to hang up event in the main field
 * \return interface to the field
 */
FieldInterface* createFieldInterface();

/**
 * callback function which is called when we click on the main field
 * \param field structure defining the field
 * \param x x position of mouse in the field
 * \param y y position of mouse in the field
 */
void clickOnScreen(FieldInterface* field, int x,int y);

#endif /* __towerField_H__ */

