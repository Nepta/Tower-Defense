#ifndef __enemy_H__
#define __enemy_H__

#include <SDL/SDL.h>

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STAY,
	AnimationStateLenght
}AnimationState;

typedef struct enemyAnimation{
	SDL_Rect *animation;
	struct enemyAnimation *nextAnimation;
}EnemyAnimation;

typedef struct enemy{
	SDL_Surface *spriteSheet;
	EnemyAnimation animation[AnimationStateLenght];
}Enemy;

#endif /* __enemy_H__ */

