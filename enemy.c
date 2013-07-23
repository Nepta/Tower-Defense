#include "enemy.h"

Enemy *newEnemy(char *enemySprite){
	Enemy *enemy = malloc(sizeof Enemy);
	SDL_Surface *spriteSheet = IMG_Load(enemySprite);
	if(spriteSheet == NULL) {
		printf("failed to load the enemy sprite sheet\n");
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	enemy->spriteSheet = spriteSheet;
}
