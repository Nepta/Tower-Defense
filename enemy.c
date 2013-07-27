#include "enemy.h"
#include <stdlib.h>
#include <SDL/SDL_image.h>

Enemy *newEnemy(char *enemySprite){
	Enemy *enemy = malloc(sizeof (Enemy));
	enemy->position.w = 0;
	enemy->position.h = 0;
	SDL_Surface *spriteSheet = IMG_Load(enemySprite);
	if(spriteSheet == NULL) {
		printf("failed to load the enemy sprite sheet\n");
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	enemy->spriteSheet = spriteSheet;
	for(int i=0; i<AnimationStateLenght; i++){
		enemy->animation[i] = malloc(sizeof (EnemyAnimation));
	}
	SDL_Rect sprite;
	
	enemy->animation[DOWN] = malloc(sizeof (EnemyAnimation));
	enemy->animation[DOWN]->nextAnimation = enemy->animation[DOWN];
	sprite.x = 0; sprite.y = 64;
	sprite.w = 24; sprite.h = 32;
	enemy->animation[DOWN]->animation = sprite;
 
	enemy->animation[STAY] = malloc(sizeof (EnemyAnimation));
	enemy->animation[STAY]->nextAnimation = enemy->animation[STAY];
	sprite.x = 0; sprite.y = 64;
	sprite.w = 24; sprite.h = 32;
	enemy->animation[STAY]->animation = sprite;
 
	enemy->animation[UP] = malloc(sizeof (EnemyAnimation));
	enemy->animation[UP]->nextAnimation = enemy->animation[UP];
	sprite.x = 0; sprite.y = 0;
	sprite.w = 24; sprite.h = 32;
	enemy->animation[UP]->animation = sprite;
 
	enemy->animation[LEFT] = malloc(sizeof (EnemyAnimation));
	enemy->animation[LEFT]->nextAnimation = enemy->animation[LEFT];
	sprite.x = 0; sprite.y = 98;
	sprite.w = 24; sprite.h = 32;
	enemy->animation[LEFT]->animation = sprite;
 
	enemy->animation[RIGHT] = malloc(sizeof (EnemyAnimation));
	enemy->animation[RIGHT]->nextAnimation = enemy->animation[RIGHT];
	sprite.x = 0; sprite.y = 32;
	sprite.w = 24; sprite.h = 32;
	enemy->animation[RIGHT]->animation = sprite;
 
 return enemy;
}

void addEnemyAnimation(Enemy *enemy, SDL_Rect animation, AnimationState state){
	EnemyAnimation *firstAnimation = enemy->animation[state];
	EnemyAnimation *animationList = enemy->animation[state];
	while(animationList->nextAnimation != firstAnimation){
		animationList = animationList->nextAnimation;
	}
	EnemyAnimation *newAnimation = malloc(sizeof (EnemyAnimation));
	newAnimation->animation = animation;
	newAnimation->nextAnimation = firstAnimation;
	animationList->nextAnimation = newAnimation;
}

void updateEnemy(Enemy *enemy, Map **map){
	Position oldPosition = {cat->position.x, cat->position.y}
	Position newPosition = map[oldPosition.x][oldPosition.y].parent;
	cat->position.x = newPosition.x;
	cat->position.y = newPosition.y;
	AnimationState newState = getState(newPosition, oldPosition);
	cat->animation[newState] = cat->animation[newState]->nextAnimation;
}

AnimationState getState(Position oldPosition, Position newPosition){
	Position delta = {newPosition.x - oldPosition.x, newPosition.y - newPosition.y};
	//{-1,0,1} --> {0,1,2}
	delta.x += 1;
	delta.y += 1;
	
	//normaly, enemy can't go in diagonal
	AnimationState refTab[][] = {
		{STAY, UP, STAY},
		{LEFT, STAY, RIGHT},
		{STAY, DOWN, STAY}
	}
	return refTab[delta.x][delta.y];
}

