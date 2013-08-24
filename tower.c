#include "tower.h"
#include "menu.h"
#include "towerField.h"
#include <SDL/SDL.h>
#include <stdlib.h>
  
extern int mapWidth;
extern int mapHeight;
extern int playerMoney;
Tower* newTower(SDL_Surface *sprite, SDL_Rect towerBox){
	Tower *tower = malloc(sizeof (Tower));
	tower->sprite = sprite;
	tower->towerBox.x = towerBox.x - towerBox.w/2;
	tower->towerBox.y = towerBox.y - towerBox.h/2;
	tower->towerBox.w = towerBox.w;
	tower->towerBox.h = towerBox.h;
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

int placeTower(Interface *interfaces, int x, int y){
	MenuItem *currentItem = interfaces->menu->currentItem;
	if(currentItem == NULL){ //there aren't any tower selected
		return 0;
	}
	if(currentItem->value > playerMoney){
		return 0;
	}
	playerMoney -= currentItem->value;
	TowerManager *manager = interfaces->field->towerManager;
	Position towerZone = getTowerZone(x,y);
	SDL_Rect newTowerBox = {x, y, 32, 32};
	if(manager->towers[towerZone.x][towerZone.y] == NULL){ //there aren't any tower in the zone
		//check surrounding area of tower
		int i[] = {0,1,0,-1,1,1,-1,-1};
		int j[] = {1,0,-1,0,1,-1,-1,1};
		int haveEnoughSpace = 1;
		for(int k=0; k<8 && haveEnoughSpace; k++){
			//if there are a tower we check if they won't overlap
			Tower *nearTower = manager->towers[towerZone.x + i[k]][towerZone.y + j[k]];
			if(nearTower != NULL){
				if(isOverlapping(nearTower->towerBox, newTowerBox)){
					haveEnoughSpace = 0;
				}
			}
		}
		if(haveEnoughSpace){
			SDL_Surface *currentSprite = currentItem->sprite;
			Tower *tower = newTower(currentSprite, newTowerBox);
			manager->towers[towerZone.x][towerZone.y] = tower;
			SDL_Rect towerBox = tower->towerBox;
			for(int i=-32; i<towerBox.w+32; i++){
				for(int j=-32; j<towerBox.h+32; j++){
					manager->workPlace[towerBox.x + i][towerBox.y + j].hasTower = 1;
				}
			}
			return 1;
		}
	}
 return 0;
}

int isOverlapping(SDL_Rect nearTower, SDL_Rect newTower){
	int distanceX = abs(nearTower.x + nearTower.w/2 - newTower.x);
	int distanceY = abs(nearTower.y + nearTower.h/2 - newTower.y);
	int xOverlap = distanceX < nearTower.w/2 + newTower.w/2 ? 1 : 0;
	int yOverlap = distanceY < nearTower.h/2 + newTower.h/2 ? 1 : 0;
 return xOverlap && yOverlap;
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

