#include "menu.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Menu* createMenu(){
	Menu *menu = malloc(sizeof (Menu));
	menu->background = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 600, 24,0,0,0,0);
	menu->blackTile = SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 24,0,0,0,0);
	menu->items[0] = createMenuItem("resources/tower.png", 0, 99);
	menu->items[1] = createMenuItem("resources/candy_cane.png", 32, 99); 
	menu->currentItem = NULL;
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

void clickOnMenu(Menu *menu, int x, int y){
	for(int i=0; i<ItemNumbers; i++){
		int xItem = menu->items[i]->position.x;
		if(xItem <= x && x <= xItem+32){
			int yItem = menu->items[i]->position.y;
			if(yItem <= y && y <= yItem+32){
				menu->currentItem = menu->items[i];
			}
		}
	}
}

void drawMenu(Menu *menu){
	for(int i=0; i<ItemNumbers; i++){
		drawMenuItem(menu->items[i], menu->background);
	}
	SDL_Rect currentItemPosition = {75,50,0,0};
	if(menu->currentItem){
		SDL_BlitSurface(menu->blackTile, NULL, menu->background, &currentItemPosition);
		SDL_BlitSurface(menu->currentItem->sprite, NULL, menu->background, &currentItemPosition);
	}
}

void drawMenuItem(MenuItem *item, SDL_Surface *surfaceToDraw){
	SDL_BlitSurface(item->sprite, NULL, surfaceToDraw, &item->position);
}

