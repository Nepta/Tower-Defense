#ifndef __shoot_H__
#define __shoot_H__
#include "enemy.h"
#include "tower.h"
/**
 * A shooting manager connects towers and enemys to know if a tower can shoot an enemy
 */
typedef struct{
	EnemySwag *enemys;
	TowerManager *towerManager;
}ShootManager;

/**
 * Check if an enemy can be shoot
 * \param enemy the enemy to shoot
 * \param tower the tower which will may shoot the enemy
 * \return 1 if the enemy can be shoot
 */
int isEnemyInRange(Enemy *enemy, Tower *tower);

#endif /* __shoot_H__ */

