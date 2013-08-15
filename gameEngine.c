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
#include "inputInterface.h"

const int mapWidth = 800;
const int mapHeight = 600;
const int menuWidth = 150;

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Surface *screen = SDL_SetVideoMode(mapWidth + menuWidth, mapHeight, 24, SDL_HWSURFACE | SDL_ASYNCBLIT | SDL_DOUBLEBUF);

	SDL_Surface *background = loadMap("resources/forest.png");
	Enemy *cat = newEnemy("resources/white_transparent_cat.png");
	cat->position.x = 400; cat->position.y = 300;
	initEnemyAnimation(cat);
	
	Position end = {700, 500};
	Position start = {cat->position.x, cat->position.y};
	Map **map = initMap();
	searchPath(map, start, end);
	
	SDL_Rect endRect = {end.x,end.y,9,9};
	Menu *menu = createMenu();
	SDL_Rect menuPosition = {mapWidth,0,mapHeight,menuWidth};
	int time = 777/2;
	int gameEnd = 0;
	Interface interfaces = {menu};
	while(time-- > 0 && gameEnd != 1){
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

Map** initMap(){
	Map *map_ = malloc(800 * 600 * sizeof (Map));
	Map **map = malloc(800 * sizeof (Map*));
	
	for(int i=0; i<800; i++){
		map[i] = &map_[i*600];
		for(int j=0; j< 600; j++){
			map[i][j].x = i;
			map[i][j].y = j;
			map[i][j].parent.x = i;
			map[i][j].parent.y = j;
			if(i == 0 || j == 0 || i == 799 || j == 599){
				map[i][j].hasTower = 1;
			}else{
				map[i][j].hasTower = 0;
			}
		}
	}
 return map;
}

