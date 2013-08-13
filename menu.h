#ifndef __menu_H__
#define __menu_H__

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define ItemNumbers 2
#define MaxDescriptionLenght 32

typedef struct{
	SDL_Color color;
	TTF_Font *font;
	SDL_Surface *sprite;
}MenuText;

typedef struct{
	SDL_Surface *sprite;
	char description[MaxDescriptionLenght];
	SDL_Rect position;
}MenuItem;

typedef struct{
	SDL_Surface *background;
	SDL_Surface *blackTile;
	MenuItem *currentItem;
	MenuText *text;
	int isUpdated;
	MenuItem *items[ItemNumbers];
}Menu;

Menu* createMenu();
MenuItem* createMenuItem(const char *sprite, int x, int y);
void updateMenu(Menu *menu);
void drawMenu(Menu *menu);
void drawMenuItem(MenuItem *item, SDL_Surface *surfaceToDraw);
void clickOnMenu(Menu *menu, int x, int y);

MenuText* initTextArea();
void drawMenuText(MenuText *text, MenuItem *currentItem);

#endif /* __menu_H__ */

