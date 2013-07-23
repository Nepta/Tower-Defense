#ifndef __enemy_H__
#define __enemy_H__

#include <SDL/SDL.h>
#include "animation.h"

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STAY,
	AnimationStateLenght
}AnimationState;

typedef struct enemy{
	SDL_Surface *spriteSheet;
	EnemyAnimation *animation[AnimationStateLenght];
}Enemy;

Enemy *newEnemy(char *enemySprite);

#endif /* __enemy_H__ */

