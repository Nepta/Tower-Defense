#ifndef __enemy_H__
#define __enemy_H__

#include <SDL/SDL.h>
#include "map.h"

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STAY,
	AnimationStateLenght
}AnimationState;

typedef struct enemyAnimation{
	SDL_Rect animation;
	struct enemyAnimation *nextAnimation;
}EnemyAnimation;

typedef struct enemy{
	SDL_Surface *spriteSheet;
	SDL_Rect position;
	AnimationState animationState;
	EnemyAnimation *animation[AnimationStateLenght];
}Enemy;



Enemy *newEnemy(char *enemySprite);
void addEnemyAnimation(Enemy *enemy, SDL_Rect animation, AnimationState state);
AnimationState getState(Position oldPosition, Position newPosition);
void updateEnemy(Enemy *enemy, Map **map);

#endif /* __enemy_H__ */

