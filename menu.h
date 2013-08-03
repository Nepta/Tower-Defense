#ifndef __menu_H__
#define __menu_H__

#include <SDL/SDL.h>

#define ItemNumbers 2

typedef struct{
	SDL_Surface *sprite;
	SDL_Rect position;
}MenuItem;

typedef struct{
	SDL_Surface *background;
	SDL_Surface *blackTile;
	MenuItem *currentItem;
	int isUpdated;
	MenuItem *items[ItemNumbers];
}Menu;

Menu* createMenu();
MenuItem* createMenuItem(char* sprite, int x, int y);
void updateMenu(Menu *menu);
void drawMenu(Menu *menu);
void drawMenuItem(MenuItem *item, SDL_Surface *surfaceToDraw);
void clickOnMenu(Menu *menu, int x, int y);

#endif /* __menu_H__ */

