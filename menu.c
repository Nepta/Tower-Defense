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
	data = fopen("resources/data.json", "r");
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
		menu->items[i]->values = malloc(sizeof (TowerValueLength)); //for item representing a tower
/*		TowerValue value = Price;*/
		GetNextStringValue("price");
		menu->items[i]->values[Price] = atoi(ExtractToken(8));
/*		value = Range;*/
		GetNextStringValue("range");
		menu->items[i]->values[Range] = atoi(ExtractToken(8));
		getNextObject(it);
	}
	menu->coin = createAnimatedItem("resources/goldCoin.png", 10, 500); //!< \attention magic value
	menu->playerMoney = 100;
	drawMenu(menu);
 return menu;
}

AnimatedItem* createAnimatedItem(const char* spriteSheet, int x, int y){
	AnimatedItem *item = malloc(sizeof (AnimatedItem));
	item->spriteSheet = IMG_Load(spriteSheet);
	if(item->spriteSheet == NULL) {
		printf("failed to load the animated item %s sprite\n", spriteSheet);
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	item->animation[0] = NULL;
	SDL_Rect sprite = {0,0,32,32}; //!< \attention magic number
	for(int i=0; i<9; i++){
		addEnemyAnimation((Enemy*)item,sprite,0);
		sprite.x += sprite.w;
	}
	SDL_Rect position = {x,y,32,32}; //!< \attention magic number
	item->position = position;
 return item;
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
	SDL_Rect position = {x,y,32,32}; //!< \attention magic number
	item->position = position;
 return item;
}

void updateMenu(Menu *menu){
	menu->isUpdated = 1;
}

void clickOnMenu(Interface *interfaces, int x, int y){
	Menu *menu = interfaces->menu;
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
	drawAnimatedItem(menu, menu->coin);
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

void drawAnimatedItem(Menu *menu, AnimatedItem *item){
	SDL_Rect itemPosition = {item->position.x,item->position.y,item->position.w,item->position.h};
	for(int i=0;i<8;i++){
		SDL_BlitSurface(menu->blackTile, NULL, menu->background, &itemPosition);
		itemPosition.x += itemPosition.w;
	}
	SDL_BlitSurface(item->spriteSheet, &item->animation[0]->animation, menu->background, &item->position);
	item->animation[0] = item->animation[0]->nextAnimation;
	char* currentMoney = malloc(8);
	snprintf(currentMoney,8,"%d",menu->playerMoney);
	SDL_Surface *money = TTF_RenderUTF8_Solid(
		menu->text->font,
		currentMoney,
		menu->text->color
	);
	SDL_Rect textPosition = {item->position.x,item->position.y,item->position.w,item->position.h};
	textPosition.x += textPosition.w + 9;
	textPosition.y += textPosition.h/2;
	SDL_BlitSurface(money, NULL, menu->background, &textPosition);
}

