#include "towerField.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

FieldInterface* createFieldInterface(char* mapName){
	FieldInterface *field = malloc(sizeof (FieldInterface));
	field->background = IMG_Load(mapName);
	if(field->background == NULL) {
		printf("failed to load the background map\n");
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
 return field;
}

void clickOnScreen(Interface *interfaces, int x,int y){
	FieldInterface *field = interfaces->field;
	printf("(%d,%d)\n",x,y);
}
