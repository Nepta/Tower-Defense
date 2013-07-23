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

#include "map.h"
#include "enemy.h"

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_ASYNCBLIT | SDL_DOUBLEBUF);

	SDL_Surface *background = loadMap("resources/forest.png");
	Enemy *cat = newEnemy("resources/white_transparent_cat.png");

	int time = 100;
	while(time-- > 0){
		SDL_BlitSurface(background, NULL, screen, NULL);
		SDL_BlitSurface(cat->spriteSheet, &cat->animation[LEFT]->animation, screen, NULL);
		SDL_Flip(screen);
	}
 return 0;
}

/**
 * \brief Create a map.
 *
 * \param mapName The Path of map's background.
 * \return The array on the map, in order to use it.
 */
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

