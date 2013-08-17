/*
 Authors: Nepta
 Copyright © 2013
 You should have received a copy of the
 GNU General Public License along with this program.
 If not, see  <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "pathFinding.h"
#include "enemy.h"
#include "map.h"
#include "gameEngine.h"
#include "menu.h"
#include "towerField.h"
#include "inputInterface.h"


const int mapWidth = 800;
const int mapHeight = 600;
const int menuWidth = 150;

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Surface *screen = SDL_SetVideoMode(mapWidth + menuWidth, mapHeight, 24, SDL_HWSURFACE | SDL_ASYNCBLIT | SDL_DOUBLEBUF);

	Position end = {700, 500};
	Position start = {100, 100};
	Map **map = initMap();
	searchPath(map, start, end);

	SDL_Surface *background = loadMap("resources/forest.png");
	Enemy *cat = newEnemy("resources/white_transparent_cat.png");
	cat->position.x = start.x; cat->position.y = start.y;
	initEnemyAnimation(cat);
	
	SDL_Rect endRect = {end.x,end.y,9,9};
	Menu *menu = createMenu();
	SDL_Rect menuPosition = {mapWidth,0,mapHeight,menuWidth};
	
	FieldInterface *field = createFieldInterface();	
	Interface interfaces = {menu,field};
	int gameEnd = 0;
	while(gameEnd != 1){
		gameEnd = pollMouseClick(interfaces);
		SDL_BlitSurface(background, NULL, screen, NULL);
		SDL_BlitSurface(cat->spriteSheet, &cat->animation[cat->animationState]->animation, screen, &cat->position);
		SDL_FillRect(screen, &endRect, SDL_MapRGB(screen->format, 100, 100, 255));
		drawMenu(menu);
		SDL_BlitSurface(menu->background, NULL, screen, &menuPosition);
		SDL_Flip(screen);
		updateEnemy(cat, map);
	}
 return 0;
}


SDL_Surface* loadMap(char* mapName){
	SDL_Surface *background;
	background = IMG_Load(mapName);
	if(background == NULL) {
		printf("failed to load the background map\n");
		printf("IMG_Load: %s\n", IMG_GetError());
		exit(-1);
	}
 return background;
}

void initEnemyAnimation(Enemy *enemy){
	SDL_Rect sprite;
	sprite.w = 24; sprite.h = 32;

	sprite.x = 24; sprite.y = 0;
	addEnemyAnimation(enemy, sprite, UP);
	sprite.x = 48; sprite.y = 0;
	addEnemyAnimation(enemy, sprite, UP);
	
	sprite.x = 24; sprite.y = 32;
	addEnemyAnimation(enemy, sprite, RIGHT);
	sprite.x = 48; sprite.y = 32;
	addEnemyAnimation(enemy, sprite, RIGHT);
	
	sprite.x = 24; sprite.y = 64;
	addEnemyAnimation(enemy, sprite, DOWN);
	sprite.x = 48; sprite.y = 64;
	addEnemyAnimation(enemy, sprite, DOWN);
	
	sprite.x = 24; sprite.y = 96;
	addEnemyAnimation(enemy, sprite, LEFT);
	sprite.x = 48; sprite.y = 96;
	addEnemyAnimation(enemy, sprite, LEFT);

	sprite.x = 24; sprite.y = 64;
	addEnemyAnimation(enemy, sprite, STAY);
	sprite.x = 48; sprite.y = 64;
	addEnemyAnimation(enemy, sprite, STAY);
}


