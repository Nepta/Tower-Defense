#ifndef __menu_H__
#define __menu_H__

#include <SDL/SDL.h>

typedef struct{
	SDL_Surface *sprite;
	SDL_Rect position;
}MenuItem;

typedef struct{
	SDL_Surface *background;
	MenuItem currentItem;
	int isUpdated;
	MenuItem *items[1];
}Menu;

Menu* createMenu();
MenuItem* createMenuItem(char* sprite, int x, int y);
void updateMenu(Menu *menu);
void drawMenu(Menu *menu);
void drawMenuItem(MenuItem *item, SDL_Surface *surfaceToDraw);

#endif /* __menu_H__ */

