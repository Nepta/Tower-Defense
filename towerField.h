#ifndef __towerField_H__
#define __towerField_H__

/**
 * TODO: doc
 */
typedef struct{
//	SDL_Surface *background;
}FieldInterface;

FieldInterface* createFieldInterface();
void clickOnScreen(FieldInterface*, int x,int y);

#endif /* __towerField_H__ */

