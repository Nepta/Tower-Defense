#include "shoot.h"
#include <stdio.h>

int isEnemyInRange(Enemy *enemy, Tower *tower){
	int x = enemy->position.x;
	int y = enemy->position.y;
	int i = tower->towerBox.x;
	int j = tower->towerBox.y;
	int r = tower->range;
	int towerToEnemyDistance = ((x-i)*(x-i)) + ((y-j)*(y-j));
	return towerToEnemyDistance <= r*r ? 1 : 0;
}

void shootEnemy(ShootManager *shootManager){
	Tower ***towers = (Tower***)shootManager->towerManager->towers;
	EnemySwag *enemys = shootManager->enemys;
	for(int i=0; i<MaxWidthTower; i++){
		for(int j=0; j<MaxHeightTower; j++){
			if(towers[i][j] != NULL){
				if(enemys->isEmpty != 1){
					for(int k=0; k<enemys->swagSize; k++){
						if(isEnemyInRange(&enemys->enemy[k],towers[i][j])){
							hitEnemy(towers[i][j], &enemys->enemy[k]);
							break; // a tower can hit only one enemy
						}
					}
				}
			}
		}
	}
}

void hitEnemy(Tower *tower, Enemy *enemy){
}

