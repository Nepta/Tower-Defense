#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <string.h> //memcpy
#include "jsonParser.h"
#include "enemy.h"

Enemy *newEnemy(char *enemyName){
	Enemy *enemy = malloc(sizeof (Enemy));
	enemy->position.w = 0;
	enemy->position.h = 0;
	FILE *data;
	data = fopen("resources/enemy.json", "r");
	char* jsonFile = fileToString(data);
	fclose(data);
	TokenIterator *it = parseJson(jsonFile);
	getNextStringValue(it,jsonFile,enemyName);
	GetNextStringValue("location");
	char* enemySprite = ExtractToken(64);
	SDL_Surface *spriteSheet = IMG_Load(enemySprite);
	if(spriteSheet == NULL) {
		printf("failed to load the enemy sprite sheet\n");
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
	enemy->spriteSheet = spriteSheet;
	for(int i=0; i<AnimationStateLenght; i++){
		enemy->animation[i] = NULL;	//enemy->animation is never allocated?
	}
	enemy->animationState = STAY;

	getNextStringValue(it,jsonFile,"height");
	enemy->spriteSize.h = atoi(ExtractToken(8));
	getNextStringValue(it,jsonFile,"width");
	enemy->spriteSize.w = atoi(ExtractToken(8));
	initEnemyAnimation(enemy,it,jsonFile);
 return enemy;
}

void addEnemyAnimation(Enemy *enemy, SDL_Rect animation, AnimationState state){
	EnemyAnimation *firstAnimation = enemy->animation[state];
	if(firstAnimation != NULL){
		EnemyAnimation *animationList = enemy->animation[state];
		while(animationList->nextAnimation != firstAnimation){
			animationList = animationList->nextAnimation;
		}
		EnemyAnimation *newAnimation = malloc(sizeof (EnemyAnimation));
		newAnimation->animation = animation;
		newAnimation->nextAnimation = firstAnimation;
		animationList->nextAnimation = newAnimation;
	}else{
		EnemyAnimation *newAnimation = malloc(sizeof (EnemyAnimation));
		newAnimation->animation = animation;
		newAnimation->nextAnimation = newAnimation;
		enemy->animation[state] = newAnimation;
	}
}

void updateEnemy(Enemy *enemy, Map **map){
	Position oldPosition = {enemy->position.x, enemy->position.y};
	Position newPosition = map[oldPosition.x][oldPosition.y].parent;
	enemy->position.x = newPosition.x;
	enemy->position.y = newPosition.y;
	enemy->animationState = getState(newPosition, oldPosition);
	enemy->animation[enemy->animationState] = enemy->animation[enemy->animationState]->nextAnimation;
}

AnimationState getState(Position oldPosition, Position newPosition){
	Position delta = {newPosition.x - oldPosition.x, newPosition.y - oldPosition.y};
	//{-1,0,1} --> {0,1,2}
	delta.x += 1;
	delta.y += 1;
	
	//normaly, enemy can't go in diagonal
	AnimationState refTab[3][3] = {
		{STAY, RIGHT, STAY},
		{DOWN, STAY, UP},
		{STAY, LEFT, STAY}
	};

	return refTab[delta.x][delta.y];
}

void initEnemyAnimation(Enemy *enemy, TokenIterator *it, char* jsonFile){
	GetNextStringValue("direction");
	SDL_Rect sprite;
	sprite.w = enemy->spriteSize.w;
	sprite.h = enemy->spriteSize.h;
	char loadingDirection = ExtractToken(1);
	char* direction[] = {"UP", "LEFT", "DOWN", "RIGHT", "STAY"}; //see enemy.json for order
	
	GetNextStringValue("animation");
	for(int i=0; i<5; i++){
		GetNextStringValue(direction[i]);
		GetNextStringValue("length");
		int length = atoi(ExtractToken(8));
		GetNextStringValue("x");
		sprite.x = atoi(ExtractToken(8));
		GetNextStringValue("y");
		sprite.y = atoi(ExtractToken(8));
		for(int ii=0; ii<length; ii++){
			addEnemyAnimation(enemy,sprite,i);
			if(loadingDirection == 'l'){ //loading in line
				sprite.y += sprite.h;
			}else{							  //loading in column
				sprite.x += sprite.w;
			}
		}
	}
}


EnemySwag* createEnemySwag(Enemy *enemy, int swagSize){
	EnemySwag *swag = malloc(sizeof (EnemySwag) + swagSize * sizeof (Enemy));
	for(int i=0; i<swagSize; i++){
		swag->enemy[i].spriteSheet = enemy->spriteSheet;
		swag->enemy[i].position.x = enemy->position.x + 4*(i+1);
		swag->enemy[i].position.y = enemy->position.y + 4*(i+1);
		swag->enemy[i].animationState = STAY;
		SDL_Rect sprite;
		swag->enemy[i].animation[DOWN] = malloc(sizeof (EnemyAnimation));
		swag->enemy[i].animation[DOWN]->nextAnimation = swag->enemy[i].animation[DOWN];
		sprite.x = 0; sprite.y = 64;
		sprite.w = 24; sprite.h = 32;
		swag->enemy[i].animation[DOWN]->animation = sprite;
	 
		swag->enemy[i].animation[STAY] = malloc(sizeof (EnemyAnimation));
		swag->enemy[i].animation[STAY]->nextAnimation = swag->enemy[i].animation[STAY];
		sprite.x = 0; sprite.y = 64;
		sprite.w = 24; sprite.h = 32;
		swag->enemy[i].animation[STAY]->animation = sprite;
	 
		swag->enemy[i].animation[UP] = malloc(sizeof (EnemyAnimation));
		swag->enemy[i].animation[UP]->nextAnimation = swag->enemy[i].animation[UP];
		sprite.x = 0; sprite.y = 0;
		sprite.w = 24; sprite.h = 32;
		swag->enemy[i].animation[UP]->animation = sprite;
	 
		swag->enemy[i].animation[LEFT] = malloc(sizeof (EnemyAnimation));
		swag->enemy[i].animation[LEFT]->nextAnimation = swag->enemy[i].animation[LEFT];
		sprite.x = 0; sprite.y = 96;
		sprite.w = 24; sprite.h = 32;
		swag->enemy[i].animation[LEFT]->animation = sprite;
	 
		swag->enemy[i].animation[RIGHT] = malloc(sizeof (EnemyAnimation));
		swag->enemy[i].animation[RIGHT]->nextAnimation = swag->enemy[i].animation[RIGHT];
		sprite.x = 0; sprite.y = 32;
		sprite.w = 24; sprite.h = 32;
		swag->enemy[i].animation[RIGHT]->animation = sprite;
	}
	swag->swagSize = swagSize;
	swag->nextSwag = NULL;
 return swag;
}

void drawEnemy(Enemy *enemy, SDL_Surface *screen){
	SDL_Rect enemyBox = {enemy->position.x, enemy->position.y,0,0};
	enemyBox.x -= enemy->spriteSize.w/2;
	enemyBox.y -= enemy->spriteSize.h/2;
	SDL_BlitSurface(enemy->spriteSheet, &enemy->animation[enemy->animationState]->animation, screen, &enemyBox);
}

