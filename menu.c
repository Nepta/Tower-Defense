#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jsonParser.h"

Menu* createMenu(){
	Menu *menu = malloc(sizeof (Menu));
	menu->background = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 600, 24,0,0,0,0);
	menu->blackTile = SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 24,0,0,0,0);
	menu->currentItem = NULL;
	menu->text = initTextArea();
	menu->isUpdated = 1;

	FILE *data;
	data = fopen("resources/data.js", "r");
	char* jsonFile = fileToString(data);
	fclose(data);
	TokenIterator *it = parseJson(jsonFile);
	getNextStringValue(it,jsonFile,"towers");
	for(int i=0; i<ItemNumbers; i++){
		getNextStringValue(it,jsonFile,"location");
		char* location = extractnToken(it->tokens[it->currentPosition], jsonFile, MaxDescriptionLenght);
		getNextStringValue(it,jsonFile,"description");
		char* description = extractnToken(it->tokens[it->currentPosition], jsonFile, MaxDescriptionLenght);
		menu->items[i] = createMenuItem(location, description, i*32, 99);
		getNextObject(it);
	}
	drawMenu(menu);
 return menu;
}

MenuItem* createMenuItem(const char* sprite, const char* description, int x, int y){
	MenuItem *item = malloc(sizeof (MenuItem));
	item->sprite = IMG_Load(sprite);
	if(item->sprite == NULL) {
		printf("failed to load the item %s sprite\n", sprite);
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	item->description = description;
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
	if(menu->currentItem){
		SDL_Rect currentItemPosition = {75,50,0,0};
		SDL_Rect currentTextPosition = {5,50,0,0};
		SDL_BlitSurface(menu->blackTile, NULL, menu->background, &currentItemPosition);
		SDL_BlitSurface(menu->currentItem->sprite, NULL, menu->background, &currentItemPosition);
		drawMenuText(menu->text, menu->currentItem);
		SDL_BlitSurface(menu->text->sprite, NULL, menu->background, &currentTextPosition);
	}
/*	SDL_Surface *renderText = TTF_RenderUTF8_Solid(font, text, blackColor);*/
}

void drawMenuItem(MenuItem *item, SDL_Surface *surfaceToDraw){
	SDL_BlitSurface(item->sprite, NULL, surfaceToDraw, &item->position);
}

MenuText* initTextArea(){
	SDL_Color white = {255,255,255,255}; 
	TTF_Font *font_ = TTF_OpenFont("resources/zombieCat.ttf", 8);
	if(!font_){
		printf("font error: %s\n",TTF_GetError());
		exit(-1);
	}
/*	TTF_Font *policeMini = TTF_OpenFont("resources/zombieCat.ttf", 14);*/
	TTF_SetFontStyle(font_,TTF_STYLE_BOLD);
/*	TTF_SetFontStyle(policeMini,TTF_STYLE_BOLD);*/
	
	MenuText *text = malloc(sizeof (MenuText));
	text->color = white;
	text->font = font_;
	text->sprite = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 32, 24,0,0,0,0);
 return text;
}

void drawMenuText(MenuText *text, MenuItem *currentItem){
	text->sprite = TTF_RenderUTF8_Solid(
		text->font,
		currentItem->description,
		text->color
	);
}
