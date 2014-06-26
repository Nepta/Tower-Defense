#include "towerField.h"
#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

FieldInterface* createFieldInterface(char* mapName){
	FieldInterface *field = malloc(sizeof (FieldInterface));
	field->background = IMG_Load(mapName);
	field->originalBackground = IMG_Load(mapName);
	if(field->background == NULL || field->originalBackground == NULL){
		printf("failed to load the background map\n");
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	field->hasChanged = 0;
 return field;
}

void clickOnScreen(Interface *interfaces, int x,int y){
	FieldInterface *field = interfaces->field;
	Menu *menu = interfaces->menu;
	if(menu->currentItem != NULL){
		field->hasChanged = placeTower(interfaces, x, y);
	}
}
