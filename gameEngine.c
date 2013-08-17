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
	Position start2 = {100, 100};
	Position start = {25, 555};
	Map **map = initMap();
	searchPath(map, start, end);
	searchPath(map, start2, end);
	
	for(int i=0; i<11; i++){		//for the black swag
		start2.x += 4;
		start2.y += 4;
		searchPath(map,start2,end);
	}
	start2.x = 100;
	start2.y = 100;
	SDL_Surface *background = loadMap("resources/forest.png");
	Enemy *whiteCat = newEnemy("resources/white_transparent_cat.png");
	Enemy *blackCat = newEnemy("resources/black_transparent_cat.png");
	whiteCat->position.x = start.x; whiteCat->position.y = start.y;
	blackCat->position.x = start2.x; blackCat->position.y = start2.y;
	initEnemyAnimation(whiteCat);
	initEnemyAnimation(blackCat);

	EnemySwag *blackSwag = createEnemySwag(blackCat,10);
	for(int i=0; i<10; i++){
		initEnemyAnimation(&blackSwag->enemy[i]);
	}
	
	SDL_Rect endRect = {end.x,end.y,9,9};
	Menu *menu = createMenu();
	SDL_Rect menuPosition = {mapWidth,0,mapHeight,menuWidth};
	
	FieldInterface *field = createFieldInterface();	
	Interface interfaces = {menu,field};
	int gameEnd = 0;
	while(gameEnd != 1){
		gameEnd = pollMouseClick(interfaces);
		SDL_BlitSurface(background, NULL, screen, NULL);
		SDL_BlitSurface(whiteCat->spriteSheet, &whiteCat->animation[whiteCat->animationState]->animation, screen, &whiteCat->position);
		SDL_BlitSurface(blackCat->spriteSheet, &blackCat->animation[blackCat->animationState]->animation, screen, &blackCat->position);
		for(int i=0; i<10; i++){
			SDL_BlitSurface(blackSwag->enemy[i].spriteSheet, &blackSwag->enemy[i].animation[blackSwag->enemy[i].animationState]->animation, screen, &blackSwag->enemy[i].position);
		}
		SDL_FillRect(screen, &endRect, SDL_MapRGB(screen->format, 100, 100, 255));
		drawMenu(menu);
		SDL_BlitSurface(menu->background, NULL, screen, &menuPosition);
		SDL_Flip(screen);
		updateEnemy(whiteCat, map);
		updateEnemy(blackCat, map);
		for(int i=0; i<10; i++){
			updateEnemy(&blackSwag->enemy[i], map);
		}
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



