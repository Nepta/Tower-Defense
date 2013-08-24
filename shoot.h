#ifndef __shoot_H__
#define __shoot_H__

/**
 * A shooting manager connects towers and enemys to know if a tower can shoot an enemy
 */
typedef struct{
	EnemySwag *enemys;
	TowerManager *towerManager;
}ShootManager;

#endif /* __shoot_H__ */

