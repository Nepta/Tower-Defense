#include "enemy.h"
#include <stdlib.h>
#include <SDL/SDL_image.h>

Enemy *newEnemy(char *enemySprite){
	Enemy *enemy = malloc(sizeof (Enemy));
	SDL_Surface *spriteSheet = IMG_Load(enemySprite);
	if(spriteSheet == NULL) {
		printf("failed to load the enemy sprite sheet\n");
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	enemy->spriteSheet = spriteSheet;
	for(int i=0; i<AnimationStateLenght; i++){
		enemy->animation[i] = malloc(sizeof (EnemyAnimation));
	}//24 x 32
	enemy->animation[DOWN] = malloc(sizeof (EnemyAnimation));
	enemy->animation[DOWN]->nextAnimation = enemy->animation[DOWN];
	SDL_Rect sprite = {0,64,24,32};
	enemy->animation[DOWN]->animation = sprite;
 return enemy;
}
