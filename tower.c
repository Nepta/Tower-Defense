#include "tower.h"
#include "menu.h"
#include "towerField.h"
#include <SDL/SDL.h>
#include <stdlib.h>

extern int mapWidth;
extern int mapHeight;

Tower* newTower(SDL_Surface *sprite, int x, int y){
	Tower *tower = malloc(sizeof (Tower));
	tower->sprite = sprite;
	tower->towerBox.x = x;
	tower->towerBox.y = y;
	tower->towerBox.w = 32;
	tower->towerBox.h = 32;
 return tower;
}

TowerManager* newTowerManager(Map **map){
	TowerManager *towerManager = malloc(sizeof (TowerManager));
	towerManager->workPlace = map;
	for(int i=0; i<MaxWidthTower; i++){
		for(int j=0; j<MaxHeightTower; j++){
			towerManager->towers[i][j] = NULL;
		}		
	}
 return towerManager;
}

Position getTowerZone(int x, int y){
	Position towerZone = {x/32, y/32};
 return towerZone;
}

void placeTower(Interface *interfaces, int x, int y){
	MenuItem *currentItem = interfaces->menu->currentItem;
	if(currentItem == NULL){ //there aren't any tower selected
		return;
	}
	TowerManager *manager = interfaces->field->towerManager;
	Position towerZone = getTowerZone(x,y);
	SDL_Rect newTowerBox = {towerZone.x, towerZone.y, 32, 32};
	if(manager->towers[towerZone.x][towerZone.y] == NULL){ //there aren't any tower in the zone
		//check surrounding area of tower
		int i[] = {0,1,0,-1};
		int j[] = {1,0,-1,0};
		int haveEnoughSpace = 1;
		for(int k=0; k<4 && haveEnoughSpace; k++){
			//if there are a tower we check if they won't overlap
			Tower *nearTower = manager->towers[i[k]][j[k]];
			if(nearTower != NULL){
				if(isOverlapping(newTowerBox, nearTower->towerBox)){
					haveEnoughSpace = 0;
					break;
				}
			}
		}
		if(haveEnoughSpace){
			SDL_Surface *currentSprite = currentItem->sprite;
			Tower *tower = newTower(currentSprite, x - newTowerBox.w, y - newTowerBox.h);
			manager->towers[towerZone.x][towerZone.y] = tower;
		}
	}
}

int isOverlapping(SDL_Rect rect1, SDL_Rect rect2){
	int xOverlap = rect1.x - rect2.x < rect1.w ? 1 : 0;
	int yOverlap = rect1.y - rect2.y < rect1.h ? 1 : 0;
 return xOverlap || yOverlap;
}

void updateTower(FieldInterface *field){
	TowerManager *towerManager = field->towerManager;
	for(int i=0; i<MaxWidthTower; i++){
		for(int j=0; j<MaxHeightTower; j++){
			Tower *tower = towerManager->towers[i][j];
			if(tower != NULL){
				SDL_Surface *background = field->background;
				SDL_BlitSurface(tower->sprite, NULL, background, &tower->towerBox);
			}
		}		
	}
}

