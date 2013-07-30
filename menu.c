#include "menu.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Menu* createMenu(){
	Menu *menu = malloc(sizeof (Menu));
	menu->background = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 600, 32,0,0,0,0);
	menu->items[0] = createMenuItem("resources/tower.png", 99, 99);
	menu->isUpdated = 1;
	drawMenu(menu);
 return menu;
}

MenuItem* createMenuItem(char* sprite, int x, int y){
	MenuItem *item = malloc(sizeof (MenuItem));
	item->sprite = IMG_Load(sprite);
	if(item->sprite == NULL) {
		printf("failed to load the item %s sprite\n", sprite);
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	SDL_Rect position = {x,y,0,0};
	item->position = position;
 return item;
}

void updateMenu(Menu *menu){
	menu->isUpdated = 1;
}

void drawMenu(Menu *menu){
	for(int i=0; i<1; i++){
		drawMenuItem(menu->items[i], menu->background);
	}
}

void drawMenuItem(MenuItem *item, SDL_Surface *surfaceToDraw){
	SDL_BlitSurface(item->sprite, NULL, surfaceToDraw, &item->position);
}

