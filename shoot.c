#include "shoot.h"

int isEnemyInRange(Enemy *enemy, Tower *tower){
	int x = enemy->position.x;
	int y = enemy->position.y;
	int i = tower->towerBox.x;
	int j = tower->towerBox.y;
	int r = tower->range;
	int towerToEnemyDistance = ((x-i)*(x-i)) + ((y-j)*(y-j));
	return towerToEnemyDistance <= r*r ? 1 : 0;
}


